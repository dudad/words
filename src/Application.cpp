#include "Application.h"

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768

void Application::Init()
{
  font_path = "FreeSans.ttf";
  SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &m_window, &m_renderer);
  SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
  TTF_Init();
}

void Application::Release()
{
  TTF_Quit();

  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void Application::mainLoop(EventHandler & eventHadler, CurrModeHandler & currModeHandler)
{
  Init();

  bool bQuit = false;
  while (!bQuit)
  {
    bQuit = eventHadler.process();
    currModeHandler.checkTransitions();

    clear();
    currModeHandler.render(*this);
    present();
  }

  Release();
}

void Application::clear()
{
  SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);
  SDL_RenderClear(m_renderer);
}

void Application::renderText(const std::string txt, int fontSize, int x, int y)
{
  SDL_Texture *texture;
  SDL_Rect rect;
  auto font = m_fonts.find(fontSize);
  if(font == m_fonts.end())
    font = m_fonts.insert(std::make_pair(fontSize, TTF_OpenFont(font_path.c_str(), fontSize))).first;

  getTextAndRect(txt.c_str(), font->second, &texture, &rect);
  
  rect.x = x < 0 ? (WINDOW_WIDTH - rect.w)/2 : x;
  rect.y = y < 0 ? (WINDOW_HEIGHT - rect.h)/2 : y;

  SDL_RenderCopy(m_renderer, texture, NULL, &rect);
  SDL_DestroyTexture(texture);
}

void Application::present()
{
  SDL_RenderPresent(m_renderer);
  SDL_Delay(30);
}        

void Application::getTextAndRect(const char *text, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) 
{
  SDL_Color textColor = {0, 0, 0, 0};

  SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, textColor);
  *texture = SDL_CreateTextureFromSurface(m_renderer, surface);  
  
  rect->x = 0;
  rect->y = 0;
  rect->w = surface->w;
  rect->h = surface->h;
  SDL_FreeSurface(surface);
}