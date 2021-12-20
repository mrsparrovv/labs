
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

void shift(byte send_to_address, byte send_this_data)
{
	digitalWrite(MAX7219_Chip_Select, LOW);
	shiftOut(MAX7219_Data_IN, MAX7219_Clock, MSBFIRST, send_to_address);
	shiftOut(MAX7219_Data_IN, MAX7219_Clock, MSBFIRST, send_this_data);
	digitalWrite(MAX7219_Chip_Select, HIGH);
	delay(200);
}

void init_MAX7219() //Setup of MAX7219 chip
{
	shift(0x0f, 0x00); //display test register - test mode off
	shift(0x0c, 0x01); //shutdown register - normal operation
	shift(0x0b, 0x07); //scan limit register - display digits 0 thru 7
	shift(0x0a, 0x0f); //intensity register - max brightness
	shift(0x09, 0xff); //decode mode register - CodeB decode all digits

}

void setup() {
	pinMode(MAX7219_Data_IN, OUTPUT);
	pinMode(MAX7219_Chip_Select, OUTPUT);
	pinMode(MAX7219_Clock, OUTPUT);
	digitalWrite(MAX7219_Clock, HIGH);
	delay(200);

	init_MAX7219();  //Setup of MAX7219 chip

	//Data transfer (adr, num):
/*shift(0x08, 0x02);
	shift(0x07, 0x03);
	shift(0x06, 0x04);
	shift(0x05, 0x05);
	shift(0x04, 0x06);
	shift(0x03, 0x07);
	shift(0x02, 0x08);
	shift(0x01, 0x09);
	delay(200);*/

	Serial.begin(9600);

}

void loop() {
	int sensorValue = analogRead(A0);
	Serial.println(sensorValue);
	//byte sensorValue1 = (byte) sensorValue;

	if(sensorValue >9 && sensorValue < 100){
		shift(0x08, sensorValue / 10);
		shift(0x07, sensorValue % 10);
		delay(100);	
	}else if(sensorValue >99 && sensorValue < 1000){
		shift(0x08, sensorValue / 100);
		shift(0x07, (sensorValue % 100) /10);
		shift(0x06, (sensorValue % 100) %10);
		delay(100);
	}else if(sensorValue >999){
		shift(0x08, sensorValue / 1000);
		shift(0x07, (sensorValue % 1000) /100);
		shift(0x06, (sensorValue % 1000) %100 /10);
		shift(0x05, (sensorValue % 1000) %100 %10);
		delay(100);
	}else{
		shift(0x08, sensorValue);
		delay(100);
	}		
	delay(1);
}

