#include "headers/engine.h"

std::vector<std::pair<long double, long double>> Engine::parse(long double min_x, long double min_yi, long double max_x, long double max_yi) {
  std::vector<std::pair<long double, long double>> grid;

  long double x_step = (max_x - min_x) / (_x_pixels - 1);
  long double yi_step = (max_yi - min_yi) / (_y_pixels - 1);

  // creating grid from min, max, and step
  for (unsigned int j = 0; j < _y_pixels; j++) {
    for (unsigned int i = 0; i < _x_pixels; i++) {
      long double x = min_x + (i * x_step);
      long double y = min_yi + (j * yi_step);
      grid.push_back(std::pair<long double, long double>(x, y));
    }
  }

  return grid;
}


unsigned int Engine::calculate_point(long double x, long double yi, unsigned int iter_depth) {
  long double tmp;
  long double Zr = 0;
  long double Zi = 0;
  unsigned int iter = 0;

  // as long as we haven't escaped or reached our max calculations, keep iterating and calculating the point
  while (Zr*Zr + Zi*Zi <= 4 && iter < iter_depth) {
    tmp = Zr*Zr - Zi*Zi + x;
    Zi = 2*Zr*Zi + yi;
    Zr = tmp;
    iter++;
  }
  double magnitude = Zr*Zr + Zi*Zi;
  magnitudes.push_back(magnitude);

  return iter;
}


Engine::Engine() {}
Engine::~Engine() {}


std::vector<unsigned int> Engine::calculate(long double min_x, long double min_yi, long double max_x, long double max_yi, unsigned int iter_depth) {
  std::vector<unsigned int> escape_vector;
  std::vector<std::pair<long double, long double>> grid = parse(min_x, min_yi, max_x, max_yi);
  escape_vector.clear();
  magnitudes.clear();

  // building the main return vector
  // for every (x, y) pair in the grid, push to return vector
  for (std::pair<long double, long double> pair : grid) {
    escape_vector.push_back(calculate_point(pair.first, pair.second, iter_depth));
  }

  return escape_vector;
}


void Engine::set_resolution(unsigned int x_pixels, unsigned int y_pixels) {
  _x_pixels = x_pixels;
  _y_pixels = y_pixels;
}
