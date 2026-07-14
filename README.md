# Scientific Programming and Computing (C++) 💻🧮

![C++](https://img.shields.io/badge/C%2B%2B-20-00599C?logo=cplusplus&logoColor=white)
![MATLAB](https://img.shields.io/badge/MATLAB-analysis-orange?logo=mathworks&logoColor=white)
![CMake](https://img.shields.io/badge/build-CMake-064F8C?logo=cmake&logoColor=white)
![Eigen](https://img.shields.io/badge/linear%20algebra-Eigen%203.3%2B-6c3483)
![Graphviz](https://img.shields.io/badge/visualization-Graphviz-F27E1E)
![License](https://img.shields.io/badge/license-MIT-blue)

This repository documents the work carried out during the *Scientific Programming and Computing* course (academic year 2025/2026), collecting the lab exercises and projects developed in C++ around generic programming, data structures, graph theory, numerical linear algebra, and scientific computing.

The work culminates in a complete project for the automatic analysis of electrical circuits using numerical methods and algorithms on graphs.

<p align="center">
  <img src="./Project/images/circuit_graph.png" alt="Circuit graph produced by the final project" height="320">
  <br>
  <em>Circuit graph automatically built and analyzed by the final project.</em>
</p>

The main goal of the course is to build advanced C++ skills applied to solving mathematical problems, running numerical simulations, and performing scientific computing.

## 🛠️ Technologies and Tools

- **Primary language:** C++ (modern standards), with Template Programming and use of the STL
- **Other languages:** MATLAB (for data analysis and validation)
- **Linear algebra and matrix computation:** Eigen library
- **Build systems:** CMake and Makefile, with both debug and release builds
- **Development environment:** version control with Git/GitHub
- **Graph export and visualization:** GraphViz (DOT format)

---

## 📂 Repository Structure

The repository is organized to cleanly separate the weekly learning exercises from the work on the main project:

```text
.
├── Exercises/           # Collection of weekly labs and exercises
│   ├── exercise_01/
│   ├── exercise_02/
│   └── ...
├── Project/             # Source code of the final exam project
│   ├── ...
│   └── README.md        # Detailed, project-specific documentation
├── .gitignore           # Excludes build artifacts and system files
└── README.md            # This file (overall presentation)
```

### 1. 📘 Exercises (`/Exercises`)

This folder contains the exercises developed throughout the course, organized as a progressive path that starts from the fundamentals of C++ and builds up to advanced data structures, graph algorithms, and numerical methods for scientific computing.

The topics covered include the hands-on implementation of:

- Memory management with pointers and smart pointers
- Code organization across source and header files
- Object-oriented programming (custom classes and data structures, constructors, destructors)
- Templates and generic programming
- Use of the Standard Template Library
- Project organization and compilation with CMake
- Graph data structures and algorithms: BFS, DFS, and Dijkstra
- Numerical linear algebra operations with Eigen
- Iterative methods for solving linear systems
- Advanced algorithms for building minimum cycle bases (De Pina)
- Graph export and visualization with GraphViz (the rendered build outputs are collected in the `images/` folder of exercise_09)

| Exercise | Topic |
|:---:|---|
| 01 | C++ fundamentals: I/O, control flow, basic programs |
| 02 | Functions and an introduction to object-oriented programming |
| 03 | Code organization across header and source files |
| 04 | Sorting algorithms (bubble, insertion, selection) with timing and MATLAB plots |
| 05 | Sorting benchmark (incl. hybrid quicksort), debug vs. release comparison |
| 08 | Generic undirected graph and edge classes |
| 09 | Graph traversals (BFS, DFS, Dijkstra) and Graphviz export |
| 10 | Conjugate Gradient method for linear systems |
| 11 | Cycle bases: fundamental cycles (DFS) and De Pina |

> For Exercise 05, see the [dedicated README](./Exercises/exercise_05/README.md) with the Debug vs Release benchmark comparison.

### 2. 🚀 Final Project (`/Project`)

The core of the repository, applying the concepts of the course to a real scientific computing problem.

#### Key software skills developed

- Design of generic data structures in C++20
- Implementation of undirected graphs and graph traversal algorithms
- Cycle-finding algorithms (DFS, De Pina)
- Solving sparse linear systems with Eigen
- Unit testing and robust input validation
- Build automation with CMake

**Note:** For detailed instructions on the software architecture of the project, the mathematical background, the dependencies, and the step-by-step build/run procedure, please refer to the **[dedicated README inside the Project folder](./Project/)**.

---

## 👤 Author

- **Giorgia Colucci** — *Mathematical Engineering student at Politecnico di Torino*
- [![LinkedIn](https://img.shields.io/badge/LinkedIn-Giorgia%20Colucci-0A66C2?logo=linkedin)](https://www.linkedin.com/in/giorgia-colucci) 
- GitHub: [@GiorgiaColucci](https://github.com/GiorgiaColucci)

The final project in `/Project` was developed together with Diego Catellani and Angelamaria Colucci.

## 📄 License

Released under the MIT License. See [LICENSE](./LICENSE) for details.