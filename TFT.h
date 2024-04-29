#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>   

class TFT {
	private:
		Adafruit_ST7789* tft;
		uint16_t tftWidth;
		uint16_t tftHeight;
		uint16_t bg;
	
	public:
		TFT( Adafruit_ST7789* screen, uint16_t width, uint16_t height) {
				tft = screen;
				tftWidth = width;
				tftHeight = height;
		}
		
		void init(uint8_t rotation, uint16_t bgColor) {
			this->tft->init(tftWidth, tftHeight);
			this->tft->setRotation(2);
			bg = bgColor;
			this->tft->fillScreen(bgColor);
      
			Serial.println("Serial initiated");
		}

		void drawFullScreenText(char *text, uint16_t color) {
			this->tft->fillScreen(bg);
			this->tft->setCursor(0, 0);
			this->tft->setTextColor(color);
			this->tft->setTextWrap(true);
			this->tft->print(text);
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
};
