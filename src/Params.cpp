#include "Params.h"


Params::Params(int argc, char **argv)
{
  if(argc != 2)
    m_strConfigFile = "defaultConfig.json";
  else
    m_strConfigFile = argv[1];
}