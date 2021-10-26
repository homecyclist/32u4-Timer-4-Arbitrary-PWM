#include <avr/io.h>

unsigned long PwmD10(unsigned long frequency){
  unsigned long TOPVAL = (F_CPU / frequency) >> 1;
    
  // Generate a PWM signal on PB6/OC4B/D10
  DDRB = (1<<DDB6);
  // Set TOP, write upper bits first.
  TC4H = (TOPVAL) >> 8; OCR4C = (TOPVAL) & 0xFF;
  // Clear OC4B on comp. match, /OC4B disconnected, enable PWM4B
  TCCR4A = (1<<COM4B1) | (1<<PWM4B);
  // Start timer, presc. 1:1.
  TCCR4B = (1<<CS40);
  // Enhanced Compare/PWM mode to add 1 more bit of resolution 
  TCCR4E = (1<<ENHC4);

  TC4H = 0 >> 8; OCR4B = 0 & 0xFF;//initialize value at zero
  return TOPVAL << 1;  // This returns the max value, *2 for enhanced pwm mode.
}

unsigned long getValPwmD10(){
  // Get current value of D10 PWM.
  unsigned int D10Val;
  D10Val  = OCR4B; //read lower
  D10Val |= TC4H << 8; //read high then shift left
  return D10Val;
}

unsigned long getTopPwmD10(){
  // Get the highest PWM value for D10 PWM.
  unsigned int D10Top;
  D10Top  = OCR4C; //read lower
  D10Top |= TC4H << 8; //read high then shift left
  return D10Top << 1;
}

void setPwmD10(unsigned long val){
  unsigned long maxval = getTopPwmD10();
  if (val > maxval){
    val = maxval; // prevent values larger than current top.
  }
  TC4H = (val) >> 8;
  OCR4B = (val) & 0xFF;
}
