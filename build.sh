#!/bin/bash
set -e

# Check for 'clean' argument
if [ "$1" = "clean" ]; then
    echo "Cleaning build directory..."
    if [ -d "build" ]; then
        rm -rf "build"
        echo "Build directory cleaned."
    else
        echo "Build directory not found. Nothing to clean."
    fi
    exit 0
fi

# Create a build directory if it doesn't exist
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

# Navigate to the build directory
cd build

# Configure the project using CMake. Using Ninja as the generator.
echo "Configuring project with CMake and Ninja..."
cmake -G "Ninja" ..

# Build the project using CMake
echo "Building project..."
cmake --build .

echo "Build successful!"
