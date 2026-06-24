# Programmazione e Calcolo Scientifico (C++) 💻🧮

Questo repository raccoglie il materiale didattico, le esercitazioni pratiche e il progetto finale sviluppati per il corso di **Programmazione e Calcolo Scientifico** (Anno Accademico 2025/2026).

L'obiettivo principale del corso è l'acquisizione di competenze avanzate nel linguaggio C++ applicato alla risoluzione di problemi matematici, simulazioni numeriche e calcolo scientifico. 

## 🛠️ Tecnologie e Strumenti utilizzati
- **Linguaggio principale:** C++ (standard moderni)
- **Altri linguaggi:** MATLAB (per analisi e validazione dati)
- **Build Systems:** CMake, Makefile
- **Ambiente di sviluppo:** Version control tramite Git/GitHub

---

## 📂 Struttura del Repository

La struttura del repository è organizzata in modo logico e pulito per separare la fase di apprendimento settimanale dal lavoro sul progetto principale:

```text
.
├── Esercitazioni/       # Raccolta dei laboratori e dei temi settimanali
│   ├── Esercitazione_01/
│   ├── Esercitazione_02/
│   └── ...
├── Progetto/            # Codice sorgente del progetto d'esame finale
│   ├── ...
│   └── README.md        # Documentazione specifica e dettagliata del progetto
├── .gitignore           # Esclusione dei file di build e di sistema
└── README.md            # Questo file (presentazione globale)
```

### 1. 📘 Esercitazioni (`/Esercitazioni`)
In questa cartella sono presenti i laboratori settimanali focalizzati su concetti chiave del C++ e del calcolo numerico:
- **Fondamenti e Gestione Memoria:** Puntatori, referenze, allocazione dinamica, smart pointers (`std::unique_ptr`, `std::shared_ptr`).
- **Programmazione a Oggetti (OOP):** Classi, incapsulamento, ereditarietà, polimorfismo, gestione delle risorse (RAII).
- **Standard Template Library (STL):** Container (`std::vector`, `std::map`, ecc.), algoritmi ed iteratori.
- **Strumenti di Build:** Automazione della compilazione tramite file `Makefile` e configurazioni `CMakeLists.txt`.

### 2. 🚀 Progetto Finale (`/Progetto`)
Il nucleo principale del repository, che rappresenta l'applicazione pratica dei concetti del corso su un problema di calcolo scientifico reale.
Qui di seguito una breve descrizione del progetto e delle strutture implementate.

L'obiettivo del progetto è implementare un risolutore per circuiti elettrici lineari mediante il **Metodo delle Correnti di Maglia**, sfruttando strumenti di teoria dei grafi e algebra lineare numerica.

## Panoramica

Il programma:

- legge una netlist che descrive il circuito;
- costruisce il grafo associato;
- individua una base di cicli del circuito;
- genera il sistema lineare delle correnti di maglia;
- risolve il sistema;
- restituisce correnti e tensioni sui componenti.

## Tecniche utilizzate

Durante lo sviluppo sono stati implementati e utilizzati diversi algoritmi studiati nel corso:

### Teoria dei grafi

- Depth First Search (DFS)
- Costruzione di alberi e coalberi
- Ricerca di cicli fondamentali
- Algoritmo di Dijkstra
- Algoritmo di De Pina per la costruzione di una Minimum Cycle Basis

### Algebra lineare numerica

- Gradiente Coniugato
- Risoluzione di sistemi lineari mediante Eigen

## Contenuti del corso applicati

- Programmazione C++
- Strutture dati
- Teoria dei grafi
- Cammini minimi
- Basi di cicli
- Algebra lineare numerica
- Metodi iterativi
- Modellazione di circuiti elettrici

- **Nota:** Per istruzioni dettagliate sull'architettura software del progetto, i requisiti matematici, le dipendenze e la procedura guidata di compilazione/esecuzione, si prega di fare riferimento al **[README specifico presente all'interno della cartella Progetto](./Progetto/)**.

---

## 👤 Autore
- **Giorgia Colucci** - *Studentessa in ambito Ingegneria*
- GitHub: [@GiorgiaColucci](https://github.com/GiorgiaColucci)
