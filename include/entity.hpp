#ifndef ENTITY_H
#define ENTITY_H

#include "type.hpp"


class Entity
{
  public:
    Entity() = default;
    Entity(Type t, int s) :type(t), speed(s) {}
    Entity(Type t) :type(t) {}

    Type type;
    bool moved;
    float speed;
    float acceleration;
    bool checked;

  protected:

  private:
};

#endif // ENTITY_H
