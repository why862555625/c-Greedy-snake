#include "game.h"
#include "PaintEngine.h"
#include <cstdlib>
#include <functional>
Snake::Snake()
{
  Game_config *config = Game_config ::get_instance();
  for (int i = 0; i < 3; i++)
  {
    snake_list.push_back(Snake_node(config->logic_w / 2 - i, /* config->logic_h / 2 */ 0));
  }
}
void Snake::paint()
{
  for (auto &node : this->snake_list)
  {
    node.paint();
  }
}

void Snake::move()
{
  auto head = snake_list.front();
  switch (dir)
  {
  case direction::up:
    snake_list.push_front(Snake_node(head.logic_x, head.logic_y - 1));
    break;
  case direction::down:
    snake_list.push_front(Snake_node(head.logic_x, head.logic_y + 1));
    break;
  case direction::left:
    snake_list.push_front(Snake_node(head.logic_x - 1, head.logic_y));
    break;
  case direction::right:
    snake_list.push_front(Snake_node(head.logic_x + 1, head.logic_y));
    break;
  };
  snake_list.front().paint();
  if (this->is_eat)
  {
    this->is_eat = false;
    return;
  }
  auto end_node = snake_list.back();
  end_node.delete_node();
  snake_list.pop_back();
}

check_result Snake::check(Food_node *food_node)
{
  auto head_node = snake_list.front();
  if (food_node->logic_x == head_node.logic_x && food_node->logic_y == head_node.logic_y)
  {
    is_eat = true;
    return check_result::eat_food;
  };

  int num = 0;
  Game_config *config = Game_config::get_instance();
  auto first_node = snake_list.front();
  if ((first_node.logic_x >= config->logic_w) || (first_node.logic_y >= config->logic_h) || (first_node.logic_x < 0) || (first_node.logic_y < 0))
  {
    return check_result::deat;
  }

  for (auto &s : snake_list)
  {
    if (num == 0)
    {
      num += 1;
      continue;
    }
    if ((s.logic_x == head_node.logic_x && s.logic_y == head_node.logic_y))
    {
      return check_result::deat;
    }
  }
  return check_result::noting;
}

Game::Game()
{
  snake = new Snake();
}

void Game::create_bg()
{
  Game_config *config = Game_config::get_instance();
  PaintEngine *p = PaintEngine ::get_instance();
  p->paint_square(config->margin - 1, config->margin - 1, config->real_w + 2, config->real_h + 2, false, 255, 0, 0, 1);
}

void Game::create_food()
{
  Game_config *config = Game_config::get_instance();
  int is_repeat = 1;
  //避免在蛇的身体里
  int x, y;
  do
  {
    x = int((rand() % config->logic_w));
    y = int((rand() % config->logic_h));
    for (auto &s : snake->snake_list)
    {

      if (s.logic_x == x && s.logic_y == y)
      {
        is_repeat = 1;
        break;
      }
      is_repeat = 0;
    }

  } while (is_repeat);
  food_node = new Food_node(x, y);
  food_node->paint();
}

void Game::change_direction(direction d)
{
  if ((d == direction::left && snake->dir == direction::right) || (d == direction::right && snake->dir == direction::left) ||
      (d == direction::up && snake->dir == direction::down) || (d == direction::down && snake->dir == direction::up))
    return;
  snake->dir = d;
}

int Game::quit()
{
  if (check_result::deat == status)
  {
    return 1;
  }
  return 0;
}
void Game::update_status()
{
  create_bg();
  snake->move();
  snake->paint();
  if (!food_node)
  {
    create_food();
  }
  status = snake->check(food_node);
  if (status == check_result::eat_food)
  {
    food_node = nullptr;
  }
}
int Game::get_snake_speed()
{
  int len = 0;
  for (auto s : snake->snake_list)
  {
    len++;
  }
  return 1000/len;
}

void Game::run()
{
  PaintEngine *p = PaintEngine::get_instance();
  auto evt_func = bind(&Game::change_direction, this, std::placeholders::_1);
  function<void()> paint_fun = bind(&Game::update_status, this);
  function<int()> is_quit = bind(&Game::quit, this);
  function<int()> speed = bind (&Game::get_snake_speed,this);
  p->start_paint(evt_func, paint_fun, is_quit, speed);
}