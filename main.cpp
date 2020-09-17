
#define DEBUG


// TODO: Remove later
////// DEBUG //////

float mx = 0;

#include "include/globals.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/chunk.hpp"

void test_chunk(Chunk& chunk);

int main(){

  // Seting up the renderwidow for SFML
  sf::RenderWindow window(sf::VideoMode(CameraWidth, CameraHeight), Title, sf::Style::Close);
//  window.setVerticalSyncEnabled(true);

  sf::Time timePerUpdate = sf::seconds(1.0f /(float)TPS);

  // Main game loop
  sf::Clock timer;
  sf::Time lastTime = sf::Time::Zero;
  sf::Time lag = sf::Time::Zero;
  sf::Event currentEvent;

  Chunk chunk;
  test_chunk(chunk);

  float fps = 0;
  float smoothing = 0.9f;


  while ( window.isOpen() ) {
        sf::Time time = timer.getElapsedTime();
        sf::Time elapsed = time - lastTime;

        lastTime = time;
        lag += elapsed;
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
                }else if(sf::Keyboard::T == currentEvent.key.code){
                  test_chunk(chunk);
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

        // Update Loop
        while ( lag >= timePerUpdate )
        {
          chunk.Update();
          lag -= timePerUpdate;
        }

        // Render
        window.clear();

        chunk.Render(window);

        window.display();


    }



  return EXIT_SUCCESS;

}


void test_chunk(Chunk& chunk){
  int square_size = 20;
  for(int i = 0; i < square_size; i++){
      for(int j = 0; j < square_size; j++){
          chunk.m_data[ChunkSize/2-square_size/2+i][ChunkSize/2-square_size/2+j].type = Type::Sand;
          chunk.m_data[ChunkSize/2-square_size/2+i][ChunkSize/2-square_size/2+j].speed = 1;

      }
  }
/*
  for(int i = 0; i < square_size; i++){
      for(int j = 0; j < square_size; j++){
          chunk.m_data[ChunkSize/2-square_size/2+i][ChunkSize/2-square_size/2+j+square_size].type = Type::Sand;
          chunk.m_data[ChunkSize/2-square_size/2+i][ChunkSize/2-square_size/2+j+square_size].speed = 1;

      }
  }

  square_size = 20;
  for(int i = 0; i < square_size; i++){
      for(int j = 0; j < square_size; j++){
          chunk.m_data[ChunkSize/2-square_size/2+i - square_size][ChunkSize/2-square_size/2+j].type = Type::Water;
          chunk.m_data[ChunkSize/2-square_size/2+i- square_size][ChunkSize/2-square_size/2+j].speed = 1;

      }
  }
*/

  for(int j = 0; j < SpeedLimit; j++){
    for(int i = 0; i < ChunkSize; i++){
        chunk.m_data[ChunkSize-j-1][i].type = Type::Stone;
        chunk.m_data[j][i].type = Type::Stone;
        chunk.m_data[i][ChunkSize-j-1].type = Type::Stone;
        chunk.m_data[i][j].type = Type::Stone;
    }
  }



}

