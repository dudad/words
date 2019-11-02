#include "Params.h"


Params::Params(int argc, char **argv)
{ 
  for(int i =1; i < argc; ++i)
    m_words.push_back(argv[i]); 
}