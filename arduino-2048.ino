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
int (*field)[4] = new int[4][4];

//Methods for field

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

void resetField() {
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      field[i][j] = 0;  

   setRandomElement();
   drawField();
}


void switchElements(int x1, int y1, int x2, int y2) {
  field[x1][y1] += field[x2][y2];
  field[x2][y2] = field[x1][y1] - field[x2][y2];
  field[x1][x2] -= field[x2][y2];
}

bool shiftTop() {
  bool moved = false;
  bool switched = true;

  while (switched == true) {
    switched = false;
    for (int i = 0; i < 4; i++) {
      for (int j = 4 - 1; j > 0; j--) {
        if (field[j - 1][i] == 0 && field[j][i]!=0) {
          switchElements(j - 1, i, j, i);
          switched = true;
          moved = true;
        }
      }
    }
  }

  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4 - 1; i++) {
      if (field[i][j] == field[i + 1][j] && field[i][j] != 0) {
        for (int k = i + 1; k < 4 - 1; k++) {
          field[k][j] = field[k + 1][j];
        }
        
        field[i][j] *= 2;
        field[4 - 1][j] = 0;
        moved = true;
      }
    }
  }
  
  return moved;
}

bool shiftBottom() {
  bool switched = true;
  bool moved = false;
  while (switched == true) {
    switched = false;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4 - 1; j++) {
        if (field[j + 1][i] == 0 && field[j][ i] != 0) {
          switchElements(j + 1, i, j, i);
          switched = true;
          moved = true;
        }
      }
    }
  }
     
  for(int j=0;j< 4; j++) {
    for(int i= 4 - 1;i>0;i--) {
      if(field[i][j]== field[i-1][j]&& field[i][j]!=0) {
        for(int k=i;k>0;k--) {
          field[k][j]= field[k-1][j];
        }

        field[i][j]*=2;
        field[0][j]=0;
        moved = true;
      }
    }
  }
  
  return moved;
}

bool shiftLeft() {
  bool switched = true;
  bool moved = false;
  
  while (switched == true) {
    switched = false;
    for (int j = 0; j < 4; j++) {
      for (int i = 4 - 1; i > 0; i--) {
        if (field[j][i - 1] == 0 && field[j][i] != 0) {
          switchElements(j, i-1, j, i);
          switched = true;
          moved = true;
        }
      }
    }
  }
        
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4 - 1; j++) {
      if (field[i][j] == field[i][j + 1] && field[i][j] != 0) {
        for (int j2 = j + 1; j2 < 4 - 1; j2++) {
          field[i][j2] = field[i][j2 + 1];
        }
        
        field[i][j] *= 2;
        field[i][4 - 1] = 0;
        moved = true;
      }
    }
  }
  
  return moved;
}

bool shiftRight() {
  bool switched = true;
  bool moved = false;
  while (switched == true) {
    switched = false;
    for (int j = 0; j < 4; j++) {
      for (int i = 0; i < 4 - 1; i++) {
        if (field[j][i + 1] == 0 && field[j][i] != 0) {
          switchElements(j, i+1, j, i);
          switched = true;
          moved = true;
        }
      }
    }
  }
  
  for (int i = 0; i < 4; i++) {
    for (int j = 4 - 1; j > 0; j--) {
      if (field[i][j] == field[i][ j - 1] && field[i][j] != 0) {
        for (int j2 = j - 1; j2 > 0; j2--) {
          field[i][j2] = field[i][j2 - 1];
        }
        
        field[i][ j] *= 2;
        field[i][0] = 0;
        moved = true;
      }
    }
  }
  
  return moved;
}

bool hasMoves() {
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      if(field[i][j] == field[i][j + 1] || field[i][j] == field[i + 1][j])
        return true;
        
  for(int i = 0; i < 3; i++)
    if(field[i][3]==field[i+1][3])
      return true;

  for(int i = 0; i < 3; i++)
    if(field[3][i]==field[3][i + 1])
      return true;

  return false;            
}
//End of methods for field

void setup() {
  Serial.begin(9600);

  tft.init(2, ST77XX_BLACK);
  
  upBtn.init();
  downBtn.init();
  leftBtn.init();
  rightBtn.init();

  randomSeed(analogRead(0));

  resetField();
      
  Serial.println("Started");
}

bool lose = false;

void prepareNextMove(bool shifted) {
  if(!shifted && !hasMoves()) {
    resetField();
    return;
  }

  if(!shifted)
    return;
  
  
  setRandomElement();
  drawField();  
}

void loop() {
  if(upBtn.isPressed()) {
    Serial.println("up");
    
    prepareNextMove(shiftTop());
    return;
  }

  if(downBtn.isPressed()) {
    Serial.println("down");
    
    prepareNextMove(shiftBottom());
    return;
  }
  
  if(leftBtn.isPressed()) {    
    Serial.println("left");
    
    prepareNextMove(shiftLeft());    
    return;
  }
  
  if(rightBtn.isPressed()) {
    Serial.println("right");
    
    prepareNextMove(shiftRight());    
    return;
  }

  lose = !hasMoves();
}
