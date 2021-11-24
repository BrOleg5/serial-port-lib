# Serial Port Library

Library was created to write and read bytes by Serial Port. Windows only.

## Requirements

- CMake v3.0 or later
- OpenRobotinoAPI v1.8.31 or later
- MSVC v19 or later

## Configure, build and install library

Command shell or PowerShell will be run as administrator to install library in system partition.

### Windows 10 x86

```
# Create build directory
mkdir build

# Configure as static library
cmake -S serial-port/ -B build/ -G "Visual Studio 15"

# Build
cmake --build build/

# Install
sudo cmake --install build/
```

### Windows 10 x64

```
# Create build directory
mkdir build

# Configure as static library
cmake -S serial-port/ -B build/ -G "Visual Studio 15 Win64"

# Build
cmake --build build/

# Install
sudo cmake --install build/
```

## Using Serial Port library with CMake

Add this strings in your CMakeLists.txt file:
```
find_package(SerialPort 1.0 REQUIRED)
target_link_libraries(<ProjectName> SerialPortLib)
# if nessesary, add include directories to target
target_include_directories(<ProjectName> ${SerialPort_INCLUDE_DIRS})
```