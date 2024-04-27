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

void loop() {
  if(upBtn.isPressed()) {
    Serial.println("up");
    tft.drawFullScreenText("UP", ST77XX_WHITE);
    return;
  }

  if(downBtn.isPressed()) {
    Serial.println("down");
    tft.drawFullScreenText("DOWN", ST77XX_WHITE);
    return;
  }
  
  if(leftBtn.isPressed()) {
    Serial.println("left");
    tft.drawFullScreenText("LEFT", ST77XX_WHITE);
    return;
  }
  
  if(rightBtn.isPressed()) {
    Serial.println("right");
    tft.drawFullScreenText("RIGHT", ST77XX_WHITE);
    return;
  }
}
