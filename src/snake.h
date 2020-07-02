#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, float speed)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2),
        speed(speed) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);
  void setlife(bool life);
  bool isAlive() const;

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  bool alive{true};
  int grid_width;
  int grid_height;
};

#endif