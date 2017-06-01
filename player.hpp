#pragma once

#include "api.hpp"

class Player {

  public:
    static const int SHAPE_SIZE = 375;
    static const int SHAPE_W = 32;
    static const int SHAPE_H = 25;
    static const Pixel SHAPE[];

    int x;
    int y;
    
    Player(int _x, int _y);
    
    void Move(float accel_x, float accel_y);
    Bullet EmitBullet();
  
  private:
    static const int BULLET_SPEED = -5; 
};

