#pragma once 

#include "IRender.h"
#include "EventHandler.h"
#include "WordProvider.h"
#include "TimeStats.h"

#include <iostream>

class Mode
{
public:
  Mode(EventHandler& eventHandler) : m_bFinished(false), m_eventHandler(eventHandler) {}
  virtual void render(IRender & render) = 0;
  bool finish() { m_bFinished = true; }
  bool isFinished() const { return m_bFinished; }
  void init();
  virtual void onInit(EventHandler& eventHandler) = 0;
private:
  bool m_bFinished;
  EventHandler& m_eventHandler;
};

class StartMode : public Mode
{
public:
  StartMode(EventHandler& eventHandler); 
  virtual void onInit(EventHandler& eventHandler);
  virtual void render(IRender & render);
};

class PlayMode : public Mode
{
public:
  PlayMode(EventHandler& eventHandler, WordProvider & wordProvider, TimeStats & timeStats);
  virtual void onInit(EventHandler& eventHandler); 
  virtual void render(IRender & render);
private:
  WordProvider & m_wordProvider;
  TimeStats & m_stats;
};


class FinishedMode : public Mode
{
public:
  FinishedMode(EventHandler& eventHandler, TimeStats & timeStats, WordProvider & m_wordProvide); 
  virtual void onInit(EventHandler& eventHandler);
  virtual void render(IRender & render);

  typedef std::vector<std::pair<uint64_t, std::string>> TopN;
private:
  TimeStats & m_timeStats;
  WordProvider & m_wordProvider;

  void renderTotalTime(IRender & render, uint64_t totalTime);
  void renderTopN(IRender & render, TopN data);
  TopN getTopN();
};