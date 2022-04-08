#pragma once

#include <list>
#include <vector>
#include "draw.h"
#include "game_config.h"
using namespace std;
enum class check_result
{
  noting,
  eat_food,
  deat
};
enum class direction
{
  up,
  down,
  left,
  right,
};
class Snake
{
public:
  direction dir = direction::right;
  list<Snake_node> snake_list;
  Snake();
  void paint();
  void move();
  check_result check(Food_node *food_node);

private:
  bool is_eat = false;
};
class Game
{
public:
  Food_node *food_node;
  Snake *snake;
  void create_food();
  Game();
  int quit();
  void create_bg();
  void run();
  void update_status();
  void change_direction(direction d);
  int get_snake_speed();
private:
  check_result status;
};
