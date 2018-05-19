/* This code is created by Mr. Nischay Chauhan
 * Your can use this and develop further towards the betterment of Technology
 * Empower Youth 
 * Empower Nation 
 * Empower Future
 * Please give credit to the developer.
 */
#include <SPI.h>
#include <SD.h>
#include "HX711.h"
//This value is obtained using the SparkFun_HX711_Calibration sketch
#define calibration_factor -2070.0 
#define DOUT  2
#define CLK  3

HX711 scale(DOUT, CLK);

const int chipSelect = 4;
int pot_F_init,pot_B_init;
float Dist_F,Dist_B;

int half_revolutions=0 ;
int a;
int rpm = 0;
unsigned long lastmillis = 0;



void rpm_fan(){
  half_revolutions++;
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pot_F_init=analogRead(A4);
  pot_B_init=analogRead(A5);
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
   scale.set_scale(calibration_factor);  

 attachInterrupt(0, rpm_fan, FALLING); //pin 2 is interrupt 0 and pin 3 is interrupt 1

}

void loop() {
 Dist_F=(analogRead(A4)-pot_F_init)/7.33;
 Dist_B=(analogRead(A5)-pot_B_init)/7.33;
  File dataFile = SD.open("Loadprod.csv", FILE_WRITE);
  if (dataFile) {
    int data=9.8*scale.get_units();
    dataFile.print(data);
    dataFile.print(",");
    dataFile.print(Dist_F);
    dataFile.print(",");
    dataFile.println(Dist_B);
    dataFile.close();
  }

     
 if (millis() - lastmillis == 1000){ //Update every one second, this will be equal to reading frecuency (Hz).
 detachInterrupt(0);//Disable interrupt when calculating
 a = half_revolutions/2;
 rpm = a * 60; // Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use half_revolutions * 30.

   
   Serial.print("Reading: ");
Serial.print(9.8*scale.get_units(),1);
  Serial.print(" Newtons"); 
  Serial.println();
Serial.print(" pot back="); 
  Serial.println(Dist_B);
Serial.print(" pot front="); 
  Serial.println(Dist_F);


Serial.print("\t RPM =\t"); //print the word "RPM" and tab.
 Serial.print(rpm); // print the rpm value.
 Serial.print("\t Hz=\t"); //print the word "Hz".
 Serial.println(a); //print revolutions per second or Hz. And print new line

 
 
 half_revolutions = 0; // Restart the RPM counter
 lastmillis = millis(); // Update lasmillis
 attachInterrupt(0, rpm_fan, FALLING); //enable interrupt

}
