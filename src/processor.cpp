#include "../include/processor.hpp"

void Processor::Update(unsigned y, unsigned x){
  bool ok;
  unsigned potentialEnergy;
  unsigned my_placex, my_placey;

  m_curr = m_world[y][x];
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

void Processor::Swap(unsigned y, unsigned x, unsigned y2, unsigned x2){
  m_world[y2][x2]->checked = true;

  Type tmp_type = std::move(m_world[y][x]->type);
  m_world[y][x]->type = std::move(m_world[y2][x2]->type);
  m_world[y2][x2]->type = std::move(tmp_type);

  float tmp_speed = std::move(m_world[y][x]->speed);
  m_world[y][x]->speed = std::move(m_world[y2][x2]->speed);
  m_world[y2][x2]->speed = std::move(tmp_speed);

  m_curr = m_world[y2][x2];

  unsigned firstx = x>>SubChunkShift;
  unsigned firsty = y>>SubChunkShift;
//  m_sub_chunks[(y>>4)*SubChunks + (x>>4)] |= ((1<<5)-1)<<1;
//  m_sub_chunks[(y2>>4)*SubChunks + (x2>>4)] |= ((1<<5)-1)<<1;
//
//  printf("Swaped at position: %u == %u", (y2>>4)*SubChunks + (x2>>4), firsty*SubChunks + firstx);
  for(int dy = -1; dy <= 1; dy++){
    for(int dx = -1; dx <= 1; dx++){
      if(firstx+dx>=0 && firstx+dx < SubChunks && firsty+dy>=0 && firsty+dy< SubChunks){
       // if(((x+SpeedLimit)>>4) == firstx+dx && ((y+SpeedLimit)>>4) == firsty+dy){
          m_sub_chunks[(firsty+dy)*SubChunks + firstx+dx] = 0xfe;
      //  }
      }
    }
  }

}
