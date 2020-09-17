#include "../include/chunk.hpp"

Chunk::Chunk()
:m_processor(ext_data)
{

  for(int i = 0; i < ChunkSize; i++){
    for(int j = 0; j < ChunkSize; j++){
      m_data[i][j].type = Type::Air;
      ext_data[i + ChunkOverlap][j + ChunkOverlap] = &m_data[i][j];
    }
  }
  m_texture.create(ChunkSize, ChunkSize);
  m_sprite.setTexture(m_texture);

}

void Chunk::Update(){

  for(int i = 0; i < ChunkSize; i++){
        for(int j = 0; j < ChunkSize; j++){
            if(m_data[i][j].checked == false){
                m_data[i][j].checked = true;
                m_processor.Update(i+ChunkOverlap, j+ChunkOverlap);
            }
        }
    }
    for(int i = 0; i < ChunkSize; i++){
        for(int j = 0; j < ChunkSize; j++){
            m_data[j][i].checked = false;
            m_data[j][i].moved = false;
        }
    }


}

void Chunk::Render(sf::RenderTarget& window){

//  sf::CircleShape c(100);
//  c.setFillColor(sf::Color::Green);
//  c.setPosition(128, 128);

   for(int i = 0; i < ChunkSize; i++){
        for(int j = 0; j < ChunkSize; j++){
            m_color_data[j][i] = GetColor(m_data[j][i].type);
        }
    }
  m_texture.update((uint8_t*)m_color_data, ChunkSize, ChunkSize, 0, 0);
  window.draw(m_sprite);
}
