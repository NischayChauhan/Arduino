/* This code is created by Mr. Nischay Chauhan
 * Your can use this and develop further towards the betterment of Technology
 * Empower Youth 
 * Empower Nation 
 * Empower Future
 * Please give credit to the developer.
 */
#include "max6675.h"
int ktcSO = 0;
int ktcCS = 1;
int ktcCLK = 4;

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);
void setup() {
 Serial.begin(115200);
 delay(500);
}

void thermocouple()
{
  Serial.print("Deg C = "); 
  Serial.print(ktc.readCelsius());
  Serial.print("\t Deg F = ");
  Serial.println(ktc.readFahrenheit());
  delay(500);
}
void loop() {
   thermocouple();
}
