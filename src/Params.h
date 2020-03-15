#pragma once

#include <string>
#include <vector>

class Params
{
public:
  Params(int argc, char **argv);
  std::string getConfigFile(){ return m_strConfigFile; }

private:
  std::string m_strConfigFile;
};