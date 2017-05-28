#pragma once

#include "api.hpp"

class Enemy {

  public:
    static const int SHAPE_SIZE = 64;
    static const int SHAPE_W = 13;
    static const int SHAPE_H = 13;
    static const Pixel SHAPE[];
   
    int x;
    int y;
    
    Enemy(int _x, int _y);
    
    void Move();
    Bullet EmitBullet();
  private:
    static const int MAX_X = 128;
    static const int MAX_Y = 128;
    static const int BULLET_SPEED = -5;
};

