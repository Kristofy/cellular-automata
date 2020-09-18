#include "worldmanager.hpp"

WorldManager::WorldManager()
:m_nope(Type::Stone)
{
  std::cout << "World manager init started\n";
  std::cout << "Setup chunk positions in World Space\n";
  // Setup chunk positions in World Space
  for(int i = 0; i < VerticalChunks; i++){
    for(int j = 0; j < HorizontalChunks; j++){
      m_chunks[i*HorizontalChunks + j].SetPosition(i*ChunkSize, j*ChunkSize);
    }
  }

  std::cout << "Binding all of the Existing Right, Bottom Right and Bottom chunk parts Together\n";
  // Binding all of the Existing Right, Bottom Right and Bottom chunk parts Together
  for(int i = 0; i < VerticalChunks-1; i++){
    for(int j = 0; j < HorizontalChunks-1; j++){
      m_chunks[i*HorizontalChunks + j].Bind(Directions::Right, m_chunks[i*HorizontalChunks + j + 1]);
      m_chunks[i*HorizontalChunks + j].Bind(Directions::Bottom_Right, m_chunks[(i+1)*HorizontalChunks + j +1]);
      m_chunks[i*HorizontalChunks + j].Bind(Directions::Bottom, m_chunks[(i+1)*HorizontalChunks + j]);
    }
  }

  std::cout << "Binding all of the Existing Left, Top Left and Top chunk parts Together\n";
  // Binding all of the Existing Left, Top Left and Top chunk parts Together
  for(int i = 1; i < VerticalChunks; i++){
    for(int j = 1; j < HorizontalChunks; j++){
      m_chunks[i*HorizontalChunks + j].Bind(Directions::Left, m_chunks[i*HorizontalChunks + j - 1]);
      m_chunks[i*HorizontalChunks + j].Bind(Directions::Top_Left, m_chunks[(i-1)*HorizontalChunks + j - 1]);
      m_chunks[i*HorizontalChunks + j].Bind(Directions::Top, m_chunks[(i-1)*HorizontalChunks + j]);
    }
  }

  std::cout << "Binding all of the Existing Bottom Lefts\n";
  // Binding all of the Existing Bottom Lefts
  for(int i = 0; i < VerticalChunks - 1; i++){
    for(int j = 1; j < HorizontalChunks; j++){
      m_chunks[i*HorizontalChunks + j].Bind(Directions::Bottom_Left, m_chunks[(i+1)*HorizontalChunks + j - 1]);
    }
  }


  std::cout << "Binding all of the Existing Top Rights\n";
  // Binding all of the Existing Top Rights
  for(int i = 1; i < VerticalChunks; i++){
    for(int j = 0; j < HorizontalChunks - 1; j++){
      m_chunks[i*HorizontalChunks + j].Bind(Directions::Bottom_Left, m_chunks[(i-1)*HorizontalChunks + j + 1]);
    }
  }

  std::cout << "Fixing Bottom middle\n";
  // Fixing Bottom middle
  for(int j = 0; j < HorizontalChunks - 1; j++){
    m_chunks[(VerticalChunks-1)*HorizontalChunks + j].Bind(Directions::Right, m_chunks[(VerticalChunks-1)*HorizontalChunks + j + 1]);
  }


  std::cout << "Fixing Left Middle\n";
  // Fixing Left Middle
  for(int i = 1; i < VerticalChunks; i++){
    m_chunks[i*HorizontalChunks].Bind(Directions::Top, m_chunks[(i-1)*HorizontalChunks]);
  }

  std::cout << "Fixing Top Middle\n";
  // Fixing Top Middle
  for(int j = 1; j < HorizontalChunks; j++){
    m_chunks[j].Bind(Directions::Left, m_chunks[j - 1]);
  }

  std::cout << "Fixing Right Middle\n";
  // Fixing Right Middle
  for(int i = 0; i < VerticalChunks - 1; i++){
    m_chunks[i*HorizontalChunks + HorizontalChunks - 1].Bind(Directions::Bottom, m_chunks[(i+1)*HorizontalChunks + HorizontalChunks - 1]);
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

}

void WorldManager::Update(){
  for(int i = 0; i < HorizontalChunks*VerticalChunks; i++){
    m_chunks[i].Update();
  }
}

void WorldManager::Render(sf::RenderTarget& window){
  for(int i = 0; i < HorizontalChunks*VerticalChunks; i++){
    m_chunks[i].Render(window);
  }
}

Entity& WorldManager::Get(int i, int j){
  return m_chunks[(i/ChunkSize)*HorizontalChunks + j/ChunkSize].m_data[i%ChunkSize][j%ChunkSize];
}