#include "Input.h"

#include <iostream>
#include <fstream>

Input::Input(std::vector<std::string> paths)
{
  for(auto path : paths)
    processFile(path);
  
  std::cout << "Processed words: " << m_words.size() << "\n";
}

void Input::processFile(const std::string & path)
{
  std::ifstream file(path);
  if (file.is_open())
  {
    std::string word;
    while (file >> word)
      m_words.push_back(word);
  
    file.close();
  }
  else
    std::cout << "Unable to open file";
}
