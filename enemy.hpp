#pragma once

#include <TFT_ILI9163C.h>
#include "api.hpp"

class Enemy {

  public:
    static const int SHAPE_SIZE = 140;
    static const int SHAPE_W = 20;
    static const int SHAPE_H = 15;
    static const Pixel SHAPE[];
   
    int x;
    int y;
    
    Enemy(int _x, int _y);
    
    void Move();
    void Draw(TFT_ILI9163C tft);
    Bullet EmitBullet();
    
  private:
    static const int BULLET_SPEED = -5;
};

