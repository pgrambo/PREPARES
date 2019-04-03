//BMES 5984 project continuation spring 2019
//Phillip Grambo phillip8@vt.edu
//This code is meant to turn on a LED and pulse a piezo buzzer for a fixed amount of time when a button is pushed
// revision history:
//      V1.0: orginal version, march 8, 2019
//------------------------------------------------
//chosen constants
const int b_pin = 7;               // read button high/low state on pin A1
const int r_pin = 2;               // declare digital output pin 2 as the line that feeds the relay
const int loop_time = 2000;        // how long the effect lasts for
int high_time = 100;               //how long the relay coil is energized for in miliseconds
const int p_pin = 5;               // declare digital output pin 5 as the line to the speaker
int lc=0;                          // initialize loop counter variable
//calculated constants 
int low_time = high_time;          //how long the relay is de-energized for in miliseconds
int period = low_time+high_time;   // how long the loop cycle is for
int l_total = loop_time/(period);  // calculate the number of loops needed to pulse
// variables
int b_state = 0;                   //button state will change on every loop
//------------------------------------------------
void setup() {
 pinMode(b_pin, INPUT_PULLUP);    // initialize the button pin as an input
 pinMode(r_pin, OUTPUT);          // initialize the relay pin as an output
 pinMode(p_pin, OUTPUT);          // initialize the piezo buzzer pin as an output
}
//------------------------------------------------
void loop() {
//measure button state
b_state = digitalRead(b_pin);
// strobe&tone effect
if (b_state == LOW){
  // tone(pin number, frequency in hertz, duration in milliseconds);  //duration is optional
  // freqencies: 3011 is the most important, 439 is 2nd, then: 129, 311, 744, 996, 4969, 7031, 7875, 1500
  // put a 100ohm resistor on the ground line of the piezo buzzer

  //LED code stays high for the void loop() code segment)
  digitalWrite(r_pin, HIGH);   // trigger the relay
  

  // pulse effect
  for (lc=1; lc < l_total; lc++){
  // tone duration tuns in parallel with delay and others, so it goes on while the rest of the code executes
  tone(p_pin, 3011, high_time);   // play the tone for the pulse time
  delay(high_time);               // wait for the tone to finish (tone() uses a different parallel timer to the delay() function)
  noTone(p_pin);                  // turn the tone off
  delay(low_time);                // wait again for the duration of low_time
  }

  delay(high_time);            // how long the relay coil is energized for 
  digitalWrite(r_pin, LOW);    // de-energize the relay coil
  } 
  else {
  // turn piezo buzzer and relay off
  noTone(p_pin);              // stop outputting the tone
  digitalWrite(r_pin, LOW);   // de-energize the relay coil
  }
digitalWrite(r_pin, LOW);     // de-energize the relay coil after the if statement, which should last the duration of "loop_time"
delay(10);                    // for switch debouncing  
} //end of code
