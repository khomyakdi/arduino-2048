// Pin wiring for ArNano
//TFT
// GND ----- GND
// VCC ----- 3V3
// SCL ----- D13
// SDA ----- D11
// RES ----- D6
// DC ------ D7
// CS ------ D8
// BLK ----- 3V3
//Buttons
// UP ------ 5
// DOWN ---- 4
// LEFT ---- 3
// RIGHT --- 2

#include "ClickButton.h"
#include "TFT.h"
#include "GameField.h"

#define TFT_RST 6
#define TFT_CS 8
#define TFT_DC 7

#define K1 2 // Right button
#define K2 3 // Left button
#define K3 4 // Down button
#define K4 5 // Up button

Adafruit_ST7789 tftDisplay = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
ClickButton upBtn = ClickButton(K4);
ClickButton downBtn = ClickButton(K3);
ClickButton leftBtn = ClickButton(K2);
ClickButton rightBtn = ClickButton(K1);

TFT tft = TFT(&tftDisplay, 240, 240);
GameField gameField = GameField();

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  tft.init(2, ST77XX_BLACK);
  upBtn.init();
  downBtn.init();
  leftBtn.init();
  rightBtn.init();

  tft.drawField(gameField.field);
}

void loop() {
  if(upBtn.isPressed()) {
    Serial.println("up");
    gameField.shiftTop();
    tft.drawField(gameField.field);
    return;
  }

  if(downBtn.isPressed()) {
    Serial.println("down");
    gameField.shiftBottom();
    tft.drawField(gameField.field);
    return;
  }
  
  if(leftBtn.isPressed()) {    
    Serial.println("left");
    gameField.shiftLeft();    
    tft.drawField(gameField.field);
    return;
  }
  
  if(rightBtn.isPressed()) {
    Serial.println("right");
    gameField.shiftRight();    
    tft.drawField(gameField.field);
    return;
  }
}
