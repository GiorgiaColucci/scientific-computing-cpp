# Programmazione e Calcolo Scientifico (C++) 💻🧮

Questo repository documenta il percorso svolto durante il corso di Programmazione e Calcolo Scientifico (a.a. 2025/2026), raccogliendo esercitazioni e progetti sviluppati in C++ sui temi di programmazione generica, strutture dati, teoria dei grafi, algebra numerica e calcolo scientifico.

Il repository mostra l'evoluzione da esercizi introduttivi sul linguaggio C++ fino allo sviluppo di un progetto completo per l'analisi automatica di circuiti elettrici mediante metodi numerici e algoritmi su grafi.

L'obiettivo principale del corso è l'acquisizione di competenze avanzate nel linguaggio C++ applicato alla risoluzione di problemi matematici, simulazioni numeriche e calcolo scientifico. 

## 🛠️ Tecnologie e Strumenti utilizzati
- **Linguaggio principale:** C++ (standard moderni), con Template Programming e utilizzo della STL
- **Altri linguaggi:** MATLAB (per analisi e validazione dati)
- **Algebra lineare e calcolo matriciale:** libreria Eigen
- **Build Systems:** CMake, Makefile
- **Ambiente di sviluppo:** Version control tramite Git/GitHub
- **Esportazione e visualizzazione dei grafi:** GraphViz (formato DOT).


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

La cartella contiene le esercitazioni sviluppate durante il corso, organizzate come un percorso progressivo che parte dai fondamenti del linguaggio C++ per arrivare a strutture dati avanzate, algoritmi su grafi e metodi numerici per il calcolo scientifico.

I temi affrontati includono:

- Fondamenti del linguaggio C++ e gestione della memoria (puntatori e smart pointers)
- Organizzazione del codice in file sorgente e header.
- Programmazione orientata agli oggetti (classi e strutture dati personalizzate, costruttori, distruttori)
- Template e generic programming
- Standard Template Library
- Organizzazione di progetti e compilazione con CMake
- Strutture dati e algoritmi su grafi: BFS, DFS e Dijkstra
- Algebra lineare numerica con Eigen
- Metodi iterativi per sistemi lineari
- Algoritmi avanzati per basi di cicli minimi (De Pina)
- Visualizzazione di grafi tramite GraphViz

### 2. 🚀 Progetto Finale (`/Progetto`)
Il nucleo principale del repository, che rappresenta l'applicazione pratica dei concetti del corso su un problema di calcolo scientifico reale.

#### Competenze dimostrate

- Progettazione di strutture dati generiche in C++20
- Implementazione di grafi non orientati e algoritmi di visita
- Algoritmi per la ricerca di cicli (DFS, De Pina)
- Risoluzione di sistemi lineari sparsi con Eigen
- Testing unitario e validazione robusta dell'input
- Build system con CMake

**Nota:** Per istruzioni dettagliate sull'architettura software del progetto, i requisiti matematici, le dipendenze e la procedura guidata di compilazione/esecuzione, si prega di fare riferimento al **[README specifico presente all'interno della cartella Progetto](./Progetto/)**.

---

## 👤 Autore
- **Giorgia Colucci** - *Studentessa di Matematica per l'Ingegneria presso il Politecnico di Torino*
- GitHub: [@GiorgiaColucci](https://github.com/GiorgiaColucci)
