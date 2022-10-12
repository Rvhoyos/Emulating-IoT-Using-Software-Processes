#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <errno.h>
#include <signal.h>
#define CONTROLLER_FIFO_NAME "/tmp/cro_fifo"
#define SENSOR_FIFO_NAME "/tmp/sens_%d_fifo"
#define ACTUATOR_FIFO_NAME "/tmp/act_%d_fifo"
#define CLOUD_FIFO_NAME "/tmp/clo_%d_fifo"


#define BUFFER_SIZE 20

struct data_to_pass_st {
	pid_t  sensor_pid;
	char   some_data[BUFFER_SIZE - 1];
	int temperature;
	int threshold;
};

struct data_to_pass_st_a {
	pid_t  actuator_pid;
	char   more_data[BUFFER_SIZE - 1];
	bool act;
   };
 
struct data_to_pass_st_c {
	pid_t cloud_pid;
	bool isMoving;
	pid_t sPID;
};
