#pragma once

#include "common.h"
#include "engine.h"
#include "canvas.h"
#include "input.h"
#include <sys/ioctl.h>
#include <unistd.h>

class Mandelbrot {
  private:
  public:
    Mandelbrot();

    /// @brief orchestrates the program
    /// @return an int for error codes
    int run();

    /// @brief reads terminal size and sets macros accordingly
    void read_terminal_size();
};
