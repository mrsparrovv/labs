int digit_pins[2] = {8, 9};
byte digit = 0;

unsigned long tm, next_sec=0, next_flick=0;

const unsigned int to_sec = 1000;

const unsigned int to_flick = 1;

int pins[4] = {0, 1, 2, 3}; //контакти 0, 1, 2, 3, на платі Arduino
//контакти D0, D1, D2, D3 декодер 74LS49
// значення для виводу цифр 0-9
byte numbers[10] = { 
0b0000, 0b1000, 0b0100, 0b1100, 0b0010, // 0, 1, 2, 3, 4,
0b1010, 0b0110, 0b1110, 0b0001, 0b1001};  // 5, 6, 7, 8, 9
// змінна для збереження значення поточної цифри

int number = 0 ;

void setDigit( byte digit, unsigned int number ){
	byte d = 0;
	switch ( digit ){
		case 0:
			digitalWrite(digit_pins[0], HIGH);
			d = number/10 ;
			showNumber(d);
			digitalWrite(digit_pins[1], LOW);
			d = 0;
			break;
		case 1:
			digitalWrite(digit_pins[1], HIGH);
			d =number - int (number/10)*10;
			showNumber(d);
			digitalWrite(digit_pins[0], LOW);
			d = 0;
			break;
	}
}

void setup()
{
	for (int i = 0; i < 4; i++)
		pinMode(pins[i], OUTPUT);
	pinMode(9, OUTPUT); 
	pinMode(8, OUTPUT);
	//digitalWrite(9, LOW); //для включення декодера
	//digitalWrite(8, LOW);
}
void loop() {
	//for(number = 0; number <=60; number++)
	tm = millis();
	if( tm > next_sec ){
		next_sec = tm + to_sec;
		number++;
		if( number == 60 )
			number= 0;
	}

	tm = millis();
	if( tm > next_flick ){
		next_flick = tm + to_flick;
		digit++;
		if( digit == 2 )
			digit = 0;
		setDigit( digit, number );
		//delay(500);

	}
/*showNumber(number);
	delay(1000);
	number = (number + 1) % 10;*/
}
// функція виводу цифр
void showNumber(int num)
{
	for (int i = 0; i < 4; i++)
	{
		if (bitRead(numbers[num], 3 - i) == HIGH) {	// вкл. сегмент
			digitalWrite(pins[i], HIGH);
		} else {	// викл. сегмент
			digitalWrite(pins[i], LOW);
		}
	}
}
