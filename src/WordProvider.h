#pragma once

#include <string>
#include <vector>
#include <set>

#include "Input.h"

class WordProvider
{
public:
  WordProvider();
  std::string get() const { return m_words[m_pos]; }
  std::string get(int pos) const { return m_words[pos]; }
  bool dec() { return (m_pos ? --m_pos,true : false); };
  bool inc() { return (m_pos < m_words.size() -1 ? ++m_pos,true : false);}

  unsigned int pos() const { return m_pos; }
  unsigned int total() const { return m_words.size(); }

protected:
  std::vector<std::string> m_words;
  unsigned int m_pos;
};

class RandomWordProvider : public WordProvider
{
public:
  RandomWordProvider(const Input & input, uint64_t wordAmount, uint64_t min, uint64_t max);
private:
  std::string stripOtherChars(std::string str);
  void addOnlyIfProperOne(std::string word, uint64_t min, uint64_t max);
  static std::string getNextRandomWord(const Input & input);
  bool needMoreWords(uint64_t wordAmount);
  std::set<std::string> m_cache;
};

class RepeatWordProvider : public WordProvider
{
public:
  RepeatWordProvider(const Input & input, uint64_t repeat);
};

class ContinousWordProvider : public WordProvider
{
public:
  ContinousWordProvider(const Input & input);
};