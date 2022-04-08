#include "game_config.h"
Game_config *Game_config::_instance = nullptr;
Game_config *Game_config::get_instance()
{
  if (_instance == nullptr)
  {
    _instance = new Game_config();
  }
  return _instance;
}
Game_config::Game_config()
{
/*   logic_w = real_w / cell_size;
  logic_h = real_h / cell_size; */
  real_w = cell_size * logic_w;
  real_h = cell_size * logic_h;
  window_w = cell_size * logic_w + margin * 2;
  window_h = cell_size * logic_h + margin * 2;
};
Game_config::~Game_config()
{
  if (_instance)
  {
    delete _instance;
  }
}

int Game_state::get_speed(int len)
{
  return speed_weight / len;
}