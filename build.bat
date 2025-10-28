@echo off
setlocal

REM Check for 'clean' argument
if /i "%1"=="clean" (
    echo "Cleaning build directory..."
    if exist "build" (
        rmdir /s /q "build"
        echo "Build directory cleaned."
    ) else (
        echo "Build directory not found. Nothing to clean."
    )
    goto :eof
)

REM Create a build directory if it doesn't exist
if not exist "build" (
    echo "Creating build directory..."
    mkdir build
)

REM Navigate to the build directory
cd build

REM Configure the project using CMake. Using Ninja as the generator.
echo "Configuring project with CMake and Ninja..."
cmake -G "Ninja" ..

REM Check if CMake configuration was successful
if %errorlevel% neq 0 (
    echo "CMake configuration failed."
    exit /b %errorlevel%
)

REM Build the project using CMake
echo "Building project..."
cmake --build .

REM Check if build was successful
if %errorlevel% neq 0 (
    echo "Build failed."
    exit /b %errorlevel%
)

echo "Build successful!"

endlocal
