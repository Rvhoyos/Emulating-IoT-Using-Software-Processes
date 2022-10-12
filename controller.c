#include "device.h"
#include <ctype.h>
/*
controller.c
reads from sensor and writes to actuator and cloud.
Monitors the sensor temperatures and thresholds, sends data to actuator if condition is met. 
Updates the cloud with a status.
*/
int main()
{
	
	int controller_fifo_fd, actuator_fifo_fd, cloud_fifo_fd;
	struct data_to_pass_st sensor_data;
	struct data_to_pass_st_a actuator_action;
	struct data_to_pass_st_c cloud_status;
	actuator_action.act = false;
	char controller_fifo[256];
	
	//Making FIFOs for actuator, controller and cloud.
	mkfifo(ACTUATOR_FIFO_NAME, 0777);
	mkfifo(CONTROLLER_FIFO_NAME, 0777);
	mkfifo(CLOUD_FIFO_NAME, 0777);	
	
	//openning controller fifo for reading and actuator/cloud for wrtting.
	controller_fifo_fd = open(CONTROLLER_FIFO_NAME, O_RDONLY);
	actuator_fifo_fd = open(ACTUATOR_FIFO_NAME, O_WRONLY);
	cloud_fifo_fd = open(CLOUD_FIFO_NAME, O_WRONLY);
	
	if(controller_fifo_fd == -1)
	{
		//checkiing if fifo was created succesfully
		fprintf(stderr, "Controller fifo failure \n");
		exit(EXIT_FAILURE);
	}
	while(1){
		sleep(1);
		
		if(controller_fifo_fd!=-1){
			if(read(controller_fifo_fd,&sensor_data, sizeof(sensor_data))>0){ //checking contents of controller fifo and printing the
				printf("recieved temperature from %d \n  temp = %d  ", sensor_data.sensor_pid, sensor_data.temperature);
				printf("recieved threshold from %d \n  thresh = %d  ", sensor_data.sensor_pid, sensor_data.threshold);
				cloud_status.sPID = sensor_data.sensor_pid;//saving sensor PID for cloud use.
			}
				
		}	
		
	sleep(1);
	if(sensor_data.temperature > sensor_data.threshold)
	{	//change to signal implemenation later
	
		//setting the actuator to move before wrrring to FIFO
		actuator_action.act = true;
		printf("threshold reached, ACTIVATING ACTUATOR \n");
		cloud_status.isMoving = true;
		write(actuator_fifo_fd, &actuator_action, sizeof(actuator_action)); //writting to actuator FIFO 
		write(cloud_fifo_fd, &cloud_status, sizeof(cloud_status)); //writting to cloud FIFO
		cloud_status.isMoving = false; //resetting boolean flags used for implementation of the logic.
		
	}
	
	}
 	close(controller_fifo_fd);
 	unlink(CONTROLLER_FIFO_NAME);
 	exit(EXIT_SUCCESS);

}
