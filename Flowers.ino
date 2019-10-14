/*
 * Code modified by Sam Damen from https://www.instructables.com/id/PCB-LED-Flower/
 * 
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h>

//All LEDs on at the same time
const int LED[12][2] = {
  { 2, 4},
  { 4, 2},
  { 2, 1},
  { 1, 2},
  { 4, 1},
  { 1, 4},
  { 3, 1},
  { 1, 3},
  { 3, 2},
  { 2, 3},
  { 3, 4},
  { 4, 3}
};

//Outside LEDs on - furthest from the centre
const int LED_out[12][2] = {
  { 2, 4},
  { 4, 2},
  { 2, 1},
  { 3, 2},
  { 2, 3},
  { 3, 4},
  { 4, 3},
  { 2, 4},
  { 2, 1},
  { 3, 4},
  { 4, 2},
  { 2, 3}
};

//Inner ring of LEDs on - closest to the centre
const int LED_in[12][2] = {
  { 1, 3},
  { 1, 3},
  { 3, 1},
  { 3, 1},
  { 1, 4},
  { 1, 4},
  { 1, 2},
  { 1, 2},
  { 4, 1},
  { 4, 1},
  { 1, 3},
  { 3, 1}
};


int prev = 0;

//Variable to change the LEDs from all on to toggle
int led_pattern = 0;
//Toggle between the inner and outer ring
int flash = 0;
unsigned long currentMillis;
unsigned long startMillis;
//Toggle every 1.5secs
const unsigned long period = 1500;


void setup() {

  //Enable PIN0 as INPUT and Pullup
  pinMode(0, INPUT_PULLUP);
  
}

void loop() {
  currentMillis = millis();

  //Check if the switch has been pulled to ground
  if (digitalRead(0) == LOW) {
    led_pattern = 1;
  } else {
    led_pattern = 0;
  }

  //Keep time for toggling the LEDs
  if (currentMillis - startMillis >= period) {
    flash = !flash;
    startMillis = currentMillis;
  }
  
  for (int i = 0; i < 12; i++) {
    charlieON(i, led_pattern);
    delayMicroseconds(20);
  }
}

void charlieON(int now, int state) {

  //Want to flash between the inner and outer LEDs
  if (state) {

    if (flash) {
      digitalWrite(LED_in[prev][1], LOW);
      pinMode(LED_in[prev][0], INPUT);
      pinMode(LED_in[prev][1], INPUT);

      pinMode(LED_in[now][0], OUTPUT);
      pinMode(LED_in[now][1], OUTPUT);
      digitalWrite(LED_in[now][0], LOW);
      digitalWrite(LED_in[now][1], HIGH);
    } else {
      digitalWrite(LED_out[prev][1], LOW);
      pinMode(LED_out[prev][0], INPUT);
      pinMode(LED_out[prev][1], INPUT);

      pinMode(LED_out[now][0], OUTPUT);
      pinMode(LED_out[now][1], OUTPUT);
      digitalWrite(LED_out[now][0], LOW);
      digitalWrite(LED_out[now][1], HIGH);
    }

  //Want to show all LEDs on at same time
  } else {
      digitalWrite(LED[prev][1], LOW);
      pinMode(LED[prev][0], INPUT);
      pinMode(LED[prev][1], INPUT);

      pinMode(LED[now][0], OUTPUT);
      pinMode(LED[now][1], OUTPUT);
      digitalWrite(LED[now][0], LOW);
      digitalWrite(LED[now][1], HIGH);    
  }
  prev = now;
}

void charlieOFF(int now) {
  digitalWrite(LED[now][1], LOW);
  pinMode(LED[now][0], INPUT);
  pinMode(LED[now][1], INPUT);
}
