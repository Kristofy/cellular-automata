#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "entity.hpp"
#include "type.hpp"
#include "globals.hpp"
#include "util.hpp"
#include <cstdio>
#include <iostream>
#include <array>

class Processor
{
  public:
    Processor(ExtGridPointer& link, std::array<uint8_t, SubChunks*SubChunks>& subChunksLink) :m_world(link), m_sub_chunks(subChunksLink)
    {}

    void Update(unsigned y, unsigned x);

  private:
    ExtGridPointer& m_world;
    std::array<uint8_t, SubChunks*SubChunks>& m_sub_chunks;
    Entity* m_curr;

    void Swap(unsigned y, unsigned x, unsigned y2, unsigned x2);

};

#endif // PROCESSOR_H
