#pragma once

#include "Mode.h"

class CurrModeHandler
{
public:
  CurrModeHandler() : m_currMode(nullptr) {}
  void addMode(Mode * mode, Mode * nextMode);
  void checkTransitions();
  void render(IRender & render){ m_currMode->render(render); }
  
private:
  Mode* m_currMode;
  std::map<Mode *, Mode *> m_transitions;
};