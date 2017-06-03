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

Adafruit_BNO055 bno = Adafruit_BNO055(BNO055_ID, BNO055_ADDRESS_B);

Badge badge;

imu::Vector<3> euler;

Player player(70, 70);

std::vector<Bullet> p_bullets;
long lastBulletTick = 0;
const long ticksPerBullet = 20;

std::vector<Enemy> enemies;
const int enemyCount = 3;

long tick;

bool gameOver;

int score;

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

  tft.setTextSize(1);
  tft.setTextColor(WHITE);

  reset();
}

void reset() {
  enemies.clear();
  p_bullets.clear();
  tick = 0;
  lastBulletTick = 0;
  score = 0;
  gameOver = false;  
}

void loop() {

  if (gameOver) {

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
  
  tft.fillScreen(BLACK);
 
  drawScore();
  
  tft.setCursor(35, 60); 
  tft.println("Game Over!");
  tft.writeFramebuffer();
}

void generateEnemies() {

  if (enemies.size() < enemyCount && tick % 50 == 0) {
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

      gameOver = true;
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
  
  for (std::vector<Bullet>::iterator bIt = p_bullets.begin(); bIt != p_bullets.end();) {
    
    Bullet& b = *bIt;
    b.x = b.x + b.m_x;
    b.y = b.y + b.m_y;

    if ((b.x > TFT_MAX || b.x < 0) || (b.y > TFT_MAX || b.y < 0)) {
      bIt = p_bullets.erase(bIt);
    } else {

       bool bulletRemoved = false;

       for (std::vector<Enemy>::iterator eIt = enemies.begin(); eIt != enemies.end();) {
    
         Enemy& e = *eIt;
         
         if ((b.x > e.x && b.x < e.x + Enemy::SHAPE_W) && b.y < e.y) {
           eIt = enemies.erase(eIt);
           bIt = p_bullets.erase(bIt);
           bulletRemoved = true;
           score++;
           break;
         } else {
           ++eIt;
         }
       }
      
      if (!bulletRemoved) {
        ++bIt;
      }
    }
  }
  
  if (badge.getJoystickState() == JoystickState::BTN_ENTER && lastBulletTick + ticksPerBullet < tick) {
    Bullet b = player.EmitBullet();
    p_bullets.push_back(b);
    lastBulletTick = tick;
  }
}

void draw() {
  tft.fillScreen(BLACK);

  drawScore();

  player.Draw(tft);

  for (std::vector<Bullet>::iterator it = p_bullets.begin(); it != p_bullets.end(); ++it) {
    
    Bullet& b = *it;
    tft.writePixel(b.x, b.y, RED);
  } 
  
  for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it) {

    Enemy& e = *it;
    e.Draw(tft);
  }

  tft.writeFramebuffer();
}

void drawScore() {
   
  tft.setCursor(2, 0);
  tft.print("Score: ");
  tft.print(score);
}
