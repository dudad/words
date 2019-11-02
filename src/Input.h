#pragma once

#include <string>
#include <vector>

class Input
{
public:
  Input(std::vector<std::string> paths);
  
  std::vector<std::string> getWords() const { return m_words; }
private:
  std::vector<std::string> m_words;

  void processFile(const std::string & path);
};

   