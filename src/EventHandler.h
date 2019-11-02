#pragma once

#include <functional>
#include <map>

class EventHandler
{
public:
  void registerMethod(int key, std::function<void()> func);
  void unregisterAll() { handlers.clear(); } 
  bool process();
private:
  std::map<int, std::function<void()>> handlers;
};