#include <GPNBadge.hpp>

#include <FS.h>
#include "rboot.h"
#include "rboot-api.h"

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#include <vector>

#include "api.hpp"
#include "player.hpp"
#include "enemy.hpp"

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

imu::Vector<3> euler;

Player player(70, 70);
std::vector<Bullet> p_bullets;

std::vector<Enemy> enemies;
int enemy_count = 3;

long tick;

bool game_over = false;
bool game_end = false;

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

  tick = 0;
}

void loop() {

  if (game_over) {

    printGameOver();
  } else {
  
    tick++;

    updatePlayer();
    updateBullets();

    generateEnemies();
    updateEnemies();
   
    draw();
  }
}

void printGameOver() {
  
  if (!game_end) {
    tft.fillScreen(BLACK);
    tft.setTextSize(1);
    tft.setTextColor(WHITE);
    tft.setCursor(35, 60); 
    tft.println("Game Over!");   
    tft.writeFramebuffer();
    
    game_end = true; 
  }
}

void generateEnemies() {

  if (enemies.size() < enemy_count && tick % 50 == 0) {
    int x = rand() % TFT_MAX;
    int y = 0;
    Enemy enemy(x, y);
    enemies.push_back(enemy);
  }  
}

void updateEnemies() {
  
 for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end();) {
    
    Enemy& e = *it;

    e.Move();

    if ((e.y + Enemy::SHAPE_H > player.y && e.y < player.y + Player::SHAPE_H) && 
          ((e.x > player.x && e.x < player.x + Player::SHAPE_W) || (e.x + Enemy::SHAPE_W > player.x && e.x < player.x + Player::SHAPE_W))) {

      game_over = true;
    }
    
    if (e.y > TFT_MAX) {
      it = enemies.erase(it);
    } else {
      ++it;
    }
  }   
}

void updatePlayer() {

  euler = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  player.Move(euler.x(), euler.y());   
}

void updateBullets() { 
  
  for (std::vector<Bullet>::iterator it = p_bullets.begin(); it != p_bullets.end();) {
    
    Bullet& b = *it;
    b.x = b.x + b.m_x;
    b.y = b.y + b.m_y;

    if ((b.x > TFT_MAX || b.x < 0) || (b.y > TFT_MAX || b.y < 0)) {
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

  for (int i = 0; i < Player::SHAPE_SIZE; i++) {
    Pixel p = Player::SHAPE[i];
    tft.writePixel(p.x + player.x, p.y + player.y, WHITE);
  }

  for (std::vector<Bullet>::iterator it = p_bullets.begin(); it != p_bullets.end(); ++it) {
    
    Bullet& b = *it;
    tft.writePixel(b.x, b.y, RED);
  } 
  
  for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it) {

    Enemy& e = *it;

    for (int i = 0; i < Enemy::SHAPE_SIZE; i++) {
      Pixel p = Enemy::SHAPE[i];
      tft.writePixel(p.x + e.x, p.y + e.y, BLUE);
    }
  } 
  
  tft.writeFramebuffer();
}
