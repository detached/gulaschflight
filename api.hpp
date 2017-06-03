#pragma once

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//#define DEBUG false

#define TFT_MAX 128

struct Pixel {
  char x;
  char y;
  short int color;
};

struct Bullet {
  char x;
  char y;
  char m_x;
  char m_y;
};

