
#define DEBUG

#include "include/globals.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/chunk.hpp"

void test_chunk(Chunk& chunk);

int main(){

  // Seting up the renderwidow for SFML
  sf::RenderWindow window(sf::VideoMode(CameraWidth, CameraHeight), Title, sf::Style::Close);
  window.setVerticalSyncEnabled(true);

  sf::Time timePerUpdate = sf::seconds(1.0f /(float)TPS);

  // Main game loop
  sf::Clock timer;
  sf::Time lastTime = sf::Time::Zero;
  sf::Time lag = sf::Time::Zero;
  sf::Event currentEvent;

  Chunk chunk;
  test_chunk(chunk);

  while ( window.isOpen() ) {
        sf::Time time = timer.getElapsedTime();
        sf::Time elapsed = time - lastTime;

        lastTime = time;
        lag += elapsed;


    // Handling SFML Events
      while ( window.pollEvent(currentEvent) ) {
          switch ( currentEvent.type ) {
              case sf::Event::Closed:
                  window.close();
                  break;

              default:
                  break;

          }
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
  int square_size = 50;
  for(int i = 0; i < square_size; i++){
      for(int j = 0; j < square_size; j++){
          chunk.m_data[ChunkSize/2-square_size/2+i][ChunkSize/2-square_size/2+j-square_size].type = Type::Sand;
          chunk.m_data[ChunkSize/2-square_size/2+i][ChunkSize/2-square_size/2+j-square_size].speed = 1;

      }
  }

  for(int i = 0; i < square_size; i++){
      for(int j = 0; j < square_size; j++){
          chunk.m_data[ChunkSize/2-square_size/2+i][ChunkSize/2-square_size/2+j+square_size].type = Type::Sand;
          chunk.m_data[ChunkSize/2-square_size/2+i][ChunkSize/2-square_size/2+j+square_size].speed = 1;

      }
  }

  square_size = 30;
  for(int i = 0; i < square_size; i++){
      for(int j = 0; j < square_size; j++){
          chunk.m_data[ChunkSize/2-square_size/2+i - square_size][ChunkSize/2-square_size/2+j].type = Type::Water;
          chunk.m_data[ChunkSize/2-square_size/2+i- square_size][ChunkSize/2-square_size/2+j].speed = 1;

      }
  }


  for(int j = 0; j < 12; j++){
    for(int i = 0; i < ChunkSize; i++){
        chunk.m_data[ChunkSize-j-1][i].type = Type::Stone;
        chunk.m_data[j][i].type = Type::Stone;
        chunk.m_data[i][ChunkSize-j-1].type = Type::Stone;
        chunk.m_data[i][j].type = Type::Stone;
    }
  }



}

