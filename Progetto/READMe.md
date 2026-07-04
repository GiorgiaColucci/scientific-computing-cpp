# Metodo delle Correnti di Maglia - PCS 2026

Progetto di **Programmazione e Calcolo Scientifico** (a.a. 2025–2026).
Questo progetto dimostra come strumenti di teoria dei grafi e algebra lineare possano essere combinati per risolvere problemi reali di analisi circuitale in modo automatico ed efficiente.
Implementazione in C++ del **metodo delle correnti di maglia** per la risoluzione
di circuiti elettrici composti da resistori e generatori ideali di
tensione, sfruttando strumenti di teoria dei grafi e algebra lineare numerica.

## Panoramica

Dato un circuito descritto in una **netlist**, il programma:
1. legge e valida la netlist che descrive il circuito;
2. costruisce il grafo associato;
3. individua le maglie (cicli del grafo) con due algoritmi alternativi:
   **DFS + coalbero** (cicli fondamentali) oppure **De Pina** (cicli minimi);
4. assembla il sistema lineare delle correnti di maglia e lo risolve con Eigen;
5. stampa, per ciascun resistore, la tensione e la corrente.

## Autori

- Catellani Diego
- Colucci Angelamaria
- Colucci Giorgia 

## Requisiti

- **CMake** ≥ 3.20
- **g++** o **clang++** con supporto a C++20
- **Eigen** ≥ 3.3 (libreria header-only per algebra lineare)

## Compilazione

```bash
mkdir build
cd build
cmake ..
make
```

## Esecuzione

```
./main <path/della/netlist>
```

All'avvio il programma chiede da terminale quale algoritmo usare per il calcolo dei cicli:

```
Scegliere l'algoritmo per il calcolo dei cicli:
[1] per De Pina (cicli minimi)
[2] per DFS
```
Dopo aver stampato i risultati, chiede anche se esportare i grafi in formato DOT (Graphviz):

```
Vuoi stampare i grafi?
[Y] per sì
[N] per no
```

Rispondendo `Y` vengono creati `grafo_principale.dot` (il grafo del circuito) e
`coalbero.dot` (il coalbero), convertibili in immagine con:

```
dot -Tpng grafo_principale.dot -o grafo.png
dot -Tpng coalbero.dot -o coalbero.png
```

## Formato della netlist

Una riga per componente, campi separati da whitespace:
```
NOME  VALORE  NODO1  NODO2
```

- **NOME** comincia con `R` (resistore) o `V` (generatore di tensione).
- **VALORE** è in ohm per i resistori, volt per i generatori.
- **NODO1**, **NODO2** sono interi positivi. Per i generatori l'ordine
  indica la polarità: NODO1 = terminale "+", NODO2 = terminale "−".

Il parser è **tollerante** a:
- spazi e tab multipli tra le colonne;
- righe vuote o di solo whitespace;
- prefisso in minuscolo (`r1`, `v2`).
- nodi decimali (es: 1.0)

Genera **warning** (proseguendo con scelte di default) per:
- campi in eccesso dopo i 4 attesi (vengono usati i primi 4);
- resistenza negativa (viene presa in valore assoluto);
- nome di componente duplicato (viene mantenuta la prima occorrenza);
- componenti in parallelo (viene mantenuta la prima occorrenza).

Restituisce **errore** (e termina) per:
- file non apribile;
- riga malformata o errori di battitura nei numeri;
- tipo di componente diverso da R o V;
- nodi coincidenti sullo stesso componente;
- indice di nodo non positivo;
- nodo decimale non riconducibile a un intero;
- resistenza pari a zero.

## Esempio

Con una netlist `prova.txt`:
```
V1 30 1 4
V2 40 3 5
R1 4  4 2
R2 10 1 2
R3 30 1 3
R4 10 3 2
R5 4  2 5
```

`./main prova.txt` produce un output del tipo:
```
Netlist:    prova.txt
Nodi:       5
Componenti: 7
Maglie:     3
Metodo:     De Pina

--- RISULTATI CIRCUITO ---
R1: V =  8 volts, I =  2 amps
R2: V = 22 volts, I = 2.2 amps
R3: V = -6 volts, I = -0.2 amps
R4: V = -28 volts, I = -2.8 amps
R5: V = 12 volts, I =  3 amps
```

## Struttura del progetto

```
pcs2026/
|-- CMakeLists.txt          
|-- README.md                   
|-- main.cpp                        # punto di ingresso del programma
|-- prova.txt						            # usato nei test 
|
|-- include/                        # file header (intestazioni)
|   |-- netlist_struct.hpp          # struct Componente, Output
|   |-- edge.hpp                    # classe edge<T>: arco non orientato
|   |-- graph.hpp                   # classe graph<T>: grafo non orientato
|   |-- graph_visit.hpp             # DFS / BFS 
|   |-- fifo.hpp, lifo.hpp          # coda / pila
|   |-- costruzione_grafo.hpp       # da netlist a grafo + mappe ausiliarie
|   |-- cicli_DFS.hpp               # cicli fondamentali (DFS + coalbero)
|   |-- de_pina.hpp                 # cicli minimi (algoritmo di De Pina)
|   |-- dijkstra.hpp                # Dijkstra (usato da De Pina)
|   |-- dot_prod.hpp                # prodotto scalare mod 2 (De Pina)
|   |-- binary_diff.hpp             # differenza simmetrica (De Pina)
|   |-- gradiente_cd.hpp            # gradiente coniugato (usato da solve.hpp)
|   |-- solve.hpp                   # solver del sistema lineare con Eigen
|   |-- stampa_archi.hpp            # stampa degli archi
|   |-- stampa_grafi.hpp            # stampa dei grafi
|
|-- src/                            # file sorgente (implementazioni) 
|   |-- netlist_parser.cpp           
|   |-- grafo_construction.cpp       
|   |-- cd_gradient.cpp             
|
|-- tests/
    |-- test_parser.cpp             # 20 test unitari sul parser
    |-- test_grafo.cpp              # test sulla costruzione del grafo
    |-- test_de_pina.cpp            # test sull'algoritmo di De Pina
    |-- test_de_pina_helper.hpp     # supporto al test di De Pina
```

## Fondamenti teorici 

### Metodo delle correnti di maglia

Dato un grafo del circuito con `m` resistori e `n` maglie:

1. **B** ∈ ℝ^(m×n) — matrice di incidenza ciclo–arco: `B[i][j] = ±1` se il
   resistore *i* appartiene alla maglia *j* (segno dato dal verso di
   percorrenza), `0` altrimenti.
2. **R** ∈ ℝ^(m×m) — matrice diagonale delle resistenze.
3. **v** ∈ ℝ^n — vettore dei termini noti dato dai contributi dei generatori.
4. Si risolve il sistema lineare **(BᵀRB) i = v** con metodo del Gradiente Coniugato ottenendo le correnti di
   maglia.
5. Le tensioni sui resistori si calcolano come **V_R = R B i**.

### Individuazione delle maglie

Per costruire il sistema delle correnti di maglia è necessario individuare una base di cicli del grafo associato al circuito.

Sono implementati due **algoritmi alternativi** (selezionabili a runtime).

#### DFS + coalbero
Calcola un albero DFS *T* del grafo e prende il coalbero
*C = G \ T*. Per ogni arco di coalbero, il cammino tra i suoi estremi in *T*
chiuso dall'arco stesso forma un ciclo fondamentale. Non garantisce cicli
minimi.

#### Algoritmo di De Pina 
Usa algebra lineare su vettori booleani per
costruire una **base di cicli minimi**. Internamente utilizza un *lifting*
del grafo e algoritmo di Dijkstra per trovare i cicli più corti.

## Testing

Il progetto include test unitari per:

- parsing e validazione della netlist (20 casi di test);
- costruzione del grafo;
- algoritmo di De Pina.

I test sono raccolti nella cartella `tests/`.

## Documentazione aggiuntiva

La documentazione completa del progetto è disponibile nei file:

- `progetto.pdf`
- `Presentazione.pdf`

## Note

- Le matrici prodotte dal solver sono di norma simmetriche e definite
  positive; si usa quindi il metodo del gradiente coniugato per risolvere il 
  sistema lineare.

- Strumenti di AI generativa sono stati utilizzati esclusivamente a progetto completato e compilante senza warning, per analisi dei punti di forza e di debolezza dell'implementazione.
