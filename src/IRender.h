#pragma once

#include <string>

class IRender
{
public:
  virtual void renderText(const std::string txt, int fontSize, int x, int y) = 0;
};