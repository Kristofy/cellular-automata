#ifndef CHUNK_H
#define CHUNK_H

#include <SFML/Graphics.hpp>
#include <bitset>
#include "globals.hpp"
#include "entity.hpp"
#include "processor.hpp"
#include "type.hpp"
#include "color.hpp"
#include "util.hpp"

class Chunk
{
  friend class WorldManager;

  public:
    Chunk();

    void Update();
    void Render(sf::RenderTarget& window);
    void SetPosition(int y, int x);
    void SetBorder(Directions Side, Entity* map_to);
    void Bind(Directions Side, Chunk& other);
    void Refresh();

  private:
    ExtGridPointer m_data;
    uint32_t* m_color_data;
    Processor m_processor;

    std::bitset<SubChunks*SubChunks> m_sub_chunk;

    sf::Texture m_texture;
    sf::Sprite m_sprite;

    void UpdateColors();
    void UpdateSubChunk(int x, int y);

};

#endif // CHUNK_H
