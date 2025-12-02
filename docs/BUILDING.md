# Building from Source - Conway's Game of Life v1.1.0

Complete guide for compiling the Game of Life from source code.

## 📋 Prerequisites

### All Platforms

- **C++20 compatible compiler**
  - GCC 10+ (recommended: 11+)
  - Clang 10+ (recommended: 12+)
  - MSVC 2019+ (Visual Studio 2019 or newer)
- **SFML 3.0** graphics library
- **Make** or **CMake** build system
- **Git** (for cloning repository)

### Platform-Specific Requirements

#### Windows
- **MSYS2/MinGW64** (recommended) OR Visual Studio 2019+
- Windows 10/11 (64-bit)
- 4 GB RAM minimum

#### Linux
- Ubuntu 20.04+ / Debian 11+ / Fedora 34+
- GCC/G++ toolchain
- X11 development libraries

#### macOS
- macOS 10.15 (Catalina) or newer
- Xcode Command Line Tools
- Homebrew package manager

---

## 🪟 Windows Build Instructions

### Option 1: MSYS2/MinGW64 (Recommended)

#### Step 1: Install MSYS2

1. Download MSYS2 installer from https://www.msys2.org/
2. Run the installer (e.g., `msys2-x86_64-20231026.exe`)
3. Follow installation wizard (default location: `C:\msys64`)
4. After installation, launch **MSYS2 MinGW 64-bit** terminal

#### Step 2: Update MSYS2

```bash
pacman -Syu
# Close terminal when asked, then reopen and run again
pacman -Syu
```

#### Step 3: Install Dependencies

```bash
# Install GCC compiler
pacman -S mingw-w64-x86_64-gcc

# Install SFML 3.0
pacman -S mingw-w64-x86_64-sfml

# Install Make
pacman -S mingw-w64-x86_64-make

# Install Git
pacman -S git
```

#### Step 4: Clone Repository

```bash
cd ~
git clone https://github.com/yourusername/GameOfLife.git
cd GameOfLife
```

#### Step 5: Build

```bash
# Build the project
make

# Or for clean build
make clean
make

# For release build (optimized)
make release
```

#### Step 6: Run

```bash
./GameOfLife.exe
```

#### Troubleshooting Windows

**Problem**: `command not found: make`
```bash
# Use mingw32-make instead
mingw32-make
```

**Problem**: Missing DLL errors when running
```bash
# Copy required DLLs from MSYS2
cp /mingw64/bin/sfml-*.dll .
cp /mingw64/bin/libgcc_s_seh-1.dll .
cp /mingw64/bin/libstdc++-6.dll .
cp /mingw64/bin/libwinpthread-1.dll .
```

**Problem**: `fatal error: SFML/Graphics.hpp: No such file or directory`
```bash
# Reinstall SFML
pacman -S --needed mingw-w64-x86_64-sfml
```

---

### Option 2: Visual Studio

#### Step 1: Install Visual Studio 2019+

1. Download Visual Studio Community from https://visualstudio.microsoft.com/
2. During installation, select:
   - Desktop development with C++
   - C++ CMake tools for Windows

#### Step 2: Install SFML

1. Download SFML 3.0 from https://www.sfml-dev.org/download/sfml/3.0.0/
2. Choose Visual Studio version (e.g., VC17 for VS2022)
3. Extract to `C:\SFML-3.0.0`

#### Step 3: Configure Project

1. Open Visual Studio
2. File → Open → CMake → Select `CMakeLists.txt` (if available)
3. OR create new project and add all source files

#### Step 4: Build

1. Build → Build Solution (F7)
2. Output will be in `x64\Release\` or `x64\Debug\`

---

## 🐧 Linux Build Instructions

### Ubuntu/Debian

#### Step 1: Install Dependencies

```bash
# Update package list
sudo apt update

# Install build tools
sudo apt install build-essential git

# Install SFML 3.0 development files
sudo apt install libsfml-dev

# If SFML 3.0 is not in repositories, build from source:
# See "Building SFML from Source" section below
```

#### Step 2: Clone Repository

```bash
cd ~
git clone https://github.com/yourusername/GameOfLife.git
cd GameOfLife
```

#### Step 3: Build

```bash
make

# Or for verbose output
make VERBOSE=1

# For release build
make release
```

#### Step 4: Run

```bash
./GameOfLife
```

### Fedora/RHEL

```bash
# Install dependencies
sudo dnf install gcc-c++ make git SFML-devel

# Clone and build
git clone https://github.com/yourusername/GameOfLife.git
cd GameOfLife
make
./GameOfLife
```

### Arch Linux

```bash
# Install dependencies
sudo pacman -S base-devel git sfml

# Clone and build
git clone https://github.com/yourusername/GameOfLife.git
cd GameOfLife
make
./GameOfLife
```

---

## 🍎 macOS Build Instructions

### Step 1: Install Xcode Command Line Tools

```bash
xcode-select --install
```

### Step 2: Install Homebrew (if not installed)

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### Step 3: Install Dependencies

```bash
# Install SFML
brew install sfml

# Install Git (if needed)
brew install git
```

### Step 4: Clone Repository

```bash
cd ~
git clone https://github.com/yourusername/GameOfLife.git
cd GameOfLife
```

### Step 5: Build

```bash
make

# For release build
make release
```

### Step 6: Run

```bash
./GameOfLife
```

---

## 🔨 Makefile Targets

The project includes a comprehensive Makefile with the following targets:

```bash
make                # Build in debug mode (default)
make release        # Build optimized release version
make clean          # Remove all compiled files
make rebuild        # Clean and rebuild
make run            # Build and run
make help           # Show available targets
```

### Makefile Variables

You can customize the build by setting variables:

```bash
# Use a different compiler
make CXX=clang++

# Add extra compiler flags
make CXXFLAGS="-Wall -Wextra -O3"

# Specify SFML path
make SFML_DIR=/custom/path/to/sfml
```

---

## 🏗️ Building SFML 3.0 from Source

If SFML 3.0 is not available in your package manager:

### Linux/macOS

```bash
# Clone SFML
git clone https://github.com/SFML/SFML.git
cd SFML
git checkout 3.0.0

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build (use -j for parallel build)
make -j$(nproc)

# Install
sudo make install

# Update library cache (Linux)
sudo ldconfig
```

### Windows (MSYS2)

```bash
# Clone SFML
git clone https://github.com/SFML/SFML.git
cd SFML
git checkout 3.0.0

# Build with MSYS2 MinGW
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
mingw32-make
mingw32-make install
```

---

## 🐛 Debugging Build Issues

### Common Errors

#### 1. `undefined reference to sf::...`

**Cause**: SFML library not linked correctly

**Solution**:
```bash
# Check if SFML is installed
pkg-config --modversion sfml-all  # Linux
brew list sfml                     # macOS

# Verify Makefile links SFML
grep "lsfml" Makefile
```

#### 2. `error: 'sf::RenderWindow' was not declared`

**Cause**: SFML headers not found

**Solution**:
```bash
# Linux: Check SFML installation
dpkg -L libsfml-dev | grep include

# Add include path if needed
make CXXFLAGS="-I/usr/include/SFML"
```

#### 3. `collect2: error: ld returned 1 exit status`

**Cause**: Linking error

**Solution**:
```bash
# Clean and rebuild
make clean
make VERBOSE=1
```

#### 4. OpenGL errors on Linux

```bash
# Install OpenGL development files
sudo apt install libgl1-mesa-dev libglu1-mesa-dev
```

---

## 📊 Build Configuration

### Debug vs Release

**Debug Build** (default):
```bash
make
```
- Debugging symbols included
- No optimization
- Larger executable
- Slower execution
- Better for development

**Release Build**:
```bash
make release
```
- Optimizations enabled (-O3)
- Debugging symbols stripped
- Smaller executable
- Faster execution
- Production-ready

### Custom Configuration

Edit the Makefile to customize:

```makefile
# Compiler
CXX = g++

# C++ Standard
CXXFLAGS = -std=c++20

# Optimization level
CXXFLAGS += -O3        # Release
# CXXFLAGS += -g       # Debug

# Warnings
CXXFLAGS += -Wall -Wextra -Wpedantic

# SFML libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
```

---

## 🧪 Verifying the Build

After successful build:

```bash
# Check executable exists
ls -lh GameOfLife.exe  # Windows
ls -lh GameOfLife      # Linux/macOS

# Check dependencies (Linux)
ldd GameOfLife

# Check dependencies (macOS)
otool -L GameOfLife

# Run with verbose output
./GameOfLife --verbose  # If implemented
```

---

## 📦 Creating Distributable Package

### Windows Installer

```bash
# Install Inno Setup from https://jrsoftware.org/isdown.php

# Compile installer script
"C:\Program Files (x86)\Inno Setup 6\ISCC.exe" installer\GameOfLife_Installer.iss

# Output: installer\GameOfLife_Setup_v1.1.0.exe
```

### Linux AppImage

```bash
# Install linuxdeploy
wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
chmod +x linuxdeploy-x86_64.AppImage

# Create AppImage
./linuxdeploy-x86_64.AppImage --appdir AppDir --executable GameOfLife --create-desktop-file
```

### macOS Bundle

```bash
# Create .app bundle structure
mkdir -p GameOfLife.app/Contents/MacOS
mkdir -p GameOfLife.app/Contents/Resources

# Copy executable
cp GameOfLife GameOfLife.app/Contents/MacOS/

# Create Info.plist
# ... (see macOS bundle documentation)
```

---

## 🔧 Development Tools

### Recommended IDE Setup

**Visual Studio Code**:
```bash
# Install C++ extension
code --install-extension ms-vscode.cpptools

# Install CMake extension
code --install-extension twxs.cmake
```

**CLion**: Full CMake support built-in

**Visual Studio**: Excellent C++ debugging

### Code Formatting

```bash
# Install clang-format
sudo apt install clang-format  # Linux
brew install clang-format      # macOS

# Format all source files
find src include -name "*.cpp" -o -name "*.hpp" | xargs clang-format -i
```

---

## 📚 Additional Resources

- **SFML Documentation**: https://www.sfml-dev.org/documentation/3.0.0/
- **C++20 Reference**: https://en.cppreference.com/w/cpp/20
- **CMake Tutorial**: https://cmake.org/cmake/help/latest/guide/tutorial/
- **GCC Manual**: https://gcc.gnu.org/onlinedocs/gcc/

---

## 💬 Getting Help

If you encounter build issues:

1. Check the [Troubleshooting](#-debugging-build-issues) section
2. Search existing [GitHub Issues](https://github.com/yourusername/GameOfLife/issues)
3. Open a new issue with:
   - Operating system and version
   - Compiler version (`g++ --version`)
   - Full error messages
   - Build commands used

---

**Last Updated**: December 1, 2025  
**Version**: 1.1.0  
**Maintainer**: [Your Name]
