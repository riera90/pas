#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]) {

	printf("username: '%s'\n", getenv("USER") );
	printf("login: '%s'\n", getlogin() );
	return 0;
}
