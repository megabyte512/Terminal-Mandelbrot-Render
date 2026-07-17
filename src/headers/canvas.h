#pragma once
#include "common.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>

constexpr const char* UPPER           = "\u2580";
constexpr const char* FOREGROUND      = "\x1b[38;2;";   // don't forget the 'm' at the end
constexpr const char* BACKGROUND      = "\x1b[48;2;";   // don't forget the 'm' at the end
constexpr const char* HIDE_CURSOR     = "\x1b[?25l";
constexpr const char* SHOW_CURSOR     = "\x1b[?25h";
constexpr const char* CLEAR_SCREEN    = "\x1b[2J";
constexpr const char* CURSOR_HOME     = "\x1b[H";
constexpr const char* RESET_COLOR     = "\x1b[0m";
constexpr const char* ALT_SCREEN_ON   = "\x1b[?1049h";  // save screen, switch to alt buffer
constexpr const char* ALT_SCREEN_OFF  = "\x1b[?1049l";  // restore original screen
constexpr const char* AUTOWRAP_ON     = "\x1b[?7h";
constexpr const char* AUTOWRAP_OFF    = "\x1b[?7l";

class Canvas {
  private:
    struct RGB {
      int r, g, b;
    };
    RGB color;
    struct Palette {
      std::vector<double> a;
      std::vector<double> b;
      std::vector<double> c;
      std::vector<double> d;
    };
    Palette palette;

    /// @brief splits the 1-dimensional vector into pixel pairs, top and bottom for the foreground/background
    /// @param pixels the vector of pixels / escape times
    /// @return pixel pairs for easy printing (top/bottom)
    std::vector<std::pair<unsigned int, unsigned int>> parse(std::vector<unsigned int> pixels);

    /// @brief calculates the color of a pixel
    /// @param escape the pixel's iterataions to escape
    /// @param iter_depth how many times we're willing to iterate
    /// @param magnitude the magnitudes at the time of escape for color smoothing
    /// @return a struct of type RGB which contains the rgb values for the pixel
    RGB calculate_color(unsigned int escape, unsigned int iter_depth, double magnitude);
  public:
    Canvas();
    ~Canvas();

    /// @brief displays the iterations-per-point in the terminal visualized with a color
    /// @param pixels a vector of pixels to display, by their escape time
    /// @param iter_depth the iteration depth (needed for nice coloring)
    /// @param magnitudes the vector of magnitudes used for color smoothing
    void display_terminal(std::vector<unsigned int> pixels, unsigned int iter_depth, std::vector<double> magnitudes);

    /// @brief prints the pixels to .ppm
    /// @param pixels a vector of pixels to display, by their escape time 
    /// @param iter_depth the iteration depth (needed for nice coloring)
    /// @param magnitudes the vector of magnitudes used for color smoothing
    void print(std::vector<unsigned int> pixels, unsigned int iter_depth, std::vector<double> magnitudes);

    /// @brief sets the palette for the render
    /// @param a a length 3 (rgb) vector describing the BRIGHTNESS of each component
    /// @param b a length 3 (rgb) vector describing the CONTRAST of each component
    /// @param c a length 3 (rgb) vector describing the FREQUENCY of each component
    /// @param d a length 3 (rgb) vector describing the HUE SHIFT of each component
    void set_palette(std::vector<double> a, std::vector<double> b, std::vector<double> c, std::vector<double> d);
};
