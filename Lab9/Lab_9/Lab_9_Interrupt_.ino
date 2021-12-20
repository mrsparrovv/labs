const byte ledPin = 13;
volatile byte state = LOW;
 
void setup(){
   pinMode(ledPin, OUTPUT);
   pinMode(A0, INPUT_PULLUP);
    pinMode(7, INPUT_PULLUP);
     pinMode(8, INPUT_PULLUP);
   PCMSK0 = B00000001; 
   PCMSK1 = B00000001;//enable PCINT8 (A0)
   PCMSK2 = B10000000;
   PCIFR = B00000000; // clear all interrupt flags
   PCICR = B00000111; // enable PCIE1 group
   /* те саме, але по іншому записано:
   PCMSK1 = 1 << PCINT8;
   PCIFR = 0;
   PCICR = 1 << PCIE1;*/
}
 
void loop(){
   digitalWrite(ledPin, state);
}
 
ISR(PCINT1_vect) {
   state = !state;
}
