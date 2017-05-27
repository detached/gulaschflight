#include <GPNBadge.hpp>
#include <FS.h>
#include "rboot.h"
#include "rboot-api.h"

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#include <vector>

#include "api.hpp"
#include "player.hpp"

#define BNO055_SAMPLERATE_DELAY_MS (100)

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_BNO055 bno = Adafruit_BNO055(BNO055_ID, BNO055_ADDRESS_B);

Badge badge;

int tft_max = 128;

imu::Vector<3> euler;
float accel_x;
float accel_y;

Player player(70, 70);
std::vector<Bullet> p_bullets;

void setup() {
  badge.init();
  badge.setBacklight(true);
  bno.begin();
  delay(300);
  badge.setGPIO(MQ3_EN,1);

  rboot_config rboot_config = rboot_get_config();
  SPIFFS.begin();
  File f = SPIFFS.open("/rom"+String(rboot_config.current_rom),"w");
  f.println("GPNFlight\n");
}

void loop() {

  updatePlayer();
  updateBullets();
  
  draw();
  
  delay(10);
}

void updatePlayer() {
  euler = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  accel_x = euler.x();
  accel_y = euler.y();

  player.Move(accel_x, accel_y);   
}

void updateBullets() {
 
  
  for (std::vector<Bullet>::iterator it = p_bullets.begin(); it != p_bullets.end();) {
    
    Bullet& b = *it;
    b.x = b.x + b.m_x;
    b.y = b.y + b.m_y;

    if ((b.x > tft_max || b.x < 0) || (b.y > tft_max || b.y < 0)) {
      it = p_bullets.erase(it);
    } else {
      ++it;
    }
  }
  
  if (badge.getJoystickState() == JoystickState::BTN_ENTER) {
    Bullet b = player.EmitBullet();
    p_bullets.push_back(b);
  }
}

void draw() {
  tft.fillScreen(BLACK);

  for (int i = 0; i < player.SHAPE_SIZE; i++) {
    Pixel p = player.shape[i];
    tft.writePixel(p.x + player.x, p.y + player.y, WHITE);
  }

  for (std::vector<Bullet>::iterator it = p_bullets.begin(); it != p_bullets.end(); ++it) {
    
    Bullet& b = *it;
    tft.writePixel(b.x, b.y, RED);
  } 
  
  tft.writeFramebuffer();
}
