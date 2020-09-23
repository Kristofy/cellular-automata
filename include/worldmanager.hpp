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
    void Refresh(int i, int j);
    void ToggleChunkBorders();
    void RefreshAll();
    void UpdateSubChunk(int x, int y, int subX, int subY);
    bool IsBorderVisible();
  private:
    Chunk m_chunks[HorizontalChunks*VerticalChunks];
    Entity m_nope;

    bool m_isBordersVisible;
    sf::VertexArray m_chunkBorders;

};

#endif // WORLDMANAGER_H
