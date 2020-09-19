#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "entity.hpp"
#include "type.hpp"
#include "globals.hpp"
#include "util.hpp"
#include <cstdio>
#include <iostream>
#include <algorithm>

class Processor
{
  public:
    Processor(ExtGridPointer& link) :m_world(link) {}

    void Update(int y, int x);

  private:
    void Swap(int y, int x, int y2, int x2){
        m_world[y][x]->moved = true;
        m_world[y2][x2]->checked = true;

        Type tmp_type = std::move(m_world[y][x]->type);
        m_world[y][x]->type = std::move(m_world[y2][x2]->type);
        m_world[y2][x2]->type = std::move(tmp_type);

        float tmp_speed = std::move(m_world[y][x]->speed);
        m_world[y][x]->speed = std::move(m_world[y2][x2]->speed);
        m_world[y2][x2]->speed = std::move(tmp_speed);

        curr = m_world[y2][x2];

    }

    Entity* curr;

    ExtGridPointer& m_world;

};

#endif // PROCESSOR_H
