//Define input channels for actuators and sensors
const int LMOTOR = 0;
const int RMOTOR = 3;
const int LSERVO = 0;
const int RSERVO = 2;
const int CAMSERVO = 1;
const int FRONT_BUMP= 15;
const int LEFT_IR= 2;
const int RIGHT_IR= 1;


//Camera Stuff
const int CAMERA_BLUE = 0;

int block_position_x;
int block_position_y;
int block_width;
int block_height;
int block_area; 
int block_error_y;
int block_error_x;
int targets;

//Value Declarations
int rightArmDown = 1100;
int leftArmDown = 1200;
int rightArmUp = 0;
int leftArmUp = 2040;

int camUp = 0;
int camDown = 900;

int defaultSpeed = 60;
int defaultTime = 300;

int threshIR = 250;

//Command Declarations
void forward();
void turnLeft();
void turnRight();
void turnAround();
void manipulate();
void handsDown();
void handsUp();
void backUp();
int hitWall();
int hitBlock();
void roam();
void collectBlock();
void stop();

//Define boolean constants
const int TRUE = 1;
const int FALSE = 0;

//main loop
int main(){
	enable_servos();
	camera_open();
	set_servo_position(CAMSERVO, camUp);
	int hasBlock = FALSE;
	
    while(1){
		if(hasBlock == FALSE){
			handsUp();
			if(hitWall() == TRUE){
				printf("hitWall \n");
				backUp();
				turnAround();
			}
			else if(hitBlock() == TRUE){
				printf("hitBlock \n");
				stop();
				hasBlock = TRUE;
				collectBlock();
			}
			else{
				roam(1);
			}
		}
		else if(hasBlock == TRUE){
			roam(0.75);
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
		if(left_ir < blockThreshold_ir && right_ir < blockThreshold_ir && 
			checkBlock() == TRUE){
        return TRUE;
		}
    }
    else{
        return FALSE;
    }
}	

///////////ROAM//////////

void roam(mod){
	int rightIRValue = analog_et(RIGHT_IR);
	int leftIRValue = analog_et(LEFT_IR);
	
	int rmSpeed = defaultSpeed + defaultSpeed * (1/mod) * (rightIRValue / threshIR);
	int lmSpeed = defaultSpeed + defaultSpeed * (1/mod) * (leftIRValue / threshIR);
	
	motor(LMOTOR, lmSpeed * mod);
	motor(RMOTOR, rmSpeed * mod);
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

///////ARM CONTROL//////////

void handsDown(){
	set_servo_position(LSERVO, leftArmDown);
	set_servo_position(RSERVO, rightArmDown);
}

void handsUp(){
	set_servo_position(LSERVO, leftArmUp);
	set_servo_position(RSERVO, rightArmUp);
}

//////CAMERA STUFF/////////

int checkBlock(){
	set_servo_position(CAMSERVO, camDown);
	msleep(100);
	camera_update();
	block_width = get_object_bbox(CAMERA_BLUE, 0).width;
	block_height = get_object_bbox(CAMERA_BLUE, 0).height;
	block_area = block_width * block_height;
	
	if(block_area > 50){
		return(TRUE);
	}
	else{
		return(FALSE);
	}
}


void collectBlock(){
	set_servo_position(CAMSERVO, camDown);
	camera_update();
	block_position_x = get_object_center(CAMERA_BLUE, 0).x;
	block_position_y = get_object_center(CAMERA_BLUE, 0).y;
	
	while(block_position_x < 60 || block_position_x > 100){
			printf("collecting \n");
			camera_update();
			block_position_x = get_object_center(CAMERA_BLUE, 0).x;
			
			if(block_position_x < 60){
				motor(RMOTOR, defaultSpeed);
				motor(LMOTOR, -defaultSpeed);
				msleep(50);
			}
			else if(block_position_x > defaultSpeed){
				motor(RMOTOR, -defaultSpeed);
				motor(LMOTOR, defaultSpeed);
				msleep(50);
			}
		}
	printf("found block \n");
	handsDown();
}
