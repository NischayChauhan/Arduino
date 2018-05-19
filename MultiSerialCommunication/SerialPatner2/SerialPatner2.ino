/* This code is created by Mr. Nischay Chauhan
 * Your can use this and develop further towards the betterment of Technology
 * Empower Youth 
 * Empower Nation 
 * Empower Future
 * Please give credit to the developer.
 */
#include <SoftwareSerial.h>

SoftwareSerial lcd(4,7);
void setup() {
  // initialize both serial ports:
  Serial.begin(115200);
  
  // read from port 0, send to port 1:
  
}

void loop() {
  lcd.begin(115200);
  String data="&";
  float a=2.22,b=33.33,c=44.44,d=55.55;
  data+=a;
  data+="&";
  data+=b;
  data+="&";
  data+=c;
  data+="&";
  data+=d;
  data+="&";
  
  lcd.print(data);
  lcd.end();
  delay(500);
  
}
