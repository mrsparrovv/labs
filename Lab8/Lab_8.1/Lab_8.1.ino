const byte helloSegments[] = {
  0x76, // H
  0x79, // E
  0x38, // L
  0x38, // L
  0x5C, // o
  0x00  // нічого
};

byte dot = 0x80;

int len = sizeof(helloSegments);
const long myDelay0 = 500;
const long myDelayB = 100;

bool stateButton_pin12()
{
  byte mask = 1 << PB4; // створюємо "маску" mask = В00001000
  int buttonState = (PINB & mask) >> PB4; // buttonState = digitalRead(buttonPin);
  return buttonState == 0 ? true : false;
}

bool stateButton_pin13()
{
  byte mask = 1 << PB5; // створюємо "маску" mask = В00010000
  int buttonState = (PINB & mask) >> PB5; // buttonState = digitalRead(buttonPin);
  return buttonState == 0 ? true : false;
}

bool stateButton_pinA0(){
  byte mask = 1 << PC0;
  int buttonState = (PINC & mask) >> PB0;
  return buttonState == 0 ? true : false;
}

void myF(int i, int &num, bool state)
{
  PORTB = B001111; // встановлюємо високий рівень на пінах 8-11 порта В
  if (state)
  {
    if (num == 3) PORTB = B001110;
    if (num == 2) PORTB = B001101;
    if (num == 1) PORTB = B001011;
    if (num == 0) PORTB = B000111;
  }
  else
  {
    if (num == 0) PORTB = B001110;
    if (num == 1) PORTB = B001101;
    if (num == 2) PORTB = B001011;
    if (num == 3) PORTB = B000111;
  }

  int index;
  if (i - num >= 0) index = i - num;
  else index = len - 1;
  if (index >= len) index = len - 1;
  if(stateButton_pinA0()){
    PORTD = dot;
  }else{
  PORTD = helloSegments[index];
  }
  delay(1);
  num = (num + 1) % 4;
  
}

void setup() {
  DDRD = B11111111; // піни пора D (на платі 0-7 піни) як виходи
  DDRB = B001111; // піни порта B (на платі 8-11 піни) позначаєм вихідними
  // 12 і 13 позначаєм вхідними (4 і 5 піни регістра B)

  PORTB = B001111; // встановлюємо високий рівень пінів порта В (на платі 8-11 піни)
}

void loop() {
  for (int i = 0; i < len + 4; i++)
  {
    int num = 0;
    long myTime = millis();
    delay(1);
    long myDelay;
    if (stateButton_pin12()) myDelay = myDelayB;
    else myDelay = myDelay0;
    while (millis() - myTime < myDelay)
    {
      bool state13 = stateButton_pin13();
      myF(i, num, state13);
    }
  }
}
