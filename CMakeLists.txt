# A minimal CMake starter file for a simple C++ project
#
# Usage:
# 1. Configure: cmake -S. -Bbuild
# 2. Build: cmake --build build
# 3. Clean and build (optional): cmake --build build --clean-first
# 4. Run: ./build/lab (Unix) or build\Debug\lab.exe (Windows/MSVC)

# Specify the minimum CMake version required
cmake_minimum_required(VERSION 3.16)

# Define the project name, version, and language
project(DigitalSim
    VERSION 1.0
    DESCRIPTION "Digital electronics simulator"
    LANGUAGES CXX
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set C++ standard to 20 and enforce it
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Ensures the standard is required, not optional
set(CMAKE_CXX_EXTENSIONS OFF)        # Disable compiler-specific extensions (e.g., GNU extensions)
add_compile_options(/Zc:__cplusplus)
# MSVC-specific workaround for C++20 (if needed for older MSVC versions)
if(MSVC)
    set(CMAKE_CXX17_STANDARD_COMPILE_OPTION "-std:c++latest")
    set(CMAKE_CXX17_EXTENSION_COMPILE_OPTION "-std:c++latest")
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Define the executable and list source files
add_executable(${PROJECT_NAME}
    #main.cpp
    # Add additional source files here as needed, e.g.:
    # src/Student.cpp
    #in main folder
    "main.cpp"
    #in /include folder
    "include/Gate.h"
    "include/ANDGate.h"
    "include/ORGate.h"
    "include/Connector.h"
    "include/XORGate.h" 
    "include/NOTGate.h"
    "include/BufforGate.h"
    "include/Clock.h"
    "include/Module.h"
    #in /src folder
    "src/Module.cpp"
    "src/Gate.cpp"
    "src/Clock.cpp"
    "src/Connector.cpp"
    "src/ANDGate.cpp" 
    "src/ORGate.cpp" 
    "src/XORGate.cpp" "include/State.h" "include/Menu.h" "src/Menu.cpp")

# Specify include directories for header files
target_include_directories(${PROJECT_NAME} PRIVATE
    include/
)
target_link_libraries(DigitalSim PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
# Ensure the target uses C++20 features
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Print a status message to confirm configuration
# Display configuration status
message(STATUS "Project ${PROJECT_NAME} v${PROJECT_VERSION} configured")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
