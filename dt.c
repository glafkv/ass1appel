#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>

//This function checks to make sure it's a directory
int isDir(const char* path){
	struct stat buf;
	stat(path, &buf);
	int dir = S_ISDIR(buf.st_mode);
	return (dir);
}
//This function opens the directory and prints the contents
void directory(const char* direct){
	DIR *dirp;
	struct dirent *direntp;
	
	if ((dirp = opendir(direct)) == NULL){
		fprintf(stderr, "Could not open %s directory: %s\n", direct, strerror(errno));
        	exit(1);
	}
	printf("%s\n", direct);
	while ( (direntp = readdir( dirp )) != NULL ){
		printf("%s\n", direntp->d_name );
	}
	//closedir(dirp);
}


	

int main(const int argc, char ** argv)
{
	int choice = 0;	
	struct dirent *dp;
	struct stat statbuf;
	struct passwd *pwd;
	struct group *grp;
	struct tm *tm;
	char datestring[256];
	char *dir = ".";
	DIR *dfd;
	
	int uidFlag = 0;	
	int pFlag = 0;
	int gidFlag = 0;

	//directory(dir);
	//Checks if argument is less than 3, if it is, then use root directory. If not, use directory user put.
	//if(optind >= argc)
	//	dir = ".";
	//else
	//	dir = argv[optind];
	
	//Error checking the directory
	if((dfd = opendir(dir)) == NULL){
		fprintf(stderr, "Could not open %s directory: %s\n", dir, strerror(errno));
		exit(1);
	}
	//getopt statement
	while((choice = getopt(argc, argv, "hI:Ltpiugsdl")) != -1){

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
	
			case 'p':
				pFlag = 1;
				break;
			case 'u':
				uidFlag = 1;
				break;
			
			case 'g':
				gidFlag = 1;
				break;
			
					

		}
	}
	//if(stat(dir, &statbuf) < 0)
		//return 1;
	if(pFlag == 1){
		if(stat(dir, &statbuf) < 0)
			return 1;
		while((dp = readdir(dfd)) != NULL){
			printf((S_ISDIR(statbuf.st_mode)) ? "d" : "-");
			printf((statbuf.st_mode & S_IRUSR) ? "r" : "-");
			printf((statbuf.st_mode & S_IWUSR) ? "w" : "-");
			printf((statbuf.st_mode & S_IXUSR) ? "x" : "-");
			printf((statbuf.st_mode & S_IRGRP) ? "r" : "-");
			printf((statbuf.st_mode & S_IWGRP) ? "w" : "-");
			printf((statbuf.st_mode & S_IXGRP) ? "x" : "-");
			printf((statbuf.st_mode & S_IROTH) ? "r" : "-");
			printf((statbuf.st_mode & S_IWOTH) ? "w" : "-");
			printf((statbuf.st_mode & S_IXOTH) ? "x" : "-");
		
			printf("\n");	
		}
		//printf("\n\n");
	}
	if(uidFlag == 1){
		
		while((dp = readdir(dfd)) != NULL){
			if(stat(dp->d_name, &statbuf) == -1)
				continue;
			if((pwd = getpwuid(statbuf.st_uid)) == NULL){
				perror("getpwuid");
			}else{
				printf("%10s%15d\n",dp->d_name, statbuf.st_uid);
			}
		}
	}
	if(gidFlag == 1){
		while((dp = readdir(dfd)) != NULL){
			if(stat(dp->d_name, &statbuf) == -1)
				continue;
			if((grp = getgrgid(statbuf.st_gid)) == NULL){
				perror("getgrgid");
			}else{
				printf("%10s%15d\n", dp->d_name, statbuf.st_gid);
			}
		}
	}

	/*if(optind >= argc){
		dir = ".";
	
	}else{
		dir = argv[optind];
		
	}
	if((dfd = opendir(dir)) == NULL){
		fprintf(stderr, "could not open %s directory: %s\n", dir, strerror(errno));
		exit(1);
	}*/
	






return 0;
}


