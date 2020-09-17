#include "../include/processor.hpp"

void Processor::Update(int y, int x){

  bool ok;
  int potentialEnergy;
  int my_placex, my_placey;

  curr = m_world[y][x];
        int speed = (int)curr->speed;
        switch(curr->type){
            case Air:
            break;
            case Sand:
                // Sand phisics handling ext_data

                //std::cout<<"Sand falling with : "<<curr->speed<<std::endl;
                // falling down
                ok = true;
                potentialEnergy = speed > 2? speed:2;
                my_placey = y+potentialEnergy;
                for(int i = 1; i <= potentialEnergy; i++){
                   if(m_world[y+i][x]->type != Type::Air /*|| m_world[y+i][x]->moved*/){
                       ok = (i != 1);
                       my_placey = y+(i-1);
                       break;
                   }
                }
                if(ok){
                    Swap(y,x,my_placey,x);
                    curr->acceleration += Gravity;
                    break;
                }

                // going to the right

                ok = (speed>0);
                my_placey = y+speed;
                my_placex = x+speed;
                for(int i = 1; i <= speed; i++){
                   if(m_world[y+i][x+i]->type != Type::Air || m_world[y+i][x+i]->moved){
                        ok = (i != 1);
                        my_placey = y+(i-1);
                        my_placex = x+(i-1);
//                        if(m_world[my_placex][my_placey]->type != Type::Air || !m_world[my_placex][my_placey]->moved){
//                            puts("HUGE ERROR");
//                        }
                        break;
                   }
                }

               if(ok){
                    Swap(y, x, my_placey, my_placex);
                    curr->acceleration += sqrt(2)/2*Gravity - SandFriction;
                    break;
                }


                ok = (speed>0);
                my_placey = y+speed;
                my_placex = x-speed;
                for(int i = 1; i <= speed; i++){
                   if(m_world[y+i][x-i]->type != Type::Air || m_world[y+i][x-i]->moved){
                        ok = (i != 1);
                        my_placey = y+(i-1);
                        my_placex = x-(i-1);
                        break;
                   }
                }

                if(ok){
                    Swap(y, x, my_placey, my_placex);
                    curr->acceleration += sqrt(2)/2*Gravity - SandFriction;
                    break;
                }

                curr->speed *= Decay;

            break;

            case Stone:
            break;
            case Water:
                // Water phisics handling
                // falling down
                ok = true;

                potentialEnergy = speed > 2? speed:2;
                my_placey = y+potentialEnergy;
                for(int i = 1; i <= potentialEnergy; i++){
                   if(m_world[y+i][x]->type != Type::Air /*|| m_world[y+i][x]->moved*/){
                       ok = (i != 1);
                       my_placey = y+(i-1);
                       break;
                   }
                }
                if(ok){
                    Swap(y,x,my_placey,x);
                    curr->acceleration += Gravity;
                    break;
                }

                // going to the right
                ok = (speed > 0);
                my_placey = y+speed;
                my_placex = x+speed;
                for(int i = 1; i <= speed; i++){
                   if(m_world[y+i][x+i]->type != Type::Air || m_world[y+i][x+i]->moved){
                        ok = (i != 1);
                        my_placey = y+(i-1);
                        my_placex = x+(i-1);
                        break;
                   }
                }

                if(ok){
                    Swap(y, x, my_placey, my_placex);
                    curr->acceleration = sqrt(2)/2 * Gravity - WaterFriction;

                    break;
                }


                // going left
                ok = (speed > 0);
                my_placey = y+speed;
                my_placex = x-speed;
                for(int i = 1; i <= speed; i++){
                   if(m_world[y+i][x-i]->type != Type::Air || m_world[y+i][x-i]->moved){
                        ok = (i != 1);
                        my_placey = y+(i-1);
                        my_placex = x-(i-1);
                        break;
                   }
                }

                if(ok){
                    Swap(y, x, my_placey, my_placex);
                    curr->acceleration += sqrt(2)/2 * Gravity - WaterFriction;
                    break;
                }

                 // going side ways left
                ok = (speed > 0);
                my_placex = x-speed;
                for(int i = 1; i <= speed; i++){
                    if(m_world[y][x-i]->type != Type::Air || m_world[y][x-i]->moved){
                        ok = (i!=1);
                        my_placex = x-(i-1);
                        break;
                    }

                }


                if(ok){
                    Swap(y, x, y, my_placex);
                    curr->acceleration += Gravity - WaterFriction;

                    break;
                }

                // going side ways right
                ok = (speed > 0);
                my_placex = x+speed;
                for(int i = 1; i <= speed; i++){
                    if(m_world[y][x+i]->type != Type::Air || m_world[y][x+i]->moved){
                        ok = (i!=1);
                        my_placex = x+(i-1);

                        break;
                    }
                }

                if(ok){
                    Swap(y, x, y, my_placex);
                    curr->acceleration += Gravity - WaterFriction;
                    break;
                }


                m_world[y][x]->speed *= Decay;



               break;
            default:
                puts("An Update case not handled!");
            break;
        }

    curr->speed += curr->acceleration;
    if(curr->speed > SpeedLimit){
        curr->speed = SpeedLimit;
    } else if (curr->speed < 0){
        curr->speed = 0;
    }
    curr->acceleration = 0;
}
