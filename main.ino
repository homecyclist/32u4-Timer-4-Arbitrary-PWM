#include "PwmD10.c"

int maxValD10;

void setup(){
  maxValD10 = PwmD10(25000); // Generate a 25000hz PWM signal on PB6/OC4B/D10 
  setPwmD10(maxValD10 / 2 ); // Set PWM width to 50%
  }

void loop(){
  }
