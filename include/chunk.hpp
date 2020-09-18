#ifndef CHUNK_H
#define CHUNK_H

#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "entity.hpp"
#include "processor.hpp"
#include "type.hpp"
#include "color.hpp"
#include "util.hpp"

class Chunk
{
  public:
    Chunk();

    void Update();
    void Render(sf::RenderTarget& window);
    void SetPosition(int y, int x);
    void SetBorder(Directions Side, Entity* map_to);
    void Bind(Directions Side, Chunk& other);

    Entity m_data[ChunkSize][ChunkSize];
  private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;

    uint32_t m_color_data[ChunkSize][ChunkSize];
    ExtGridPointer m_ext_data;
    Processor m_processor;

};

#endif // CHUNK_H
