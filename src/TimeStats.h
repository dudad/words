#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class TimeStats
{
public:
  TimeStats(unsigned int buckets) : m_buckets(buckets, 0) {}
  void init(unsigned int bucket);
  void set(unsigned int bucket);
  std::vector<unsigned int> getStats() const { return m_buckets; }

  uint64_t totalTime();
private:
  std::vector<unsigned int> m_buckets;
  unsigned int m_currBucketIdx;
  Uint32 m_ticks;
};