#include <iostream>
#include <thread>
#include "startMenu.h"
#include "SDL.h"

StartMenu::StartMenu(std::size_t grid_width, std::size_t grid_height)
    : grid_width(grid_width),
      grid_height(grid_height) {}

std::unique_ptr<Game> StartMenu::Run(Renderer &renderer,
           std::size_t target_frame_duration){
  renderer.RenderMenu();
  Game::Mode mode = Game::Mode::kWait;
  while (mode == Game::Mode::kWait){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    mode = menucontroller.HandleInput();
  }
  game = std::make_unique<Game>(grid_width,grid_height,mode);

  return std::move(game);
}