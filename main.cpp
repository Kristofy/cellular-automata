
#define DEBUG


// TODO: Remove later
////// DEBUG //////

float mx = 0;

#include <SFML/Graphics.hpp>
#include "include/globals.hpp"
#include "worldmanager.hpp"
#include "type.hpp"
#include <iostream>
#include "include/chunk.hpp"

Type current = Type::Sand;

void test_chunk(WorldManager& chunk, int x, int y);

int main(){

  std::cout << "The allocated Stack size By the Whole World is: "<<sizeof(Chunk)<<std::endl;
  // The main object
  WorldManager manager;

  // Setting up the Render window for SFML
  sf::RenderWindow window(sf::VideoMode(CameraWidth, CameraHeight), Title, sf::Style::Close);
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

  // Main game loop
  while ( window.isOpen() ) {

    sf::Time time = timer.getElapsedTime();
    sf::Time elapsed = time - lastTime;
    lastTime = time;
    lag += elapsed;

    // Calculate FPS
    fps = (fps * smoothing) + (1.0f/elapsed.asSeconds() * (1.0f - smoothing));

    // Handling SFML Events
    while ( window.pollEvent(currentEvent) ) {
      switch ( currentEvent.type ) {
        case sf::Event::Closed:
          window.close();
        break;
        case sf::Event::KeyPressed:
          if(sf::Keyboard::M == currentEvent.key.code){
            printf("The current max is: %f\n", mx);
          }else if(sf::Keyboard::D == currentEvent.key.code){
            printf("TPS: %d \t\t FPS: %f\n", TPS, fps);
          }else if(sf::Keyboard::B == currentEvent.key.code){
            manager.ToggleChunkBorders();
          }else if( currentEvent.key.code >= sf::Keyboard::Num0 && currentEvent.key.code < sf::Keyboard::Num0 + Type::End){
            current = (Type)(currentEvent.key.code - sf::Keyboard::Num0);
          }
        case sf::Event::MouseButtonPressed:
          if(currentEvent.mouseButton.button == sf::Mouse::Left){
            printf("%d %d\n", sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            test_chunk(manager, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
          }
        break;
        default:
        break;
      }
    }

    //TODO: Remove later
    if(lag >= timePerUpdate){
    mx = 0;
    }

    // Update Loop Runs exactly at TPS
    while ( lag >= timePerUpdate )
    {
    manager.Update();
    lag -= timePerUpdate;
    }

    // Render
    window.clear();

    manager.Render(window);

    window.display();

}

  return EXIT_SUCCESS;
}

void test_chunk(WorldManager& manager, int x, int y){
  int square_size = 20;
  std::cout << "Test input started" << std::endl;
  for(int i = 0; i < square_size; i++){
      for(int j = 0; j < square_size; j++){
          manager.Get(y-square_size/2+i,x-square_size/2+j).type = current;
      }
  }

  std::cout << "Test input done" << std::endl;

}


