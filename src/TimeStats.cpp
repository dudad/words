#include "TimeStats.h"

#include <numeric>

void TimeStats::init(unsigned int bucket)
{
  m_currBucketIdx = bucket;
  m_ticks = SDL_GetTicks();
}

void TimeStats::set(unsigned int bucket)
{
  Uint32 now = SDL_GetTicks();
  m_buckets[m_currBucketIdx] += (now - m_ticks);

  m_currBucketIdx = bucket;
  m_ticks = now;
}

uint64_t TimeStats::totalTime()
{
  return std::accumulate(m_buckets.begin(), m_buckets.end(), 0);
}