#include <GPNBadge.hpp>
#include <FS.h>
#include "rboot.h"
#include "rboot-api.h"

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(BNO055_ID, BNO055_ADDRESS_B);

Badge badge;

int player_x = 70;
int player_y = 70;

int player_s = 20;

int max_x = 128;
int max_y = 128;

imu::Vector<3> euler;

float accel_x;
float accel_y;

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

  calcPlayerMovement();
  
  drawPlayer();
  
  delay(50);
}

void calcPlayerMovement() {
  euler = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  accel_x = euler.x();
  accel_y = euler.y();

  int new_x = player_x;
  int new_y = player_y;
  
  if (accel_x > 1) {
      new_x = player_x + (int) accel_x;
  }
  
  if (accel_x < -1) {
      new_x = player_x + (int) accel_x;
  }

  if (new_x > 0 && new_x < max_x - player_s) {
    player_x = new_x;
  }

  if (accel_y > 1) {
      new_y = player_y - (int) accel_y;
  }
  
  if (accel_y < -1) {
      new_y = player_y - (int) accel_y;
  }

  if (new_y > 0 && new_y < max_y - player_s) {
    player_y = new_y;  
  }
}

void drawPlayer() {
  tft.fillScreen(BLACK);
  tft.drawRect(player_x, player_y, player_s, player_s, WHITE);
  tft.writeFramebuffer();
}
