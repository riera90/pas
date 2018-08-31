#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
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
	mqd_t mq_client = mq_open(QUEUE_NAME, O_RDWR, 0644, &attr);

	if( mq_client == (mqd_t)-1 )
	{
		fprintf(stderr, "\n[SERVER]: error, queue could not be created\n");
		abort();
	}
	printf(" DONE\n");






	char buffer[MAX_MESSAGE_SIZE + 1];

	while ( buffer != EXIT_COMMAND)
	{
		printf("message> ");
		fflush(stdout);                  // Limpiar buffer de salida
		memset(buffer, 0, MAX_MESSAGE_SIZE);     // Poner a 0 el buffer
		fgets(buffer, MAX_MESSAGE_SIZE, stdin);  // Leer por teclado
		buffer[strlen(buffer)-1] = '\0'; // Descartar el salto de línea


		printf("[SERVER]: sending message...");
		fflush(stdout);

		if (  mq_send(mq_client, buffer, MAX_MESSAGE_SIZE, 0) != 0 )
		{
			fprintf(stderr,"\n[SERVER]: Error sending message trought queue\n");
			abort();
		}
		printf(" DONE\n");
	}





	//closes the queue
	printf("[SERVER]: Closing queue...");
	fflush(stdout);
	if(mq_close(mq_client) == -1)
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
