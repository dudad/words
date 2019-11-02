#pragma once

#include <string>
#include <vector>

class Params
{
public:
  Params(int argc, char **argv);
  std::vector<std::string> getWordsFiles() const { return m_words;}
private:
  std::vector<std::string> m_words;

};