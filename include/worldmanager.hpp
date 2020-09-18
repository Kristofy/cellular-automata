#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <SFML/Graphics.hpp>
#include "chunk.hpp"
#include "entity.hpp"
#include "globals.hpp"
#include "util.hpp"

class WorldManager
{
  public:
    WorldManager();
    void Update();
    void Render(sf::RenderTarget& window);
    Entity& Get(int i, int j);

  private:
    Chunk m_chunks[HorizontalChunks*VerticalChunks];
    Entity m_nope;

};

#endif // WORLDMANAGER_H
