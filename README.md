# Adaptive Sorting Algorithm Framework

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com)
[![License](https://img.shields.io/badge/license-Educational-orange.svg)](LICENSE)

> A high-performance C++ framework for adaptive sorting algorithm analysis with integrated benchmarking and statistical measurement tools.

## 📋 Table of Contents

- [Overview](#-overview)
- [Key Features](#-key-features)
- [Quick Start](#-quick-start)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Usage](#usage)
- [Architecture](#-architecture)
- [Input Format](#-input-format)
- [Algorithms](#-algorithms)
- [Benchmarking](#-benchmarking)
- [Development](#-development)
  - [Project Structure](#project-structure)
  - [Building from Source](#building-from-source)
  - [Code Style](#code-style)
- [Performance](#-performance)
- [Testing](#-testing)
- [Contributing](#-contributing)
- [Troubleshooting](#-troubleshooting)
- [License](#-license)
- [Authors](#-authors)

## 🎯 Overview

This project implements an **adaptive sorting algorithm framework** designed for educational and research purposes. It intelligently selects between QuickSort and InsertionSort based on runtime performance analysis and cost estimation, providing detailed benchmarking capabilities for algorithm comparison.

### What Makes This Special?

- **Adaptive Algorithm Selection**: Automatically chooses the optimal sorting algorithm based on input characteristics and performance metrics
- **Comprehensive Benchmarking**: Built-in timing and statistical analysis tools
- **Performance Calibration**: Smart caching system for algorithm performance parameters
- **Modular Architecture**: Clean separation of concerns for easy extension and testing

## ✨ Key Features

| Feature                     | Description                                                             |
| --------------------------- | ----------------------------------------------------------------------- |
| **Sorting Algorithms**      | QuickSort and InsertionSort implementations with optimizations          |
| **Universal Sorter**        | Adaptive algorithm selection based on cost threshold analysis           |
| **Performance Measurement** | High-precision timing, statistical analysis, and benchmarking suite     |
| **Calibration System**      | Automatic calibration with persistent caching (`calibration_cache.dat`) |
| **Custom Data Structures**  | Lightweight `Vector` implementation optimized for the framework         |
| **Extensive Test Suite**    | 10+ test cases with expected outputs for validation                     |

## 🚀 Quick Start

### Prerequisites

- **Operating System**: Linux (POSIX-compatible)
- **Compiler**: GCC/G++ with C++17 support (version 7.0+)
- **Build System**: GNU Make 4.0+

**Installation on Debian/Ubuntu:**

```bash
sudo apt update
sudo apt install build-essential make
```

**Verify installation:**

```bash
g++ --version  # Should be >= 7.0
make --version # Should be >= 4.0
```

### Installation

1. **Clone or navigate to the project directory:**

```bash
cd /path/to/TP
```

2. **Build the project:**

```bash
make
```

This will:

- Compile all source files with optimizations enabled
- Create the executable at `bin/tp1.out`
- Generate object files in `obj/`

3. **Verify the build:**

```bash
ls -lh bin/tp1.out
```

### Usage

**Basic execution:**

```bash
./bin/tp1.out data/teste1.txt
```

**Run multiple test cases:**

```bash
for i in {1..10}; do
    echo "Running test $i..."
    ./bin/tp1.out data/teste${i}.txt
done
```

**Capture output:**

```bash
./bin/tp1.out data/teste1.txt > results/output1.txt
```

**Clean build artifacts:**

```bash
make clean  # Removes obj/, bin/, and calibration cache
```

## 🏗️ Architecture

```
┌─────────────────────────────────────────┐
│          Application Layer              │
│         (src/app/main.cpp)              │
└────────────────┬────────────────────────┘
                 │
┌────────────────▼────────────────────────┐
│         Core Components                 │
│  • UniversalSorter                      │
│  • CalibrationCacheManager              │
└─────┬──────────────────────┬────────────┘
      │                      │
┌─────▼─────────┐    ┌──────▼─────────────┐
│  Algorithms   │    │   Measurement      │
│  • QuickSort  │    │  • Benchmark       │
│  • Insertion  │    │  • Timer           │
│    Sort       │    │  • Statistics      │
└───────┬───────┘    └────────────────────┘
        │
┌───────▼────────────┐
│  Data Structures   │
│  • Vector          │
└────────────────────┘
```

### Component Responsibilities

- **Application Layer**: Input parsing, workflow orchestration, output formatting
- **Core**: High-level sorting logic and calibration management
- **Algorithms**: Concrete sorting implementations
- **Measurement**: Performance analysis and statistical tools
- **Data Structures**: Custom container implementations

## 📝 Input Format

The program expects a text file with the following structure:

```
<seed>              # Random seed for reproducibility
<cost_threshold>    # Threshold for algorithm selection
<a>                 # Calibration parameter A
<b>                 # Calibration parameter B
<c>                 # Calibration parameter C
<size>              # Number of elements
<element_1>         # Array elements (one per line)
<element_2>
...
<element_n>
```

**Example (`data/teste1.txt`):**

```
42
1000.0
0.5
1.2
0.8
10
5
2
8
1
9
3
7
4
6
10
```

## 🔧 Algorithms

### QuickSort

- **Time Complexity**: O(n log n) average, O(n²) worst case
- **Space Complexity**: O(log n)
- **Best For**: Large, randomly distributed datasets

### InsertionSort

- **Time Complexity**: O(n²) worst case, O(n) best case
- **Space Complexity**: O(1)
- **Best For**: Small arrays (<50 elements) or nearly sorted data

### Adaptive Selection

The `UniversalSorter` uses a cost function to determine the optimal algorithm:

```
Cost = a * comparisons + b * swaps + c * overhead
```

If `Cost < threshold`, use QuickSort; otherwise, use InsertionSort.

## 📊 Benchmarking

The framework includes sophisticated benchmarking capabilities:

- **High-Precision Timing**: Microsecond-level accuracy using `std::chrono`
- **Statistical Analysis**: Mean, median, standard deviation, min/max
- **Calibration**: Automatic parameter tuning with persistent caching
- **Comparative Analysis**: Side-by-side algorithm performance

**Example output:**

```
Algorithm: QuickSort
Elements: 10000
Time: 2.345 ms
Comparisons: 138,428
Swaps: 12,456
```

## 💻 Development

### Project Structure

```
TP/
├── Makefile                    # Build configuration
├── README.md                   # This file
├── .clang-format               # Code formatting rules
├── calibration_cache.dat       # Performance calibration cache
│
├── bin/                        # Compiled executables
│   └── tp1.out
│
├── include/                    # Public headers
│   ├── algorithms/
│   │   ├── InsertionSort.h
│   │   └── QuickSort.h
│   ├── core/
│   │   ├── UniversalSorter.h
│   │   └── CalibrationCacheManager.h
│   ├── datastructures/
│   │   └── Vector.h
│   └── measurement/
│       ├── Benchmark.h
│       ├── Timer.h
│       └── Statistics.h
│
├── src/                        # Implementation files
│   ├── algorithms/
│   ├── core/
│   ├── datastructures/
│   ├── measurement/
│   └── app/
│       └── main.cpp
│
├── obj/                        # Build artifacts (generated)
├── data/                       # Test cases
│   ├── teste1.txt - teste10.txt
│   └── teste1out.txt, teste2out.txt
│
└── docs/                       # Documentation
    └── gabriel_santos_faria_2024013990.pdf
```

### Building from Source

**Compile:**

```bash
make                # Build the project
```

**Rebuild:**

```bash
make clean && make  # Clean build
```

**Run:**

```bash
make run            # Build and run with default input
```

**Makefile Targets:**

| Target  | Description                      |
| ------- | -------------------------------- |
| `all`   | Build the executable (default)   |
| `clean` | Remove build artifacts and cache |
| `run`   | Build and execute the program    |

### Code Style

The project follows a consistent C++17 style with:

- **Formatting**: Automatic formatting via `.clang-format`
- **Naming**: CamelCase for classes, snake_case for functions
- **Headers**: Include guards and forward declarations
- **Documentation**: Inline comments for complex logic

**Apply formatting:**

```bash
find src include -name "*.cpp" -o -name "*.h" | xargs clang-format -i
```

## ⚡ Performance

Typical performance on modern hardware (Intel i5/AMD Ryzen 5):

| Array Size | QuickSort | InsertionSort | Adaptive |
| ---------- | --------- | ------------- | -------- |
| 100        | 0.05 ms   | 0.03 ms       | 0.03 ms  |
| 1,000      | 0.5 ms    | 2.5 ms        | 0.5 ms   |
| 10,000     | 6 ms      | 250 ms        | 6 ms     |
| 100,000    | 75 ms     | 25 sec        | 75 ms    |

_Note: Times are approximate and depend on hardware and data distribution_

## 🧪 Testing

**Manual Testing:**

```bash
# Run all test cases
for test in data/teste*.txt; do
    ./bin/tp1.out "$test"
done
```

**Validate Against Expected Output:**

```bash
./bin/tp1.out data/teste1.txt > output.txt
diff output.txt data/teste1out.txt
```

**Future Enhancements:**

- Unit tests with Google Test or Catch2
- Continuous Integration with GitHub Actions
- Automated regression testing

## 🤝 Contributing

Contributions are welcome! Here's how to get started:

1. **Fork** the repository
2. **Create** a feature branch: `git checkout -b feature/amazing-feature`
3. **Commit** your changes: `git commit -m 'Add amazing feature'`
4. **Push** to the branch: `git push origin feature/amazing-feature`
5. **Open** a Pull Request

**Guidelines:**

- Follow the existing code style
- Add tests for new features
- Update documentation as needed
- Write clear commit messages

**Good First Issues:**

- Add more sorting algorithms (MergeSort, HeapSort)
- Implement unit tests
- Improve documentation
- Add performance visualizations

## ❗ Troubleshooting

### Common Issues

**Build fails with "command not found":**

```bash
# Install build tools
sudo apt install build-essential
```

**"Permission denied" when running executable:**

```bash
chmod +x bin/tp1.out
```

**Segmentation fault:**

- Check input file format matches specification
- Verify array size matches number of elements provided

**Calibration cache errors:**

```bash
# Reset calibration
rm calibration_cache.dat
./bin/tp1.out data/teste1.txt
```

## 📄 License

This project is developed for **educational purposes** as part of the Data Structures and Algorithms coursework at UFMG (Universidade Federal de Minas Gerais).

For academic use and distribution, please contact the author.

## 👨‍💻 Authors

**Gabriel Santos Faria**

- Student ID: 2024013990
- Institution: UFMG - Federal University of Minas Gerais
- Course: Data Structures and Algorithms

For questions or collaboration, please refer to the documentation in `docs/`.

---

<div align="center">

**Built with ❤️ for learning and research**

[Report Bug](https://github.com/username/repo/issues) · [Request Feature](https://github.com/username/repo/issues)

</div>
