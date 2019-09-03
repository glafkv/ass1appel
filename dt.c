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
	closedir(dirp);
}

/*void permissionBits(const char* direct){
	DIR *dirp;
	struct dirent *info_archivo;
	struct stat fileStat;
	char fullPath[256];
	
	while ((info_archivo = readdir(dirp)) != NULL){
		if(!stat(fullPath, &fileStat)){
			printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
			printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
			printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
			printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
			printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
			printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
			printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
			printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
			printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");			
		}
		else {
			perror("Error in stat");
		}
		printf("\n");
	}
	
	closedir(dirp);
}*/
/*void getUID(const char* direct){
	struct passwd pwd;
	struct passwd *result;
	char *buf;
	size_t bufsize;
	int s;
	
	bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
	if(bufsize = -1)
		bufsize = 16384;

	buf = malloc(bufsize);
	if(buf == NULL){
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	s = getpwnam_r(argv[2], &pwd, buf, bufsize, &result);
	if(result == NULL){
		if(s==0)
			printf("not found\n");
		else {
			errno = s;
			perror("getpwnam_r");
		}
		exit(EXIT_FAILURE);
	}
	printf("UID %ld\n", (long) pwd.pw_uid);
	exit(EXIT_SUCCESS);
}*/
int main(int argc, char *argv[])
{
	int choice = 0;	
	struct dirent *dp;
	struct stat statbuf;
	struct passwd *pwd;
	struct group *grp;
	struct tm *tm;
	char datestring[256];
	char *dir;
	DIR *dfd;
	
		

	

	
	//Checks if argument is less than 3, if it is, then use root directory. If not, use directory user put.
	if(argc < 3)
		dir = ".";
	else
		dir = argv[2];
	
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
	
			//case 'p':
				//while((dp = readdir(dfd)) != NULL){
					//if(stat(dp->d_name, &statbuf) == -1)
						//continue;
					//printf("%s\n", dp->d_name);
					//printf("%10.10s", sperm (statbuf.st_mode));
				//	printf("%4d", statbuf.st_nlink);
			//	}
				//directory(direct);
				//permissionBits(direct);
				/*if(stat(direct,&fileStat) < 0)
					return 1;		
				directory(direct);
				
				//while((direntp = readdir(dirp)) != 0){
				//we can print one file's permission bits
				//need to figure out how to do the whole file
				printf("file permissions:\n");
				printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
				 printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
 appel.2.1 is  not a directory
				 printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    				printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    				printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
   				 printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    				printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    				printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    				printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    				printf("\n\n");
			//}*/
			case 'u':
				//confirm it is indeed a directory
				if(isDir(dir) == 1){
					//loop through everything that's in there and print the UID
					while((dp = readdir(dfd)) != NULL){
						if((pwd = getpwuid(statbuf.st_uid)) == NULL){
							perror("getpwuid");
						}else{
							//we need to figure out how to nicely print this next to each other
							printf("%s\t%s\n",dp->d_name, pwd->pw_name);
						}
					}	
				}else{
					printf("This is not a directory\n");
				}
			break;
			
			case 'g':
				//confirm it's a directory
				if(isDir(dir) == 1){
					//loop through everything and print the GID
					while((dp = readdir(dfd)) != NULL){
						if((grp = getgrgid(statbuf.st_gid)) == NULL){
							perror("getgrgid");
						}else{
							printf("%s\t%s\n", dp->d_name, grp->gr_name);
						}
					}
				}else{
					printf("This is not a directory\n");
				}
			break;
					

		}
	}
	

	






return 0;
}


