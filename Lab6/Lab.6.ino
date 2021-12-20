#include <SD.h>
#include <TFT.h>
#include <SPI.h>

TFT TFTscreen = TFT(7, 8, 1); //CS, DC, RESET
const int chipSelect = 4;
File myFile;
int sensorValue = analogRead(A0);
int xPos = 0;

void Triugolnik1( int x, int y, int pix){
	TFTscreen.line( x, y, x, y+pix);
	TFTscreen.line( x, y, x+pix, y+pix);
	TFTscreen.line( x, y+pix, x+pix, y+pix);
}

void setup()
{	

	TFTscreen.begin();

	TFTscreen.background ( 200,200,200 );

	Serial.begin(9600);

	Serial.print("Initializing SD card...");
	if (!SD.begin(chipSelect)) {
		Serial.println("initialization failed!");

	}
	Serial.println("initialization done.");
	myFile = SD.open("test.txt", FILE_WRITE);

	if (myFile) {	// if the file opened okay, write to it:
		Serial.print("Writing to test.txt...");

		myFile.println(sensorValue);

		// close the file:
		myFile.close();
		Serial.println("done.");
	} else {
		Serial.println("error opening test.txt");
	}

	myFile = SD.open("test.txt"); // re-open the file for reading:
	if (myFile) {
		Serial.println("test.txt:");

		// read from the file until there's nothing else in it:
		while (myFile.available()) {
			Serial.write(myFile.read());
		}
		myFile.close();// close the file:
	} else {
		Serial.println("error opening test.txt");
	}

}

void loop() {

	int sensor = analogRead(A0);
	Serial.println(sensor);
	int cvet = map(sensor, 0, 1023, 0, 255);
	TFTscreen.setTextSize(3);
	TFTscreen.stroke(cvet,255-cvet,0);
	TFTscreen.text("PI-n01", 0, 0);
	

	TFTscreen.fill(cvet,255-cvet,0);
	TFTscreen.circle (50, 70, 10);

	int drawHeight = map(sensor, 0, 1023, 0, TFTscreen.height());
	// print out the height to the serial monitor

	// draw a line in a nice color
	TFTscreen.fill(cvet,255-cvet,0);
	TFTscreen.stroke(cvet,255-cvet,0);
	TFTscreen.line(xPos, TFTscreen.height() - drawHeight, xPos, TFTscreen.height());
	delay(16);

	if (xPos >= 160) {
		xPos = 0;
		TFTscreen.background(0, 0, 0);
	} else {
		// increment the horizontal position:
		xPos++;
	}

	delay(16);

}
