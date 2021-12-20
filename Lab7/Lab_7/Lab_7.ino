/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/






int j = 0, k, m = 0;
void myF(int i, int &num)
{  
 
  byte number[10]  {
  B00111111,  // 0
  B00000110,  // 1
  B01011011,  // 2
  B01001111,  // 3
  B01100110,  // 4
  B01101101,  // 5
  B01111101,  // 6
  B00000111,  // 7
  B01111111,  // 8
  B01101111,  // 9
};
  byte firstNum, secondNum, thirdNum;
   
  if(j>9){
    firstNum = number[m];
    secondNum = number[j%10];
  }else{
   firstNum = number[j];
   secondNum = 0x00;
  }
  byte helloSegments[] = {
  0x76, // H
  0x79, // E
  0x38, // L
  0x38, // L
  0x5C, // o
  firstNum,
  secondNum,
  0x00  // нічого
};

  int len = sizeof(helloSegments);
  const long myDelay = 500;
   


  PORTB |= ~PORTB; //PORTB = B111111; // встановлюємо високий рівень на пінах 8-13 порта В
  PORTB &= ~(1 << num); // встановлюємо низький рівень піна порта В
  int index = i - num >= 0 ? i - num : len - 1;
  index = index < len ? index : len - 1;
  PORTD = helloSegments[index];
  if(index%5==0 && num==3){

  PORTD = number[j];
  }
  delay(1);
  num = (num + 1) % 4;
  
}

void setup() {
  DDRD = B11111111; // піни порту D (на платі 0-7 піни) позначаєм вихідними
  DDRB = B111111; // піни порту B (на платі 8-13 піни) позначаєм вихідними

  PORTB = B111111; // встановлюємо високий рівень пінів порта В (на платі 8-13 піни)
}

void loop() {
  for (k = 1; k < 6 + 4; k++){
  for (int i = 0; i < 6 + 4; i++)
  {
    int num = 0;
    long myTime = millis();
    delay(1);
    while (millis() - myTime < 200)
    {
      myF(i, num);
      
    }
  }j++;
  }m++;
}
