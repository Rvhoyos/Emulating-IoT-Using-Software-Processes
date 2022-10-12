/*
cloud.c
Opens FIFO with controller for reading.
Cloud process communicates with controller process
*/
#include "device.h"
#include <ctype.h>

int main()
{
	int i;
	int temp;
	int cloud_fifo_fd;
	char cloud_fifo[256];
	struct data_to_pass_st_c cloud_status;
		
	cloud_fifo_fd = open(CLOUD_FIFO_NAME, O_RDONLY); //open in read only
	
	if(cloud_fifo_fd == -1) //checking if fifo was created
	{
		fprintf(stderr,"Cloud fifo failure \n");
		perror("");
		exit(EXIT_FAILURE);
	}
	i = 1;
	while(1)
	{
		//Loop to check contents of FIFO and store sensor PID
		printf(" \n command # %d ", i);
		i++;
		sleep(1); // wait 1 second
		if(cloud_fifo_fd != -1)
		{
			if(read(cloud_fifo_fd,&cloud_status, sizeof(cloud_status))>0)
			{
				if(cloud_status.isMoving){
					printf("updates received from %d sensor for actuator action \n", cloud_status.sPID); 
					}
			}		
		}
	}
}
