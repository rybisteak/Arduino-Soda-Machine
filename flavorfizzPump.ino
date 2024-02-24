#include <DHT.h>
#include <DHT_U.h>



const int sodaInPin = 3;
int sodaState = 0;
const int syrupInPin = 5;
int syrupState = 0;

const int pourPin = 11;
int pourState = 0;

const int soda1 = 6;
const int soda2 = 8;
const int syrup1 = 9;
const int syrup2 = 10;

// DHT setup
#define DHTPIN 7        // Define the pin where the DHT sensor is connected
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  // put your setup code here, to run once:
  pinMode(sodaInPin, INPUT);
  pinMode(syrupInPin, INPUT);

  pinMode(pourPin, INPUT);

  pinMode(soda1, OUTPUT);
  pinMode(soda2, OUTPUT);
  pinMode(syrup1, OUTPUT);
  pinMode(syrup2, OUTPUT);

  dht.begin();
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  pourState = digitalRead(pourPin);
  sodaState = digitalRead(sodaInPin);
  syrupState = digitalRead(syrupInPin);

  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read humidity (percent)
  float h = dht.readHumidity();

  if (isnan(h) || isnan(t)) {
    Serial.print("Failed to read");
    return;
  }

  if (pourState == HIGH) {
    if (sodaState == HIGH) {
      if (syrupState == HIGH) {
        digitalWrite(soda1, LOW);
        digitalWrite(soda2, HIGH);
        digitalWrite(syrup1, LOW);
        digitalWrite(syrup2, HIGH);
        //Serial.println("soda2, syrup2");
      } else {
        digitalWrite(soda1, LOW);
        digitalWrite(soda2, HIGH);
        digitalWrite(syrup1, HIGH);
        digitalWrite(syrup2, LOW);
        //Serial.println("soda2, syrup1");
      }
    } else {
      if (syrupState == HIGH) {
        digitalWrite(soda1, HIGH);
        digitalWrite(soda2, LOW);
        digitalWrite(syrup1, LOW);
        digitalWrite(syrup2, HIGH);
        //Serial.println("soda1, syrup2");
      } else {
        digitalWrite(soda1, HIGH);
        digitalWrite(soda2, LOW);
        digitalWrite(syrup1, HIGH);
        digitalWrite(syrup2, LOW);
        //Serial.println("soda1, syrup1");
      }
    }
  } else {
    digitalWrite(soda1, LOW);
    digitalWrite(soda2, LOW);
    digitalWrite(syrup1, LOW);
    digitalWrite(syrup2, LOW);
    //Serial.println("Nothing");
  }

  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print((char)223);
  Serial.println("C");

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println("%");


}
