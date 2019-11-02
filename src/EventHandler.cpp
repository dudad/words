#include "EventHandler.h"
#include <SDL2/SDL.h>

bool EventHandler::process()
{
  SDL_Event event;
  while (SDL_PollEvent(&event) == 1) {
    switch(event.type)
    {
      case SDL_QUIT:
        return true;
        break;
      case SDL_KEYDOWN:
        auto result = handlers.find(event.key.keysym.sym);
        if( result != handlers.end())
          result->second();
        else
        {
           if(event.key.keysym.sym == SDLK_ESCAPE)
            return true; 
        }
        
        break;
    }
  }
}

void EventHandler::registerMethod(int key, std::function<void()> func)
{
  handlers.insert(std::make_pair(key, func));
}