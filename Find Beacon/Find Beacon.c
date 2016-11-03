
//Port Declarations
const int LMOTOR = 0;
const int RMOTOR = 3;
const int LSERVO = 2;
const int RSERVO = 0;
const int NBEACON= 4;
const int EBEACON= 5;
const int SBEACON= 6;
const int WBEACON= 7;

//Value Declarations
int beaconVal = 100;

int rightArmDown = 1100;
int leftArmDown = 1200;
int rightArmUp = 0;
int leftArmUp = 1024;

int defaultSpeed = 50;
int defaultTime = 50;

//Command Declarations
void foward();
void turnLeft();
void turnRight();
void turnAround();
void manipulate();
void findBeacon();

//////////MAIN///////////

int main(){
	while(1){
		findBeacon();
	}
}

/////////BASIC MOVEMENT/////////

void forward(){
	motor(LMOTOR, defaultSpeed);
	motor(RMOTOR, defaultSpeed);
	sleep(defaultTime / 2);
}

void turnLeft(){
	motor(LMOTOR, -defaultSpeed);
	motor(RMOTOR, defaultSpeed);
	sleep(defaultTime);
}

void turnRight(){
	motor(LMOTOR, defaultSpeed);
	motor(RMOTOR, -defaultSpeed);
	sleep(defaultTime);
}

void turnAround(){
	motor(LMOTOR, -defaultSpeed);
	motor(RMOTOR, defaultSpeed);
	sleep(defaultTime * 2);
}

///////ARM CONTROL//////////

void manipulate(){
	set_servo_position(LSERVO, leftArmDown);
	set_set_position(RSERVO, rightArmDown);
}

///////BEACON SEEKING////////

void findBeacon(){
	if(NBEACON < beaconVal){
		forward();
	}
	else if(EBEACON < beaconVal){
		turnRight();
	}
	else if(WBEACON < beaconVal){
		turnLeft();
	}
	else if(SBEACON < beaconVal){
		turnAround();
	}
	else{
		forward();
	}
}		
