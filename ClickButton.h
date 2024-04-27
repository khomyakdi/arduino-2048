class ClickButton {
  private:
    bool state = HIGH;
    uint8_t btnPin;
    bool lastBtnState;
    bool currBtnState;

  public:
    ClickButton(uint8_t pin) {
      btnPin = pin;
    }
    
    void init() {
      pinMode(btnPin, INPUT_PULLUP);
      currBtnState = digitalRead(btnPin);
    }
    
    bool isPressed() {
      lastBtnState = currBtnState;
      currBtnState = digitalRead(btnPin);
      delay(5); // Small delay to prevent wrong state on output flickering.
      return lastBtnState == HIGH && currBtnState == LOW;
    }
};