#pragma once

#include "api.hpp"

class Enemy {

  public:
    static const int SHAPE_SIZE = 140;
    static const int SHAPE_W = 15;
    static const int SHAPE_H = 20;
    static const Pixel SHAPE[];
   
    int x;
    int y;
    
    Enemy(int _x, int _y);
    
    void Move();
    Bullet EmitBullet();
  private:
    static const int BULLET_SPEED = -5;
};

