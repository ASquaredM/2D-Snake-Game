#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  enum class Mode { kEasy, kMedium, kHard, kUnPlayable, kInsaine, kWait, Exit};
  Game(std::size_t grid_width, std::size_t grid_height, Mode mode);
  void Run(Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  Mode _mode = Mode::kEasy;

private:
  Snake snake;
  Controller controller;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  bool running{true};
  int score{0};

  void PlaceFood();
  void Update();
};

#endif