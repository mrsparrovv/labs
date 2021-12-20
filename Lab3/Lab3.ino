int pinPWE = 5, pinDIR = 7, pinEnc = 6;
int pinPWE02 = 11, pinDIR02 = 9, pinEnc02 = 10;
float gradus = 0; int encoder = 0; int flag = 0; int count = 0;
float gradus02 = 0; int encoder02 = 0; int flag02 = 0; int count02 = 0; 
int DIR02 = 0; int DIR01 = 0;

void checkRound()
{
	if (DIR01 == 1){
		gradus = gradus + 22.5;
		if (int(gradus) % 360 == 0) {
			count++;
			gradus = 0;
		}
	}
	if (DIR01 == 2){
		gradus = gradus - 22.5;
		if (int(gradus) % 360 == 0) {
			count--;
			gradus = 0;
		}
	}
}
void checkRound02()
{
	if (DIR02 == 1){
		gradus02 = gradus02 + 22.5;
		if (int(gradus02) % 360 == 0) {
			count02++;
			gradus02 = 0;
		}
	}
	if (DIR02 == 2){
		gradus02 = gradus02 - 22.5;
		if (int(gradus02) % 360 == 0) {
			count02--;
			gradus02 = 0;
		}
	}
}

void setup()
{
	pinMode(pinEnc, INPUT);
	pinMode(pinPWE, OUTPUT);
	pinMode(pinDIR, OUTPUT);
	pinMode(pinEnc02, INPUT);
	pinMode(pinPWE02, OUTPUT);
	pinMode(pinDIR02, OUTPUT);
	Serial.begin(9600);
	//digitalWrite(pinDIR, LOW);
	//digitalWrite(pinDIR, HIGH);
}

void loop()
{
	//01
	encoder = digitalRead(6);
	if ((encoder == HIGH) && (flag == 0)){
		checkRound();
		flag = 1;
	}
	if ((encoder == LOW) && (flag == 1)){
		checkRound();
		flag = 0;
	}

	int sensorReading = analogRead(A0);
	int t = map(sensorReading, 0, 1023, 0, 255);

	if (sensorReading <= 410){
		digitalWrite(pinDIR, LOW);
		DIR01 = 1;}

	if (sensorReading >= 614){
		digitalWrite(pinDIR, HIGH); DIR01 = 2;}

	if ((sensorReading >= 410) && (sensorReading <= 614)){
		t = 0; DIR01 = 3;}

	Serial.print("MOTOR A0 ");
	Serial.print(abs(count));
	if (count <= 0){
		Serial.println(" left ");}
	if (count > 0){
		Serial.println(" right ");}

	analogWrite(pinPWE, t);
	//02
	encoder02 = digitalRead(10);
	if ((encoder02 == HIGH) && (flag02 == 0)){
		checkRound02();
		flag02 = 1;
	}
	if ((encoder02 == LOW) && (flag02 == 1)){
		checkRound02();
		flag02 = 0;
	}

	int sensorReading02 = analogRead(A1);
	int t02 = map(sensorReading02, 0, 1023, 0, 255);

	if (sensorReading02 <= 410){
		digitalWrite(pinDIR02, LOW);
		DIR02 = 1;}

	if (sensorReading02 >= 614){
		digitalWrite(pinDIR02, HIGH); DIR02 = 2;}

	if ((sensorReading02 >= 410) && (sensorReading02 <= 614)){
		t02 = 0; DIR02 = 3;}

	Serial.print("MOTOR A1 ");
	Serial.print(abs(count02));
	if (count02 <= 0){
		Serial.println(" left ");}
	if (count02 > 0){
		Serial.println(" right ");}

	analogWrite(pinPWE02, t02);

}
