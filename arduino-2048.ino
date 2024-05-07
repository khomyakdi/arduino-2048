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

void setup() {
  Serial.begin(9600);

  tft.init(2, ST77XX_BLACK);
  tft.drawFullScreenText("Hello", ST77XX_WHITE);
  
  upBtn.init();
  downBtn.init();
  leftBtn.init();
  rightBtn.init();

  
  Serial.println("Started");
}

const uint16_t tileSize = 60;
int field[4][4] = {
  {2, 4, 8, 16},
  {32, 64, 128, 256},
  {512, 1024, 2048, 4096},
  {8192, 0, 0, 0},
};

void drawField() {
  uint8_t x = 0;
  uint8_t y = 0;
  
  for(int i = 0; i<4;i = i + 1) {
        for(int j = 0; j < 4; j = j + 1) {
          x = i*tileSize;
          y = j*tileSize;
          int fieldValue = field[j][i];
          String val = fieldValue == 0 ? String(' ') : String(fieldValue);
          
          tft.placeSquare(x, y, tileSize, tileSize,ST77XX_YELLOW, ST77XX_MAGENTA);
          tft.placeText(x+5, y+5, val, ST77XX_WHITE, 2);
        }
    }
}

void loop() {
  if(upBtn.isPressed()) {
    Serial.println("up");
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
