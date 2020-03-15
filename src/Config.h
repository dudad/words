#pragma once
#include <string>
#include <vector>

#include "WordProvider.h"

class Config
{
public:
  Config(std::string strConfigFile);
  std::vector<std::string> getWordsFiles() const { return m_inputFiles;}
  WordProvider& getWordProvider() const { return *m_wordProvider; }
private:
  std::vector<std::string> m_inputFiles;
  WordProvider* m_wordProvider;
};