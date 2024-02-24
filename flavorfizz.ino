#include <LiquidCrystal.h>

LiquidCrystal lcd(1, 2, 4, 12, 13, 7);

int sodaType = 0;
int syrupType = 0;

const int buttonPin = 3;
int buttonState = 0;


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(buttonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    if (sodaType == 0) {
      sodaType = 1;
    } else if (sodaType == 1) {
      sodaType = 2;
    } else {
      sodaType = 0;
    }
  }
  delay(100);
  lcd.setCursor(0,0);
  lcd.print("Soda: ");
  if (sodaType == 0) {
    lcd.print("Soda 1");
  } else if (sodaType == 1) {
    lcd.print("Soda 2");
  } else {
    lcd.print("Soda 3");
  }
  delay(10);
  lcd.setCursor(0,1);
  lcd.print("Syrup: ");
  if (syrupType == 0) {
    lcd.print("Syrup 1");
  } else if (syrupType == 1) {
    lcd.print("Syrup 2");
  } else {
    lcd.print("Syrup 3");
  }
  delay(10);

}
