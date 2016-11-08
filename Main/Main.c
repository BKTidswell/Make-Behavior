//Define input channels for actuators and sensors
const int LMOTOR = 0;
const int RMOTOR = 3;
const int LSERVO = 0;
const int RSERVO = 2;
const int NBEACON= 4;
const int EBEACON= 5;
const int SBEACON= 6;
const int WBEACON= 7;
const int FRONT_BUMP= 15;
const int LEFT_IR= 2;
const int RIGHT_IR= 1;

//Value Declarations
int beaconVal = 100;

int rightArmDown = 1100;
int leftArmDown = 1200;
int rightArmUp = 0;
int leftArmUp = 2040;

int defaultSpeed = 75;
int defaultTime = 300;

int threshIR = 250;

//Command Declarations
void forward();
void turnLeft();
void turnRight();
void turnAround();
void manipulate();
void findBeacon();
void handsDown();
void handsUp();
void backUp();
int hitWall();
int hitBlock();
void roam();
void findBeacon();
int isBeacon();

//Define boolean constants
const int TRUE = 1;
const int FALSE = 0;

//main loop
int main(){
	int hasBlock = FALSE;
	
    while(1){
		if(hasBlock == FALSE){
			handsUp();
			if(hitWall()== TRUE){
				printf("hitWall \n");
				backUp();
				turnAround();
			}
			else if(hitBlock() == TRUE){
				printf("hitBlock \n");
				hasBlock = TRUE;
				handsDown();	
			}
			else{
				printf("else \n");
				roam();
			}
		}
		else if(hasBlock == TRUE && isBeacon() == TRUE){
			printf("findBeacon \n");
			findBeacon();
		}
		else{
			printf("else \n");
			roam();
		}
	}
}


//return true or false telling whether robot has hit the wall
int hitWall(){
    
	int left_ir;
	int right_ir;
    int front_bump;
    
	int escapeThreshold_ir = 300;
	
	left_ir = analog_et(LEFT_IR);
	right_ir = analog_et(RIGHT_IR);
	front_bump = digital(FRONT_BUMP);
	
    if(front_bump == TRUE){
		if(left_ir > escapeThreshold_ir || right_ir > escapeThreshold_ir){
        return TRUE;
		}
    }
    else{
        return FALSE;
    }
}

//return tru of false if we have hit a block
int hitBlock(){
	int left_ir;
	int right_ir;
    int front_bump;
    
	int blockThreshold_ir = 300;
	
	left_ir = analog_et(LEFT_IR);
	right_ir = analog_et(RIGHT_IR);
	front_bump = digital(FRONT_BUMP);
	
    if(front_bump == TRUE){
		if(left_ir < blockThreshold_ir || right_ir < blockThreshold_ir){
        return TRUE;
		}
    }
    else{
        return FALSE;
    }
}	

///////////ROAM//////////

void roam(){
	int rightIRValue = analog_et(RIGHT_IR);
	int leftIRValue = analog_et(LEFT_IR);
	
	int rmSpeed = defaultSpeed + defaultSpeed * (rightIRValue / threshIR);
	int lmSpeed = defaultSpeed + defaultSpeed *  (leftIRValue / threshIR);
	
	motor(LMOTOR, lmSpeed);
	motor(RMOTOR, rmSpeed);
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
	msleep(defaultTime / 2);
}

void turnRight(){
	motor(LMOTOR, defaultSpeed);
	motor(RMOTOR, -defaultSpeed);
	msleep(defaultTime / 2);
}

void turnAround(){
	motor(LMOTOR, -defaultSpeed);
	motor(RMOTOR, defaultSpeed);
	msleep(defaultTime * 2);
}

void backUp() {
	motor(LMOTOR, -defaultSpeed);
	motor(RMOTOR, -defaultSpeed);
	msleep(defaultTime/2);
}

void stop(){
	motor(LMOTOR, 0);
	motor(RMOTOR, 0);
}

///////BEACON SEEKING////////

int isBeacon(){
	if(digital(NBEACON) + digital(EBEACON) + digital(WBEACON) + digital(SBEACON) >= 1){
		return(TRUE);
	}
	else{
		return(FALSE);
	}
}

void findBeacon(){
	if(digital(NBEACON) == TRUE){
		forward();
	}
	else if(digital(EBEACON) == TRUE){
		turnRight();
	}
	else if(digital(WBEACON) == TRUE){
		turnLeft();
	}
	else if(digital(SBEACON) == TRUE){
		turnAround();
	}
	else{
		stop();
	}
}		

///////ARM CONTROL//////////

void handsDown(){
	enable_servos();
	set_servo_position(LSERVO, leftArmDown);
	set_servo_position(RSERVO, rightArmDown);
}

void handsUp(){
	enable_servos();
	set_servo_position(LSERVO, leftArmUp);
	set_servo_position(RSERVO, rightArmUp);
}

