#include "headers/mandelbrot.h"

Mandelbrot::Mandelbrot() {}

Engine engine;
Canvas canvas;
Input input;

int Mandelbrot::run() {
  engine.set_resolution(TERM_WIDTH, TERM_HEIGHT*2);
  std::vector<unsigned int> render = engine.calculate(input.parameters.min_x, input.parameters.min_yi, input.parameters.max_x, input.parameters.max_yi, input.parameters.iter_depth);
  
  canvas.set_palette(input.parameters.a, input.parameters.b, input.parameters.c, input.parameters.d);
  canvas.display_terminal(render, input.parameters.iter_depth, engine.magnitudes);

  while (!input.get_input()) {
    render = engine.calculate(input.parameters.min_x, input.parameters.min_yi, input.parameters.max_x, input.parameters.max_yi, input.parameters.iter_depth);
    canvas.set_palette(input.parameters.a, input.parameters.b, input.parameters.c, input.parameters.d);
    canvas.display_terminal(render, input.parameters.iter_depth, engine.magnitudes);
  }
  return 0;
}
