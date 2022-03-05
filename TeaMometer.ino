/********************************************************************/
// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
#include "U8glib.h" 
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 4 
// Setup LEDs
const int blue = 6;
const int green = 7;
const int red = 8;
// Setup Buzzer
const int buzz = 10;
int beepCounter = 0;
char displayStr[] = "";
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 
//Initialize display.
U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE); // Just for 0.91”(128*32)

void setup(void) 
{ 
 // flip screen, if required
  // u8g.setRot180();
  

  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  u8g.setFont(u8g_font_unifont);
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
 
 if (temp>0 and temp<60){
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
  display(temp);
 delay(1000); 
}
void display(int temp){
  
  // picture loop
  u8g.firstPage();  
  do {
    u8g.setPrintPos(0, 10); 
    u8g.print(String(temp)+" Degrees C");
    u8g.setPrintPos(0, 30);
    if (temp>60){
    u8g.print("TOO HOT!!!");
  }else{
    u8g.print("Drinkable! :)");
  } 
    
  } while( u8g.nextPage() );
}

void beep(void){
    if (beepCounter<5){
    tone(buzz, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzz);     // Stop sound...
    beepCounter = beepCounter + 1;
  }
}
