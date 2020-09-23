
#define DEBUG

float fastestElement;

#include <SFML/Graphics.hpp>
#include "Imgui/imgui.h"
#include "Imgui/imgui-SFML.h"

#include <iostream>
#include "include/globals.hpp"
#include "include/worldmanager.hpp"
#include "include/type.hpp"
#include "include/util.hpp"
#include "include/chunk.hpp"
#include <string>

Type current = Type::Sand;
bool test = true;
char buff[256];


void test_chunk(WorldManager& manager, int x, int y);

sf::Vector2f operator-(const sf::Vector2f& a, const sf::Vector2f& b){
  return sf::Vector2f(a.x-b.x, a.y-b.y);
}





int main(){

  std::cout << "The allocated Stack size By the Whole World is: "<<sizeof(WorldManager)<<std::endl;
  // The main object
  WorldManager manager;

  // Setting up the Render window for SFML
  sf::RenderWindow window(sf::VideoMode(CameraWidth, CameraHeight), Title, sf::Style::Close);
  sf::Vector2f screenCenter(sf::Vector2f(CameraWidth/2.0f, CameraHeight/2.0f));
  sf::View camera(screenCenter, sf::Vector2f(CameraWidth, CameraHeight));
  //window.setView(camera);
  sf::CircleShape c(40);
  c.setFillColor(sf::Color::Red);

  //  window.setVerticalSyncEnabled(true);

  // Setting up the times for the game loop
  sf::Time timePerUpdate = sf::seconds(1.0f /(float)TPS);
  sf::Clock timer;
  sf::Time lastTime = sf::Time::Zero;
  sf::Time lag = sf::Time::Zero;
  sf::Event currentEvent;

  // Fps count
  float fps = 0;
  float smoothing = 0.69f;

  // ImGui Setup
  ImGui::SFML::Init(window);
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();


  // Main game loop

  while ( window.isOpen() ) {


    sf::Time time = timer.getElapsedTime();
    sf::Time elapsed = time - lastTime;
    lastTime = time;
    lag += elapsed;

    // Calculate FPS
    fps = (fps * smoothing) + (1.0f/(elapsed.asSeconds()+0.001f) * (1.0f - smoothing));

    // Handling Events
    while ( window.pollEvent(currentEvent) ) {
      ImGui::SFML::ProcessEvent(currentEvent);
      switch ( currentEvent.type ) {
        case sf::Event::Closed:
          window.close();
        break;
        case sf::Event::MouseMoved:
          {

          }
        break;
        default:
        break;
      }

    }

    float maximum = 6;
    sf::Vector2f mouse(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    sf::Vector2f dist = (mouse - screenCenter);
    float len = sqrt(dist.x*dist.x+dist.y*dist.y);

    if(!io.WantCaptureMouse && len > 150 && mouse.x >= 0 && mouse.x < CameraWidth && mouse.y >= 0 && mouse.y < CameraHeight){

      dist.x = (dist.x/len);
      dist.y = (dist.y/len);
      dist.x = maximum * dist.x;
      dist.y = maximum * dist.y;
      dist.x *= dist.x * dist.x;
      dist.y *= dist.y * dist.y;
      dist.x *= elapsed.asSeconds();
      dist.y *= elapsed.asSeconds();
      camera.move(dist);
      window.setView(camera);
    }
    if(ImGui::SFML::isButtonPressed(sf::Mouse::Left, io)){
      int x = (int)(camera.getCenter().x - screenCenter.x + mouse.x);
      int y = (int)(camera.getCenter().y - screenCenter.y + mouse.y);
      test_chunk(manager, x, y);
    }
    if(ImGui::SFML::isKeyPressed(sf::Keyboard::B, io)){
      manager.ToggleChunkBorders();
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

    }

    if (lag >= timePerUpdate){
      fastestElement = 0;
    }

    // Update Loop Runs exactly at TPS
    while ( lag >= timePerUpdate ){
      manager.Update();
      lag -= timePerUpdate;
    }

    ImGui::SFML::Update(window, elapsed);

    sf::Vector2f mouseWPos = window.mapPixelToCoords(sf::Mouse::getPosition());
    if(test){
      ImGui::Begin("Logs", &test);
      ImGui::TextColored(ImVec4(sf::Color(0x119da4ff)), ("Fps:   \t\t\t" + std::to_string(fps)).c_str());
      ImGui::TextColored(ImVec4(sf::Color(0xd8973cff)), ("Tps:   \t\t\t" + std::to_string(TPS)).c_str());
      ImGui::TextColored(ImVec4(sf::Color(0x77ff94ff)), ("Camera center: \t" + std::to_string(camera.getCenter().x) + " " + std::to_string(camera.getCenter().y)).c_str());
      ImGui::TextColored(ImVec4(sf::Color(0xec9dedff)), ("Mouse position: \t" + std::to_string(mouse.x) + " " + std::to_string(mouse.y)).c_str());
      ImGui::TextColored(ImVec4(sf::Color(0xf37748ff)), ("Mouse (w)position: " + std::to_string(mouseWPos.x) + " " + std::to_string(mouseWPos.y)).c_str());
      ImGui::TextColored(ImVec4(sf::Color(0x688e26ff)), ("Fastest speed: \t" + std::to_string(fastestElement)).c_str());
      ImGui::TextColored(ImVec4(sf::Color(0xecc30bff)), ("Borders are:   \t" + std::string((manager.IsBorderVisible())? "on" : "off")).c_str());
      bool border = manager.IsBorderVisible();

      ImGui::SameLine();ImGui::Checkbox("", &border);
      if(border != manager.IsBorderVisible()) manager.ToggleChunkBorders();
      ImGui::End();
    }
  c.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition()));
//    ImGui::ShowDemoWindow();
    // Render
    window.clear();
    manager.Render(window);
    window.draw(c);
    ImGui::SFML::Render(window);
    window.display();


  }

  return EXIT_SUCCESS;
}

void test_chunk(WorldManager& manager, int x, int y){
  int square_size = 50;
  for(int i = 0; i < square_size; i++){
      for(int j = 0; j < square_size; j++){
          manager.Get(y-square_size/2+i,x-square_size/2+j).type = current;
          manager.Refresh(y-square_size/2+i, x-square_size/2+j);
      }
  }
}


