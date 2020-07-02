#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  // Initialize SDL_ttf
  if (TTF_Init() == -1) {
    std::cerr << "SDL_TTF could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  _font = TTF_OpenFont("../res/INVASION2000.TTF", 28);
  // If there was an error in loading the font
  if (_font == NULL) {
    std::cerr << "Font could not be loaded.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  _font2 = TTF_OpenFont("../res/lazy.ttf", 28);
  // If there was an error in loading the font
  if (_font2 == NULL) {
    std::cerr << "Font2 could not be loaded.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

// Used the following stackoverflow answer https://stackoverflow.com/a/48291620/13637969
void Renderer::DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
   const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0, 255, 0x00, 0xFF);
  int x = (food.x * block.w) + 7;
  int y = (food.y * block.h) + 7;
  DrawCircle(sdl_renderer,x,y,7);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.isAlive()) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::RenderMenu(){
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
  
  SDL_Color White = {255, 255, 255};  // this is the color in rgb format,
                                      // maxing out all would give you the color white, and it will be your text's color

  DrawText("Snake x Destroyer x X2020X",312,251,625,100,_font,White);
  DrawText("Choose Difficulty",250,100,500,50,_font2,White);
  DrawText("[1] Easy",75,25,150,50,_font2,White);
  DrawText("[2] Medium",75,-25,150,50,_font2,White);
  DrawText("[3] Hard",75,-75,150,50,_font2,White);
  DrawText("[4] UnPlayable",100,-125,201,50,_font2,White);
  DrawText("[5] Bro!! U Insaine?!",150,-175,301,50,_font2,White);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::DrawText(const char* string,int dx,int dy,int w,int h,TTF_Font *font,SDL_Color color){
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, string, color); // as TTF_RenderText_Solid could only be used on SDL_Surface
                                                                                // then you have to create the surface first

  SDL_Texture* Message = SDL_CreateTextureFromSurface(sdl_renderer, surfaceMessage); //now you can convert it into a texture

  SDL_Rect Message_rect; //create a rect
  Message_rect.x = (screen_width / 2) - dx;  //controls the rect's x coordinate 
  Message_rect.y = (screen_height / 2) - dy; // controls the rect's y coordinte
  Message_rect.w = w; // controls the width of the rect
  Message_rect.h = h; // controls the height of the rect

  //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understand

  //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

  SDL_RenderCopy(sdl_renderer, Message, NULL, &Message_rect); // you put the renderer's name first, the Message, the crop size
                                                              // (you can ignore this if you don't want to dabble with cropping),
                                                              // and the rect which is the size and coordinate of your texture
}

void Renderer::RenderGO(){
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
  
  SDL_Color White = {255, 255, 255};  // this is the color in rgb format,
                                      // maxing out all would give you the color white, and it will be your text's color

  DrawText("Game Over",312,50,625,100,_font,White);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}