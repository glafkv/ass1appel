#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


int main(int argc, char *argv[])
{
	//Declaration of variables
	int choice = 0;

	//getopt statement
	while((choice = getopt(argc, argv, "h:I:Ltpiugsdl")) != -1){

		switch(choice){
			case 'h':
				printf("\tI'm here to help!\n");
				printf("***********************\n");
				printf("-h brings up the help menu\n");
				printf("I n : change the indentation to n spaces for each level\n");
				printf("L : follow symbolic links, if any. Default will be to not follow symbolic links\n");
				printf("t : print information on file type\n");
				printf("p : print permission bits\n");
				printf("i : print the number of links to file in inode table\n");
				printf("u : print the UID associated with the file\n");
				printf("g : print the GID associated with the file\n");
				printf("s : print the size of file in bytes\n");
				printf("d : show the time of last modification\n");
				printf("l : print information on the file as if the options 'tpiugs' are all specified\n");

				exit(0);		
	
			
		}
	}










return 0;
}
