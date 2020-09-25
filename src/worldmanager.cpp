#include "worldmanager.hpp"

WorldManager::WorldManager()
:m_nope(Type::Stone), m_isBordersVisible(false), m_chunkBorders(sf::PrimitiveType::Lines, (HorizontalChunks+1)*4 + (VerticalChunks+1)*4)
{
  std::cout << "World manager init started\n";
  std::cout << "Setup chunk positions in World Space\n";
  // Setup chunk positions in World Space
  for(int i = 0; i < VerticalChunks; i++){
    for(int j = 0; j < HorizontalChunks; j++){
      m_chunks[i*HorizontalChunks + j].SetPosition(i*ChunkSize, j*ChunkSize);
      m_chunks[i*HorizontalChunks + j].SetWorldPosition(j, i);
      m_chunks[i*HorizontalChunks + j].SetManager(this);
    }
  }

  std::cout << "Binding parts\n";

  // Binding Right parts
  for(int i = 0; i < VerticalChunks; i++){
    for(int j = 0; j < HorizontalChunks - 1; j++){
      m_chunks[i*HorizontalChunks + j].Bind(Directions::Right, m_chunks[i*HorizontalChunks + j + 1]);
    }
  }

  // Binding Bottom Right parts
  for(int i = 0; i < VerticalChunks - 1; i++){
    for(int j = 0; j < HorizontalChunks - 1; j++){
      m_chunks[i*HorizontalChunks + j].Bind(Directions::Bottom_Right, m_chunks[(i+1)*HorizontalChunks + j + 1]);
    }
  }

  // Binding Bottom parts
  for(int i = 0; i < VerticalChunks - 1; i++){
    for(int j = 0; j < HorizontalChunks; j++){
      m_chunks[i*HorizontalChunks + j].Bind(Directions::Bottom, m_chunks[(i+1)*HorizontalChunks + j]);
    }
  }

  // Binding Bottom Left parts
  for(int i = 0; i < VerticalChunks - 1; i++){
    for(int j = 1; j < HorizontalChunks; j++){
      m_chunks[i*HorizontalChunks + j].Bind(Directions::Bottom_Left, m_chunks[(i+1)*HorizontalChunks + j - 1]);
    }
  }

  // Binding Left parts
  for(int i = 0; i < VerticalChunks; i++){
    for(int j = 1; j < HorizontalChunks; j++){
      m_chunks[i*HorizontalChunks + j].Bind(Directions::Left, m_chunks[i*HorizontalChunks + j - 1]);
    }
  }

  // Binding Top Left parts
  for(int i = 1; i < VerticalChunks; i++){
    for(int j = 1; j < HorizontalChunks; j++){
      m_chunks[i*HorizontalChunks + j].Bind(Directions::Top_Left, m_chunks[(i-1)*HorizontalChunks + j - 1]);
    }
  }

  // Binding Top parts
  for(int i = 1; i < VerticalChunks; i++){
    for(int j = 0; j < HorizontalChunks; j++){
      m_chunks[i*HorizontalChunks + j].Bind(Directions::Top, m_chunks[(i-1)*HorizontalChunks + j]);
    }
  }

  // Binding Top Right parts
  for(int i = 1; i < VerticalChunks; i++){
    for(int j = 0; j < HorizontalChunks - 1; j++){
      m_chunks[i*HorizontalChunks + j].Bind(Directions::Top_Right, m_chunks[(i-1)*HorizontalChunks + j + 1]);
    }
  }

  std::cout << "Placing the border\n";
  // Placing the border
  for(int j = 0; j < HorizontalChunks; j++){
    m_chunks[j].SetBorder(Directions::Top, &m_nope);
    m_chunks[j].SetBorder(Directions::Top_Right, &m_nope);
    m_chunks[j].SetBorder(Directions::Top_Left, &m_nope);

    m_chunks[(VerticalChunks-1)*HorizontalChunks + j].SetBorder(Directions::Bottom, &m_nope);
    m_chunks[(VerticalChunks-1)*HorizontalChunks + j].SetBorder(Directions::Bottom_Right, &m_nope);
    m_chunks[(VerticalChunks-1)*HorizontalChunks + j].SetBorder(Directions::Bottom_Left, &m_nope);
  }

  for(int i = 0; i < VerticalChunks; i++){
    m_chunks[i*HorizontalChunks].SetBorder(Directions::Left, &m_nope);
    m_chunks[i*HorizontalChunks].SetBorder(Directions::Top_Left, &m_nope);
    m_chunks[i*HorizontalChunks].SetBorder(Directions::Bottom_Left, &m_nope);

    m_chunks[i*HorizontalChunks + HorizontalChunks - 1].SetBorder(Directions::Right, &m_nope);
    m_chunks[i*HorizontalChunks + HorizontalChunks - 1].SetBorder(Directions::Top_Right, &m_nope);
    m_chunks[i*HorizontalChunks + HorizontalChunks - 1].SetBorder(Directions::Bottom_Right, &m_nope);
  }

  // setting up border Vertices

  int vertexIndex = 0;
  for(int i = 0; i <= HorizontalChunks; i++){
    int x = i*ChunkSize;
    m_chunkBorders[vertexIndex+0].position = sf::Vector2f(x, 0);
    m_chunkBorders[vertexIndex+1].position = sf::Vector2f(x, WorldHeight);
    m_chunkBorders[vertexIndex+2].position = sf::Vector2f(x-1, 0);
    m_chunkBorders[vertexIndex+3].position = sf::Vector2f(x-1, WorldHeight);
    m_chunkBorders[vertexIndex+0].color = sf::Color::Red;
    m_chunkBorders[vertexIndex+1].color = sf::Color::Red;
    m_chunkBorders[vertexIndex+2].color = sf::Color::Red;
    m_chunkBorders[vertexIndex+3].color = sf::Color::Red;
    vertexIndex += 4;
  }

  for(int i = 0; i <= VerticalChunks; i++){
    int y = i*ChunkSize;
    m_chunkBorders[vertexIndex+0].position = sf::Vector2f(0, y);
    m_chunkBorders[vertexIndex+1].position = sf::Vector2f(WorldWidth, y);
    m_chunkBorders[vertexIndex+2].position = sf::Vector2f(0, y+1);
    m_chunkBorders[vertexIndex+3].position = sf::Vector2f(WorldWidth, y+1);
    m_chunkBorders[vertexIndex+0].color = sf::Color::Red;
    m_chunkBorders[vertexIndex+1].color = sf::Color::Red;
    m_chunkBorders[vertexIndex+2].color = sf::Color::Red;
    m_chunkBorders[vertexIndex+3].color = sf::Color::Red;
    vertexIndex += 4;

  }

}

void WorldManager::Update(){
  for(int i = VerticalChunks-1; i >= 0; i--){
    if(i&1) for(int j = 0; j < HorizontalChunks; j++){
      m_chunks[i*HorizontalChunks + j].Update();
    }else for(int j = HorizontalChunks - 1; j >= 0; j--){
      m_chunks[i*HorizontalChunks + j].Update();
    }
  }
}

void WorldManager::Render(sf::RenderTarget& window){
  sf::Vector2f viewCenter(window.getView().getCenter());
  sf::Vector2f viewSize(window.getView().getSize());
  sf::FloatRect cameraBounds(viewCenter - viewSize / 2.f, viewSize);
  for(int i = 0; i < HorizontalChunks*VerticalChunks; i++){
    m_chunks[i].Render(window, cameraBounds);
  }

  if(m_isBordersVisible)
    window.draw(m_chunkBorders);
}

Entity& WorldManager::Get(int i, int j){
  return *m_chunks[(i>>ChunkShift)*HorizontalChunks + (j>>ChunkShift)].m_data[(i&ChunkMod) + ChunkOverlap][(j&ChunkMod) + ChunkOverlap];
}

void WorldManager::Refresh(int i, int j){
  m_chunks[(i>>ChunkShift)*HorizontalChunks + (j>>ChunkShift)].m_sub_chunks[((i&ChunkMod)>>SubChunkShift) * SubChunks + (((j&ChunkMod)>>SubChunkShift)&SubChunkMod)] |= UpdateMask;
}

void WorldManager::ToggleChunkBorders(){
  m_isBordersVisible = !m_isBordersVisible;
}

void WorldManager::RefreshAll(){
  for(int i = 0; i < HorizontalChunks*VerticalChunks; i++){
    m_chunks[i].Refresh();
  }
}

void WorldManager::UpdateSubChunk(int x, int y, int subX, int subY){
    if(x >= 0 && x < HorizontalChunks && y >= 0 && y < VerticalChunks){
      m_chunks[y*HorizontalChunks + x].m_sub_chunks[subY*SubChunks + subX] |= UpdateMask;
    }
}

bool WorldManager::IsBorderVisible(){
  return m_isBordersVisible;
}
