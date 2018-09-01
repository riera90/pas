#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <time.h>
#include <errno.h>
#include <getopt.h>
#include <regex.h>
#include <string.h>



void help()
{
	printf("-s <secret> set the secret password.\n");
	printf("-h prints this help message.\n");
}


int main(int argc, char *argv[]) {

	char* options_with_argument="s";
	int opt;
	char* secret=NULL;


	while ( (opt = getopt(argc, argv, "s:h")) != -1 )
	{
		switch (opt) {
			case 's':
			{
				secret=optarg;
				printf("[SERVER] Secret password set to <%s>\n",secret );
				break;
			}

			case 'h':
			{
				help();
				return 0;
			}

			case '?':
			{
				int option_index=0;
				while ( options_with_argument[option_index] != '\0' )
				{
					if ( optopt==options_with_argument[option_index] )
					{
						//wow thats what I call a shity code with a lot of indentation...
						printf("-%c needs an argument\n",optopt);
						help();
						abort();
					}
					option_index++;
				}
				printf("-%c is not an option\n",optopt);
				help();
				abort();
				}

			default:
			{
				fprintf(stderr, "\n\n\tFATAL ERROR, ABORTING!\n\n");
				abort();
				break;
			}
		}
	}

	if (secret == NULL)
	{
		help();
		return 1;
	}

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



	//compiles the regex
	printf("[SERVER]: 'compiling' regex...");
	fflush(stdout);
	char regex_char[MAX_MESSAGE_SIZE];
	memset(regex_char,0,MAX_MESSAGE_SIZE);
	strcat(regex_char,".*");
	strcat(regex_char,secret);
	strcat(regex_char,".*");
	regex_t regex;
	int rflag = regcomp(&regex, regex_char, 0);

	if (rflag) {
		fprintf(stderr, "\nCould not compile regex\n");
		exit(1);
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

		//executes the regex
		rflag=regexec(&regex, buffer, 0, NULL, 0);

		if (strcmp(buffer,EXIT_COMMAND) == 0)
		{
			break;
		}

		if ( !rflag )
		{
			printf("[SERVER]: the message matches the regex 👌\n");
		}
		else if( rflag == REG_NOMATCH )
		{
			printf("[SERVER]: messgage denied\n");
		}
		else
		{
			fprintf(stderr, "[SERVER]: ERROR FATAL, REGEX FAILED\n");
			abort();
		}

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
