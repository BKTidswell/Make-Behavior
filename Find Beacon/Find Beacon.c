int LMOTOR = 0;
int RMOTOR = 3;
int LSERVO = 2;
int RSERVO = 0;
int NBEACON= 10;

void foward();
void turnLeft();
void turnRight();
void turnAround();
void manipulate();
void findBeacon();

/////////////////////////

int main(){
	while(1){
		findBeacon();
	}
}

/////////////////////////

void forward(){
	motor(LMOTOR, 50);
	motor(RMOTOR, 50);
	sleep(30);
}

void turnLeft(){
	motor(LMOTOR, -50);
	motor(RMOTOR, 50);
	sleep(50);
}

void turnRight(){
	motor(LMOTOR, 50);
	motor(RMOTOR, -50);
	sleep(50);
}

void turnAround(){
	motor(LMOTOR, -50);
	motor(RMOTOR, 50);
	sleep(100);
}

void manipulate(){
	set_servo_position(LSERVO, 1200);
	set_set_position(RSERVO, 1100);
}

void findBeacon(){
	if(NBEACON < 100){
		forward();
	}
	else if(EBEACON < 100){
		turnRight();
	}
	else if(WBEACON < 100){
		turnLeft();
	}
	else if(SBEACON < 100{
		turnAround();
	}
	else{
		forward();
	}
}		
