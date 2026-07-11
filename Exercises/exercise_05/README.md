# Exercise 05 — Sorting Algorithms Benchmark

Benchmark of six sorting algorithms — bubble sort, selection sort, insertion
sort, merge sort, quicksort (including a hybrid variant), and the standard
library's `std::sort` — comparing execution times across Debug and Release
builds.

## What this exercise does

For each algorithm, execution time is measured on randomly filled vectors of
size 2 to 100 (step 2), averaging 100 runs per size with a fixed random seed
(42). The same benchmark is run once in Debug mode and once in Release mode,
each producing its own set of measurements and its own MATLAB plot:

- [`grafico_completo_debug.m`](./grafico_completo_debug.m)
- [`grafico_completo_release.m`](./grafico_completo_release.m)

Both scripts plot all six algorithms together on a log-log scale.

| Debug | Release |
|:---:|:---:|
| ![Debug comparison](./Confronto%20Algoritmi%20di%20Ordinamento%20Debug.png) | ![Release comparison](./Confronto%20Algoritmi%20di%20Ordinamento%20Release.png) |

## Debug vs Release Comparison

**Asymptotic behavior.** The quadratic algorithms (bubble, selection,
insertion) show a clearly steeper slope, consistent with O(n²) complexity.
The O(n log n) algorithms (merge, quick, `std::sort`) show a visibly lower
slope, which looks nearly linear for n ≤ 100 given the limited range.

**Fixed overhead of recursive algorithms.** For small n (roughly n < 42),
merge sort is the slowest of all despite its better asymptotic complexity,
especially for n < 10. This is due to the fixed costs of recursive calls
(parameter passing, stack frame allocation/deallocation) and the temporary
memory allocated for sub-vectors, which dominate when n is small.

**Crossover point.** Insertion sort (the fastest quadratic algorithm)
overtakes quicksort around n = 40–42. Below this threshold insertion sort is
faster; this motivated the hybrid `hybrid_quicksort` implementation, which
falls back to insertion sort for sub-vectors of size ≤ 42.

**Debug vs Release.** Release builds are noticeably faster across all
algorithms, with the largest relative gap for the simpler ones (bubble,
insertion). The qualitative behavior — relative ordering of the algorithms
and the position of the crossover threshold — stays essentially unchanged
between the two build modes.

**Comparison with `std::sort`.** The standard library's `std::sort` sits at
roughly average speed for small sizes (n < 56) but becomes one of the fastest
for larger sizes, close to quicksort.

## Build

```bash
mkdir build_debug && cd build_debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

mkdir ../build_release && cd ../build_release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```