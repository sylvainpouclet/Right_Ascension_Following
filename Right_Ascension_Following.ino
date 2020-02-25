/*	Right Ascension Following
Release 1: 28/05/2018
Material used : 
	NANO V3.0 ATmega328P CH340
	A4988 Stepper Motor Driver Carrier
	Nema 17 17HS4401
*/

// Pin of the board
#define M1_DIR 5
#define M1_STEP 6
#define M1_ENABLE 9
#define BACKWARD 10
#define FORWARD 11
#define FAST 12

//Speed parameters
//Note: this parameters will be multipied by 4 later on the loop (sorry, it's cheap...)
#define STARS_SPEED 6882; 	
#define MAX_SPEED 50;

typedef struct stepperMotor {

	bool enable;
	bool direction;
	int  pulse;
};

struct stepperMotor followingRA;

void setup() {	

	pinMode(BACKWARD, 	INPUT);	
	pinMode(FORWARD, 	INPUT);
	pinMode(FAST, 		INPUT);
	pinMode(M1_DIR, 	OUTPUT);
	pinMode(M1_STEP, 	OUTPUT);
	pinMode(M1_ENABLE,	OUTPUT);
}

void loop() {

	if (digitalRead(FORWARD) == HIGH) {
		followingRA.enable = true;
		followingRA.direction = true;

	} else if (digitalRead(BACKWARD) == HIGH) {
		followingRA.enable = true;
		followingRA.direction = false;	
	} else {
		followingRA.enable = false;
	}

	if (digitalRead(FAST) == HIGH){
		followingRA.pulse = MAX_SPEED;
	} else {
		followingRA.pulse = STARS_SPEED;
	}

	motorCtrl(&followingRA);
}

void motorCtrl(struct stepperMotor *stepMotor){

	if (stepMotor->direction == true){
		digitalWrite(M1_DIR, LOW);		//LOW = Forward  HIGH = Backward
	} else {
		digitalWrite(M1_DIR, HIGH); 		//LOW = Forward  HIGH = Backward
	}

	if (stepMotor->enable == true){

		digitalWrite(M1_ENABLE, LOW); 		//LOW = Motor Enabled  HIGH = Motor Disabled
		
		delayMicroseconds(stepMotor->pulse);
		delayMicroseconds(stepMotor->pulse);
		delayMicroseconds(stepMotor->pulse);
		delayMicroseconds(stepMotor->pulse);

		digitalWrite(M1_STEP, HIGH);

		delayMicroseconds(stepMotor->pulse);
		delayMicroseconds(stepMotor->pulse);
		delayMicroseconds(stepMotor->pulse);
		delayMicroseconds(stepMotor->pulse);
		
		digitalWrite(M1_STEP, LOW);
	} else {
		digitalWrite(M1_ENABLE, HIGH);		///LOW = Motor Enabled  HIGH = Motor Disabled
	}
}
