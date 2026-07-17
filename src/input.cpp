#include "headers/input.h"
#include "headers/common.h"
#include "headers/engine.h"
#include "headers/canvas.h"
#include <thread>

Engine print_engine;
Canvas print_canvas;

void Input::move_up() {
  parameters.min_yi -= 1.0L / zoom_level;
  parameters.max_yi -= 1.0L / zoom_level;
  cy = (parameters.min_yi + parameters.max_yi) / 2.0L;
}
void Input::move_right() {
  parameters.min_x += 1.0L / zoom_level;
  parameters.max_x += 1.0L / zoom_level;
  cx = (parameters.min_x + parameters.max_x) / 2.0L;
}
void Input::move_down() {
  parameters.min_yi += 1.0L / zoom_level;
  parameters.max_yi += 1.0L / zoom_level;
  cy = (parameters.min_yi + parameters.max_yi) / 2.0L;
}
void Input::move_left() {
  parameters.min_x -= 1.0L / zoom_level;
  parameters.max_x -= 1.0L / zoom_level;
  cx = (parameters.min_x + parameters.max_x) / 2.0L;
}
void Input::cycle_palettes() {
  palette_idx++;
  if (palette_idx > palettes.size() - 1) {
    palette_idx = 0;
  }

  parameters.a = palettes.at(palette_idx).a;
  parameters.b = palettes.at(palette_idx).b;
  parameters.c = palettes.at(palette_idx).c;
  parameters.d = palettes.at(palette_idx).d;
}
void Input::zoom_in() {
  zoom_level *= zoom;
  parameters.min_x = parameters.min_x - ((parameters.min_x - cx) - ((parameters.min_x - cx) / zoom));
  parameters.max_x = parameters.max_x - ((parameters.max_x - cx) - ((parameters.max_x - cx) / zoom));
  parameters.min_yi = parameters.min_yi - ((parameters.min_yi - cy) - ((parameters.min_yi - cy) / zoom));
  parameters.max_yi = parameters.max_yi - ((parameters.max_yi - cy) - ((parameters.max_yi - cy) / zoom));
}
void Input::zoom_out() {
  zoom_level /= zoom;
  parameters.min_x = parameters.min_x + (((parameters.min_x - cx) * zoom) - (parameters.min_x - cx));
  parameters.max_x = parameters.max_x + (((parameters.max_x - cx) * zoom) - (parameters.max_x - cx));
  parameters.min_yi = parameters.min_yi + (((parameters.min_yi - cy) * zoom) - (parameters.min_yi - cy));
  parameters.max_yi = parameters.max_yi + (((parameters.max_yi - cy) * zoom) - (parameters.max_yi - cy));
}
void Input::increase_iteration_depth() {
  parameters.iter_depth = static_cast<unsigned int>(static_cast<double>(parameters.iter_depth) * 1.1);
}
void Input::decrease_iteration_depth() {
  parameters.iter_depth = static_cast<unsigned int>(static_cast<double>(parameters.iter_depth) * 0.9);
  if (parameters.iter_depth < 10) {
    parameters.iter_depth = 10;
  }
}
void Input::get_info() {
  std::cout << "Iteration depth: " << parameters.iter_depth << std::endl;
  std::cout << "Zoom: " << zoom_level << std::endl;
  std::cout << "cx: " << cx << std::endl;
  std::cout << "cy: " << cy << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(5));
}
void Input::home() {
  parameters.min_x      = -2.8L;
  parameters.min_yi     = -1.4L;
  parameters.max_x      = 1.8L;
  parameters.max_yi     = 1.4L;
  parameters.iter_depth = 50;
  zoom_level            = 1.0L;
  cx                    = 0.0L;
  cy                    = 0.0L;
}
void Input::print() {
  print_engine.set_resolution(PRINT_WIDTH, PRINT_HEIGHT);
  std::vector<unsigned int> photo = print_engine.calculate(parameters.min_x, parameters.min_yi, parameters.max_x, parameters.max_yi, parameters.iter_depth);
  print_canvas.set_palette(parameters.a, parameters.b, parameters.c, parameters.d);
  print_canvas.print(photo, parameters.iter_depth, print_engine.magnitudes);
}


Input::Input() {}
Input::~Input() {}


bool Input::get_input() {
  char key;
  std::cin >> key;
  switch (key) {
    case('w'):
      move_up();
      break;
    case('a'):
      move_left();
      break;
    case('s'):
      move_down();
      break;
    case('d'):
      move_right();
      break;
    case('r'):
      cycle_palettes();
      break;
    case('f'):
      zoom_in();
      break;
    case('e'):
      zoom_out();
      break;
    case('c'):
      increase_iteration_depth();
      break;
    case('x'):
      decrease_iteration_depth();
      break;
    case('i'):
      get_info();
      break;
    case('h'):
      home();
      break;
    case('p'):
      print();
      break;
    case('q'):
      return true;
      break;
    // brightness
    case('1'):
      parameters.a.at(0) += 0.1;
      break;
    case('2'):
      parameters.a.at(1) += 0.1;
      break;
    case('3'):
      parameters.a.at(2) += 0.1;
      break;
    // contrast
    case('4'):
      parameters.b.at(0) += 0.1;
      break;
    case('5'):
      parameters.b.at(1) += 0.1;
      break;
    case('6'):
      parameters.b.at(2) += 0.1;
      break;
    // frequency
    case('7'):
      parameters.c.at(0) += 0.1;
      break;
    case('8'):
      parameters.c.at(1) += 0.1;
      break;
    case('9'):
      parameters.c.at(2) += 0.1;
      break;
    // hue shift
    case('0'):
      parameters.d.at(0) += 0.1;
      break;
    case('-'):
      parameters.d.at(1) += 0.1;
      break;
    case('='):
      parameters.d.at(2) += 0.1;
      break;
    // brightness
    case('!'):
      parameters.a.at(0) -= 0.1;
      break;
    case('@'):
      parameters.a.at(1) -= 0.1;
      break;
    case('#'):
      parameters.a.at(2) -= 0.1;
      break;
    // contrast
    case('$'):
      parameters.b.at(0) -= 0.1;
      break;
    case('%'):
      parameters.b.at(1) -= 0.1;
      break;
    case('^'):
      parameters.b.at(2) -= 0.1;
      break;
    // frequency
    case('&'):
      parameters.c.at(0) -= 0.1;
      break;
    case('*'):
      parameters.c.at(1) -= 0.1;
      break;
    case('('):
      parameters.c.at(2) -= 0.1;
      break;
    // hue shift
    case(')'):
      parameters.d.at(0) -= 0.1;
      break;
    case('_'):
      parameters.d.at(1) -= 0.1;
      break;
    case('+'):
      parameters.d.at(2) -= 0.1;
      break;
  }
  return false;
}

