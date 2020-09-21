#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "entity.hpp"
#include "type.hpp"
#include "globals.hpp"
#include "util.hpp"
#include <cstdio>
#include <iostream>
#include <array>

class WorldManager;

class Processor
{
  friend class Chunk;
  public:
    Processor(ExtGridPointer& link, std::array<uint8_t, SubChunks*SubChunks>& subChunksLink)
    :m_world(link), m_sub_chunks(subChunksLink)
    {}

    void Update(unsigned y, unsigned x);

  private:
    ExtGridPointer& m_world;
    std::array<uint8_t, SubChunks*SubChunks>& m_sub_chunks;
    Entity* m_curr;
    int m_world_pos_x, m_world_pos_y;
    WorldManager* m_manager;

    void Swap(int y, int x, int y2, int x2);
    void SetWorldPosition(int x, int y);
    void SetManager(WorldManager* manager);

};

#endif // PROCESSOR_H
