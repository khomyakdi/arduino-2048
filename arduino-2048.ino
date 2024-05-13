// pin wiring to Nano
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
TFT tft = TFT(&tftDisplay, 240, 240);

ClickButton upBtn = ClickButton(K4);
ClickButton downBtn = ClickButton(K3);
ClickButton leftBtn = ClickButton(K2);
ClickButton rightBtn = ClickButton(K1);

GameField gameField = GameField();

int16_t getColorByValue(int val) {
  switch(val) {
    case 0:
    case 2:
    case 4:
      return 0x736C;
    default:
      return 0xFFBE;
  }
}

int16_t getBgColorByValue(int val) {
  switch(val) {
    case 0:
      return 0xBD74;
    case 2:
      return 0xEF3B;
    case 4:
      return 0xEF19;
    case 8:
     return 0xF58F;
    case 16:
     return 0xF4AC;
    case 32:
      return 0xF3EB;
    case 64:
      return 0xF2E7;
    case 128:
      return 0xEE8E;
    case 256:
      return 0xEE6C;
    case 512:
      return 0xEE4A;
    case 1024:
      return 0xEE27;
    case 2048:
      return 0xEE05;
    default:
      return 0x39C6;
  }
}

const uint16_t tileSize = 60;
void drawField() {
  uint8_t x = 0;
  uint8_t y = 0;
  
  for(int i = 0; i<4;i = i + 1) {
        for(int j = 0; j < 4; j = j + 1) {
          x = i*tileSize;
          y = j*tileSize;
          int fieldValue = gameField.field[j][i];
          String val = fieldValue == 0 ? String(' ') : String(fieldValue);
          int16_t tileBgColor = getBgColorByValue(fieldValue);
          tft.placeSquare(x, y, tileSize, tileSize,ST77XX_BLACK, tileBgColor);
          int16_t tileColor = getColorByValue(fieldValue);
          int8_t textSize = 3;
          if(fieldValue > 64)
            textSize = 2;
          if(fieldValue > 512)
            textSize = 1;
            
          tft.placeText(x+5, y+5, val, tileColor, textSize);
        }
    }
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  tft.init(2, ST77XX_BLACK);
  
  upBtn.init();
  downBtn.init();
  leftBtn.init();
  rightBtn.init();

  drawField();
      
  Serial.println("Started");
}

void loop() {
  if(upBtn.isPressed()) {
    Serial.println("up");
    
    gameField.shiftTop();
    drawField();
    return;
  }

  if(downBtn.isPressed()) {
    Serial.println("down");
    
    gameField.shiftBottom();
    drawField();
    return;
  }
  
  if(leftBtn.isPressed()) {    
    Serial.println("left");
    
    gameField.shiftLeft();    
    drawField();
    return;
  }
  
  if(rightBtn.isPressed()) {
    Serial.println("right");
    
    gameField.shiftRight();    
    drawField();
    return;
  }
}
