#include "PaintEngine.h"
#include "game_config.h"

/**
 * @brief Construct a new Paint Engine:: Paint Engine object
 *
 * @param window_w  窗口宽
 * @param window_h  窗口高
 */

PaintEngine *PaintEngine::_instance = nullptr;
PaintEngine *PaintEngine::get_instance()
{
  if (!_instance)
  {
    _instance = new PaintEngine();
  }
  return _instance;
}

PaintEngine::PaintEngine()
{
  Game_config *game_config = Game_config::get_instance();
  SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  this->window = SDL_CreateWindow("snake game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game_config->window_w, game_config->window_h, SDL_WINDOW_OPENGL);
  this->render = SDL_CreateRenderer(this->window, -1, 0);
}
/**
 * @brief
 *
 * @param x  坐标x
 * @param y  坐标y
 * @param w  宽
 * @param h  高
 * @param fill  是否实心
 * @param r  三原色 红色
 * @param g
 * @param b
 * @param a  透明度
 */
void PaintEngine::paint_square(int x, int y, int w, int h, bool fill, int r, int g, int b, int a)
{
  SDL_SetRenderDrawColor(render, r, g, b, a);
  SDL_Rect rect = {x, y, w, h};
  if (!fill)
  {
    SDL_RenderDrawRect(render, &rect);
  }
  else
  {
    SDL_RenderFillRect(render, &rect);
  }
}

void PaintEngine::start_paint(std::function<void(direction)> evt_fun, std::function<void()> &paint_fun, function<int()> &is_quit, function<int()> &speed)
{
  int running = 1;
  while (running)
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        running = 0;
      }
      if (event.type == SDL_KEYDOWN)
      {
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
          evt_fun(direction::up);
          break;
        case SDLK_s:
          evt_fun(direction::down);
          break;
        case SDLK_d:
          evt_fun(direction::right);
          break;
        case SDLK_a:
          evt_fun(direction::left);
          break;
        }
      }
    }

    paint_fun();
    if (is_quit())
    {
      running = 0;
      quit();
    }
    SDL_RenderPresent(this->render);
    SDL_Delay(speed());
  }
}
void PaintEngine::quit()
{
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  SDL_Quit();
}