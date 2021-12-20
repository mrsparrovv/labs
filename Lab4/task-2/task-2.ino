#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"

Adafruit_LiquidCrystal lcd(0);
int columnLCD = 20, rowsLCD = 4;

unsigned long time = 0;
int X = 0, Y = 1;
String str = "RTF *.*";
int len = 0;
bool flag = true;
int buttonPin = 9;

void moveString()
{
	if(flag){
		lcd.setCursor(X,Y);
		lcd.print(" ");
		X++;
		if (X == 20 - len)
			flag = !flag;
	}else
	{
		lcd.setCursor(X + len - 1, Y);
		lcd.print(" ");
		X--;
		if( X == 0)
			flag = !flag;
	}
}

void buttonState()
{
	if((digitalRead(buttonPin)) == HIGH){
		lcd.setCursor(2,0);
		lcd.print("Push: On");
		lcd.print(" ");

	}else if((digitalRead(buttonPin)) == LOW){
		lcd.setCursor(2,0);
		lcd.print("Push: Off");
	}

}
void setup()
{
	pinMode(buttonPin, INPUT);
	len = str.length();
	lcd.begin(columnLCD, rowsLCD);
	lcd.setBacklight(HIGH);

	lcd.setCursor(0,1);
	lcd.print(str);
	lcd.setCursor(0,2);
	lcd.print("A0 = ???");
	lcd.setCursor(2,0);
	lcd.print("Push: ???");
}

void loop()
{
	if( millis() > time + 1000)
	{
		time = millis();
		moveString();
		lcd.setCursor(X,Y);
		lcd.print(str);
	}
	buttonState();
	lcd.setCursor(0,2);
	lcd.print("A0 = ");
	int sensorReading = analogRead(A0);
	lcd.print(sensorReading);
	if(sensorReading < 10)
		lcd.print("  ");
	else if(sensorReading < 100)
		lcd.print("  ");
	else if(sensorReading < 1000)
		lcd.print(" ");
}