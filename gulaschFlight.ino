#include <GPNBadge.hpp>
#include <FS.h>
#include "rboot.h"
#include "rboot-api.h"

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#include "api.hpp"
#include "player.hpp"

#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(BNO055_ID, BNO055_ADDRESS_B);

Badge badge;

imu::Vector<3> euler;
float accel_x;
float accel_y;

Player player(70, 70);

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
  
  draw();
  
  delay(10);
}

void calcPlayerMovement() {
  euler = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  accel_x = euler.x();
  accel_y = euler.y();

  player.Move(accel_x, accel_y);
}

void draw() {
  tft.fillScreen(BLACK);

  for (int i = 0; i < player.SHAPE_SIZE; i++) {
    Pixel p = player.shape[i];
    tft.writePixel(p.x + player.x, p.y + player.y, WHITE);
  }
  
  tft.writeFramebuffer();
}
