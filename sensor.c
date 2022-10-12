
/*
Sensor.c
Opens FIFO with controller for writting.
Sensor process performs a periodic temperature monitoring task and sends to controller.
*/

#include "device.h"
#include "ctype.h"

int main()
{
	//*TO DO 
	// be able to enter threshold limit as a command in the SCRIPT FILE.
	int r;
	int controller_fifo_fd, sensor_fifo_fd;
	struct data_to_pass_st sensor_data;
	char sensor_fifo[256];
	int numOfChars;
	
	sensor_data.threshold = 40;
	
	

	controller_fifo_fd = open(CONTROLLER_FIFO_NAME, O_WRONLY); //opens for writting
	printf("controller opening FIFO to sensor for writting \n");
	if(controller_fifo_fd == -1){
		fprintf(stderr, "sorry, no controller\n");
		exit(EXIT_FAILURE);
		}
		
	sensor_data.sensor_pid = getpid();
	sprintf(sensor_fifo, SENSOR_FIFO_NAME, sensor_data.sensor_pid);  //storing pid in sensor fifo
	
	int i = 0;
	while(1) //random temperature generated and write to FIFO
	{
		i++;
		r = rand()%50;
		sleep(1);
		sensor_data.temperature = r;
		printf("\n sensor temp: %d, \n", r);
		numOfChars = write(controller_fifo_fd, &sensor_data, sizeof(sensor_data)); //code works without assignming the return from read, was using to catch a bug
		if(numOfChars == -1){
			perror(""); //catching error if fifo isnt writting to controller
		}
		printf(" #%d  \n ", i);  //used for styling to see the number of rows	
	}
	
	//check if sensor_fio is unused
	exit(EXIT_SUCCESS);
}
