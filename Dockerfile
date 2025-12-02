# Dockerfile for Conway's Game of Life
# Multi-stage build for optimized console mode

# Build stage
FROM gcc:12 AS builder

# Install dependencies
RUN apt-get update && apt-get install -y \
    make \
    libsfml-dev \
    catch2 \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy source files
COPY Grid.cpp Grid.hpp \
     GameEngine.cpp GameEngine.hpp \
     Config.cpp Config.hpp \
     TextFileIO.cpp TextFileIO.hpp \
     Makefile \
     ./

COPY src/ ./src/
COPY include/ ./include/

# Build console mode
RUN make clean && make

# Runtime stage (smaller image)
FROM ubuntu:22.04

# Install only runtime dependencies
RUN apt-get update && apt-get install -y \
    libsfml-graphics3.0 \
    libsfml-window3.0 \
    libsfml-system3.0 \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy only the built executable
COPY --from=builder /app/GameOfLife /app/

# Create directory for output files
RUN mkdir -p input_out

# Copy example input file if it exists
# (Create input.txt manually or mount volume for custom input)

# Set permissions
RUN chmod +x GameOfLife

# Default command: run console mode
CMD ["./GameOfLife"]

# Metadata
LABEL maintainer="your.email@example.com"
LABEL version="1.1.0"
LABEL description="Conway's Game of Life - C++ OOP Project"

# Usage instructions:
# Build: docker build -t gameoflife:1.1.0 .
# Run:   docker run -it gameoflife:1.1.0
# Mount: docker run -v $(pwd)/input_out:/app/input_out gameoflife:1.1.0
