#ifndef COLOR_H
#define COLOR_H

#ifdef DEBUG
 #include<cstdio>
#endif

#include "type.hpp"

// color type int uint32_t 0x ff(alpha) ff(blue) ff(green) ff(blue)

const uint32_t colors[(int)Type::End] = {
  0xffffffff, /* Air */
  0xff0fa5db, /* Sand */
  0xff0f0f0f , /* Stone */
  0xffb8291f, /* Water */
};

static_assert((int)Type::Air   == 0, "You need to adjust the colors");
static_assert((int)Type::Sand  == 1, "You need to adjust the colors");
static_assert((int)Type::Stone == 2, "You need to adjust the colors");
static_assert((int)Type::Water == 3, "You need to adjust the colors");

inline uint32_t GetColor(Type t){
  #ifdef DEBUG
  if((int)t < 0 || (int)t > (int)Type::End){
    puts("Error, color index out of bounds!");
    return 0xffeb34cf;
  }
  #endif
  return colors[(int)t];
}

#endif // COLOR_H_INCLUDED
