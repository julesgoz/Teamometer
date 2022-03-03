/********************************************************************/
// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 
// Setup LEDs
const int blue = 6;
const int green = 7;
const int red = 8;
// Setup Buzzer
const int buzz = 10;
int beepCounter = 0;
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 
void setup(void) 
{ 

 // initialize digital pin LED_BUILTIN as an output.
 pinMode(blue, OUTPUT);
 pinMode(green, OUTPUT);
 pinMode(red, OUTPUT);
 // Initialize pins for buzzer
 pinMode(buzz,OUTPUT);
 // start serial port 
 Serial.begin(9600); 
 // Start up the sensors 
 sensors.begin(); 
} 
void loop(void) 
{ 

 // call sensors.requestTemperatures() to issue a global temperature 
 // request to all devices on the bus 
 sensors.requestTemperatures(); // Send the command to get temperature readings 
 float temp = sensors.getTempCByIndex(0);
/********************************************************************/
 Serial.println(temp); // Why "byIndex"? 
 digitalWrite(blue, LOW);    // turn the LED off by making the voltage LOW
 digitalWrite(green, LOW);
 digitalWrite(red, LOW); 
 
 if (temp>0 and temp<55){
  digitalWrite(blue, HIGH);
  digitalWrite(green, LOW);
  digitalWrite(red, LOW);
 }
 if (temp>55 and temp<60){
  beep();
  digitalWrite(blue, LOW);
  digitalWrite(green, HIGH);
  digitalWrite(red, LOW);

  
 }
 if (temp>60){
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);
 }

 delay(1000); 
}

void beep(void){
    if (beepCounter<5){
    tone(buzz, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzz);     // Stop sound...
    beepCounter = beepCounter + 1;
  }
}
