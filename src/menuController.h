#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include <memory>
#include "game.h"

class MenuController {
 public:
  Game::Mode HandleInput() const;
};

#endif