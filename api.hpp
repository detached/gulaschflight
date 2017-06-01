#pragma once

struct Pixel {
  int x;
  int y;
  int color;
};

struct Bullet {
  int x;
  int y;
  int m_x;
  int m_y;
};

const int TFT_MAX = 128;
