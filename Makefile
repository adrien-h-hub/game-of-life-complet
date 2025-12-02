# Beautiful Game of Life - Standalone App Makefile

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -O3 -I. -Iinclude
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -mwindows
LDFLAGS_CONSOLE = -lsfml-system
TEST_LDFLAGS = -lCatch2Main -lCatch2
WINDRES = windres

# Target executables
TARGET = GameOfLife.exe
TARGET_CONSOLE = GameOfLife_Console.exe
TARGET_TESTS = run_tests.exe

# Source files (all in same directory)
SOURCES = main.cpp \
          Grid.cpp \
          GameEngine.cpp \
          TextFileIO.cpp \
          Config.cpp \
          EnhancedGUIRenderer.cpp \
          src/UIButton.cpp \
          src/PatternDetector.cpp

# Console-only sources (no GUI)
CONSOLE_SOURCES = Grid.cpp \
                  GameEngine.cpp \
                  TextFileIO.cpp

# Test sources
TEST_SOURCES = tests/test_main.cpp \
               tests/test_grid.cpp \
               tests/test_rules.cpp \
               Grid.cpp \
               GameEngine.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)
CONSOLE_OBJECTS = $(CONSOLE_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Icon resource
ICON_RES = icon.res

# Default target
all: gui
	@echo "✨ Build complete! Run with: ./$(TARGET)"

# GUI target (default)
gui: $(TARGET)

# Console mode target
console: $(TARGET_CONSOLE)
	@echo "✨ Console build complete! Run with: ./$(TARGET_CONSOLE)"

# Test target
tests: $(TARGET_TESTS)
	@echo "✨ Tests build complete! Run with: ./$(TARGET_TESTS)"
	@echo "🧪 Running tests..."
	./$(TARGET_TESTS)

# Compile icon resource
$(ICON_RES): icon.rc
	@echo "🎨 Compiling icon..."
	@if [ -f app_icon.ico ]; then $(WINDRES) icon.rc -O coff -o $(ICON_RES); else echo "⚠️  No icon found, skipping..."; touch $(ICON_RES); fi

# Link the GUI executable
$(TARGET): $(OBJECTS) $(ICON_RES)
	@echo "🔗 Linking $(TARGET)..."
	@if [ -s $(ICON_RES) ]; then $(CXX) $(OBJECTS) $(ICON_RES) -o $(TARGET) $(LDFLAGS); else $(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS); fi
	@echo "✅ Success!"

# Link the console executable
$(TARGET_CONSOLE): $(CONSOLE_OBJECTS)
	@echo "🔗 Linking console mode $(TARGET_CONSOLE)..."
	$(CXX) $(CONSOLE_OBJECTS) -o $(TARGET_CONSOLE) $(LDFLAGS_CONSOLE)
	@echo "✅ Console build success!"

# Link the test executable
$(TARGET_TESTS): $(TEST_OBJECTS)
	@echo "🔗 Linking tests $(TARGET_TESTS)..."
	$(CXX) $(TEST_OBJECTS) -o $(TARGET_TESTS) $(TEST_LDFLAGS)
	@echo "✅ Tests build success!"

# Compile source files
%.o: %.cpp
	@echo "⚙️  Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	@echo "🧹 Cleaning..."
	del /Q $(OBJECTS) $(TARGET) $(TARGET_CONSOLE) $(TARGET_TESTS) $(ICON_RES) 2>nul || true
	del /Q tests\*.o 2>nul || true
	del /Q src\*.o 2>nul || true
	@echo "✅ Clean complete!"

# Generate documentation with Doxygen
docs:
	@echo "📚 Generating documentation..."
	@if command -v doxygen >/dev/null 2>&1; then \
		doxygen Doxyfile; \
		echo "✅ Documentation generated in ./doxygen/html/"; \
	else \
		echo "❌ Doxygen not found. Install with: sudo apt install doxygen"; \
	fi

# Format code with clang-format
format:
	@echo "🎨 Formatting code..."
	@if command -v clang-format >/dev/null 2>&1; then \
		find . -name "*.cpp" -o -name "*.hpp" | xargs clang-format -i; \
		echo "✅ Code formatted!"; \
	else \
		echo "❌ clang-format not found."; \
	fi

# Docker build
docker-build:
	@echo "🐳 Building Docker image..."
	docker build -t gameoflife:1.1.0 .
	@echo "✅ Docker image built! Run with: docker run -it gameoflife:1.1.0"

# Docker run
docker-run:
	@echo "🐳 Running in Docker..."
	docker run -it -v $(PWD)/input_out:/app/input_out gameoflife:1.1.0

# Run the application
run: $(TARGET)
	@echo "🚀 Starting Game of Life..."
	./$(TARGET)

# Run with a pattern
run-glider: $(TARGET)
	./$(TARGET) --file=patterns/glider.txt

run-gun: $(TARGET)
	./$(TARGET) --file=patterns/gosper_glider_gun.txt --cell-size=8

run-pulsar: $(TARGET)
	./$(TARGET) --file=patterns/pulsar.txt

# Help
help:
	@echo "🎮 Game of Life - Build Commands"
	@echo "================================"
	@echo "MAIN TARGETS:"
	@echo "  make          - Build GUI application (default)"
	@echo "  make gui      - Build GUI application"
	@echo "  make console  - Build console mode"
	@echo "  make tests    - Build and run tests"
	@echo "  make all      - Build GUI (same as default)"
	@echo ""
	@echo "RUN TARGETS:"
	@echo "  make run         - Build and run GUI"
	@echo "  make run-gun     - Run with Gosper Glider Gun"
	@echo "  make run-pulsar  - Run with Pulsar"
	@echo ""
	@echo "DEVELOPMENT:"
	@echo "  make clean       - Remove build files"
	@echo "  make docs        - Generate Doxygen documentation"
	@echo "  make format      - Format code with clang-format"
	@echo ""
	@echo "DOCKER:"
	@echo "  make docker-build - Build Docker image"
	@echo "  make docker-run   - Run in Docker container"
	@echo ""
	@echo "  make help        - Show this help"

.PHONY: all gui console tests clean run run-glider run-gun run-pulsar help docs format docker-build docker-run
