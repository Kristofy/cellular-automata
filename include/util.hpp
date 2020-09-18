#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "globals.hpp"
#include "entity.hpp"
#include <array>

enum Directions{
  Left = 0,
  Bottom_Left = 1,
  Bottom = 2,
  Bottom_Right = 3,
  Right = 4,
  Top_Right = 5,
  Top = 6,
  Top_Left = 7
};

typedef std::array<std::array<Entity*, ChunkSize + 2*ChunkOverlap>, ChunkSize+2*ChunkOverlap> ExtGridPointer;

#endif // UTIL_H_INCLUDED
