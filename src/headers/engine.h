#pragma once
#include <vector>

class Engine {
  private:
    unsigned int _x_pixels;
    unsigned int _y_pixels;

    /// @brief parses the input min and max x/y
    /// @param min_x the lowest x value the calculation will be done for
    /// @param min_yi the lowest yi value the calculation will be done for
    /// @param max_x the maximum x value the calculation will be done for
    /// @param max_yi the maximum yi value the calculation will be done for
    /// @return a grid of points to do the calculation on
    std::vector<std::pair<long double, long double>> parse(long double min_x, long double min_yi, long double max_x, long double max_yi);

    /// @brief does the calculation for the mandelbrot fractal
    /// @param x the x point for the calculation
    /// @param yi the yi point for the calculation
    /// @param iter_depth the maximum iterations to use when calculating
    /// @return the amount of iterations it took to escape, if it does in the specified iter_depth
    unsigned int calculate_point(long double x, long double yi, unsigned int iter_depth);

  public:
    Engine();
    ~Engine();

    std::vector<double> magnitudes;

    /// @brief the main calculator for how many iterations it takes for a point to 'escape'
    /// @param min_x the lowest x value the calculation will be done for
    /// @param min_yi the lowest yi value the calculation will be done for
    /// @param max_x the maximum x value the calculation will be done for
    /// @param max_yi the maximum yi value the calculation will be done for
    /// @param iter_depth the maximum iterations to use when calculating
    /// @return a vector of how many iterations each point took to escape
    std::vector<unsigned int> calculate(long double min_x, long double min_yi, long double max_x, long double max_yi, unsigned int iter_depth);

    /// @brief set sthe resolution in {X}x{Y} pixels on the terminal or photo
    /// @param x_pixels the amount of pixels we're rendering in the x direction
    /// @param y_pixels the amount of pixels we're rendering in the y direction
    void set_resolution(unsigned int x_pixels, unsigned int y_pixels);
};
