#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <getopt.h>
#include <regex.h>

struct passwd* passwd;
struct group* group;

int readNumber()
{
  char *p, s[100];
  int n;

  while (fgets(s, sizeof(s), stdin)) {
      n = strtol(s, &p, 10);
      if (p == s || *p != '\n') {
          printf("Please enter an integer: ");
      } else break;
  }
  return n;
}

void printPasswdInfo(struct passwd* passwd)
{
	if ( passwd == NULL ) {
		fprintf(stderr, "ERROR, ABORTING.\n");
		abort();
	}
	printf("name: %s\n", passwd->pw_name);
	printf("passwd: %s\n", passwd->pw_passwd);
	printf("UID: %d\n", passwd->pw_uid);
	printf("GID: %d\n", passwd->pw_gid);
	printf("gecos: %s\n", passwd->pw_gecos);
	printf("dir: %s\n", passwd->pw_dir);
	printf("shell: %s\n", passwd->pw_shell);
}

void printGroupInfo(struct group* group)
{
	if ( group == NULL ) {
		fprintf(stderr, "ERROR, ABORTING.\n");
		abort();
	}
	printf("group name: %s\n", group->gr_name);
	printf("group passwd: %s\n", group->gr_passwd);
	printf("GID: %d\n", group->gr_gid);
	printf("members: (not working)\n");
	for (size_t i = 0; i < sizeof(group->gr_mem)/sizeof(char*); i++)
	{
		printf("\t->%s\n",group->gr_mem[i] );
	}
}

void help()
{
	printf("ussage:\n");
	printf("  -h, --help        Imprimir esta ayuda\n");
	printf("  -u, --username    Nombre de Usuario\n");
	printf("  -i, --useruid     Identificador de Usuario\n");
	printf("  -g, --groupname   Nombre de Grupo\n");
	printf("  -d, --groupuid    Identificador de Grupo\n");
	printf("  -s, --allgroups   Muestra info de todos los grupos del sistema\n");
	printf("  -a, --allinfo     Nombre de Usuario\n");
	printf("  -b, --bactive     Muestra info grupo usuario Actual\n");
}


void username(char* username)
{
	passwd = getpwnam(username);
	if (passwd==NULL)
	{
		fprintf(stderr, "ERROR THE USERNAME '%s' DOES NOT EXIST, ABORTING\n", username);
		abort();
	}
	printPasswdInfo(passwd);
}


void userid(char* userid)
{
	passwd=getpwuid(atoi(userid));
	if (passwd==NULL)
	{
		fprintf(stderr, "ERROR THE USERID '%s' DOES NOT EXIST, ABORTING\n", userid);
		abort();
	}
	printPasswdInfo(passwd);
}


void groupname(char* groupname)
{
	group = getgrnam(groupname);
	if ( group == NULL )
	{
		fprintf(stderr, "ERROR THE GID '%s' DOES NOT EXIST, ABORTING\n", groupname);
		abort();
	}
	printGroupInfo(group);
}


void groupid(char* groupid)
{
	group = getgrgid(atoi(groupid));
	if ( group == NULL )
	{
		fprintf(stderr, "ERROR THE GID '%s' DOES NOT EXIST, ABORTING\n", groupid);
		abort();
	}
	printGroupInfo(group);
}

void allgroups()
{
	int start, end;
	printf("where do you want to start?: ");
	start = readNumber();
	printf("where do you want to end?  : ");
	end = readNumber();
	int total=end-start;

	for (size_t i = start; i < end; i++) {
		if (i%1000000==0) {
			printf("%i%% completed\n",(int)(((float)(i-start)/total)*100) );
		}
		group = getgrgid(i);
		if ( group != NULL )
		{
			printGroupInfo(group);
			printf("\n\n");
		}
	}

}


void bactive()
{
	int gid=getpwnam(getenv("USER"))->pw_gid;
	group = getgrgid(gid);
	printGroupInfo(group);
}


void allinfo(char* username)
{
	passwd = getpwnam(username);
	printPasswdInfo(passwd);
	group = getgrgid(passwd->pw_gid);
	printGroupInfo(group);
}


int main(int argc, char *argv[])
{

	int opt;

	char* options="u:i:g:d:sa:bh";
	char* options_with_argument="uigda"; //for internal use only

	int option_long_index=0;

	int u_flag=0;
	int i_flag=0;
	int g_flag=0;
	int d_flag=0;
	int s_flag=0;
	int a_flag=0;
	int b_flag=0;
	int h_flag=0;

	char* u_value=NULL;
	char* i_value=NULL;
	char* g_value=NULL;
	char* d_value=NULL;
	char* a_value=NULL;

	static struct option option_long[]={
		{"username",	required_argument,	0, 'u'},
		{"userid",		required_argument,	0, 'i'},
		{"groupname",	required_argument,	0, 'g'},
		{"groupid",		required_argument,	0, 'd'},
		{"allgroups",	no_argument,				0, 's'},
		{"allinfo",		required_argument,	0, 'a'},
		{"bactive",		no_argument,				0, 'b'},
		{"help",			no_argument,				0, 'h'},
		{0, 0, 0, 0}, //flag of end of struct
	};

	while ( (opt = getopt_long(argc, argv, options, option_long, &option_long_index) ) != -1 )
	{
		switch (opt) {
			case 'u':
			{
				if ( i_flag == 1 )
				{
					fprintf(stderr, "you can't activate the 'username' and 'userid' flags at the same time!\n");
					help();
					abort();
				}
				else
				{
					u_flag=1;
					u_value=optarg;
				}
				break;
			}

			case 'i':
			{
				if (u_flag == 1 )
				{
					fprintf(stderr, "you can't activate the 'username' and 'userid' flags at the same time!\n");
					help();
					abort();
				}
				else
				{
					i_flag=1;
					i_value=optarg;
				}
				break;
			}

			case 'g':
			{
				g_flag=1;
				g_value=optarg;
				break;
			}

			case 'd':
			{
				d_flag=1;
				d_value=optarg;
				break;
			}

			case 's':
			{
				s_flag=1;
				break;
			}

			case 'a':
			{
				a_flag=1;
				a_value=optarg;
				break;
			}

			case 'b':
			{
				b_flag=1;
				break;
			}

			case 'h':
			{
				h_flag=1;
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

	//resolve

	if ( u_flag == i_flag == g_flag == d_flag == s_flag == a_flag == b_flag == 0 )
	{
		help();
		return 0;
	}


	if ( u_flag == 1 )
	{
		username(u_value);
	}

	if ( i_flag == 1 )
	{
		userid(i_value);
	}

	if ( g_flag == 1 )
	{
		groupname(g_value);
	}

	if ( d_flag == 1 )
	{
		groupid(d_value);
	}

	if ( s_flag == 1 )
	{
		allgroups();
	}

	if ( a_flag == 1 )
	{
		allinfo(a_value);
	}

	if ( b_flag == 1 )
	{
		bactive();
	}


	return 0;
}
