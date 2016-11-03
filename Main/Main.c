//Define input channels for actuators and sensors
const int LEFT_MOTOR = 0;
const int RIGHT_MOTOR = 3;
const int FRONT_BUMP = 15;
const int BACK_BUMP = 14; 
const int LEFT_PHOTO = 3;
const int RIGHT_PHOTO = 4;
const int LEFT_IR = 2;
const int RIGHT_IR = 1;
const int BACK_LEFT_PHOTO = 6;  
const int BACK_RIGHT_PHOTO = 7; 

//Define boolean constants
const int TRUE = 1;
const int FALSE = 0;

//Speed in move function will be a percentage of top speed
const int TOP_SPEED = 100;

//main loop
int main(){
    
    while(1){
	//future code	
	}
}


/* this function gives true or false telling whether robot has hit the wall*/
int hitWall(){
    
	int left_ir;
	int right_ir;
    int front_bump;
    
	int escapeThreshold_ir = 400;
	
	left_ir = analog_et(LEFT_IR);
	right_ir = analog_et(RIGHT_IR);
	front_bump = digital(FRONT_BUMP);
	
    if(front_bump == TRUE){
		if(left_ir > escapeThreshold || right_ir > escapeThreshold){
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
    
	int blockThreshold_ir = 400;
	
	left_ir = analog_et(LEFT_IR);
	right_ir = analog_et(RIGHT_IR);
	front_bump = digital(FRONT_BUMP);
	
    if(front_bump == TRUE){
		if(left_ir < blockThreshold || right_ir < blockThreshold){
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

//

//Move function
void Move(int command){
    if(command == BACK_LEFT){
        motor(LEFT_MOTOR, -TOP_SPEED * 0.50);
        motor(RIGHT_MOTOR, -TOP_SPEED * 0.70);
        sleep(1);
    }
    else if(command == BACK_RIGHT){
        motor(LEFT_MOTOR, -TOP_SPEED * 0.70);
        motor(RIGHT_MOTOR, -TOP_SPEED * 0.50);
        sleep(1);
    }
    
    else if(command == ARC_RIGHT){
        motor(LEFT_MOTOR, TOP_SPEED * 0.70);
        motor(RIGHT_MOTOR, TOP_SPEED * 0.50);
        sleep(1);
    }
    
    else if(command == ARC_LEFT){
        motor(LEFT_MOTOR, TOP_SPEED * 0.50);
        motor(RIGHT_MOTOR, TOP_SPEED * 0.70);
        sleep(1);
    }
    
    else if(command == ESCAPE_FORWARD){
        motor(LEFT_MOTOR, TOP_SPEED * 1.00);
        motor(RIGHT_MOTOR, TOP_SPEED * 1.00);
        sleep(1);
        motor(LEFT_MOTOR, TOP_SPEED * 0.70);
        motor(RIGHT_MOTOR, TOP_SPEED * 0.50);
        sleep(2);
    }
    else if(command == FORWARD){
        motor(LEFT_MOTOR, TOP_SPEED * 0.70);
        motor(RIGHT_MOTOR, TOP_SPEED * 0.70);
    }
}
