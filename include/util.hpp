#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "globals.hpp"
#include "entity.hpp"
#include <array>

typedef std::array<std::array<Entity*, ChunkSize + 2*ChunkOverlap>, ChunkSize+2*ChunkOverlap> ExtGridPointer;

#endif // UTIL_H_INCLUDED
