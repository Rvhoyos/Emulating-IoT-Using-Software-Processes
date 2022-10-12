//Actuator process recieves alert from controller and triggers action for now it is a print statement.

#include "device.h"
#include "ctype.h"

int main()
{
	int actuator_fifo_fd;
	char actuator_fifo[256];
	struct data_to_pass_st_a actuator_action;
	
	printf("current actuator action set to %b [0 false /1 True] by default \n", actuator_action.act);
	printf(" Actuator fifo being opened \n");
	
	
	actuator_fifo_fd = open(ACTUATOR_FIFO_NAME, O_RDONLY); //open fifo in read only 
	
	if(actuator_fifo_fd == -1)
	{
		fprintf(stderr, "Actuator fifo failure \n"); //checking for errors in making fifo
		exit(EXIT_FAILURE);
	}
	if(actuator_fifo_fd != -1)
		{
			printf("fifo exists \n");
			while(1){
			sleep(1);		
				if(read(actuator_fifo_fd,&actuator_action, sizeof(actuator_action))>0 && actuator_action.act == true) //checking contents of the read and if the actuator must move
				{
					printf("The actuator will act now\n");
					actuator_action.act = false;
					
				} else
				{ 
					printf("The actuator will not act");
				}
			}

		}
	exit(EXIT_SUCCESS);
}
