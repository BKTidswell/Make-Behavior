//Define input channels for actuators and sensors
const int LMOTOR = 0;
const int RMOTOR = 3;
const int LSERVO = 2;
const int RSERVO = 0;
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
int leftArmUp = 1024;

int defaultSpeed = 75;
int defaultTime = 300;

//Command Declarations
void forward();
void turnLeft();
void turnRight();
void turnAround();
void manipulate();
void findBeacon();
void armsDown();
void backUp();
int hitWall();
int hitBlock();

//Define boolean constants
const int TRUE = 1;
const int FALSE = 0;

//main loop
int main(){
    
    while(1){
		if(hitWall()== TRUE){
			printf("hitWall \n");
			backUp();
			turnAround();
		}
		else if(hitBlock() == TRUE){
			printf("hitBlock \n");
			armsDown();	
		}
		else{
			printf("else \n");
			forward();
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

//Roam fucntion includes avoiding objects	

int Roam(){
    
    int left_ir;
    int right_ir;
    
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
void backUp() {
	motor(LMOTOR, -defaultSpeed);
	motor(RMOTOR, -defaultSpeed);
	msleep(defaultTime/2);
}

///////ARM CONTROL//////////

void armsDown(){
	enable_servos();
	set_servo_position(LSERVO, leftArmDown);
	set_servo_position(RSERVO, rightArmDown);
}
