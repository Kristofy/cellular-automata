#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "entity.hpp"
#include "type.hpp"
#include "globals.hpp"
#include "util.hpp"
#include <cstdio>
#include <iostream>

class Processor
{
  public:
    Processor(ExtGridPointer& link) :m_world(link) {}

    void Update(int y, int x);

  private:
    void UpdateEntitySpeed(Entity* curr);
    void Move(int x1, int y1, int x2, int y2){
        m_world[y2][x2]->checked = true;
        m_world[y1][x1]->moved = true;

        Type tmp_type = m_world[y1][x1]->type;
        m_world[y1][x1]->type = m_world[y2][x2]->type;
        m_world[y2][x2]->type = tmp_type;

        float tmp_speed = m_world[y1][x1]->speed;
        m_world[y1][x1]->speed = m_world[y2][x2]->speed;
        m_world[y2][x2]->speed = tmp_speed;

    }
    ExtGridPointer& m_world;

};

#endif // PROCESSOR_H
