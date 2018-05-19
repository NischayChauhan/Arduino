/* This code is created by Mr. Nischay Chauhan
 * Your can use this and develop further towards the betterment of Technology
 * Empower Youth 
 * Empower Nation 
 * Empower Future
 * Please give credit to the developer.
 */
 int half_revolutions=0 ;
 int a;
 int rpm = 0;
 unsigned long lastmillis = 0;
 void setup(){
 Serial.begin(9600);
 attachInterrupt(0, rpm_fan, FALLING);
 }
 void loop(){
  
 if (millis() - lastmillis == 1000){ //Uptade every one second, this will be equal to reading frecuency (Hz).
 detachInterrupt(0);//Disable interrupt when calculating
 a = half_revolutions/2;
 rpm = a * 60; // Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use half_revolutions * 30.

 //Serial.print("Check \t ");
 //Serial.print(a);
 Serial.print("\t RPM =\t"); //print the word "RPM" and tab.
 Serial.print(rpm); // print the rpm value.
 Serial.print("\t Hz=\t"); //print the word "Hz".
 Serial.println(a); //print revolutions per second or Hz. And print new line or enter.M
 half_revolutions = 0; // Restart the RPM counter wwwww
 lastmillis = millis(); // Uptade lasmillis
 attachInterrupt(0, rpm_fan, FALLING); //enable interrupt
  }
 }
 // this code will be executed every time the interrupt 0 (pin2) gets low.
 void rpm_fan(){
  half_revolutions++;
 }
 
