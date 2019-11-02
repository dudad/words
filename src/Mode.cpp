#include "Mode.h"

#include <algorithm>
#include <sstream>

void Mode::init()
{
  m_bFinished = false;
  m_eventHandler.unregisterAll();
  onInit(m_eventHandler);
}

StartMode::StartMode(EventHandler& eventHandler) : Mode(eventHandler)
{
}

void StartMode::onInit(EventHandler& eventHandler)
{
  eventHandler.registerMethod(SDLK_RETURN,  [this]{this->finish();});
}

void StartMode::render(IRender & render)
{
  render.renderText("Zaczynamy", 72, -1, 200);
  render.renderText("(wciśnij ENTER, żeby zacząć)", 24, -1, 300);
}

PlayMode::PlayMode(EventHandler & eventHandler, WordProvider & provider, TimeStats & stats) :  Mode(eventHandler), m_wordProvider(provider), m_stats(stats)
{
}

void PlayMode::onInit(EventHandler& eventHandler)
{
  eventHandler.registerMethod(SDLK_LEFT,  [this]{m_wordProvider.dec(); m_stats.set(m_wordProvider.pos());});
  eventHandler.registerMethod(SDLK_RIGHT, [this]{if(false == m_wordProvider.inc()) this->finish(); m_stats.set(m_wordProvider.pos());});
  m_stats.init(m_wordProvider.pos());
}

void PlayMode::render(IRender & render)
{
  render.renderText(m_wordProvider.get(), 72, -1, -1);
 
  // render stats
  std::stringstream ss;
  ss << "[" << m_wordProvider.pos()+1 <<" / " << m_wordProvider.total() << "]"; 
  render.renderText(ss.str(), 24, 10, 10);
}


FinishedMode::FinishedMode(EventHandler& eventHandler, 
                           TimeStats & timeStats, 
                           WordProvider & wordProvider) : Mode(eventHandler), 
                                                          m_timeStats(timeStats), 
                                                          m_wordProvider(wordProvider)
{
  // empty c-tor
}

void FinishedMode::onInit(EventHandler& eventHandler)
{
}

void FinishedMode::render(IRender & render)
{
  render.renderText("Super :-)", 72, -1, 200);
  render.renderText("(wciśnij ESC, żeby zakończyć)", 24, -1, 300);
  
  renderTotalTime(render, m_timeStats.totalTime());
  renderTopN(render, getTopN());
}

void FinishedMode::renderTotalTime(IRender & render, uint64_t totalTime)
{
  std::stringstream ss;
  ss << "Całkowity czas: " << m_timeStats.totalTime()/1000.0 <<"[s]";
  render.renderText(ss.str(), 36, -1, 380);
}

void FinishedMode::renderTopN(IRender & render, TopN data)
{
  render.renderText("Najwiecej czasu zajęły słowa:", 24, -1, 450);

  for(int i =0; i < 5; ++i)
  {
    std::stringstream ss;
    ss <<i+1 <<". " << data[data.size()-1-i].second << " : " << data[data.size()-1-i].first/1000.0 << "[s]";
    render.renderText(ss.str(), 24, -1, 490+i*30);
  }
}

FinishedMode::TopN FinishedMode::getTopN()
{
  TopN tmp;
  auto buckets = m_timeStats.getStats();
   for(int i = 0; i < buckets.size(); ++i)
     tmp.push_back(std::make_pair(buckets[i], m_wordProvider.get(i)));

  std::sort(tmp.begin(), tmp.end());
  
  return tmp;
}



