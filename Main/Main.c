//Define input channels for actuators and sensors
const int LMOTOR = 0;
const int RMOTOR = 3;
const int LSERVO = 0;
const int RSERVO = 2;
const int CAMSERVO = 1;
const int FRONT_BUMP = 15;
const int LEFT_IR = 2;
const int RIGHT_IR = 1;
const int RIGHT_LINE = 12;
const int LEFT_LINE = 8;


//Camera Stuff
const int CAMERA_BLUE = 0;
const int CAMERA_GREEN = 1;

int block_count;
int block_position_x;
int block_position_y;
int block_width;
int block_height;
int block_area; 
int block_error_y;
int block_error_x;
int targets;

//Value Declarations
int leftArmUp = 360;
int leftArmDown = 770;
int rightArmUp = 1700;
int rightArmDown = 1150;

int camUp = 100;
int camDown = 800;

int defaultSpeed = 75;
int defaultTime = 300;

int threshIR = 300;

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
int inNest();
int lookBlock();
void roam();
void collectBlock();
void stop();
void seekNest();
void trackBlock();

//Define boolean constants
const int TRUE = 1;
const int FALSE = 0;

//main loop
int main(){
	enable_servos();
	camera_open();
	set_servo_position(LSERVO, leftArmUp);
	set_servo_position(RSERVO, rightArmUp);
	set_servo_position(CAMSERVO, camUp);
	int hasBlock = FALSE;
	int nest = FALSE;
	int seekBlock = FALSE;
	
    while(1){
		if(hasBlock == FALSE){
			//if(lookBlock()==TRUE && hitBlock() == FALSE){
			//	trackBlock();
			//	forward();
			//}
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
			seekNest();
			printf("found nest!");
			roam(1);
			if(inNest()){
				printf("in nest!");
				nest = TRUE;
				hasBlock = FALSE;
				handsUp();
				turnAround();
			}
		}
		else if(nest == TRUE){
		stop();
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

//return true or false if we have hit a block
int hitBlock(){
	int left_ir;
	int right_ir;
    int front_bump;
	
	int blockThreshold_ir = 350;
	
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

/* mod is a number passed  to the roam function to modify the reaction time and speed if the robot. 
*/
void roam(mod){
	int rightIRValue = analog_et(RIGHT_IR);
	int leftIRValue = analog_et(LEFT_IR);
	
	int rmSpeed = defaultSpeed + defaultSpeed * (rightIRValue / threshIR) * 0.75;
	int lmSpeed = defaultSpeed + defaultSpeed * (leftIRValue / threshIR) * 0.75;
	
	motor(LMOTOR, (lmSpeed * mod));
	motor(RMOTOR, (rmSpeed * mod));
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
	printf("hands up");
}

//////CAMERA STUFF/////////

int checkBlock(){
	set_servo_position(CAMSERVO, camDown);
	msleep(100);
	camera_update();
	block_width = get_object_bbox(CAMERA_BLUE, 0).width;
	block_height = get_object_bbox(CAMERA_BLUE, 0).height;
	block_area = block_width * block_height;
	
	if(block_area > 100){
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
				motor(RMOTOR, defaultSpeed/ 1.5);
				motor(LMOTOR, -defaultSpeed/ 1.5);
				msleep(50);
			}
			else if(block_position_x > defaultSpeed){
				motor(RMOTOR, -defaultSpeed/ 1.5);
				motor(LMOTOR, defaultSpeed/ 1.5);
				msleep(50);
			}
			//motor(RMOTOR, -defaultSpeed);
			//motor(LMOTOR, defaultSpeed);
		}
	printf("found block \n");
	handsDown();
	set_servo_position(CAMSERVO, camUp);
}

int lookBlock(){
	camera_update();
	int block_count = get_object_count(CAMERA_BLUE);
	
	if (block_count >= 1){
			block_width = get_object_bbox(CAMERA_BLUE, 0).width;
			block_height = get_object_bbox(CAMERA_BLUE, 0).height;
			block_area = block_width * block_height;
		if(block_area > 150){
			return TRUE;
		}
	}
	else{return FALSE;}
	printf("look block \n");
}

void trackBlock(){
	camera_update();
	block_position_x = get_object_center(CAMERA_BLUE, 0).x;
	block_position_y = get_object_center(CAMERA_BLUE, 0).y;
	
	while(block_position_x < 30 || block_position_x > 130){
		printf("tracking \n");
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
	
}

void seekNest(){
	camera_update();
	set_servo_position(CAMSERVO, camUp);
	int nest_position_x = get_object_center(CAMERA_GREEN, 0).x;
	int nest_position_y = get_object_center(CAMERA_GREEN, 0).y;
	
	while(nest_position_x < 60 || nest_position_x > 100){
		printf("nest finding \n");
		camera_update();
		nest_position_x = get_object_center(CAMERA_GREEN, 0).x;
		
		if(nest_position_x < 60){
			motor(RMOTOR, defaultSpeed/1.2);
			motor(LMOTOR, -defaultSpeed/1.2);
			msleep(50);
		}
		else if(nest_position_x > defaultSpeed){
			motor(RMOTOR, -defaultSpeed/1.2);
			motor(LMOTOR, defaultSpeed/1.2);
			msleep(50);
		}
	}
}

int inNest(){
	camera_update();
	block_width = get_object_bbox(CAMERA_GREEN, 0).width;
	block_height = get_object_bbox(CAMERA_GREEN, 0).height;
	block_area = block_width * block_height;
	
	if(block_area > 5000){
		return(TRUE);
	}
	else{
		return(FALSE);
	}
}

