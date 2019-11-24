# =================================
# project definition
# =================================
cmake_minimum_required(VERSION 3.13)
project(secret-santa VERSION 1.0.0)

# =================================
# toolchain configuration
# =================================
set(CMAKE_CXX_STANDARD 17)

# =================================
# external deps
# =================================
add_subdirectory(vendor)

# =================================
# subfolders
# =================================
add_subdirectory(secret-santa)
