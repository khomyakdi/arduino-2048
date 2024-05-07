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

const uint16_t tileSize = 60;
int (*field)[4] = new int[4][4];

//Methods for field

void resetField() {
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      field[i][j] = 0;  
}

bool containsEmpty() {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (field[i][j] == 0)
        return true;

  return false;
}

void setRandomElement() {
  int value = random(0, 2) == 0 ? 2 : 4;

  if(containsEmpty())
    while(true) {
      int x = random(0, 4);
      int y = random(0, 4);
      
      if(field[x][y] == 0) {
        field[x][y] = value;
        break;
      }
    }
}

void drawField() {
  uint8_t x = 0;
  uint8_t y = 0;
  
  for(int i = 0; i<4;i = i + 1) {
        for(int j = 0; j < 4; j = j + 1) {
          x = i*tileSize;
          y = j*tileSize;
          int fieldValue = field[j][i];
          String val = fieldValue == 0 ? String(' ') : String(fieldValue);
          
          tft.placeSquare(x, y, tileSize, tileSize,ST77XX_YELLOW, ST77XX_BLACK);
          tft.placeText(x+5, y+5, val, ST77XX_GREEN, 2);
        }
    }
}

void setup() {
  Serial.begin(9600);

  tft.init(2, ST77XX_BLACK);
  
  upBtn.init();
  downBtn.init();
  leftBtn.init();
  rightBtn.init();

  randomSeed(analogRead(0));

  resetField();
  setRandomElement();
  drawField();
      
  Serial.println("Started");
}

void loop() {
  if(upBtn.isPressed()) {
    Serial.println("up");
    setRandomElement();
    drawField();
    return;
  }

  if(downBtn.isPressed()) {
    Serial.println("down");
    drawField();
    return;
  }
  
  if(leftBtn.isPressed()) {
    Serial.println("left");
    drawField();
    return;
  }
  
  if(rightBtn.isPressed()) {
    drawField();
    return;
  }
}
