#pragma once
#include <map>
#include <string>
#include "game.h"

using namespace std;
#include <SDL.h>
#include <functional>
class PaintEngine
{
private:
  SDL_Window *window;
  SDL_Renderer *render;
  PaintEngine();
  static PaintEngine *_instance;

public:
  static PaintEngine *get_instance();
  static const map<string, int[]> color;
  void paint_square(int x, int y, int w, int h, bool fill, int r, int g, int b, int a);
  void start_paint(std::function<void(direction)> evt_fn, std::function<void()> &paint,  function<int()> &is_quit, function<int()> &speed);
  void quit();
};
