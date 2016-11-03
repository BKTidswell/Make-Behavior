
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


void forward(){
	motor(LEFT_MOTOR, .5*TOP_SPEED);
	motor(RIGHT_MOTOR, .5*TOP_SPEED);
	msleep(25);
}

void turnLeft(){
	motor(LEFT_MOTOR, -.75*TOP_SPEED);
	motor(RIGHT_MOTOR, .75*TOP_SPEED);
	msleep(100);
}

void turnRight() {
	motor(RIGHT_MOTOR, -.75*TOP_SPEED);
	motor(LEFT_MOTOR,.75*TOP_SPEED);
	msleep(100);
}



int main (){
	while(1){
		if(digital(12) == 1){
			turnLeft();
		}
		else{
			forward();
		}
	}	
}
	
