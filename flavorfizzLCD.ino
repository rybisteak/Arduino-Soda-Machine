#include <LiquidCrystal.h>

LiquidCrystal lcd(1, 2, 4, 12, 13, 7);

int sodaType = 0;
int syrupType = 0;
bool pourMode = false;

//toggle soda/syrup
const int sodaButtonPin = 3;
int sodaButtonState = 0;

const int syrupButtonPin = 5;
int syrupButtonState = 0;

//distance sensor
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distanceInch;

bool canPour = false;

//Outputs to arduino 2
const int sodaOut = 6;
const int syrupOut = 8;
const int pourPin = 11;
int pourState = 0;


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(sodaButtonPin, INPUT);
  pinMode(syrupButtonPin, INPUT);

  pinMode(pourPin, INPUT);
  pinMode(sodaOut, OUTPUT);
  pinMode(syrupOut, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sodaButtonState = digitalRead(sodaButtonPin);
  syrupButtonState = digitalRead(syrupButtonPin);
  pourState = digitalRead(pourPin);

  if (sodaType == 0) {
    digitalWrite(sodaOut, LOW);
  } else {
    digitalWrite(sodaOut, HIGH);
  }
  if (syrupType == 0) {
    digitalWrite(syrupOut, LOW);
  } else {
    digitalWrite(syrupOut, HIGH);
  }

  if (pourMode) {
    if (sodaButtonState == HIGH || syrupButtonState == HIGH) {
      pourMode = false;
    }
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distanceInch = duration*0.0133/2;

    Serial.println("hi");

    if (distanceInch < 3) {
      canPour = true;
      Serial.println("Pour");
    } else {
      canPour = false;
      Serial.println("Too far");
    }
    delay(100);

    lcd.setCursor(0,0);
    if (canPour) {
      lcd.print("Ready to pour");
    } else {
      lcd.print("Cup too far.   ");
    }
    delay(10);
    lcd.setCursor(0,1);
    lcd.print("Back to selection");
  } else {
    if (pourState == HIGH) {
      pourMode = true;
    }
    if (sodaButtonState == HIGH) {
      if (sodaType == 0) {
        sodaType = 1;
      } else {
        sodaType = 0;
      }
    }
    delay(100);
    if (syrupButtonState == HIGH) {
      if (syrupType == 0) {
        syrupType = 1;
      } else {
        syrupType = 0;
      }
    }
    delay(100);
    lcd.setCursor(0,0);
    if (sodaType == 0) {
      lcd.print("Soda Yellow.         ");
    } else {
      lcd.print("Soda Red.         ");
    }
    delay(10);
    lcd.setCursor(0,1);
    if (syrupType == 0) {
      lcd.print("Syrup Green.        ");
    } else {
      lcd.print("Syrup Blue.        ");
    }
    delay(10);
  }

}
