
//Port Declarations
const int LMOTOR = 0;
const int RMOTOR = 3;
const int LSERVO = 2;
const int RSERVO = 0;
const int NBEACON= 13;
const int EBEACON= 12;
const int SBEACON= 11;
const int WBEACON= 10;
const int LEFT_IR = 2;
const int RIGHT_IR = 1;

//True/False Delcaration
const int TRUE = 1;
const int FALSE = 0;

//Value Declarations
int rightArmDown = 1100;
int leftArmDown = 1200;
int rightArmUp = 0;
int leftArmUp = 1024;

int defaultSpeed = 75;
int defaultTime = 500;

//Command Declarations
void foward();
void turnLeft();
void turnRight();
void turnAround();
void manipulate();
void findBeacon();
void roam();

//////////MAIN///////////

int main(){
	while(1){
		roam();
	}
}

///////////ROAM//////////

void roam(){
	int rightIRValue = analog_et(RIGHT_IR);
	int leftIRValue = analog_et(LEFT_IR);
	
	int rmSpeed = defaultSpeed * (leftIRValue / rightIRValue);
	int lmSpeed = defaultSpeed * (rightIRValue / leftIRValue);
	
	motor(LMOTOR, rmSpeed);
	motor(RMOTOR, lmSpeed);
}

/////////BASIC MOVEMENT/////////

void forward(){
	motor(LMOTOR, defaultSpeed);
	motor(RMOTOR, defaultSpeed);
	msleep(defaultTime / 2);
}

void turnLeft(){
	motor(LMOTOR, -defaultSpeed);
	motor(RMOTOR, defaultSpeed);
	msleep(defaultTime);
}

void turnRight(){
	motor(LMOTOR, defaultSpeed);
	motor(RMOTOR, -defaultSpeed);
	msleep(defaultTime);
}

void turnAround(){
	motor(LMOTOR, -defaultSpeed);
	motor(RMOTOR, defaultSpeed);
	msleep(defaultTime * 2);
}

///////ARM CONTROL//////////

void manipulate(){
	enable_servos();
	set_servo_position(LSERVO, leftArmDown);
	set_servo_position(RSERVO, rightArmDown);
}

///////BEACON SEEKING////////

void findBeacon(){
	if(digital(NBEACON) == TRUE){
		printf("NORTH");
		forward();
	}
	else if(digital(EBEACON) == TRUE){
		printf("EAST");
		turnRight();
	}
	else if(digital(WBEACON) == TRUE){
		printf("WEST");
		turnLeft();
	}
	else if(digital(SBEACON) == TRUE){
		printf("SOUTH");
		turnAround();
	}
	else{
		forward();
		printf("NONE");
	}
}		
