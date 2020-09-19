#include "../include/chunk.hpp"

Chunk::Chunk()
:m_processor(m_data, m_sub_chunks)
{
  for(uint8_t& p : m_sub_chunks){
    p=true;
  }

  for(unsigned i = ChunkOverlap; i < ChunkSize + ChunkOverlap; i++){
    for(unsigned j = ChunkOverlap; j < ChunkSize + ChunkOverlap; j++){
      m_data[i][j] = new Entity(Type::Air);
    }
  }

  m_texture.create(ChunkSize, ChunkSize);
  m_sprite.setTexture(m_texture);

  m_color_data = (uint32_t*) malloc(4*ChunkSize*ChunkSize);
  UpdateColors();
  Refresh();

}

void Chunk::Update(){

  for(unsigned i = ChunkSize + ChunkOverlap - 1; i >= ChunkOverlap; i--){
    for(unsigned j = ChunkOverlap; j < ChunkSize + ChunkOverlap; j++){
       if(m_sub_chunks[((i-ChunkOverlap)>>SubChunkShift)*SubChunks + ((j-ChunkOverlap)>>SubChunkShift)] == 0){
        j+=SubChunkSize-1;
      } else if(m_data[i][j]->checked == false){
        m_data[i][j]->checked = true;
        m_processor.Update(i, j);
      }
    }
  }

/*
  for(unsigned y = 0; y < SubChunks; y++){
    if(y&1)
    for(unsigned x = 0; x < SubChunks; x++){
      if(m_sub_chunks[y*SubChunks + x]&1){
        UpdateSubChunk(x, y);
      }
    }
    else for(unsigned x = SubChunks - 1; ~x; x--){
      if(m_sub_chunks[y*SubChunks + x]&1){
        UpdateSubChunk(x, y);
      }
    }
  }
*/
  for(unsigned i = ChunkOverlap; i < ChunkSize + ChunkOverlap; i++){
    for(unsigned j = ChunkOverlap; j < ChunkSize + ChunkOverlap; j++){
      if(m_sub_chunks[((i-ChunkOverlap)>>SubChunkShift)*SubChunks + ((j-ChunkOverlap)>>SubChunkShift)] == 0){
          j+=SubChunkSize-1;
       }else
          m_data[i][j]->checked = false;

    }
  }

  for(int i = 0; i < SubChunks*SubChunks; i++){
    m_sub_chunks[i] >>= 1;
  }
}

void Chunk::UpdateSubChunk(int x, int y){
  for(unsigned i = y*SubChunkSize + ChunkOverlap; i < (y+1)*SubChunkSize + ChunkOverlap; i++){
    for(unsigned j = x*SubChunkSize + ChunkOverlap; j < (x+1)*SubChunkSize + ChunkOverlap; j++){
      if(m_data[i][j]->checked == false){
        m_data[i][j]->checked = true;
        m_processor.Update(i, j);
      }
    }
  }
  for(unsigned i = y*SubChunkSize + ChunkOverlap; i < (y+1)*SubChunkSize + ChunkOverlap; i++){
    for(unsigned j = x*SubChunkSize + ChunkOverlap; j < (x+1)*SubChunkSize + ChunkOverlap; j++){
      m_data[j][i]->checked = false;
    }
  }
}

void Chunk::UpdateColors(){
  for(unsigned i = 0; i < ChunkSize; i++){
    for(unsigned j = 0; j < ChunkSize; j++){
      m_color_data[i * ChunkSize + j] = GetColor(m_data[i + ChunkOverlap][j + ChunkOverlap]->type);
    }
  }
}

void Chunk::Render(sf::RenderTarget& window){
  UpdateColors();
  m_texture.update((uint8_t*)m_color_data, ChunkSize, ChunkSize, 0, 0);
  window.draw(m_sprite);

  sf::RectangleShape highlight(sf::Vector2f(SubChunkSize, SubChunkSize));
  for(int i = 0; i < SubChunks; i++){
    for(int j = 0; j < SubChunks; j++){
      if(m_sub_chunks[i*SubChunks + j]&1){
        highlight.setPosition(j*SubChunkSize + m_sprite.getPosition().x, i*SubChunkSize + m_sprite.getPosition().y);
        highlight.setFillColor(sf::Color(255,0,0,100));
        window.draw(highlight);
      }
    }
  }

}

void Chunk::SetPosition(int y, int x){
  m_sprite.setPosition(x, y);
}

void Chunk::SetBorder(Directions Side, Entity* target){
  switch(Side){
    case Directions::Bottom:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkSize; j++){
          m_data[i+ChunkOverlap + ChunkSize][j + ChunkOverlap] = target;
        }
      }
    break;

    case Directions::Bottom_Left:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_data[i + ChunkOverlap + ChunkSize][j] = target;
        }
      }

    break;
    case Directions::Left:
      for(unsigned i = 0; i < ChunkSize; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_data[i + ChunkOverlap][j] = target;
        }
      }
    break;

    case Directions::Top_Left:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_data[i][j] = target;
        }
      }
    break;

    case Directions::Top:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkSize; j++){
          m_data[i][j+ChunkOverlap] = target;
        }
      }
    break;

    case Directions::Top_Right:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_data[i][j + ChunkSize + ChunkOverlap] = target;
        }
      }
    break;

    case Directions::Right:
      for(unsigned i = 0; i < ChunkSize; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_data[i + ChunkOverlap][j + ChunkSize + ChunkOverlap] = target;
        }
      }
    break;

    case Directions::Bottom_Right:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_data[i + ChunkSize + ChunkOverlap][j + ChunkSize + ChunkOverlap] = target;
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
          m_data[i+ChunkOverlap + ChunkSize][j + ChunkOverlap] = other.m_data[i + ChunkOverlap][j + ChunkOverlap];
        }
      }
    break;

    case Directions::Bottom_Left:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_data[i + ChunkOverlap + ChunkSize][j] = other.m_data[i + ChunkOverlap][j + ChunkSize];
        }
      }
    break;

    case Directions::Left:
      for(unsigned i = 0; i < ChunkSize; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_data[i + ChunkOverlap][j] = other.m_data[i + ChunkOverlap][j + ChunkSize];
        }
      }
    break;

    case Directions::Top_Left:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_data[i][j] = other.m_data[i + ChunkSize][j + ChunkSize];
        }
      }
    break;

    case Directions::Top:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkSize; j++){
          m_data[i][j+ChunkOverlap] = other.m_data[i + ChunkSize][j + ChunkOverlap];
        }
      }
    break;

    case Directions::Top_Right:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_data[i][j + ChunkSize + ChunkOverlap] = other.m_data[i + ChunkSize][j + ChunkOverlap];
        }
      }
    break;

    case Directions::Right:
      for(unsigned i = 0; i < ChunkSize; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_data[i + ChunkOverlap][j + ChunkSize + ChunkOverlap] = other.m_data[i + ChunkOverlap][j + ChunkOverlap];
        }
      }
    break;

    case Directions::Bottom_Right:
      for(unsigned i = 0; i < ChunkOverlap; i++){
        for(unsigned j = 0; j < ChunkOverlap; j++){
          m_data[i + ChunkSize + ChunkOverlap][j + ChunkSize + ChunkOverlap] = other.m_data[i + ChunkOverlap][j + ChunkOverlap];
        }
      }
    break;
  }

}

void Chunk::Refresh(){
  for(uint8_t& p : m_sub_chunks){
    p |= 1;
  }
}
