#include "menuController.h"
#include <iostream>
#include "SDL.h"

Game::Mode MenuController::HandleInput() const {
  SDL_Event e;
  while (SDL_WaitEvent(&e)) {
    if (e.type == SDL_QUIT) {
      return Game::Mode::Exit;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_1:
          return Game::Mode::kEasy;
        case SDLK_2:
          return Game::Mode::kMedium;
        case SDLK_3:
          return Game::Mode::kHard;
        case SDLK_4:
          return Game::Mode::kUnPlayable;
        case SDLK_5:
          return Game::Mode::kInsaine;
        case SDLK_ESCAPE:
          return Game::Mode::Exit;
        default:
          return Game::Mode::kWait;
      }
    }
  }
}