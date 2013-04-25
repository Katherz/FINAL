//+++++++++++++++DHT TEMP SENSOR+++++++++++++

#include "DHT.h" // DHT library
#define DHTPIN 2 // what pin DHT is connected too
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);


//+++++++++TEMP+++++++++

float fahTemp = 0; //temperature to convert
int NewTempint = 0; // int to convert fahtemp float into an int
int newTempReading; // Final temp reading with mapping

//++++PHOTORESISTOR++++++++++++

int photocellPin = 1; //photoresistor A1
int photocellReading; //photoresistor reading before mapping
int newphotoReading; //new reading for photoresistor after mapping

//+++++++++++NOISE++++++++++++++

int newSample; 

//++++++++++RGB LED+++++++++

int latchPin = 8; // shift register pin 8
int clockPin = 12; // shift register pin 12
int dataPin = 11; // shift register pin 11
int Power = 3; // to common anode in RGB LEDs to control brightness

// +++++++++++++++++SETUP++++++++++++++++++++

void setup() {
  Serial.begin(9600);
  dht.begin(); //begin reading temp

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(Power, OUTPUT);


}

//++++++++++++++++++LOOP+++++++++++++++++++++++++++++++++

void loop() {

  //+++++++++TEMP++++++++
  float t = dht.readTemperature(); //read temp in *C
  fahTemp = (t * 1.8) +32; //convert *C to *F
  NewTempint = (int(fahTemp)); //converting the *F temp into an int
  newTempReading = map(NewTempint, 65,90, 0,255); //mapping the temp to 0-255

    //+++++++PHOTORESISTOR+++++++++

  photocellReading = analogRead(photocellPin); //reading the values from the photoresistor
  photocellReading = 1023 - photocellReading; //inverting values from 0-1023 to 1023-0
  newphotoReading = map(photocellReading, 0, 1023,0,255); //mapping photoresistor values to 0-255

    //++++++++++++NOISE+++++++++++++
  int sensorValue = analogRead(0);
  newSample = map(sensorValue, 0,200 ,0, 255);
  delay(25);

  //++++++++++++++RGB LEDS+++++++++++++++++++++++++++++++++

int brightness = newTempReading ;
int red = 255;
int green = newphotoReading;
int blue = newSample;

for (int i = 0; i < 24; i++){

digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, LSBFIRST, red);
shiftOut(dataPin, clockPin, MSBFIRST, green);
shiftOut(dataPin, clockPin, MSBFIRST, blue);
digitalWrite(latchPin, HIGH);
analogWrite(Power, brightness);
delay(25); // milliseconds
}

  Serial.print (brightness);
  Serial.print(",");
  Serial.print( red);
  Serial.print (",");
  Serial.print(green);
  Serial.print (",");
  Serial.print (blue);
  Serial.print("\n");
  //++++++++++PRINT TO SERIAL MONITER++++++++++

  delay (25); //delay after reading

}














