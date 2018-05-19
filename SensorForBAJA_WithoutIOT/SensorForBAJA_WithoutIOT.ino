/* This code is created by Mr. Nischay Chauhan
 * Your can use this and develop further towards the betterment of Technology
 * Empower Youth 
 * Empower Nation 
 * Empower Future
 * Please give credit to the developer.
 */
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Wire.h>
#include <max6675.h>

MAX6675 ktc(12, 11, 10);
TinyGPS gps;

SoftwareSerial l =  SoftwareSerial(8,9); 
SoftwareSerial lcd(4,7);

/*thermocouple*/
float deg_c=0;
/* thermocouple*/ 

/* rpm*/
int half_revolutions=0 ;
int a;
int rpm = 0;
unsigned long lastmillis = 0;
/*rpm*/

/* flow rate*/
byte sensorPin = 2;
float calibrationFactor = 4.5;
volatile byte pulseCount;  
float flowRate;
unsigned int flowMilliLitres;
float totalMilliLitres;
unsigned long oldTime;
/* flow rate*/

/* gps*/
float lat,lang;
/*gps*/


int RAD=20;

void showResponse(int waitTime){
  long t=millis();
  char c;
  while (t+waitTime>millis()){
    if (espSerial.available()){
      c=espSerial.read();
      if (DEBUG) Serial.print(c);
    }
  }
}


// this code will be executed every time the interrupt 0 (pin2) gets low.
void rpm_fan(){
  half_revolutions++;
}

void pulseCounter()
{
// Increment the pulse counter
  pulseCount++;
}
void setup() {
  
  Serial.begin(115200);  
  
  DEBUG=true; 
  attachInterrupt(0, rpm_fan, FALLING); //pin 2 is interrupt 0 and pin 3 is interrupt 1
  
  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;
  
  attachInterrupt(1, pulseCounter, FALLING);

}
void loop() {

//3400  
deg_c=ktc.readCelsius();

/* rpm*/  
 if (1){ //Update every one second, this will be equal to reading frecuency (Hz).
 detachInterrupt(0);//Disable interrupt when calculating
 detachInterrupt(1);
 a = half_revolutions;
 rpm = a * 60; // Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use half_revolutions * 30.
 rpm/=3.4;
 //Serial.print("Check \t ");
 //Serial.print(a);
 Serial.print("\t RPM =\t"); //print the word "RPM" and tab.
 Serial.print(rpm); // print the rpm value.
 Serial.print("\t Hz=\t"); //print the word "Hz".
 Serial.println(a); //print revolutions per second or Hz. And print new line
 half_revolutions = 0; // Restart the RPM counter

  flowRate = ((1000.0 / (3400)) * pulseCount) / calibrationFactor;  
  flowMilliLitres = (flowRate / 60) * 1000;
  totalMilliLitres += flowMilliLitres;
  unsigned int frac;
  frac = (flowRate - int(flowRate)) * 10;
  Serial.print("  Output Liquid Quantity: ");             // Output separator
  Serial.print(totalMilliLitres);
  Serial.println("mL"); 
  totalMilliLitres/=1000;
  pulseCount = 0;
  attachInterrupt(1, pulseCounter, FALLING);
  attachInterrupt(0, rpm_fan, FALLING); //enable interrupt
}
/*rpm*/

/* gps start*/
l.begin(9600);

  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (l.available())
    {
      char c = l.read();
        if (gps.encode(c)) // Did a new valid sentence come in?
          newData = true;
    }
  }          
  
  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
     Serial.print("LAT=");
    Serial.println( flat, 6);
    Serial.print(" LON=");
    Serial.println(flon, 6);
    lat=flat;
    lang=flon;
  }
l.end();
/* gps end*/

/* oled*/

  lcd.begin(9600);
  String data="";
  data+=String((2*3.14*rpm*RAD)/flowRate,2);
  data+="&";
  data+=String(deg_c,2);
  data+="&";
  data+=String(rpm,2);
  data+="&";
  
  lcd.print(data);
  lcd.end();
  Serial.println(data);
/*oled*/


Serial.println(lang);
Serial.println(lat);
Serial.println(totalMilliLitres);
Serial.println(deg_c);
Serial.println(rpm);

}
