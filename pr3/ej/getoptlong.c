#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>


int main(int argc, char *argv[]) {

	int opt;
	opterr=0;

	static struct option options[]={
		{"add", no_argument, 0, 'a'},
		{"block", required_argument, 0, 'b'},
		{0, 0, 0, 0}
	};

	int options_index=0;

	while ( (opt = getopt_long (argc, argv, "ab:", options, &options_index ) ) != -1 )
	{
		if (opt == -1)
		{
			break;
		}

		switch (opt)
		{
			case 'a':{
				printf("a detected\n");
				break;
			}

			case 'b':{
				printf("b detected with flag '%s'\n",optarg);
				break;
			}

			case '?':{
				if (optopt == 'b') {
					printf ("La opción %c requiere un argumento\n", optopt);
					break;
				}
				printf("input not known '%c'\n", optopt);
				break;
			}

			default:{
				printf("error fatal!\n");
				abort();
			}
		}
	}
	return 0;
}
