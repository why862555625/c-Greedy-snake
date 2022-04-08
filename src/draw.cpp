#include "draw.h"
#include "PaintEngine.h"
#include "game_config.h"
Node::Node(int x, int y) : logic_x(x), logic_y(y)
{
}
void Node::paint()
{
  Game_config *game_config = Game_config::get_instance();
  PaintEngine *paint_engine = PaintEngine::get_instance();
  paint_engine->paint_square(logic_x * game_config->cell_size + game_config->margin, logic_y * game_config->cell_size + game_config->margin, game_config->cell_size, game_config->cell_size, true, color[0], color[1], color[2], 1);
}

void Node::delete_node()
{
  Game_config *game_config = Game_config::get_instance();
  PaintEngine *paint_engine = PaintEngine::get_instance();
  paint_engine->paint_square(logic_x * game_config->cell_size + game_config->margin, logic_y * game_config->cell_size + game_config->margin, game_config->cell_size, game_config->cell_size, true, 0, 0, 0, 1);
}

Snake_node::Snake_node(int x, int y) : Node(x, y)
{
  this->color = {0, 0, 255};
}
Food_node::Food_node(int x, int y) : Node(x, y)
{
  this->color = {0, 255, 0};
}
Wall_node::Wall_node(int x, int y) : Node(x, y)
{
  this->color = {123, 123,221};
}