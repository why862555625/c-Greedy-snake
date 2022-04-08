#pragma once

#include <vector>
class Drawable
{
public:
  virtual void paint() = 0;
};
/**
 * @brief  节点类
 *
 */
class Node : public Drawable
{
public:
  int logic_x;
  int logic_y;
  std::vector<int> color;
  Node(int x, int y);
  void paint();
  void delete_node();
};

class Snake_node : public Node
{
public:
  Snake_node(int x, int y);
};
class Food_node : public Node
{
public:
  Food_node(int x, int y);
};
class Wall_node : public Node
{
public:
  Wall_node(int x, int y);
};