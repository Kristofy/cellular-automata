#ifndef BRUSH_H
#define BRUSH_H

#include "worldmanager.hpp"
#include "type.hpp"
#include "../Imgui/imgui.h"
#include "../Imgui/imgui-SFML.h"
#include <string>

namespace Brush
{
  enum Model:int;

  void Init(WorldManager& manager);
  void SetType(Type type);
  void DrawPixel(int x, int y);

  void DrawRect(int x, int y, int width, int height);
  void DrawRectWithImGui(int x, int y);

  void DrawCircle(int x, int y, int radius);

  void DisplayImGuiPalette();
  void DrawWithImGui(int x, int y);

};

#endif // BRUSH_H
