# OOP Lab Work 01: GCD C++ Program

## Description

This is Lab Work №1 from the MAI OOP course. The program implements the Greatest Common Divisor (GCD) calculation in C++ using CMake build system and Google Test framework for unit testing.

## Goals

- Study C++ build systems using CMake
- Study version control systems Git
- Study memory management in C++
- Study input/output operations to standard streams
- Study unit testing using Google Test Framework

## Project Structure

```
GCD/
├── CMakeLists.txt          # CMake configuration file
├── main.cpp                # Main program
├── README.md               # This file
├── include/
│   └── GCD.hpp             # Header file with function declarations
├── src/
│   └── GCD.cpp             # Function implementations
├── tests/
│   └── test01.cpp          # Unit tests using Google Test
└── build/                  # Build directory (generated)
    ├── bin/                # Compiled executables
    └── lib/                # Compiled libraries
```

## Prerequisites

- C++ compiler (gcc 12+ or equivalent)
- CMake 3.10+
- Git

## Installation

Clone the repository:

```bash
git clone https://github.com/SheatA3Vp/GCD.git
cd GCD
```

## Building the Project

```bash
# Create a build directory
mkdir build
cd build

# Configure the project
cmake ..

# Build the project
cmake --build .
```

## Usage

### Running the Main Program

```bash
# From the build directory
./Lab01_exe
```

The program reads two integers from standard input and outputs their GCD.

Example:
```
Input: 48 18
Output: 6
```

### Running Tests

```bash
# From the build directory
./tests

# Or via CTest
ctest --verbose
```