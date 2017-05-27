#pragma once

#include "api.hpp"

class Player {

  public:
    static const int SHAPE_SIZE = 133;
    static const int SHAPE_W = 27;
    static const int SHAPE_H = 27;
    int x;
    int y;
    
    Player(int _x, int _y);
    
    void Move(float accel_x, float accel_y);
    Bullet EmitBullet();

    Pixel shape[SHAPE_SIZE] = {
      { 9, 27 }, { 10, 27 }, { 11, 27 }, { 12, 27 }, { 13, 27 }, { 14, 27 }, { 15, 27 }, {16, 27 }, {17, 27}, {18, 27}, { 19, 27},
      { 6, 26}, { 7, 26}, { 8, 26}, { 20, 26}, { 21, 26}, { 22, 26},
      { 5, 25}, { 23, 25},
      { 4, 24}, {14, 24} ,{ 24, 24},
      { 5, 23}, { 13, 23}, { 15, 23}, { 23, 23},
      { 6, 22}, { 7, 22}, { 8, 22}, { 9, 22}, { 10, 22}, { 11, 22}, { 12, 22}, { 16, 22}, { 17, 22}, { 18, 22}, { 19, 22}, { 20, 22}, { 21, 22 }, { 22, 22}, 
      { 12, 21}, { 16, 21},
      { 12, 20}, { 16, 20}, 
      { 12, 19}, { 16, 19},
      { 11, 18}, { 17, 18},
      { 11, 17}, { 17, 17},
      { 11, 16}, { 17, 16},
      { 11, 15}, { 17, 15},
      { 11, 14}, { 17, 14},
      { 11, 13}, { 17, 13},
      { 11, 12}, { 17, 12},
      { 3, 11}, { 4, 11}, { 5, 11}, { 6, 11}, { 7, 11}, { 8, 11}, { 9, 11}, { 10, 11}, { 11, 11}, { 12, 11}, {13, 11}, {14, 11}, {15, 11}, {16, 11}, {17, 11}, {18, 11}, {19, 11}, {20, 11}, {21, 11}, {21, 11}, {22, 11}, {23, 11}, {24, 11}, {25, 11},
      {2, 10}, {26, 10},
      {1, 9}, {27, 9},
      {0, 8}, {28, 8},
      {1, 7}, {27, 7},
      {2, 6}, {26, 6},
      { 3, 5}, { 4, 5}, { 5, 5}, { 6, 5}, { 7, 5}, { 8, 5}, { 9, 5}, { 10, 5}, { 11, 5}, { 12, 5}, {13, 5}, {14, 5}, {15, 5}, {16, 5}, {17, 5}, {18, 5}, {19, 5}, {20, 5}, {21, 5}, {21, 5}, {22, 5}, {23, 5}, {24, 5}, {25, 5},
      { 11, 4}, { 17, 4},
      { 11, 3}, { 17, 3},
      { 12, 2}, { 16, 2}, 
      { 13, 1}, { 15, 1},
      { 11, 0}, { 12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 0}};

  private:
    static const int MAX_X = 128;
    static const int MAX_Y = 128;
    static const int BULLET_SPEED = -5;
 
};