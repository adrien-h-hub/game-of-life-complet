# Unit Tests - Conway's Game of Life

## 📋 Overview

This directory contains unit tests for the Game of Life project using **Catch2 v3** framework.

## 🧪 Test Files

### `test_grid.cpp`
Tests for the `Grid` class:
- Grid construction and validation
- Cell operations (get, set, toggle)
- Neighbor counting (standard and toroidal)
- Clear and count operations
- Copy constructor and assignment
- File I/O operations
- String representation

### `test_rules.cpp`
Tests for Conway's Game of Life rules:
- **Rule 1: Birth** - Dead cell with 3 neighbors becomes alive
- **Rule 2: Survival** - Living cell with 2-3 neighbors survives
- **Rule 3: Death** - Living cell dies from under/overpopulation
- Classic patterns (Block, Blinker)
- Generation counter
- Edge cases

### `test_main.cpp`
Main entry point that provides `main()` function for test runner.

## 🔨 Building and Running Tests

### Prerequisites

Install Catch2 v3:

**Windows (vcpkg)**:
```powershell
vcpkg install catch2:x64-windows
```

**Linux (Ubuntu/Debian)**:
```bash
sudo apt install catch2
# OR build from source
git clone https://github.com/catchorg/Catch2.git
cd Catch2
cmake -Bbuild -H. -DBUILD_TESTING=OFF
sudo cmake --build build/ --target install
```

**macOS (Homebrew)**:
```bash
brew install catch2
```

### Build Tests

From project root:
```bash
make tests
```

### Run Tests

```bash
./run_tests
```

### Run Specific Tests

```bash
# Run only Grid tests
./run_tests "[grid]"

# Run only rule tests
./run_tests "[rules]"

# Run specific test case
./run_tests "Conway's Rule 1: Birth"

# Run with verbose output
./run_tests -v high
```

## 📊 Test Coverage

### Grid Class
- ✅ Construction and validation
- ✅ Boundary checking
- ✅ 8-neighbor topology
- ✅ Toroidal topology
- ✅ File I/O
- ✅ Copy semantics

### Game Rules
- ✅ Birth rule (3 neighbors)
- ✅ Survival rule (2-3 neighbors)
- ✅ Death rules (under/overpopulation)
- ✅ Classic patterns verification

### Edge Cases
- ✅ Empty grid
- ✅ Single cell
- ✅ Boundary cells
- ✅ Corner cells
- ✅ Invalid dimensions

## 🎯 Test Statistics

- **Total Test Cases**: 20+
- **Total Sections**: 50+
- **Assertions**: 100+

## 📝 Writing New Tests

To add new tests:

1. Create new `.cpp` file in `tests/` directory
2. Include Catch2 headers:
   ```cpp
   #include <catch2/catch_test_macros.hpp>
   #include "../Grid.hpp"
   ```

3. Write test cases:
   ```cpp
   TEST_CASE("Description", "[tag]") {
       SECTION("Specific scenario") {
           // Arrange
           Grid grid(10, 10);
           
           // Act
           grid.setCell(5, 5, true);
           
           // Assert
           REQUIRE(grid.getCell(5, 5) == true);
       }
   }
   ```

4. Add to Makefile `TEST_SOURCES`
5. Run `make tests`

## 📚 Catch2 Documentation

- Official docs: https://github.com/catchorg/Catch2
- Assertions: https://github.com/catchorg/Catch2/blob/devel/docs/assertions.md
- Test cases: https://github.com/catchorg/Catch2/blob/devel/docs/test-cases-and-sections.md

## 🐛 Troubleshooting

**Catch2 not found**:
```bash
# Add include path
make tests CXXFLAGS="-I/path/to/catch2/include"
```

**Linking errors**:
```bash
# Catch2 v3 uses different linking
# Make sure to link with: -lCatch2Main -lCatch2
```

**Tests fail to run**:
```bash
# Check executable permissions
chmod +x run_tests
./run_tests
```

---

**Last Updated**: December 2, 2025  
**Catch2 Version**: v3.x  
**Test Framework**: Catch2
