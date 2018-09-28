

#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.
//  Variables

const int PULSE_SENSOR_COUNT = 2;
const int PulseWire1 = A0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int PulseWire2 = A1;
const int LED13 = 13;
const int LED12 = 12;  
int Threshold = 550;   


PulseSensorPlayground pulse(2);  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

void setup() {

  Serial.begin(9600);          // For Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it.
  pulse.analogInput(PulseWire1,0);
  pulse.analogInput(PulseWire2,1);

  pulse.fadeOnPulse(LED12,0); 
  pulse.fadeOnPulse(LED13,1);       //auto-magically blink Arduino's LED with heartbeat.
  
  pulse.setThreshold(Threshold);
  
    
   if (pulse.begin()) {
    Serial.println("We created a pulseSensor Object !");  
  }
}



void loop() {

 int myBPM = pulse.getBeatsPerMinute(0);  // Calls function on our pulseSensor object that returns BPM as an "int".
 int myBPM2 = pulse.getBeatsPerMinute(1);


if (pulse.sawStartOfBeat(0)) {            
  
 Serial.print("BPMa: ");                        
 Serial.println(myBPM);                        
}

if(pulse.sawStartOfBeat(1)){
  Serial.print("BPMb: ");
  Serial.println(myBPM2);
  }


  delay(20);                    // considered best practice in a simple sketch.

}
