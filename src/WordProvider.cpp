#include "WordProvider.h"
#include <algorithm>
#include <random>
#include <set>

WordProvider::WordProvider() : m_pos(0)
{

}

RandomWordProvider::RandomWordProvider(const Input & input, uint64_t wordAmount, uint64_t min, uint64_t max)
{  
  srand (time(NULL));
  while(needMoreWords(wordAmount))
    addOnlyIfProperOne(stripOtherChars(getNextRandomWord(input)), min, max);    
}

bool RandomWordProvider::needMoreWords(uint64_t wordAmount)
{
  return m_words.size() < wordAmount;
}

std::string RandomWordProvider::getNextRandomWord(const Input & input)
{
  const auto N = input.getWords().size();
  return input.getWords()[rand() % N];
}

// todo refactor or replace
int utf8_strlen(const std::string& str)
{
    int c,i,ix,q;
    for (q=0, i=0, ix=str.length(); i < ix; i++, q++)
    {
        c = (unsigned char) str[i];
        if      (c>=0   && c<=127) i+=0;
        else if ((c & 0xE0) == 0xC0) i+=1;
        else if ((c & 0xF0) == 0xE0) i+=2;
        else if ((c & 0xF8) == 0xF0) i+=3;
        else return 0;//invalid utf8
    }
    return q;
}

void RandomWordProvider::addOnlyIfProperOne(std::string word, uint64_t min, uint64_t max)
{
  auto len = utf8_strlen(word);
  if(len >= min && len <= max)
  {
    if(m_cache.insert(word).second)
      m_words.push_back(word);
  }
}

std::string RandomWordProvider::stripOtherChars(std::string str)
{
  std::string removed = "(),.!?:\"";
  str.erase(std::remove_if(str.begin(), 
                           str.end(), 
                           [removed]( auto const& c ) -> bool { return removed.find_first_of(c) != std::string::npos; }), 
            str.end());
  
  return str;
}


RepeatWordProvider::RepeatWordProvider(const Input & input, uint64_t repeat)
{
  auto copyInput = input.getWords();
  for(int i = 0; i < repeat; ++i)
  {
    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(copyInput.begin(), copyInput.end(), g);
    for(auto word: copyInput)
      m_words.push_back(word);
  }
}


ContinousWordProvider::ContinousWordProvider(const Input & input)
{
  for(auto word: input.getWords())
    m_words.push_back(word);
}