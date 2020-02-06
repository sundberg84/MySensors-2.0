// Enable debug prints
#define MY_DEBUG

// Enable and select radio type attached
#define MY_RADIO_NRF24
//#define MY_RADIO_RFM69

#define MY_NODE_ID 10
//#define MY_REPEATER_FEATURE

#include <SPI.h>
#include <MySensor.h>

#define CHILD_ID 1   // Id of the sensor child
#define DIGITAL_INPUT_SENSOR 3   // The digital input you attached your motion sensor.  (Only 2 and 3 generates interrupt!)
#define LED 4   // The digital input you attached your motion sensor.  (Only 2 and 3 generates interrupt!)

int oldTripped = 0;
int tripped = 0;

// Initialize motion message
MyMessage msg(CHILD_ID, V_TRIPPED);

void setup()  
{  
  pinMode(DIGITAL_INPUT_SENSOR, INPUT);      // sets the motion sensor digital pin as input
  pinMode(LED, OUTPUT);
}

void presentation()  {
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo("Motion Garaget #10", "1.2");

  // Register all sensors to gw (they will be created as child devices)
  present(CHILD_ID, S_MOTION);
}

void loop()     
{
     
//Read digital motion value
tripped = digitalRead(DIGITAL_INPUT_SENSOR);

if (tripped != oldTripped){
  Serial.println("Motion");
  send(msg.set(tripped?"1":"0"));  // Send tripped value to gw

  wait(50);
  
  if(tripped == true){
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
  
  oldTripped = tripped;

  
}}


