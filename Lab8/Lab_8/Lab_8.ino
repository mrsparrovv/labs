//const byte buttonPin = 12; // PB4
//const byte ledPin =  13; // PB5

int buttonState = 0;

void setup() {
  //DDRB = B00100000; // встановимо 13 пін Arduino (5 пін регістра B) як вихід, а 12 пін Arduino (4 пін регістра B) як вхід
  DDRB |= 1 << PB5; // DDRB = DDRB | (1 << 5); // pinMode(ledPin, OUTPUT);
  DDRB &= ~(1 << PB4); // DDRB = DDRB & (~(1 << 4)); // pinMode(buttonPin, INPUT); 
  DDRB |= 1 << PB1;
  DDRB &= ~(1);
  DDRC &= ~(1 << PC5);
  DDRC |= (1 << PC4);
  DDRD |= (1 << PD1);
  DDRD &= ~(1 << PD0);
  
}

void loop() {
 // buttonState = ( PINB & (1 << PB4) ) >> PB4; // buttonState = digitalRead(buttonPin);
  
  ( PINB & (1 << PB4) ) >> PB4 == 1 ? PORTB |= 1 << PB5 : PORTB &= ~(1 << PB5);
  (PINB & (1 << PB0)) >> PB0 == 1 ? PORTB |= 1 << PB1 : PORTB &= ~(1 << PB1);
  (PINC & (1 << PC5)) >> PC5 == 1 ? PORTC |= 1 << PC4 : PORTC &= ~(1 << PC4);
  (PIND & (1 << PD0)) >> PD0 == 1 ? PORTD |= 1 << PD1 : PORTD &= ~(1 << PD1);
}
