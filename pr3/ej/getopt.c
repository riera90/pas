#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]) {

	int opt;
	opterr=0;

	while ( (opt = getopt (argc, argv, "ab:" ) ) != -1 )
	{
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
