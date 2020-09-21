#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "globals.hpp"
#include "entity.hpp"
#include <array>

enum Directions{
  Top_Right     = 0,
  Top           = 1,
  Top_Left      = 2,
  Right         = 3,
  Center        = 4,
  Left          = 5,
  Bottom_Left   = 6,
  Bottom        = 7,
  Bottom_Right  = 8,
};

typedef std::array<std::array<Entity*, ChunkSize + 2*ChunkOverlap>, ChunkSize+2*ChunkOverlap> ExtGridPointer;

#endif // UTIL_H_INCLUDED
