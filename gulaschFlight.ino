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

#define LED_MAX_BRIGHT 50

Adafruit_BNO055 bno = Adafruit_BNO055(BNO055_ID, BNO055_ADDRESS_B);

Badge badge;

imu::Vector<3> euler;

Player player(70, 70);

std::vector<Bullet> p_bullets;
long lastBulletTick = 0;
const long ticksPerBullet = 20;

std::vector<Enemy> enemies;
int enemyCount = 3;

long tick;

bool gameOver;

int score;

short int level = 1;

short int ledBrightness = 0;

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
  tft.setTextColor(BLACK);
  
  reset();
}

void reset() {
  enemies.clear();
  p_bullets.clear();
  tick = 0;
  lastBulletTick = 0;
  score = 0;
  level = 0;
  gameOver = false;  
}

void loop() {

  updateFx();

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
  
  drawBackground();
 
  drawStatus();
  
  tft.setCursor(35, 60); 
  tft.println("Game Over!");
  tft.setCursor(32, 110);
  tft.println("Press ENTER");
  tft.writeFramebuffer();

  if (badge.getJoystickState() == JoystickState::BTN_ENTER) {
    reset();
  }
}

void generateEnemies() {

  if (enemies.size() < enemyCount && tick % 55 - level * 5  == 0) {
    int x = rand() % (TFT_MAX - Enemy::SHAPE_W * 2 + 1) + Enemy::SHAPE_W;
    Enemy enemy(x, 0);
    enemies.push_back(enemy);
  }  
}

void updateEnemies() {
  
 for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end();) {
    
    Enemy& e = *it;

    e.Move();

    if ((e.y + Enemy::SHAPE_H > player.y && e.y < player.y + Player::SHAPE_H) && 
          ((e.x > player.x && e.x < player.x + Player::SHAPE_W) || (e.x + Enemy::SHAPE_W > player.x && e.x < player.x + Player::SHAPE_W))) {
      
      gameOverFx();
      gameOver = true;
    }
    
    if (e.y > TFT_MAX) {
      it = enemies.erase(it);
    } else {
      ++it;
    }
  }   
}

void gameOverFx() {
  hitFx();
  badge.setVibrator(true);
  delay(100);
  badge.setVibrator(false);
}

void hitFx() {
  ledBrightness = LED_MAX_BRIGHT;
  pixels.setBrightness(ledBrightness);
  pixels.setPixelColor(0, 255, 0, 0);
  pixels.setPixelColor(1, 255, 0, 0);
  pixels.setPixelColor(2, 255, 0, 0);
  pixels.setPixelColor(3, 255, 0, 0);
  pixels.show(); 
}

void updateFx() {
  if (ledBrightness > 0) {
    ledBrightness -= 5;
    pixels.setBrightness(ledBrightness);
    pixels.show(); 
  }
}

void updatePlayer() {

  euler = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  player.Move(euler.x(), euler.y());   
}

void increaseScore() {

  score++;  

  if (score % 10 == 0) {
    level++;
    enemyCount++;
  }
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
           increaseScore();
           hitFx();
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
  drawBackground();

  drawStatus();

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

void drawStatus() {
   
  tft.setCursor(2, 1);
  tft.print("Score: ");
  tft.print(score);
  
  tft.setCursor(70, 1);
  tft.print("Level: ");
  tft.print(level);
}

void drawBackground() {

  char i = 200;
  
  for (int y = 0; y < TFT_MAX; y++) {
    tft.drawFastHLine(0, y, TFT_MAX, tft.Color565(i, i + 20, 255));

    if (y % 5 == 0) {
      i -= 3;
    }
  }
}
