int LMOTOR = 0;
int RMOTOR = 3;
int LSERVO = 2;
int RSERVO = 0;

void forward()
{ motor (LMOTOR, 50);
	motor(RMOTOR, 50);
	sleep(30);
}

void manipulate()
{ set_servo_position (LSERVO, 1200);
	set_set_position (RSERVO, 1100);
}

int main()
	{while(1)
		{if(digital(15)==1)
			{manipulate();}
			else 
			{forward();}
		}
	}
		
