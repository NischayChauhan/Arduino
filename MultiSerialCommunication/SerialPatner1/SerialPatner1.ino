/* This code is created by Mr. Nischay Chauhan
 * Your can use this and develop further towards the betterment of Technology
 * Empower Youth 
 * Empower Nation 
 * Empower Future
 * Please give credit to the developer.
 */
#include <SoftwareSerial.h>

SoftwareSerial lcd(10,11);

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
lcd.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int flag=0;
String data="";
String ji[4]={""};
  while(lcd.available()) {
    int inByte = lcd.read();
  int a=inByte;
  char c=a;
  data+=c;
  }
  Serial.println(data);
  char charBuf[30];
  data.toCharArray(charBuf,30);
  int count=1;
  int j=0;
  for(int i=0;i<30;i++){
    if(charBuf[j]=='&'){
      j++;
      continue;
    }
    ji[j]+=charBuf[i];
  }
  for(int i=0;i<4;i++){
  Serial.println(ji[i]);
  }
  delay(500);
  
}
