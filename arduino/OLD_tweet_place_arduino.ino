//ARDUINO 1.0+ ONLY
//ARDUINO 1.0+ ONLY
#include <Ethernet.h>
#include <SPI.h>

int ledPin = 8; // LED pin
#define BUTTON 7

////////////////////////////////////////////////////////////////////////
//CONFIGURE
////////////////////////////////////////////////////////////////////////
byte server[] = {5, 135, 188, 103};

//The location to go to on the server
//make sure to keep HTTP/1.0 at the end, this is telling it what type of file it i
String location = "/open HTTP/1.0";

// if need to change the MAC address (Very Rare)
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
////////////////////////////////////////////////////////////////////////

String data;

int val_bouton = 0;
int start_val_bouton;
int icpt = 0;


EthernetClient client;

char inString[32]; // string for incoming serial data
int stringPos = 0; // string index counter
boolean startRead = false; // is reading?


void setup(){
  Ethernet.begin(mac);
  Serial.begin(9600);
  pinMode(BUTTON, INPUT);
  pinMode(ledPin, OUTPUT);
  start_val_bouton = digitalRead(BUTTON);
}

void loop(){
 // Serial.println(start_val_bouton);
// if (icpt == 0)
 //connectAndRead(); //connect to the server and  
 icpt = icpt + 1;
  val_bouton = digitalRead(BUTTON);
  if (val_bouton !=start_val_bouton ) {
      pushStatus();
      start_val_bouton = val_bouton;
 }
 // Serial.println(val_bouton);
  // led_ = digitalRead(ledPin);
    if (val_bouton == HIGH) {
       digitalWrite(ledPin, LOW);
    }else {
       digitalWrite(ledPin, HIGH);
    }
    // Serial.println(led_);


 // Serial.println(pageValue); //print out the findings.

  delay(1000); //wait 5 seconds before connecting again
}

String pushStatus(){
  //connect to the server

  Serial.println("connecting...");

  //port 80 is typical of a www page
  if (client.connect(server, 80)) {
    Serial.println("connected");
    val_bouton = digitalRead(BUTTON);
    Serial.println("valeur du bouton");
   // led_ = digitalRead(ledPin);
    if (val_bouton == HIGH) {
      Serial.println( "DOWN" );
      data = "status=0";
     
    }else {
       Serial.println( "UP" );
        data = "status=1";
 
    }
    
   

    Serial.println( data );
    client.println( "POST /s HTTP/1.1" );
    client.println("Host: api.la-tapisserie.net");
    client.println( "Content-Type: application/x-www-form-urlencoded" );
    client.println("User-Agent: Arduino/1.1");
    //client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);
    client.stop();
    client.flush();
 }else{
    return "connection failed";
  }

}
