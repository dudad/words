#include "Config.h"

#include <string>
#include <fstream>
#include "../3rdParty/json.hpp"
#include <iostream>

Config::Config(std::string strConfigFile)
{
  std::ifstream inputFile(strConfigFile);
  nlohmann::json jsonObj;
  inputFile >> jsonObj;
  std::vector<std::string> tmp = jsonObj["input-files"];
  m_inputFiles = tmp;
  auto mode = jsonObj["mode"];
  std::string modeName = mode["name"];

  if(modeName == "random")
  {
    uint64_t amount = mode["amount"];
    uint64_t min = mode["min"];
    uint64_t max = mode["max"];

    m_wordProvider = new RandomWordProvider (Input(m_inputFiles), amount, min, max);
  } 
  else if(modeName == "repeat")
  {
    uint64_t repeatAmount = mode["repeat-amount"];
    m_wordProvider = new RepeatWordProvider (Input(m_inputFiles), repeatAmount);
  }
  else if(modeName == "continious")
  {
    m_wordProvider = new ContinousWordProvider (Input(m_inputFiles));
  }
  else
  {
    // todo throw ex
  }
  

}