#include "CurrModeHandler.h"

void CurrModeHandler::addMode(Mode * mode, Mode * nextMode)
{
  if(m_currMode == nullptr)
  {
    m_currMode = mode;
    m_currMode->init();
  }
  m_transitions.insert(std::make_pair(mode, nextMode));
}
void CurrModeHandler::checkTransitions()
{
  if(m_currMode->isFinished())
  {
    auto next = m_transitions.find(m_currMode);
    if(next != m_transitions.end())
    {
      m_currMode = next->second;
      m_currMode->init();
    }
  }
}