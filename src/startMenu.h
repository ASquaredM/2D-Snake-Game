#ifndef STARTMENU_H
#define STARTMENU_H

#include <memory>
#include "SDL.h"
#include "menuController.h"
#include "renderer.h"
#include "game.h"

class StartMenu {
public:
  StartMenu(std::size_t grid_width, std::size_t grid_height);
  std::unique_ptr<Game> Run(Renderer &renderer,
                            std::size_t target_frame_duration);

private:
  MenuController menucontroller;
  std::unique_ptr<Game> game;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif