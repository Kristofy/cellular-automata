#include "brush.hpp"

namespace{
  static WorldManager* s_manager;
  static Type s_type = Type::Air;
  static Brush::Model s_model = (Brush::Model)0;
  static int s_model_width = 1; // rect width
  static int s_model_height = 1; // rect height
  static int s_model_radius = 1; // circle radius
}

namespace Brush{
   enum Model:int{
    Nothing,
    Point,
    Rect,
    Circle
  };

  void Init(WorldManager& manager){
    s_manager = &manager;
  }

  void SetType(Type type){
    s_type = type;
  }

  void DrawPixel(int x, int y){
    s_manager->Get(y, x).Set(s_type);
    s_manager->Refresh(y, x);
  }

  void DrawRect(int x, int y, int width, int height){
    for(int i = y; i <= y+height; i++){
      for(int j = x; j <= x+width; j++){
        s_manager->Get(i, j).Set(s_type);
      }
    }
    for(int i = y>>SubChunkShift; i <= (y+height)>>SubChunkShift; i++){
      for(int j = x>>SubChunkShift; j <= (x+width)>>SubChunkShift; j++){
        s_manager->Refresh(i<<SubChunkShift, j<<SubChunkShift);
      }
    }
  }

  void DrawCircle(int x, int y, int radius){
    for(int i = y - radius; i <= y+radius; i++){
      for(int j = x - radius; j <= x+radius; j++){
        if((j-x)*(j-x) + (i-y)*(i-y) <= radius*radius){
          s_manager->Get(i, j).Set(s_type);
        }
      }
    }

    for(int i = (y-radius)>>SubChunkShift; i <= (y+radius)>>SubChunkShift; i++){
      for(int j = (x-radius)>>SubChunkShift; j <= (x+radius)>>SubChunkShift; j++){
        s_manager->Refresh(i<<SubChunkShift, j<<SubChunkShift);
      }
    }
  }

  void DisplayImGuiPalette(){
    ImGui::Begin("Palette");
    if(ImGui::CollapsingHeader("Model")){
      ImGui::Indent(20.0f);
      ImGui::RadioButton("Nothing", (int*)&s_model, (int)Model::Nothing);
      ImGui::RadioButton("Point", (int*)&s_model, (int)Model::Point);
      ImGui::RadioButton("Rectangle", (int*)&s_model, (int)Model::Rect);
      ImGui::RadioButton("Circle", (int*)&s_model, (int)Model::Circle);
      ImGui::Indent(-20.0f);
    }
    if(ImGui::CollapsingHeader("Material")){
      ImGui::Indent(20.0f);
      ImGui::RadioButton("Air", (uint8_t*)&s_type, (uint8_t)Type::Air);
      ImGui::RadioButton("Sand", (uint8_t*)&s_type, (uint8_t)Type::Sand);
      ImGui::RadioButton("Stone", (uint8_t*)&s_type, (uint8_t)Type::Stone);
      ImGui::RadioButton("Water", (uint8_t*)&s_type, (uint8_t)Type::Water);
      ImGui::Indent(-20.0f);
    }
    if(ImGui::CollapsingHeader("Transform")){
      ImGui::Indent(20.0f);
      switch(s_model){
        case Model::Nothing: break;
        case Model::Point: break;
        case Model::Rect:
          ImGui::DragInt("width", &s_model_width, 1.0f, 1, WorldWidth, "%d");
          ImGui::DragInt("height", &s_model_height, 1.0f, 1, WorldHeight, "%d");
        break;
        case Model::Circle:
          ImGui::DragInt("radius", &s_model_radius, 1.0f, 1, std::min(WorldWidth, WorldHeight), "%d");
        break;
      }
      ImGui::Indent(-20.0f);
    }

    ImGui::End();
  }

  void DrawWithImGui(int x, int y){
    switch(s_model){
      case Model::Nothing: break;
      case Model::Point:
        DrawPixel(x, y);
      case Model::Rect:
        DrawRect(x, y, s_model_width, s_model_height);
      break;
      case Model::Circle:
        DrawCircle(x, y, s_model_radius);
      break;
    }
  }

}
