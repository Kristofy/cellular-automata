#include "../include/processor.hpp"
#include "../include/worldmanager.hpp"

extern float fastestElement;

void Processor::Update(unsigned y, unsigned x){
  bool ok;
  unsigned potentialEnergy;
  unsigned my_placex, my_placey;

  m_curr = m_world[y][x];
  fastestElement = (fastestElement > m_curr->speed) ? fastestElement : m_curr->speed;
  int speed = (int)m_curr->speed;
  switch(m_curr->type){
    case Air:
    break;
    case Sand:
      // Setup
      ok = true;
      potentialEnergy = speed > BaseEnergy ? speed : BaseEnergy;

      // Falling Downwards
      my_placey = y + potentialEnergy;
      for(int i = 1; i <= potentialEnergy; i++){
        if(m_world[y+i][x]->type != Type::Air){
          ok = (i != 1);
          my_placey = y + (i - 1);
          break;
        }
      }
      if(ok){
        Swap(y,x,my_placey,x);
        m_curr->acceleration += Gravity;
        break;
      }

      // Falling Right

      ok = true;
      my_placey = y+potentialEnergy;
      my_placex = x+potentialEnergy;
      for(int i = 1; i <= potentialEnergy; i++){
        if(m_world[y+i][x+i]->type != Type::Air){
          ok = (i != 1);
          my_placey = y + (i - 1);
          my_placex = x + (i - 1);
          break;
        }
      }

      if(ok){
        Swap(y, x, my_placey, my_placex);
        m_curr->acceleration += GravitySide - SandFriction;
        break;
      }

      // Falling Left
      ok = true;
      my_placey = y + potentialEnergy;
      my_placex = x - potentialEnergy;
      for(int i = 1; i <= potentialEnergy; i++){
        if(m_world[y+i][x-i]->type != Type::Air){
          ok = (i != 1);
          my_placey = y + (i - 1);
          my_placex = x - (i - 1);
          break;
        }
      }

      if(ok){
        Swap(y, x, my_placey, my_placex);
        m_curr->acceleration += GravitySide - SandFriction;
        break;
      }

      // If not moving loose speed
      m_curr->speed *= Decay;
    break;

    case Stone:
    break;

    case Water:
      // Setup
      ok = true;
      potentialEnergy = speed > 2? speed:2;

      // Falling Downwards
      my_placey = y + potentialEnergy;
      for(int i = 1; i <= potentialEnergy; i++){
        if(m_world[y+i][x]->type != Type::Air){
          ok = (i != 1);
          my_placey = y+(i-1);
          break;
        }
      }

      if(ok){
        Swap(y,x,my_placey,x);
        m_curr->acceleration += Gravity;
        break;
      }

      // Falling Right
      ok = true;
      my_placey = y + potentialEnergy;
      my_placex = x + potentialEnergy;
      for(int i = 1; i <= potentialEnergy; i++){
        if(m_world[y+i][x+i]->type != Type::Air){
          ok = (i != 1);
          my_placey = y + (i - 1);
          my_placex = x + (i - 1);
          break;
        }
      }

      if(ok){
        Swap(y, x, my_placey, my_placex);
        m_curr->acceleration = GravitySide - WaterFriction;
        break;
      }


      // Falling Left
      ok = true;
      my_placey = y + potentialEnergy;
      my_placex = x - potentialEnergy;
      for(int i = 1; i <= potentialEnergy; i++){
        if(m_world[y+i][x-i]->type != Type::Air){
          ok = (i != 1);
          my_placey = y + (i - 1);
          my_placex = x - (i - 1);
          break;
        }
      }

      if(ok){
        Swap(y, x, my_placey, my_placex);
        m_curr->acceleration += GravitySide - WaterFriction;
        break;
      }

      // Flowing Right
      ok = (speed > 0);
      my_placex = x+speed;
      for(int i = 1; i <= speed; i++){
        if(m_world[y][x+i]->type != Type::Air){
          ok = (i!=1);
          my_placex = x + (i - 1);
          break;
        }
      }

      if(ok){
        Swap(y, x, y, my_placex);
        m_curr->acceleration -= Mu*WaterFriction;
        break;
      }

      // Flowing Left
      ok = (speed > 0);
      my_placex = x-speed;
      for(int i = 1; i <= speed; i++){
        if(m_world[y][x-i]->type != Type::Air){
          ok = (i!=1);
          my_placex = x - (i - 1);
          break;
        }
      }

      if(ok){
        Swap(y, x, y, my_placex);
        m_curr->acceleration -= Mu*WaterFriction;
        break;
      }

      // If not moving loose speed
      m_world[y][x]->speed *= Decay;
    break;

    default:
    puts("An Update case not handled!");
    break;
  }

  m_curr->speed += m_curr->acceleration;
  if(m_curr->speed > SpeedLimit){
    m_curr->speed = SpeedLimit;
  } else if (m_curr->speed < 0){
    m_curr->speed = 0;
  }
  m_curr->acceleration = 0;
}

void Processor::Swap(int y, int x, int y2, int x2){
  m_world[y2][x2]->checked = true;

  Type tmp_type = std::move(m_world[y][x]->type);
  m_world[y][x]->type = std::move(m_world[y2][x2]->type);
  m_world[y2][x2]->type = std::move(tmp_type);

  float tmp_speed = std::move(m_world[y][x]->speed);
  m_world[y][x]->speed = std::move(m_world[y2][x2]->speed);
  m_world[y2][x2]->speed = std::move(tmp_speed);

  m_curr = m_world[y2][x2];

  int firstx = (x - ChunkOverlap)>>SubChunkShift;
  int firsty = (y - ChunkOverlap)>>SubChunkShift;
  // TODO: Fix it, its working but ugly and slow
  for(int dy = -1; dy <= 1; dy++){
    for(int dx = -1; dx <= 1; dx++){
    //    if(firstx+dx == ((x - ChunkOverlap + dx*SpeedLimit)>>SubChunkShift) && firsty+dy == ((y - ChunkOverlap + dy*SpeedLimit)>>SubChunkShift )){
          if(firstx+dx>=0 && firstx+dx < SubChunks && firsty+dy>=0 && firsty+dy < SubChunks){
            m_sub_chunks[(firsty+dy)*SubChunks + firstx+dx] = UpdateMask;
          }else{
            if( abs(dx) + abs(dy) == 1){
              m_manager->UpdateSubChunk(m_world_pos_x + dx, m_world_pos_y + dy, (firstx+dx+(int)SubChunks)%SubChunks, (firsty+dy+(int)SubChunks)%SubChunks );
            }
          }
//        }
    }
  }

}

void Processor::SetWorldPosition(int x, int y){
  m_world_pos_x = x;
  m_world_pos_y = y;
}

void Processor::SetManager(WorldManager* manager){
  m_manager = manager;
}
