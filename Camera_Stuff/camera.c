const int CAMERA_BLUE = 0;

int block_position_x;
int block_position_y;
int block_width;
int block_height;
int block_error_y;
int block_error_x;
int targets;

int MRIGHT = 3;
int MLEFT = 0;
int BUMPER = 15;

int main(){
	camera_open();
	sleep(3);
	
	while(1){
		camera_update();
		targets = get_object_count(CAMERA_BLUE);
		block_position_x = get_object_center(CAMERA_BLUE, 0).x;
		block_position_y = get_object_center(CAMERA_BLUE, 0).y;
		block_width = get_object_bbox(CAMERA_BLUE, 0).width;
		block_height= get_object_bbox(CAMERA_BLUE, 0).height;
		
		printf("Block Area: %d \n", block_width * block_height);
		printf("Block X: %d \n", block_position_x);
		printf("Block Y: %d \n", block_position_y);
		
		while(block_position_x < 60 || block_position_x > 100){
			camera_update();
			block_position_x = get_object_center(CAMERA_BLUE, 0).x;
			
			if(block_position_x < 60){
				motor(MRIGHT, 50);
				motor(MLEFT, -50);
				msleep(100);
			}
			else if(block_position_x > 100){
				motor(MRIGHT, -50);
				motor(MLEFT, 50);
				msleep(100);
			}
			motor(MRIGHT, 0);
			motor(MLEFT, 0);
		}
		
		motor(MRIGHT, 50);
		motor(MLEFT, 50);
		
		if(digital(BUMPER) == 1){
			motor(MRIGHT, 0);
			motor(MLEFT, 0);
		}
		
		sleep(5);
	}
}
