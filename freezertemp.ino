#include <Ethernet.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

// Ethernet variables
byte mac[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05 };
IPAddress ip(1,2,3,4);
IPAddress dns(1,1,1,1);
IPAddress gateway(5,6,7,8);
IPAddress subnet(255,255,255,0);
EthernetServer server(80);
boolean alreadyConnected = false;

int buzzPin =  3;    //Connect Buzzer on Digital Pin3
float temperatureC;
int failcount = 0;

void setup(){
  //OneWire setup
  sensors.begin();
  //Serial setup
  Serial.begin(9600);
  // Ethernet setup
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("===============================> SERVER IP ");
  Serial.println(Ethernet.localIP());
  // Buzzer setup
  pinMode(buzzPin, OUTPUT);
}

void loop() {
  // Ethernet stuff
  EthernetClient client = server.available();

  
  sensors.requestTemperatures(); 
  temperatureC = sensors.getTempCByIndex(0);
  Serial.print(temperatureC);
  Serial.print("*C / ");
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  Serial.print(temperatureF); 
  Serial.println("*F");

  if (temperatureF < -190 ) {
    Serial.println("Sensor appears failed, resetting.");
    delay(100);
    void(* resetFunc) (void) = 0;//declare reset function at address 0
    resetFunc(); //call reset  
  }
 
  // Respond to HTTP requests with some JSON
  if (client) {
    if (!alreadyConnected) {
      Serial.println("===============================> HTTP CONNECTION");
      alreadyConnected = true;
    }
    boolean currentLineIsBlank = true;
    char c = client.read();
    if (c == '\n' && currentLineIsBlank) {
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("Connection: close");
      client.println();
      client.print("{\"temperatureC\": ");
      client.print(temperatureC);
      client.print(", \"temperatureF\": ");
      client.print(temperatureF);
      client.println("}");
      delay(1);
      client.stop();
      alreadyConnected = false;
    }
  }
  if (temperatureF > 0) {
    failcount++;

  } else {
    failcount = 0;
  }
  if (failcount > 10) {
    Serial.println("!!----- ALARM -----!!");
    digitalWrite(buzzPin, HIGH);
    delay(250);
    digitalWrite(buzzPin, LOW);
    delay(125);
    digitalWrite(buzzPin, HIGH);
    delay(125);
    digitalWrite(buzzPin, LOW);
    delay(125);
    digitalWrite(buzzPin, HIGH);
    delay(125);
    digitalWrite(buzzPin, LOW);
    delay(250);
  }
}
