#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "entity.hpp"
#include "type.hpp"
#include "globals.hpp"
#include "util.hpp"
#include <cstdio>
#include <iostream>
#include <bitset>

class Processor
{
  public:
    Processor(ExtGridPointer& link, std::bitset<SubChunks*SubChunks>& subChunksLink) :m_world(link), m_sub_chunks(subChunksLink) {}

    void Update(int y, int x);

  private:
    ExtGridPointer& m_world;
    std::bitset<SubChunks*SubChunks>& m_sub_chunks;
    Entity* m_curr;

    void Swap(int y, int x, int y2, int x2);

};

#endif // PROCESSOR_H
