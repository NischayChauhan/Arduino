/* This code is created by Mr. Nischay Chauhan
 * Your can use this and develop further towards the betterment of Technology
 * Empower Youth 
 * Empower Nation 
 * Empower Future
 * Please give credit to the developer.
 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);  //RX,TX
//  Arduino pin 2 (RX) to ESP8266 TX
//  Arduino pin 3 to voltage divider then to ESP8266 RX
//  Connect GND from the Arduiono to GND on the ESP8266
//  Connect ESP8266 CH_PD to 3.3 V

//  When a command is entered in to the serial monitor on the computer 
//  the Arduino will relay it to the ESP8266

void setup() 
{
    Serial.begin(115200);     // communication with the host computer
    mySerial.begin(115200);  
    Serial.println("Remember to to set Both NL & CR in the serial monitor.");
}
void loop() 
{
    // listen for communication from the ESP8266 and then write it to the serial monitor
    if ( mySerial.available() > 0 )   { 
      byte b = mySerial.read();
      Serial.write( b ); 
      }
 
    // listen for user input and send it to the ESP8266
    if ( Serial.available() > 0 )       {  
      byte b=Serial.read();
      mySerial.write( b ); 
      
      }
}
