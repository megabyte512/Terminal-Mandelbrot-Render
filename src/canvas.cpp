#include "headers/canvas.h"
#include "headers/common.h"

std::vector<std::pair<unsigned int, unsigned int>> Canvas::parse(std::vector<unsigned int> pixels) {
  std::vector<std::pair<unsigned int, unsigned int>> pixel_pairs;

  // iterates over every other row of pixels and builds the pixel pair vector
  for (unsigned int row = 0; row < TERM_HEIGHT*2; row += 2) {
    for (unsigned int col = 0; col < TERM_WIDTH; col++) {
      // not very clear, sorry (to whoever is reading this)
      // this line builds the pairs by using the top row (of each cursor char) for the first element and the bottom row for the second
      pixel_pairs.push_back(std::pair<unsigned int, unsigned int>(pixels.at(row*TERM_WIDTH + col), pixels.at((row + 1)*TERM_WIDTH + col)));
    }
  }

  return pixel_pairs;
}

std::vector<std::pair<double, double>> Canvas::parse_magnitudes(std::vector<double> magnitudes) {
  std::vector<std::pair<double, double>> magnitude_pairs;

  // iterates over every other row of pixels and builds the pixel pair vector
  for (unsigned int row = 0; row < TERM_HEIGHT*2; row += 2) {
    for (unsigned int col = 0; col < TERM_WIDTH; col++) {
      // not very clear, sorry (to whoever is reading this)
      // this line builds the pairs by using the top row (of each cursor char) for the first element and the bottom row for the second
      magnitude_pairs.push_back(std::pair<double, double>(magnitudes.at(row*TERM_WIDTH + col), magnitudes.at((row + 1)*TERM_WIDTH + col)));
    }
  }

  return magnitude_pairs;
}

Canvas::RGB Canvas::calculate_color(unsigned int escape, unsigned int iter_depth, double magnitude) {
  double mu = static_cast<double>(escape) - std::log2(std::log2(magnitude));
  double t = mu / static_cast<double>(iter_depth);
  // double t = static_cast<double>(escape) / static_cast<double>(iter_depth);
  double intensity;

  // sinusoiodal palette generation: intensity(i) = a + b * cos(2pi(c * t + d))
  // red
  intensity = palette.a[0] + palette.b[0] * (std::cos(2.0*M_PI * (palette.c[0] * t + palette.d[0])));
  intensity = std::clamp(intensity, 0.0, 1.0);
  color.r = static_cast<int>(255.0 * intensity);

  // green
  intensity = palette.a[1] + palette.b[1] * (std::cos(2.0*M_PI * (palette.c[1] * t + palette.d[1])));
  intensity = std::clamp(intensity, 0.0, 1.0);
  color.g = static_cast<int>(255.0 * intensity);

  // blue
  intensity = palette.a[2] + palette.b[2] * (std::cos(2.0*M_PI * (palette.c[2] * t + palette.d[2])));
  intensity = std::clamp(intensity, 0.0, 1.0);
  color.b = static_cast<int>(255.0 * intensity);

  return color;
}

Canvas::Canvas() {
  std::cout << HIDE_CURSOR;
  std::cout << CURSOR_HOME;
  std::cout << CLEAR_SCREEN;
  std::cout << AUTOWRAP_OFF;
}

Canvas::~Canvas() {
  std::cout << SHOW_CURSOR;
  std::cout << RESET_COLOR;
  std::cout << AUTOWRAP_ON;
}


void Canvas::display_terminal(std::vector<unsigned int> pixels, unsigned int iter_depth, std::vector<double> magnitudes) {
  std::vector<std::pair<unsigned int, unsigned int>> pixel_pairs = parse(pixels);
  std::vector<std::pair<double, double>> magnitude_pairs = parse_magnitudes(magnitudes);

  // this loop iterates over every pixel and decides what to color it
  for (unsigned int i = 0; i < pixel_pairs.size(); i++) {
    // top row
    if (pixel_pairs.at(i).first == iter_depth) {  // if in set 
      std::cout << FOREGROUND << "0;0;0m";
    } else {                                      // if escaped
      color = calculate_color(pixel_pairs.at(i).first, iter_depth, magnitude_pairs.at(i).first);
      std::cout << FOREGROUND << color.r << ";" << color.g << ";" << color.b << "m";
    }

    // bottom row
    if (pixel_pairs.at(i).second == iter_depth) { // if in set
      std::cout << BACKGROUND << "0;0;0m";
    } else {                                      // if escaped
      color = calculate_color(pixel_pairs.at(i).second, iter_depth, magnitude_pairs.at(i).second);
      std::cout << BACKGROUND << color.r << ";" << color.g << ";" << color.b << "m";
    }

    std::cout << UPPER;
    std::cout << RESET_COLOR;

    // move to next line if necessary
    if ((i+1) % TERM_WIDTH == 0) {
      std::cout << '\n';
    }
  }
  std::cout << std::flush;
  std::cout << CURSOR_HOME;
}


void Canvas::print(std::vector<unsigned int> pixels, unsigned int iter_depth, std::vector<double> magnitudes) {
  std::ofstream ofs("mandelbrot.ppm", std::ios_base::binary);
  ofs << "P6\n" << PRINT_WIDTH << ' ' << PRINT_HEIGHT << "\n255\n";

  for (unsigned int i = 0; i < pixels.size(); i++) {
    if (pixels.at(i) == iter_depth) {
      ofs << static_cast<char>(0) << static_cast<char>(0) << static_cast<char>(0);
    } else {
      color = calculate_color(pixels.at(i), iter_depth, magnitudes.at(i));
      ofs << static_cast<char>(color.r) << static_cast<char>(color.g) << static_cast<char>(color.b);
    }
  }
  ofs.flush();
  ofs.close();
}


void Canvas::set_palette(std::vector<double> a, std::vector<double> b, std::vector<double> c, std::vector<double> d) {
  palette.a = a;
  palette.b = b;
  palette.c = c;
  palette.d = d;
}
