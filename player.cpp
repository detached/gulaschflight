#include "player.hpp"

const Pixel Player::SHAPE[] =
{{ 15, 0, 0x4227}, { 16, 0, 0x2944},
{ 14, 1, 0x3122}, { 15, 1, 0x83ED}, { 16, 1, 0x738B}, { 17, 1, 0x20A0},
{ 14, 2, 0x3143}, { 15, 2, 0x62C8}, { 16, 2, 0x5A66}, { 17, 2, 0x28E1},
{ 13, 3, 0x10A0}, { 14, 3, 0x5225}, { 15, 3, 0x5A66}, { 16, 3, 0x5A86}, { 17, 3, 0x49E4},
{ 9, 4, 0x41C5}, { 10, 4, 0x4A05}, { 11, 4, 0x0120}, { 13, 4, 0x20A0}, { 14, 4, 0x3142}, { 15, 4, 0x52C9}, { 16, 4, 0x5AC8}, { 17, 4, 0x28E1}, { 18, 4, 0x1000}, { 20, 4, 0x08C3}, { 21, 4, 0x5246}, { 22, 4, 0x3164},
{ 3, 5, 0x5226}, { 4, 5, 0x7B28}, { 5, 5, 0x18E3}, { 8, 5, 0x5246}, { 9, 5, 0x836A}, { 10, 5, 0x7329}, { 11, 5, 0x3164}, { 12, 5, 0x41A5}, { 13, 5, 0x2902}, { 14, 5, 0x4247}, { 15, 5, 0x8574}, { 16, 5, 0x7CB1}, { 17, 5, 0x2923}, { 18, 5, 0x49E6}, { 19, 5, 0x20E2}, { 20, 5, 0x49E5}, { 21, 5, 0x836A}, { 22, 5, 0x7329}, { 23, 5, 0x49A6}, { 26, 5, 0x31A4}, { 27, 5, 0x7B69}, { 28, 5, 0x31A4},
{ 2, 6, 0x4206}, { 3, 6, 0x8369}, { 4, 6, 0x93EA}, { 5, 6, 0x5205}, { 6, 6, 0x2080}, { 7, 6, 0x20E1}, { 8, 6, 0x41C5}, { 9, 6, 0x6AE9}, { 10, 6, 0x5247}, { 11, 6, 0x18C2}, { 12, 6, 0x3984}, { 13, 6, 0x3164}, { 14, 6, 0x4AEA}, { 15, 6, 0x7534}, { 16, 6, 0x7CD3}, { 17, 6, 0x39C5}, { 18, 6, 0x39A5}, { 19, 6, 0x2943}, { 20, 6, 0x2923}, { 21, 6, 0x62C8}, { 22, 6, 0x62A8}, { 23, 6, 0x3964}, { 24, 6, 0x20A1}, { 25, 6, 0x28E1}, { 26, 6, 0x6AC7}, { 27, 6, 0x93EA}, { 28, 6, 0x72C7}, { 29, 6, 0x3180},
{ 1, 7, 0x5AC9}, { 2, 7, 0x4A68}, { 3, 7, 0x5A46}, { 4, 7, 0x6287}, { 5, 7, 0x3963}, { 6, 7, 0x3122}, { 7, 7, 0x39A3}, { 8, 7, 0x39A3}, { 9, 7, 0x5245}, { 10, 7, 0x39E4}, { 11, 7, 0x18E2}, { 12, 7, 0x18E2}, { 13, 7, 0x2122}, { 14, 7, 0x4206}, { 15, 7, 0x534C}, { 16, 7, 0x536D}, { 17, 7, 0x31A4}, { 18, 7, 0x2122}, { 19, 7, 0x1902}, { 20, 7, 0x2122}, { 21, 7, 0x4A05}, { 22, 7, 0x49E5}, { 23, 7, 0x3183}, { 24, 7, 0x3142}, { 25, 7, 0x3142}, { 26, 7, 0x41C4}, { 27, 7, 0x6287}, { 28, 7, 0x4A26}, { 29, 7, 0x4248}, { 30, 7, 0x18E3},
{ 0, 8, 0x3121}, { 1, 8, 0x52A7}, { 2, 8, 0x736A}, { 3, 8, 0x6AE8}, { 4, 8, 0x5AC7}, { 5, 8, 0x5AE8}, { 6, 8, 0x5AA7}, { 7, 8, 0x5245}, { 8, 8, 0x4A25}, { 9, 8, 0x5266}, { 10, 8, 0x5286}, { 11, 8, 0x39C4}, { 12, 8, 0x3184}, { 13, 8, 0x39A4}, { 14, 8, 0x42A9}, { 15, 8, 0x6D54}, { 16, 8, 0x64F3}, { 17, 8, 0x4205}, { 18, 8, 0x39C4}, { 19, 8, 0x31A4}, { 20, 8, 0x4225}, { 21, 8, 0x5AA6}, { 22, 8, 0x4A45}, { 23, 8, 0x4A25}, { 24, 8, 0x5266}, { 25, 8, 0x5AA7}, { 26, 8, 0x5AC8}, { 27, 8, 0x5266}, { 28, 8, 0x6AA8}, { 29, 8, 0x52A8}, { 30, 8, 0x2923},
{ 0, 9, 0x10C1}, { 1, 9, 0x52A7}, { 2, 9, 0xAAC9}, { 3, 9, 0xB2EA}, { 4, 9, 0x840D}, { 5, 9, 0x7C4F}, { 6, 9, 0x7C4E}, { 7, 9, 0x6B6A}, { 8, 9, 0x5AA7}, { 9, 9, 0x5286}, { 10, 9, 0x5265}, { 11, 9, 0x5245}, { 12, 9, 0x5245}, { 13, 9, 0x4A45}, { 14, 9, 0x4226}, { 15, 9, 0x7D12}, { 16, 9, 0x6C4F}, { 17, 9, 0x41C4}, { 18, 9, 0x5265}, { 19, 9, 0x5286}, { 20, 9, 0x5265}, { 21, 9, 0x5266}, { 22, 9, 0x4A45}, { 23, 9, 0x5AC7}, { 24, 9, 0x6B8B}, { 25, 9, 0x740D}, { 26, 9, 0x740E}, { 27, 9, 0x8BAC}, { 28, 9, 0xBA48}, { 29, 9, 0x8AA8}, { 30, 9, 0x2923},
{ 0, 10, 0x08A1}, { 1, 10, 0x5267}, { 2, 10, 0xA32A}, { 3, 10, 0xB3CD}, { 4, 10, 0x94D0}, { 5, 10, 0x9D33}, { 6, 10, 0x94F2}, { 7, 10, 0x94F2}, { 8, 10, 0x8CB0}, { 9, 10, 0x8C4D}, { 10, 10, 0x7BEC}, { 11, 10, 0x73AC}, { 12, 10, 0x842E}, { 13, 10, 0x738A}, { 14, 10, 0x4A04}, { 15, 10, 0x7BCB}, { 16, 10, 0x6B29}, { 17, 10, 0x4A25}, { 18, 10, 0x840D}, { 19, 10, 0x8C6E}, { 20, 10, 0x73AB}, { 21, 10, 0x73AB}, { 22, 10, 0x7BCB}, { 23, 10, 0x8CB0}, { 24, 10, 0x8CD1}, { 25, 10, 0x8CD2}, { 26, 10, 0x8CD1}, { 27, 10, 0x946F}, { 28, 10, 0xBB8C}, { 29, 10, 0x8B09}, { 30, 10, 0x2943},
{ 1, 11, 0x4163}, { 2, 11, 0x62C7}, { 3, 11, 0x73AA}, { 4, 11, 0x844E}, { 5, 11, 0x9532}, { 6, 11, 0x9512}, { 7, 11, 0x9D73}, { 8, 11, 0xA573}, { 9, 11, 0x9D10}, { 10, 11, 0xA572}, { 11, 11, 0x9D74}, { 12, 11, 0xB617}, { 13, 11, 0x9D52}, { 14, 11, 0x5245}, { 15, 11, 0x7B8A}, { 16, 11, 0x6B28}, { 17, 11, 0x62E8}, { 18, 11, 0xADF5}, { 19, 11, 0xB637}, { 20, 11, 0x9D53}, { 21, 11, 0x9D10}, { 22, 11, 0x94F0}, { 23, 11, 0xA5B4}, { 24, 11, 0x9D32}, { 25, 11, 0x9512}, { 26, 11, 0x94F1}, { 27, 11, 0x73CB}, { 28, 11, 0x736A}, { 29, 11, 0x49E4}, { 30, 11, 0x1881},
{ 2, 12, 0x4000}, { 3, 12, 0x3922}, { 4, 12, 0x4A46}, { 5, 12, 0x632A}, { 6, 12, 0x6B6B}, { 7, 12, 0x73CD}, { 8, 12, 0x73CC}, { 9, 12, 0x6308}, { 10, 12, 0x73AB}, { 11, 12, 0x7C4F}, { 12, 12, 0x94F2}, { 13, 12, 0x8CD1}, { 14, 12, 0x4A25}, { 15, 12, 0x7349}, { 16, 12, 0x62E8}, { 17, 12, 0x5AA8}, { 18, 12, 0x9D32}, { 19, 12, 0x9D12}, { 20, 12, 0x7C2E}, { 21, 12, 0x6B69}, { 22, 12, 0x6308}, { 23, 12, 0x73ED}, { 24, 12, 0x6B8C}, { 25, 12, 0x6B4B}, { 26, 12, 0x630A}, { 27, 12, 0x3962}, { 28, 12, 0x30C0},
{ 8, 13, 0x3186}, { 9, 13, 0x2100}, { 10, 13, 0x4162}, { 11, 13, 0x4A68}, { 12, 13, 0x52E9}, { 13, 13, 0x5288}, { 14, 13, 0x3963}, { 15, 13, 0x736A}, { 16, 13, 0x62E7}, { 17, 13, 0x3963}, { 18, 13, 0x630A}, { 19, 13, 0x5AE9}, { 20, 13, 0x4227}, { 21, 13, 0x30C0}, { 22, 13, 0x2124}, { 23, 13, 0x4200},
{ 13, 14, 0x2901}, { 14, 14, 0x3983}, { 15, 14, 0x7BAA}, { 16, 14, 0x7348}, { 17, 14, 0x3142}, { 18, 14, 0x18E0},
{ 13, 15, 0x2080}, { 14, 15, 0x3963}, { 15, 15, 0x7328}, { 16, 15, 0x62C7}, { 17, 15, 0x3962},
{ 13, 16, 0x28A0}, { 14, 16, 0x3962}, { 15, 16, 0x6B08}, { 16, 16, 0x5266}, { 17, 16, 0x3122},
{ 13, 17, 0x10A0}, { 14, 17, 0x3942}, { 15, 17, 0x62A7}, { 16, 17, 0x5225}, { 17, 17, 0x3101},
{ 10, 18, 0x2940}, { 11, 18, 0x1860}, { 12, 18, 0x3122}, { 13, 18, 0x3162}, { 14, 18, 0x3963}, { 15, 18, 0x62C8}, { 16, 18, 0x5266}, { 17, 18, 0x3962}, { 18, 18, 0x39A3}, { 19, 18, 0x3982}, { 20, 18, 0x2122},
{ 9, 19, 0x52A7}, { 10, 19, 0x5AA7}, { 11, 19, 0x5245}, { 12, 19, 0x5286}, { 13, 19, 0x5AA6}, { 14, 19, 0x4A25}, { 15, 19, 0x6AC8}, { 16, 19, 0x5A66}, { 17, 19, 0x5265}, { 18, 19, 0x62E7}, { 19, 19, 0x5AE7}, { 20, 19, 0x5A86}, { 21, 19, 0x4A67}, { 22, 19, 0x39E5},
{ 8, 20, 0x4A47}, { 9, 20, 0x73CC}, { 10, 20, 0x8C8F}, { 11, 20, 0x8C8E}, { 12, 20, 0x8C4D}, { 13, 20, 0x840C}, { 14, 20, 0x62C8}, { 15, 20, 0x49E5}, { 16, 20, 0x49E4}, { 17, 20, 0x7BAA}, { 18, 20, 0x8C4D}, { 19, 20, 0x8C8E}, { 20, 20, 0x8C6E}, { 21, 20, 0x7C2E}, { 22, 20, 0x5B0A}, { 23, 20, 0x3186},
{ 8, 21, 0x5206}, { 9, 21, 0x7BEC}, { 10, 21, 0x94D0}, { 11, 21, 0x9CF0}, { 12, 21, 0x94EF}, { 13, 21, 0x8C8D}, { 14, 21, 0x6B29}, { 15, 21, 0x3963}, { 16, 21, 0x49E4}, { 17, 21, 0x842C}, { 18, 21, 0x94AE}, { 19, 21, 0x9CF0}, { 20, 21, 0x94D0}, { 21, 21, 0x8C6F}, { 22, 21, 0x6B4A}, { 23, 21, 0x2945},
{ 9, 22, 0x4A04}, { 10, 22, 0x5A86}, { 11, 22, 0x5AC6}, { 12, 22, 0x5A66}, { 13, 22, 0x5265}, { 14, 22, 0x49E4}, { 15, 22, 0x3122}, { 16, 22, 0x3942}, { 17, 22, 0x5265}, { 18, 22, 0x5A86}, { 19, 22, 0x5A86}, { 20, 22, 0x5265}, { 21, 22, 0x4A25}, { 22, 22, 0x3142},
{ 11, 23, 0x2100}, { 12, 23, 0x2080}, { 13, 23, 0x3922}, { 14, 23, 0x4183}, { 15, 23, 0x3123}, { 16, 23, 0x3123}, { 17, 23, 0x3101}, { 18, 23, 0x3101}, { 19, 23, 0x20A0}, { 20, 23, 0x2940}};

 
Player::Player(int _x, int _y) {
  x = _x;
  y = _y;
}

void Player::Move(float accel_x, float accel_y) {

  if (accel_x > 1.0 || accel_x < -1.0) {
    int new_x = x + (int) accel_x;
    
    if (new_x > 0 && new_x < TFT_MAX - SHAPE_W) {
      x = new_x;
    }
  }

  if (accel_y > 1.0 || accel_y < -1.0) {
    int new_y = y - (int) accel_y;
  
    if (new_y > 0 && new_y < TFT_MAX - SHAPE_H) {
      y = new_y;
    }
  }
}

Bullet Player::EmitBullet() {

  Bullet b;
  b.x = x + SHAPE_W / 2;
  b.y = y;
  b.m_x = 0;
  b.m_y = BULLET_SPEED;

  return b;
}

void Player::Draw(TFT_ILI9163C tft) {
  
  for (int i = 0; i < Player::SHAPE_SIZE; i++) {
    Pixel p = Player::SHAPE[i];
    tft.writePixel(p.x + x, p.y + y, p.color);
  }

#ifdef DEBUG
  tft.drawRect(x, y, Player::SHAPE_W, Player::SHAPE_H, GREEN);
#endif
}
