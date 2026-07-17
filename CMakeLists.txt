cmake_minimum_required(VERSION 3.28.3)
project(mandelbrot VERSION 1.0 LANGUAGES CXX)

set(SRC_FILES
  src/main.cpp
  src/mandelbrot.cpp
  src/engine.cpp
  src/canvas.cpp
  src/input.cpp
)

add_executable(mandelbrot ${SRC_FILES})
