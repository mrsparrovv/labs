

typedef struct STATE{
  bool one = 1;
  bool zero = 0;
}state;



void setup() {
  DDRD = B11111111; // піни порту D (на платі 0-7 піни) позначаєм вихідними
  byte diode = B11110000;
  PORTD = diode;
  delay(700);
  int i, j, d=5;
  for( i=4; i>=0; i--){
    for(j=4; j>=0; j--){
      
      for( i=j; i>=0; i--){
        
        PORTD &=~(1<<i);
        PORTD |= 1<<(i-1);
        delay(700);
      }
      diode &=~(1<<i);
      diode &=~(1<<d);
      diode |=1<<j-1;
      PORTD = diode;
      diode &=~(1<<j);
      delay(700);
    }
    
  }d++;
}

void loop() {
  
 
}
