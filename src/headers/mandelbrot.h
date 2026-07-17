#pragma once

#include "common.h"
#include "engine.h"
#include "canvas.h"
#include "input.h"

class Mandelbrot {
  private:
  public:
    Mandelbrot();

    /// @brief orchestrates the program
    /// @return an int for error codes
    int run();
};
