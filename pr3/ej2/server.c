#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <time.h>
#include <errno.h>


int main(int argc, char const *argv[]) {

	//creates the queue
	struct mq_attr attr;

	attr.mq_maxmsg = MAX_MESSAGES;      // MAX NUM OF MESSAGES
	attr.mq_msgsize = MAX_MESSAGE_SIZE; // MAX SIZE OF MESSAGE

	printf("[SERVER]: Opening queue...");
	fflush(stdout);
	mqd_t mq_server = mq_open(QUEUE_NAME, O_CREAT, 0644, &attr);

	if( mq_server == (mqd_t)-1 )
	{
		fprintf(stderr, "\n[SERVER]: error, queue could not be created\n");
		abort();
	}
	printf(" DONE\n");






	char buffer[MAX_MESSAGE_SIZE + 1];
	size_t bytes_read;

	while (1)
	{
		printf("[SERVER]: Waiting for message...");
		fflush(stdout);
		bytes_read = mq_receive(mq_server, buffer, MAX_MESSAGE_SIZE, NULL);
		if ( 0 )
		{
			fprintf(stderr, "\n[SERVER]: ERROR, QUEUE NOT WORKING PROPERLY, ABORTING\n");
			abort();
		}
		printf(" received.\n");

		printf("<%s>\n",buffer);

		// sleep(1);
	}

	//closes the queue
	printf("[SERVER]: Closing queue...");
	fflush(stdout);
	if(mq_close(mq_server) == -1)
	{
		fprintf(stderr,"\n[SERVER]: Error closing the queue\n");
		exit(-1);
	}
	printf(" DONE\n");

	//removes the queue
	printf("[SERVER]: removing queue...");
	fflush(stdout);
	if(mq_unlink(QUEUE_NAME) == -1)
	{
		fprintf(stderr,"\n[SERVER]: Error deleting the queue\n");
		exit(-1);
	}
	printf(" DONE\n");

	return 0;
}
