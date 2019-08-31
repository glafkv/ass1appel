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


int isDir(const char* path){
	struct stat buf;
	stat(path, &buf);
	int dir = S_ISDIR(buf.st_mode);
	return (dir);
}
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
/*void getUID(const char* path){
	struct stat info;
	stat(path, &info);
	struct passwd *pw = getpwuid(info.st_uid);
}*/
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
	DIR *dfd;
	char *dir;
	//dir = "../appel.2";
	//char *dir;
	//struct dirent *direntp;
	//struct passwd pwd;
//	int s;
	
	//if((dfd = opendir(dir)) == NULL){
	//	fprintf(stderr, "can't open %s\n", dir);
	//	return 0;
	//}
	//directory(direct);
	//exit(0);
	//listdir(".",0);	

	
	//Declaration of variables
	//int choice = 0;
	//int real =  getuid();
	//printf("real: %d\n", real);
	/*if(isDir(direct) == 1)
		printf("yes\n");
	else
		printf("no\n");*/
	
	//this is a problem statement
	if(argc < 3){
		dir = ".";
		//directory(direct);
	}else{
		dir = argv[2];
		//directory(direct);
	}
//	printf("%s is %s a directory\n", dir, isDir(dir) ? "" : " not");

	if((dfd = opendir(dir)) == NULL){
		fprintf(stderr, "cant open %s\n", dir);
		return 0;
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
				while((dp = readdir(dfd)) != NULL){
					if(stat(dp->d_name, &statbuf) == -1)
						continue;
					printf("%s\n", dp->d_name);
					//printf("%10.10s", sperm (statbuf.st_mode));
					printf("%4d", statbuf.st_nlink);
				}
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
			//case 'u':
				
				//printf("%d\n", real);
				//getUID(direct);
				//printf("UID: %ld\n", (long) pwd.pw_uid);				
		}
	}
	
	//need to figure out how to accept a directory name without having to put the full path.
	//lets come back to this later
/*	const char* directory = "appel.1";

	if(isDir(directory)==1){
		printf("yes");
	} else{
		printf("no");
	if ((dirp = opendir(direct)) == NULL){
                fprintf(stderr, "Could not open %s directory: %s\n", direct, strerror(errno));
        }               exit(1);

}*/



	//closedir(dirp);






return 0;
}


