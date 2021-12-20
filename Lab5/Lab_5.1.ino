#define MAX7219_Data_IN 11
#define MAX7219_Chip_Select  9
#define MAX7219_Clock 13

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
	uint8_t i;

	for (i = 0; i < 8; i++)  {
		if (bitOrder == LSBFIRST) {
			digitalWrite(dataPin, val & 1); // dataPin = MOSI
			val >>= 1;
		} else {	// MSBFIRST
			digitalWrite(dataPin, (val & 128) != 0); // dataPin = MOSI
			val <<= 1;
		}

		digitalWrite(clockPin, HIGH); // clockPin = SCK
		digitalWrite(clockPin, LOW); // clockPin = SCK	
	}
}

byte number[10]  {
	B01111110,  // 0
	B00110000,  // 1
	B01101101,  // 2
	B01111001,  // 3
	B00110011,  // 4
	B01011011,  // 5
	B01011111,  // 6
	B01110000,  // 7
	B01111111,  // 8
	B01110011,  // 9
};

byte name_PI_n81[8] = {
 
  B00000000,
  B00000000,
  
  B00110111,  // H
  B01001111,  // E
  B00001110,  // L
  B01100111,  // P
  number[0],  // NUMBER
  B00000000,
};

void shift(byte send_to_address, byte send_this_data) 
{
	digitalWrite(MAX7219_Chip_Select, LOW);
	shiftOut(MAX7219_Data_IN, MAX7219_Clock, MSBFIRST, send_to_address);
	shiftOut(MAX7219_Data_IN, MAX7219_Clock, MSBFIRST, send_this_data);
	digitalWrite(MAX7219_Chip_Select, HIGH);
	delay(100);
}
void init_max7219() //Setup of MAX7219 chip
{
	shift(0x0f, 0x00); //display test register - test mode off
	shift(0x0c, 0x01); //shutdown register - normal operation
	shift(0x0b, 0x07); //scan limit register - display digits 0 thru 7
	shift(0x0a, 0x0f); //intensity register - max brightness
	shift(0x09, 0x00); // 0xff); //decode mode register - No decode for digits

}

void setup() {
	int i = 1, j = 0;

	pinMode(MAX7219_Data_IN, OUTPUT);
	pinMode(MAX7219_Chip_Select, OUTPUT);
	pinMode(MAX7219_Clock, OUTPUT);
	digitalWrite(MAX7219_Clock, HIGH);
	init_max7219(); //init MAX2719 chip

	for ( i = 1; i < 8; i++){
		shift(i, name_PI_n81[7-i]);

	}

	while(1){
		for(i=8; i>0; i--){
			if(i==1){
				name_PI_n81[7] = name_PI_n81[0];	
			}else{
				name_PI_n81[8-i] = name_PI_n81[8-i+1];
			}

		}

		if(j%7==0){
			j /= 7; 
			number[j] = number[j+1];
		}
		j++;

		for(i=1; i<8; i++){
			shift(i, name_PI_n91[7-i]);

		}

		delay(100);
	}
}

void loop() {
}	