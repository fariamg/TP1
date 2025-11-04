# TP — Algorithms & Measurement (C++)

This repository contains a C++ assignment project (TP) for data structures and algorithms coursework. It includes sorting algorithms, measurement and benchmarking utilities, a simple application entry point, and example input data. The project is organized with a Makefile for building and produces an executable at `bin/tp1.out`.

## Table of contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Build](#build)
- [Run / Usage](#run--usage)
- [Project structure](#project-structure)
- [Development notes](#development-notes)
- [Testing & Benchmarking](#testing--benchmarking)
- [Contributing](#contributing)
- [License](#license)
- [Authors & Contact](#authors--contact)

## Project overview

This project demonstrates basic algorithm implementations, measurement utilities, and a small driver application. It is intended for educational use in an algorithms/data structures course. The codebase contains:

- Sorting algorithm implementations (InsertionSort, QuickSort).
- A simple benchmarking/measurement framework.
- A vector/datastructure implementation used by the algorithms.
- A main application that ties the pieces together and reads input from files.

The code is organized to be readable and modular so students can adapt or extend the algorithms and measurement tools.

## Features

- Implementation of insertion sort and quick sort (in `src/algorithms`).
- Simple `Vector` container implementation (in `src/datastructures`).
- Measurement/benchmark components (`Timer`, `Statistics`, `Benchmark`) to collect execution metrics.
- A `CalibrationCacheManager` and `UniversalSorter` core utilities.
- Example input files in `data/` to exercise the program.

## Prerequisites

- A POSIX-like environment (Linux recommended).
- GNU Make and a C++ compiler (g++). The codebase targets modern C++ (C++11 or later). Example packages on Debian/Ubuntu:

```bash
sudo apt update
sudo apt install build-essential make
```

## Build

Build the project using the supplied `Makefile` from the `TP` directory. This will compile sources and place the final executable in `bin/`.

```bash
cd /home/gabriel-faria/Documentos/UFMG/EDD/TP
make
```

If the build succeeds, you should see `bin/tp1.out` created (or updated).

## Run / Usage

The program expects input provided via files (example files are in `data/`). A minimal run looks like:

```bash
./bin/tp1.out < data/teste1.txt
```

Redirect or capture output as needed:

```bash
./bin/tp1.out < data/teste1.txt > output.txt
```

Example provided inputs and expected outputs (where available):

- `data/teste1.txt` — example input
- `data/teste1out.txt` — expected output (for reference)

Note: the exact input format and options are defined by the program's `main` implementation in `src/app/main.cpp`. Inspect that file if you need to modify inputs or behavior.

## Project structure

Top-level layout (important folders):

- `Makefile` — build rules.
- `bin/` — compiled executables (e.g. `tp1.out`).
- `data/` — example input and output files used for testing.
- `include/` — public headers, organized by component (algorithms, core, datastructures, measurement).
- `src/` — implementation files mirroring `include/` layout.
- `obj/` — intermediate object files (build artifacts).
- `docs/` — project documents and reports.

Key source locations:

- `src/algorithms/` — sorting algorithms implementations.
- `src/datastructures/` — `Vector` implementation.
- `src/measurement/` — `Timer`, `Benchmark`, `Statistics`.
- `src/core/` — higher-level utilities like `UniversalSorter` and calibration cache manager.
- `src/app/main.cpp` — application entry point.

## Development notes

- Coding style: the project uses a straightforward C++ style. There is a `.clang-format` file at the root; consider running `clang-format` for consistent formatting.
- Header-first organization: public headers are in `include/` and corresponding implementations in `src/`.
- To add a new component, create the header in `include/<area>/` and implementation in `src/<area>/`, then extend the `Makefile` if necessary.

Edge cases and suggestions:

- Input validation: `main` may assume well-formed input for educational clarity. Add defensive checks if integrating with untrusted inputs.
- Large inputs: if benchmarking large datasets, ensure you have enough memory and consider algorithmic complexity when selecting input sizes.

## Testing & Benchmarking

- There are example inputs in `data/` to run quick manual tests. There are no automated unit tests included by default.
- The `measurement/` utilities can be used to collect timings and statistics during experiments.
- If you add unit tests, prefer a lightweight test framework (Catch2 or GoogleTest) and add a new target to the `Makefile`.

## Contributing

Contributions are welcome. Good contributions for this educational project include:

- Adding implementations of other algorithms.
- Improving measurement/benchmark accuracy and reporting.
- Adding unit tests and CI configuration.

When contributing:

1. Fork the repository.
2. Create a feature branch.
3. Add tests for your change when applicable.
4. Open a pull request with a clear description of the change and rationale.

## License

This repository does not include a LICENSE file in the project snapshot. If you intend to share or reuse this code publicly, add an appropriate license (for example, MIT, Apache-2.0). Contact the project owner to confirm licensing.

## Authors & Contact

Primary author (from repository documents):

- Gabriel Santos Faria — reference documents available under `docs/` (e.g. `gabriel_santos_faria_2024013990.pdf`).

If you need to contact the maintainer, include a short message and a reference to the repo name and student ID found in `docs/`.

## Acknowledgements

Built as an educational assignment for data structures & algorithms coursework. The project demonstrates core algorithm implementations and measurement techniques.

---

Files added/edited by this change:

- `README.md` — this file, added to the `TP` folder to document the project.
