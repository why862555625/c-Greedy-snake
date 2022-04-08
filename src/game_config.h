#pragma once
class Game_config
{
public:
  static Game_config *get_instance();
  int real_w;
  int real_h;
  int window_w;
  int window_h;
  int cell_size = 20;
  int margin = 50;
  int logic_w = 60;
  int logic_h = 40;

private:
  static Game_config *_instance;
  Game_config();
  ~Game_config();
};

class Game_state
{
private:
  int speed_weight = 1000;

public:
  int get_speed(int len);
};
