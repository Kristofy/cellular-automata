
#define DEBUG


// TODO: Remove later
////// DEBUG //////

float mx = 0;

#include <SFML/Graphics.hpp>
#include "include/globals.hpp"
#include "worldmanager.hpp"
#include <iostream>
#include "include/chunk.hpp"

void test_chunk(WorldManager& chunk);

int main(){

  std::cout << "The allocated Stack size By the Whole World is: "<<sizeof(WorldManager)<<std::endl;
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
  float smoothing = 0.9f;

  test_chunk(manager);

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

void test_chunk(WorldManager& manager){
  int square_size = 50;
  std::cout << "Test input started" << std::endl;
  for(int i = 0; i < square_size; i++){
      for(int j = 0; j < square_size; j++){
          manager.Get(WorldHeight/2-square_size/2+i,WorldWidth/2-square_size/2+j).type = Type::Water;
      }
  }

  std::cout << "Test input done" << std::endl;

}


