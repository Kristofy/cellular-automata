#include "../include/processor.hpp"

void Processor::Update(int y, int x){

  bool ok;
  int potentialEnergy;
  int my_placex, my_placey;

  Entity* curr = m_world[y][x];
        int speed = (int)curr->speed;
        switch(curr->type){
            case Air:
            break;
            case Sand:
                // Sand phisics handling ext_data
                UpdateEntitySpeed(curr);
                //std::cout<<"Sand falling with : "<<curr->speed<<std::endl;
                // falling down
                ok = true;
                potentialEnergy = speed > 2? speed:2;
                my_placey = y+potentialEnergy;
                for(int i = 1; i <= potentialEnergy; i++){
                   if(m_world[y+i][x]->type != Type::Air || m_world[y+i][x]->moved){
                       ok = (i != 1);
                       my_placey = y+(i-1);
                       break;
                   }
                }
                if(ok){
                    Move(x,y,x,my_placey);
                    break;
                }
/*
                // going to the right
                ok = (speed>0);
                my_placey = y-speed;
                my_placex = x+speed;
                for(int i = 1; i <= speed; i++){
                   if(m_world[x+i][y-i].type != Type::Air || m_world[x+i][y-i].moved){
                        ok = (i != 1);
                        my_placey = y-(i-1);
                        my_placex = x+(i-1);
                        break;
                   }
                }

                if(ok){
                    m_world[x][y].speed*=SandFriction;
                    Move(x,y,my_placex,my_placey);
                    break;
                }


                ok = (speed>0);
                my_placey = y-speed;
                my_placex = x-speed;
                for(int i = 1; i <= speed; i++){
                   if(m_world[x-i][y-i].type != Type::Air || m_world[x-i][y-i].moved){
                        ok = (i != 1);
                        my_placey = y-(i-1);
                        my_placex = x-(i-1);
                        break;
                   }
                }

                if(ok){
                    m_world[x][y].speed*=SandFriction;
                    Move(x,y,my_placex,my_placey);
                    break;
                }

                m_world[x][y].speed *= SandFriction;
                // if(m_world[x][y].speed < 1){
                //     m_world[x][y].speed = 1;
                // }

            break;
            case Stone:
            break;
            case Water:
                // Water phisics handling
                UpdateEntitySpeed(curr);
                // falling down
                ok = true;

                potentialEnergy = speed > 2? speed:2;
                my_placey = y-potentialEnergy;
                for(int i = 1; i <= potentialEnergy; i++){
                   if(m_world[x][y-i].type != Type::Air){
                       ok = (i != 1);
                       my_placey = y-(i-1);
                       break;
                   }
                }
                if(ok){
                    Move(x,y,x,my_placey);
                    break;
                }

                // going to the right
                ok = (speed > 0);
                my_placey = y-speed;
                my_placex = x+speed;
                for(int i = 1; i <= speed; i++){
                   if(m_world[x+i][y-i].type != Type::Air || m_world[x+i][y-i].moved){
                        ok = (i != 1);
                        my_placey = y-(i-1);
                        my_placex = x+(i-1);
                        break;
                   }
                }

                if(ok){
                    m_world[x][y].speed*=WaterFriction;
                    Move(x,y, my_placex, my_placey);

                    break;
                }


                // going left
                ok = (speed > 0);
                my_placey = y-speed;
                my_placex = x-speed;
                for(int i = 1; i <= speed; i++){
                   if(m_world[x-i][y-i].type != Type::Air || m_world[x-i][y-i].moved){
                        ok = (i != 1);
                        my_placey = y-(i-1);
                        my_placex = x-(i-1);
                        break;
                   }
                }

                if(ok){
                    m_world[x][y].speed*=WaterFriction;
                    Move(x,y, my_placex, my_placey);

                    break;
                }

                 // going side ways left
                ok = (speed > 0);
                my_placex = x-speed;
                for(int i = 1; i <= speed; i++){

                    // if(m_world[x-i][y].type != Type.Air && !m_world[x+1][y-i].moved){
                    //     ok = (i != 1);
                    //     my_placex = x-(i-1);
                    //     break;
                    // } else
                    if(m_world[x-i][y].type != Type::Air || m_world[x-i][y].moved){
                        ok = (i!=1);
                        my_placex = x-(i-1);
                        break;
                    }

                }


                if(ok){
                    m_world[x][y].speed*=WaterFriction;
                    Move(x,y,my_placex,y);

                    break;
                }

                // going side ways right
                ok = (speed > 0);
                my_placex =x+speed;
                for(int i = 1; i <= speed; i++){
                    // if(m_world[x+i][y].type != Type.Air && !m_world[x+1][y-i].moved){
                    //     ok = (i != 1);
                    //     my_placex = x+(i-1);
                    //     break;
                    // } else
                    if(m_world[x+i][y].type != Type::Air || m_world[x+i][y].moved){
                        ok = (i!=1);
                        my_placex = x+(i-1);

                        break;
                    }
                }

                if(ok){
                    m_world[x][y].speed*=WaterFriction;
                    Move(x,y,my_placex,y);
                    break;
                }


                m_world[x][y].speed *= WaterFriction;
               break;
            default:
                puts("An Update case not handled!");
            break;*/
        }
}

void Processor::UpdateEntitySpeed(Entity* curr){
    curr->acceleration += Gravity;
    curr->speed += curr->acceleration;
    if(curr->speed > SpeedLimit){
        curr->speed = SpeedLimit;
    }
    curr->acceleration = 0;
}
