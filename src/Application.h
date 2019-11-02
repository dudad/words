#pragma once

#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>

#include "IRender.h"
#include "EventHandler.h"
#include "CurrModeHandler.h"

class Application : public IRender
{
public:
  Application(){}
  void Init();
  void Release();
  void mainLoop(EventHandler & eventHadler, CurrModeHandler & currModeHandler);

  // render
  void clear();
  void renderText(const std::string txt, int fontSize, int x, int y);
  void present();
  void getTextAndRect(const char *text, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect);
  

private:
  SDL_Renderer *m_renderer;
  SDL_Window *m_window;
  std::string font_path;
  std::map<unsigned int, TTF_Font *> m_fonts;
};