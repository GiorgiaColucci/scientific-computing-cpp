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

La cartella contiene le esercitazioni sviluppate durante il corso, organizzate come un percorso progressivo che parte dai fondamenti del linguaggio C++ per arrivare a strutture dati avanzate, algoritmi su grafi e metodi numerici per il calcolo scientifico.

Gli argomenti affrontati includono:

#### 🔹 Fondamenti del linguaggio C++

* Gestione degli argomenti da linea di comando (`argc`, `argv`);
* Input/output da terminale e da file;
* Utilizzo dei tipi fondamentali e conversioni di tipo;
* Organizzazione del codice in file sorgente e header.

#### 🔹 Memoria e puntatori

* Indirizzamento della memoria e aritmetica dei puntatori;
* Relazione tra array e puntatori;
* Passaggio di parametri per valore e per riferimento;
* Allocazione dinamica della memoria e smart pointers (`std::unique_ptr`)
  
#### 🔹 Programmazione orientata agli oggetti (OOP)

* Definizione di classi e strutture dati personalizzate;
* Costruttori, distruttori e gestione delle risorse;
* Incapsulamento e modularizzazione del codice;
* Implementazione di una classe per numeri razionali con normalizzazione automatica delle frazioni.

#### 🔹 Generic Programming e STL

* Utilizzo dei template C++;
* Sviluppo di componenti riutilizzabili e indipendenti dal tipo;
* Impiego dei container e degli algoritmi della Standard Template Library (`std::vector`, `std::map`, ecc.).

#### 🔹 Build Automation

* Configurazione di progetti tramite CMake;
* Organizzazione modulare del codice in più file;
* Compilazione e gestione delle dipendenze.

#### 🔹 Strutture dati e algoritmi su grafi

* Implementazione di grafi orientati e non orientati;
* Rappresentazione tramite liste di adiacenza;
* Visite in ampiezza (BFS) e in profondità (DFS);
* Calcolo di cammini minimi mediante algoritmo di Dijkstra;
* Esportazione e visualizzazione dei grafi tramite GraphViz e formato DOT.

#### 🔹 Analisi di cicli e connettività

* Ricerca e gestione dei cicli fondamentali;
* Studio delle proprietà strutturali dei grafi;
* Implementazione di componenti ausiliarie per algoritmi di teoria dei grafi.

#### 🔹 Calcolo scientifico e algebra numerica

* Utilizzo della libreria Eigen per il calcolo matriciale;
* Risoluzione di sistemi lineari;
* Studio del numero di condizionamento delle matrici.

#### 🔹 Metodi iterativi per sistemi lineari

* Implementazione del metodo del Gradiente Coniugato (Conjugate Gradient);
* Valutazione della convergenza e dell'errore relativo;
* Confronto tra soluzioni esatte e approssimate.

#### 🔹 Algoritmi avanzati su grafi

* Implementazione e studio dell'algoritmo di De Pina per il Minimum Cycle Basis;
* Strumenti per il calcolo e la manipolazione di basi di cicli;
* Componenti che costituiscono la base teorica e software del progetto finale.


### 2. 🚀 Progetto Finale (`/Progetto`)
Il nucleo principale del repository, che rappresenta l'applicazione pratica dei concetti del corso su un problema di calcolo scientifico reale.

**Nota:** Per istruzioni dettagliate sull'architettura software del progetto, i requisiti matematici, le dipendenze e la procedura guidata di compilazione/esecuzione, si prega di fare riferimento al **[README specifico presente all'interno della cartella Progetto](./Progetto/)**.

---

## 👤 Autore
- **Giorgia Colucci** - *Studentessa in ambito Ingegneria*
- GitHub: [@GiorgiaColucci](https://github.com/GiorgiaColucci)
