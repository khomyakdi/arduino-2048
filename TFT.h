#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>   

class TFT {
  private:
    Adafruit_ST7789* tft;
    uint16_t tftWidth;
    uint16_t tftHeight;
    uint16_t tSize;

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

  public:
    TFT( Adafruit_ST7789* screen, uint16_t width, uint16_t height, uint16_t tileSize) {
        tft = screen;
        tftWidth = width;
        tftHeight = height;
        tSize = tileSize;
    }
    
    void init() {
      this->tft->init(tftWidth, tftHeight);
      this->tft->setRotation(2);
      this->tft->fillScreen(ST77XX_BLACK);
      
      Serial.println("Serial initiated");
    }

    void placeSquare(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t borderColor, uint16_t bgColor) {
      this->tft->drawRect(x, y, width, height,borderColor);
      this->tft->fillRect(x+1, y+1, width - 1, height - 1, bgColor);
    }

    void placeText(uint8_t x, uint8_t y, String text, uint16_t color, uint8_t size) {
      this->tft->setCursor(x,y);
      this->tft->setTextColor(color);
      this->tft->setTextSize(size);
      this->tft->print(text);
    }

    void drawField(int **field) {
      uint8_t x = 0;
      uint8_t y = 0;
      
      for(int i = 0; i<4;i = i + 1)
        for(int j = 0; j < 4; j = j + 1) {
          x = i*tSize;
          y = j*tSize;

          int fieldValue = field[j][i];
          String val = fieldValue == 0 ? String(' ') : String(fieldValue);
          int16_t tileBgColor = getBgColorByValue(fieldValue);
          placeSquare(x, y, tSize, tSize, ST77XX_BLACK, tileBgColor);

          int16_t tileTextColor = getColorByValue(fieldValue);
          int8_t textSize = 3;
          if(fieldValue > 64)
            textSize = 2;

          if(fieldValue > 512)
            textSize = 1;
            
          placeText(x+5, y+5, val, tileTextColor, textSize);
        }
    }
};
