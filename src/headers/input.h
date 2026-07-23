#pragma once
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>

class Input {
  private:
    termios orig_termios;
    long double zoom = 2.0L;
    long double zoom_level = 1.0L;
    long double cx = 0.0L;
    long double cy = 0.0L;

    struct Palette {
      std::vector<double> a;  // brightness
      std::vector<double> b;  // contrast
      std::vector<double> c;  // frequency
      std::vector<double> d;  // hue shift
    };

    std::vector<Palette> palettes = {
      {{0.6, 0.6, 0.6}, {0.7, 0.7, 0.7}, {2.0, 2.0, 2.0}, {0.67, 0.33, 0.00}},  // classic
      {{0.8, 0.4, 0.6}, {0.7, 0.7, 0.7}, {10.0, 10.0, 10.0}, {0.00, 0.33, 0.67}},  // rainbow
      {{0.6, 0.6, 0.6}, {0.4, 0.4, 0.4}, {1.0, 1.0, 1.0}, {0.00, 0.00, 0.00}},  // black and white
      {{0.5, 0.0, 0.0}, {-0.7, 0.0, 0.0}, {2.0, 2.0, 2.0}, {0.67, 0.33, 0.00}}, // red
      {{0.0, 0.6, 0.0}, {0.0, 0.5, 0.0}, {2.0, 2.0, 2.0}, {0.67, 0.33, 0.00}},  // green
      {{0.0, 0.0, 0.6}, {0.0, 0.0, 0.4}, {2.0, 2.0, 2.0}, {0.67, 0.33, 0.00}},  // blue
      {{0.3, 0.3, 0.3}, {0.8, 0.8, 0.8}, {3.0, 3.0, 3.0}, {0.00, 0.00, 0.00}}
    };
    unsigned int palette_idx = 0;

    // @brief moves window up based on zoom level
    void move_up();
    /// @ brief moves window right based on zoom level
    void move_right();
    /// @brief moves window down based on zoom level
    void move_down();
    /// @brief moves window left based on zoom level
    void move_left();
    /// @brief zooms window in
    void zoom_in();
    /// @brief zooms window out
    void zoom_out();

    /// @brief cycles palette presets
    void cycle_palettes();

    /// @brief increases iteration depth
    void increase_iteration_depth();
    /// @brief decreases iteration depth
    void decrease_iteration_depth();

    /// @brief prints info about center x/y, iteration count, etc.
    void get_info();

    /// @brief goes back to default window
    void home();

    /// @brief prints to file
    void print();

  public:
    Input();
    ~Input();

    struct Params {
      long double min_x       = -2.8L;
      long double min_yi      = -1.4L;
      long double max_x       = 1.8L;
      long double max_yi      = 1.4L;
      unsigned int iter_depth = 50;
      std::vector<double> a   = {0.6, 0.6, 0.6};
      std::vector<double> b   = {0.7, 0.7, 0.7};
      std::vector<double> c   = {2.0, 2.0, 2.0};
      std::vector<double> d   = {0.67, 0.33, 0.00};
    }; 
    Params parameters;

    /// @brief main function called by loop, handles all input
    /// @return true when quit 'q' pressed
    bool get_input();
};
