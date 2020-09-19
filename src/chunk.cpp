#include "../include/chunk.hpp"

// TODO: Remove later
extern float mx;

Chunk::Chunk()
:m_processor(m_ext_data)
{

  for(unsigned i = 0; i < ChunkSize; i++){
    for(unsigned j = 0; j < ChunkSize; j++){
      m_data[i][j].type = Type::Air;
      m_ext_data[i + ChunkOverlap][j + ChunkOverlap] = &m_data[i][j];
    }
  }
  m_texture.create(ChunkSize, ChunkSize);
  m_sprite.setTexture(m_texture);

}

void Chunk::Update(){

  for(unsigned i = 0; i < ChunkSize; i++){
    for(unsigned j = 0; j < ChunkSize; j++){
      if(m_data[i][j].checked == false){
        m_data[i][j].checked = true;
        m_processor.Update(i+ChunkOverlap, j+ChunkOverlap);
        // TODO: Remove later
        mx = std::max(mx, m_data[i][j].speed);
      }
    }
  }

  for(unsigned i = 0; i < ChunkSize; i++){
    for(unsigned j = 0; j < ChunkSize; j++){
      m_data[j][i].checked = false;
      m_data[j][i].moved = false;
    }
  }


}

void Chunk::Render(sf::RenderTarget& window){
  for(unsigned i = 0; i < ChunkSize; i++){
    for(unsigned j = 0; j < ChunkSize; j++){
      m_color_data[j][i] = GetColor(m_data[j][i].type);
    }
  }
  m_texture.update((uint8_t*)m_color_data, ChunkSize, ChunkSize, 0, 0);
  window.draw(m_sprite);
}

void Chunk::SetPosition(int y, int x){
  m_sprite.setPosition(x, y);
}


void Chunk::SetBorder(Directions Side, Entity* target){
  switch(Side){
    case Directions::Bottom:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkSize; j++){
          m_ext_data[i+ChunkOverlap + ChunkSize][j + ChunkOverlap] = target;
        }
      }
    break;

    case Directions::Bottom_Left:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_ext_data[i + ChunkOverlap + ChunkSize][j] = target;
        }
      }

    break;
    case Directions::Left:
      for(unsigned i = 0; i < ChunkSize; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_ext_data[i + ChunkOverlap][j] = target;
        }
      }
    break;

    case Directions::Top_Left:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_ext_data[i][j] = target;
        }
      }
    break;

    case Directions::Top:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkSize; j++){
          m_ext_data[i][j+ChunkOverlap] = target;
        }
      }
    break;

    case Directions::Top_Right:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_ext_data[i][j + ChunkSize + ChunkOverlap] = target;
        }
      }
    break;

    case Directions::Right:
      for(unsigned i = 0; i < ChunkSize; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_ext_data[i + ChunkOverlap][j + ChunkSize + ChunkOverlap] = target;
        }
      }
    break;

    case Directions::Bottom_Right:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_ext_data[i + ChunkSize + ChunkOverlap][j + ChunkSize + ChunkOverlap] = target;
        }
      }
    break;
  }

}

void Chunk::Bind(Directions Side, Chunk& other){
  switch(Side){
    case Directions::Bottom:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkSize; j++){
          m_ext_data[i+ChunkOverlap + ChunkSize][j + ChunkOverlap] = &other.m_data[i][j];
        }
      }
    break;

    case Directions::Bottom_Left:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_ext_data[i + ChunkOverlap + ChunkSize][j] = &other.m_data[i][j + ChunkSize - ChunkOverlap];
        }
      }
    break;

    case Directions::Left:
      for(unsigned i = 0; i < ChunkSize; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_ext_data[i + ChunkOverlap][j] = &other.m_data[i][j + ChunkSize - ChunkOverlap];
        }
      }
    break;

    case Directions::Top_Left:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_ext_data[i][j] = &other.m_data[i + ChunkSize - ChunkOverlap][j + ChunkSize - ChunkOverlap];
        }
      }
    break;

    case Directions::Top:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkSize; j++){
          m_ext_data[i][j+ChunkOverlap] = &other.m_data[i + ChunkSize - ChunkOverlap][j];
        }
      }
    break;

    case Directions::Top_Right:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_ext_data[i][j + ChunkSize + ChunkOverlap] = &other.m_data[i + ChunkSize - ChunkOverlap][j];
        }
      }
    break;

    case Directions::Right:
      for(unsigned i = 0; i < ChunkSize; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_ext_data[i + ChunkOverlap][j + ChunkSize + ChunkOverlap] = &other.m_data[i][j];
        }
      }
    break;

    case Directions::Bottom_Right:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_ext_data[i + ChunkSize + ChunkOverlap][j + ChunkSize + ChunkOverlap] = &other.m_data[i][j];
        }
      }
    break;
  }

}

