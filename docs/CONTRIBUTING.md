# Contributing to Conway's Game of Life

First off, thank you for considering contributing to this project! 🎉

The following is a set of guidelines for contributing to Conway's Game of Life. These are mostly guidelines, not rules. Use your best judgment, and feel free to propose changes to this document in a pull request.

## 📋 Table of Contents

- [Code of Conduct](#code-of-conduct)
- [How Can I Contribute?](#how-can-i-contribute)
- [Development Setup](#development-setup)
- [Coding Standards](#coding-standards)
- [Commit Guidelines](#commit-guidelines)
- [Pull Request Process](#pull-request-process)
- [Project Structure](#project-structure)
- [Testing](#testing)

---

## 📜 Code of Conduct

This project adheres to a Code of Conduct that all contributors are expected to follow. Please read and follow these guidelines:

### Our Pledge

We pledge to make participation in this project a harassment-free experience for everyone, regardless of age, body size, disability, ethnicity, gender identity and expression, level of experience, nationality, personal appearance, race, religion, or sexual identity and orientation.

### Our Standards

**Examples of behavior that contributes to a positive environment:**
- Using welcoming and inclusive language
- Being respectful of differing viewpoints and experiences
- Gracefully accepting constructive criticism
- Focusing on what is best for the community
- Showing empathy towards other community members

**Examples of unacceptable behavior:**
- The use of sexualized language or imagery
- Trolling, insulting/derogatory comments, and personal or political attacks
- Public or private harassment
- Publishing others' private information without explicit permission
- Other conduct which could reasonably be considered inappropriate in a professional setting

---

## 🤝 How Can I Contribute?

### Reporting Bugs

Bugs are tracked as GitHub issues. Before creating a bug report, please check existing issues to avoid duplicates.

**How to Submit a Good Bug Report:**

1. **Use a clear and descriptive title** for the issue
2. **Describe the exact steps to reproduce the problem**
3. **Provide specific examples** to demonstrate the steps
4. **Describe the behavior you observed** and what you expected
5. **Include screenshots or GIFs** if applicable
6. **Provide your environment details**:
   - OS and version (e.g., Windows 11, Ubuntu 22.04)
   - Compiler version (e.g., GCC 11.3)
   - SFML version
   - Application version

**Bug Report Template:**

```markdown
**Describe the bug**
A clear and concise description of what the bug is.

**To Reproduce**
Steps to reproduce the behavior:
1. Launch application
2. Press 'R' to generate pattern
3. See error

**Expected behavior**
A clear description of what you expected to happen.

**Screenshots**
If applicable, add screenshots to help explain your problem.

**Environment:**
 - OS: [e.g., Windows 11]
 - Compiler: [e.g., GCC 11.3]
 - Version: [e.g., 1.1.0]

**Additional context**
Add any other context about the problem here.
```

### Suggesting Enhancements

Enhancement suggestions are also tracked as GitHub issues.

**Before Suggesting an Enhancement:**
- Check if the enhancement has already been suggested
- Check if the feature already exists in a newer version
- Consider if the feature fits the project's scope

**How to Submit a Good Enhancement Suggestion:**

```markdown
**Is your feature request related to a problem?**
A clear description of what the problem is. Ex. I'm always frustrated when [...]

**Describe the solution you'd like**
A clear and concise description of what you want to happen.

**Describe alternatives you've considered**
A clear description of any alternative solutions or features you've considered.

**Additional context**
Add any other context or screenshots about the feature request here.
```

### Your First Code Contribution

Unsure where to begin? You can start by looking for issues labeled:
- `good first issue` - Simple issues good for newcomers
- `help wanted` - Issues that need attention
- `beginner-friendly` - Issues suitable for those new to the project

### Pull Requests

We actively welcome your pull requests!

**How to Submit a Pull Request:**

1. Fork the repository
2. Create a new branch from `main`
3. Make your changes
4. Write or update tests if needed
5. Update documentation if needed
6. Ensure code follows style guidelines
7. Commit your changes with clear messages
8. Push to your fork
9. Submit a pull request

---

## 🛠️ Development Setup

### Prerequisites

- C++20 compatible compiler (GCC 10+, Clang 10+, MSVC 2019+)
- SFML 3.0
- Git
- Make or CMake

### Setup Steps

```bash
# Clone your fork
git clone https://github.com/YOUR_USERNAME/GameOfLife.git
cd GameOfLife

# Add upstream remote
git remote add upstream https://github.com/ORIGINAL_OWNER/GameOfLife.git

# Create a new branch
git checkout -b feature/your-feature-name

# Build the project
make

# Run the application
./GameOfLife
```

### Keeping Your Fork Updated

```bash
# Fetch upstream changes
git fetch upstream

# Merge upstream changes to your main branch
git checkout main
git merge upstream/main

# Push to your fork
git push origin main
```

---

## 📝 Coding Standards

### C++ Style Guide

#### Naming Conventions

```cpp
// Classes: PascalCase
class GameEngine { };

// Functions/Methods: camelCase
void updateGrid();
int countNeighbors(int row, int col);

// Variables: camelCase
int currentGeneration;
bool isRunning;

// Member variables: camelCase with underscore suffix
class Grid {
private:
    int rows_;
    int cols_;
};

// Constants: UPPER_CASE
const int MAX_GENERATIONS = 1000;

// Enums: PascalCase for type, UPPER_CASE for values
enum class Theme {
    NEON,
    OCEAN,
    FOREST
};
```

#### Formatting

```cpp
// Indentation: 4 spaces (no tabs)
void exampleFunction() {
    if (condition) {
        // Code here
    }
}

// Braces: Opening brace on same line
class Example {
    // ...
};

// Line length: Maximum 100 characters

// Comments: Use // for single line, /* */ for multi-line
// This is a single line comment

/*
 * This is a multi-line
 * comment block
 */
```

#### Best Practices

```cpp
// Use const correctness
const Grid& getGrid() const;

// Use references to avoid copies
void processGrid(const Grid& grid);

// Use smart pointers when appropriate
std::unique_ptr<Grid> grid_;

// Prefer nullptr over NULL
Grid* ptr = nullptr;

// Use auto for complex types
auto it = map.begin();

// Range-based for loops when possible
for (const auto& cell : cells) {
    // Process cell
}
```

### File Organization

```
src/
├── ClassName.cpp          # Implementation
include/
├── ClassName.hpp          # Header file
```

**Header File Structure:**

```cpp
#pragma once

#include <vector>
#include <string>

// Class declaration
class Example {
public:
    // Public methods
    
private:
    // Private members
};
```

**Source File Structure:**

```cpp
#include "Example.hpp"

#include <algorithm>
#include <iostream>

// Implementation
Example::Example() {
    // Constructor
}
```

### Documentation

Use Doxygen-style comments for public APIs:

```cpp
/**
 * @brief Counts the number of living neighbors for a cell
 * 
 * @param row The row index of the cell
 * @param col The column index of the cell
 * @return int The number of living neighbors (0-8)
 */
int countNeighbors(int row, int col) const;
```

---

## 📋 Commit Guidelines

### Commit Message Format

```
<type>(<scope>): <subject>

<body>

<footer>
```

**Types:**
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation changes
- `style`: Code style changes (formatting, etc.)
- `refactor`: Code refactoring
- `test`: Adding or updating tests
- `chore`: Maintenance tasks

**Examples:**

```
feat(renderer): add cell age visualization

Implemented color gradient based on how long cells have been alive.
Cells change from bright to darker colors as they age.

Closes #123
```

```
fix(engine): correct neighbor counting at grid boundaries

Fixed bug where neighbor count was incorrect for cells at the
edge of the grid. Now properly handles boundary conditions.

Fixes #456
```

```
docs(readme): update installation instructions

Added detailed steps for macOS installation using Homebrew.
```

### Commit Best Practices

- Write clear, concise commit messages
- Keep commits atomic (one logical change per commit)
- Commit often, push regularly
- Don't commit generated files (.o, .exe, etc.)
- Reference issues in commit messages

---

## 🔄 Pull Request Process

### Before Submitting

1. ✅ **Code compiles without warnings**
   ```bash
   make clean && make
   ```

2. ✅ **Code follows style guidelines**
   ```bash
   # Run clang-format if available
   clang-format -i src/*.cpp include/*.hpp
   ```

3. ✅ **Tests pass** (if applicable)

4. ✅ **Documentation updated**
   - Update README.md if adding features
   - Update docs/ if changing architecture
   - Add comments to new code

5. ✅ **No merge conflicts**
   ```bash
   git fetch upstream
   git rebase upstream/main
   ```

### PR Template

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Testing
How has this been tested?
- [ ] Tested on Windows
- [ ] Tested on Linux
- [ ] Tested on macOS

## Checklist
- [ ] Code compiles without warnings
- [ ] Code follows style guidelines
- [ ] Documentation updated
- [ ] No merge conflicts

## Screenshots (if applicable)
Add screenshots to demonstrate changes
```

### Review Process

1. A maintainer will review your PR
2. Address any requested changes
3. Once approved, a maintainer will merge
4. Your contribution will be credited!

---

## 📁 Project Structure

Understanding the project structure helps you navigate the codebase:

```
GameOfLife/
├── src/                    # C++ source files
│   ├── Grid.cpp
│   ├── GameEngine.cpp
│   ├── EnhancedGUIRenderer.cpp
│   ├── PatternDetector.cpp
│   ├── PatternLibrary.cpp
│   └── TimelineManager.cpp
├── include/                # Header files
│   ├── Grid.hpp
│   ├── GameEngine.hpp
│   ├── EnhancedGUIRenderer.hpp
│   ├── PatternDetector.hpp
│   ├── PatternLibrary.hpp
│   ├── TimelineManager.hpp
│   ├── Config.hpp
│   ├── Statistics.hpp
│   └── UIButton.hpp
├── docs/                   # Documentation
│   ├── ARCHITECTURE.md
│   ├── SOLID_PRINCIPLES.md
│   ├── BUILDING.md
│   └── CONTRIBUTING.md
├── installer/              # Installation scripts
│   └── GameOfLife_Installer.iss
├── screenshots/            # Application screenshots
├── Makefile               # Build configuration
├── README.md              # Main documentation
├── CHANGELOG.md           # Version history
└── LICENSE                # MIT License
```

---

## 🧪 Testing

### Manual Testing

Before submitting, manually test:

1. **Basic Functionality**:
   - Launch application
   - Generate random pattern (R)
   - Start/pause simulation (SPACE)
   - Change themes (K)

2. **Advanced Features**:
   - Time travel (← →)
   - Auto-pause (O)
   - Drawing cells (mouse)
   - Zoom and pan

3. **Edge Cases**:
   - Grid boundaries
   - Maximum zoom
   - Long-running simulations

### Future: Automated Testing

We plan to add unit tests:

```cpp
// Example test structure (GoogleTest)
TEST(GridTest, CountNeighbors) {
    Grid grid(10, 10);
    grid.setCell(5, 5, true);
    EXPECT_EQ(grid.countNeighbors(4, 4), 1);
}
```

---

## 🎨 Adding New Features

### Example: Adding a New Theme

1. **Define theme colors** in `EnhancedGUIRenderer.cpp`:

```cpp
case Theme::YOUR_THEME:
    return {
        sf::Color(r, g, b),     // background
        sf::Color(r, g, b),     // gridLines
        sf::Color(r, g, b),     // aliveCell
        sf::Color(r, g, b),     // deadCell
        sf::Color(r, g, b, a),  // panelBg
        sf::Color(r, g, b)      // text
    };
```

2. **Add enum value** in `EnhancedGUIRenderer.hpp`:

```cpp
enum class Theme {
    NEON,
    OCEAN,
    // ... existing themes ...
    YOUR_THEME,
    COUNT
};
```

3. **Update documentation** in README.md

4. **Submit PR** with screenshot of new theme

---

## 📞 Getting Help

- **Discord**: [Join our server] (if available)
- **GitHub Discussions**: For questions and ideas
- **GitHub Issues**: For bug reports and features
- **Email**: your.email@example.com

---

## 🏆 Recognition

Contributors will be recognized in:
- README.md Contributors section
- CHANGELOG.md for significant contributions
- GitHub contributors page

Thank you for contributing! 🙏

---

**Last Updated**: December 1, 2025  
**Version**: 1.1.0  
**Maintainer**: [Your Name]
