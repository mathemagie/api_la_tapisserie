#include <Process.h> 
#include <Bridge.h>
 
int led = 13;
int sensorPin = A0;
int tapisserieOpen;
int firstTime = 1;
unsigned int sensorValue;

void setup() 
{
        Bridge.begin();
        pinMode(led, OUTPUT); 
        Serial.begin(9600);
}

void OpenTapisserie() {
  Process p;        // Create a process and call it "p"
  p.runShellCommand("curl -d 'status=1&debug=0'  http://api.la-tapisserie.net/s");
  //or use runShellCommandAsynchronously instead of runShellCommand
}

void closeTapisserie() {
  Process p;        // Create a process and call it "p"
  p.runShellCommand("curl -d 'status=0&debug=0'  http://api.la-tapisserie.net/s");
}

void loop() 
{
        sensorValue = analogRead(sensorPin); 
        if (firstTime) {
           if(sensorValue<400) {
              tapisserieOpen = 0;
           }else {
               tapisserieOpen = 1;
           }
           firstTime = 0;
        }
           
        Serial.println(sensorValue, DEC);
        if(sensorValue<700) {
               if (tapisserieOpen) {
                 closeTapisserie();
                   Serial.println("CLOSE");
                    tapisserieOpen = 0;
                  delay(4000);
                 }
                digitalWrite(led, LOW);
        }
        else {
              if (tapisserieOpen == 0) {
                 OpenTapisserie(); 
                
                 Serial.println("OPEN");
                 tapisserieOpen = 1;
                  delay(4000);
              }
              digitalWrite(led,HIGH); 
            
             
                
        }
        delay(200);
 }
