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
  m_render_next = true;
  m_color_data = (uint32_t*) malloc(4*ChunkSize*ChunkSize);
  Refresh();

}

Chunk::~Chunk(){
  for(unsigned i = ChunkOverlap; i < ChunkSize + ChunkOverlap; i++){
    for(unsigned j = ChunkOverlap; j < ChunkSize + ChunkOverlap; j++){
      delete m_data[i][j];
    }
  }
}

void Chunk::SetManager(WorldManager* manager){
  m_manager = manager;
  m_processor.SetManager(manager);
}

void Chunk::SetWorldPosition(int x, int y){
  m_world_pos_x = x;
  m_world_pos_y = y;
  m_processor.SetWorldPosition(x, y);
}

void Chunk::Update(){
  uint64_t changed = 0;
  for(int i = 0; i < SubChunks*SubChunks; i+=8){
    changed |= *((uint64_t *)((&m_sub_chunks[0])+i));
  }
  if(!changed){
    return;
  }
  m_render_next = true;


  for(unsigned i = ChunkSize + ChunkOverlap - 1; i >= ChunkOverlap; i--){
    if(i&1) for(unsigned j = ChunkOverlap; j < ChunkSize + ChunkOverlap; j++){
       if(m_sub_chunks[((i-ChunkOverlap)>>SubChunkShift)*SubChunks + ((j-ChunkOverlap)>>SubChunkShift)] == 0){
        j+=SubChunkSize-1;
      } else if(m_data[i][j]->checked == false){
        m_data[i][j]->checked = true;
        m_processor.Update(i, j);
      }
    } else for(unsigned j = ChunkSize + ChunkOverlap - 1; j >= ChunkOverlap; j--){
       if(m_sub_chunks[((i-ChunkOverlap)>>SubChunkShift)*SubChunks + ((j-ChunkOverlap)>>SubChunkShift)] == 0){
        j-=SubChunkSize-1;
      } else if(m_data[i][j]->checked == false){
        m_data[i][j]->checked = true;
        m_processor.Update(i, j);
      }
    }
  }

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

void Chunk::UpdateColors(){
  for(unsigned i = 0; i < ChunkSize; i++){
    for(unsigned j = 0; j < ChunkSize; j++){
      m_color_data[i * ChunkSize + j] = GetColor(m_data[i + ChunkOverlap][j + ChunkOverlap]->type);
    }
  }
}

void Chunk::Render(sf::RenderTarget& window, sf::FloatRect cameraBounds){
  if(!m_sprite.getGlobalBounds().intersects(cameraBounds)){
    return;
  }
#if !CHUNK_DEBUG
  if(!m_render_next){
      window.draw(m_sprite);
      return;
  }
#endif // CHUNK_DEBUG

  UpdateColors();
  m_texture.update((uint8_t*)m_color_data, ChunkSize, ChunkSize, 0, 0);
  window.draw(m_sprite);

  // highlight updated subchunks
#if CAMERA_DEBUG
  sf::RectangleShape highlight(sf::Vector2f(SubChunkSize, SubChunkSize));
  highlight.setFillColor(sf::Color(255,0,0,100));
  for(int i = 0; i < SubChunks; i++){
    for(int j = 0; j < SubChunks; j++){
      if(m_sub_chunks[i*SubChunks + j]){
        highlight.setPosition(j*SubChunkSize + m_sprite.getPosition().x, i*SubChunkSize + m_sprite.getPosition().y);
        window.draw(highlight);
      }
    }
  }
#endif // CAMERA_DEBUG

  m_render_next = false;
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
    p |= UpdateMask;
  }
}
