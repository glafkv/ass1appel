#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

int isDir(const char* path){
	struct stat buf;
	stat(path, &buf);
	if(stat(path, &buf) != 0)
		return 0;
	return S_ISDIR(buf.st_mode);
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
/*void permissionBits(const char* direct){
	DIR *dirp;
	struct dirent *info_archivo;
	struct stat fileStat;
	char fullPath[256];
	
	while ((info_archivo = readdir(dirp)) != 0){
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
int main(int argc, char *argv[])
{
	
	const char* direct = "/classes/OS/appel/appel.1";
	struct stat fileStat;
	DIR *dirp;
	struct dirent *direntp;
	//directory(direct);
	//exit(0);
	//listdir(".",0);	

	
	//Declaration of variables
	int choice = 0;

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
				//directory(direct);
				//permissionBits(direct);
				if(stat(direct,&fileStat) < 0)
					return 1;		
				directory(direct);
				
				//while((direntp = readdir(dirp)) != 0){
				//we can print one file's permission bits
				//need to figure out how to do the whole file
				printf("file permissions:\n");
				printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
				 printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
 				 printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    				printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    				printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
   				 printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    				printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    				printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    				printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    				printf("\n\n");
			//}
		}
	}
	
	//need to figure out how to accept a directory name without having to put the full path.
	//lets come back to this later
	/*const char* directory = "appel.1";

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


