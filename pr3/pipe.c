/*
this is a very bad written code, becouse is a 'training' code, i am learning how to do pipes and queues, so don't even think of using this, i am writing spaghetti code  at its finest, not checking for any errors :)
*/


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>



int main(int argc, char const *argv[]) {

	const int MAX_SIZE=100;

	//opens the pipe!
	int fildes[2];
	int status = pipe(fildes);
	//chechs fot status
	if (status == -1)
	{
		//error!
		fprintf(stderr, "FATAL ERROR, PIPE COULD NOT BE CREATED\n");
		abort();
	}

	switch (fork()) {
		case -1:
		{
			fprintf(stderr, "FATAL ERROR, PIPE COULD NOT BE CREATED\n");
			abort();
		}

		case 0: // children
		{
			//closes the writing part
			char buffer[MAX_SIZE];
			close(fildes[1]);
			//reads the message and closes the pipe
			int nbytes=read(fildes[0],buffer,sizeof(buffer));
			if (nbytes == -1) {
				fprintf(stderr, "FATAL ERROR, PIPE COULD NOT BE READ\n");
				exit(EXIT_FAILURE);
			}
			//waits for no reasson
			sleep(1);
			close(fildes[0]);
			printf("[children] message: <%s>\n", buffer);
			//waits for no reasson
			sleep(1);
			exit(EXIT_SUCCESS);

		}

		default:// parent
		{
			//close the reading part
			close(fildes[0]);
			//waits for no reasson
			sleep(1);
			//writes the message and closes the pipe
			printf("[parent] sending message.\n");
			write(fildes[1], "hello, world\0", 13);

			//waits for the children
			printf("[parent] waiting for children.\n");
			int exit_status;
			wait(&exit_status); // very bad code :)
			close(fildes[1]);
		}
	}

	return 0;
}
