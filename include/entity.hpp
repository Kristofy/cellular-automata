#ifndef ENTITY_H
#define ENTITY_H

#include "type.hpp"


class Entity
{
  public:
    Entity() = default;
    Entity(Type t, int s) :type(t), speed(s) {}
    Entity(Type t) :type(t) {}

    inline void Set(Type t){
      type = t;
      speed = 0;
    }

    Type type;

    float speed;
    float acceleration;

    bool checked;

};

#endif // ENTITY_H
