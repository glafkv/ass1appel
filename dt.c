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
/*void listDir(const char *direct, int indent){
	DIR *dir;
	struct dirent *entry;
	
	if(!(dir = opendir(direct)))
		return;
	
	while((entry = readdir(dir)) != NULL){
		if(entry->d_type == DT_DIR){
			char path[1024];
			if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
			snprintf(path, sizeof(path), "%s/%s", direct, entry->d_name);
			printf("%*s[%s]\n", indent, "", entry->d_name);
			listDir(path, indent + 2);
		}else{
			printf("%*s- %s\n", indent, "", entry->d_name);
		}
	}
	closedir(dir);
}*/
/*void listFiles(char* direct){
	char path[1000];
	struct dirent *dp;
	DIR *dir = opendir(direct);
	
	if(!dir)
		return;
	
	while((dp = readdir(dir)) != NULL){
		if(strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, ".." != 0)){
			printf("%s\n", dp->d_name);
			strcpy(path, direct);
			strcat(path, "/");
			strcat(path, dp->d_name);

			listFiles(path);
		}
	}
	closedir(dir);
}*/
/*void list(char* path){
	DIR *dir;
	struct dirent *ent;
	
	if((dir=opendir(path)) != NULL){
		while((ent = readdir(dir)) != NULL){
			if(ent->d_type == DT_DIR && strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0){
				printf("%s\n", ent->d_name);
				list(ent->d_name);
			}
		}
		closedir(dir);
	}
}*/
void listdir(char *dir){
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	char *subdir;
	
	if((dp = opendir(dir)) == NULL){
		fprintf(stderr, "cannot open directory: %s\n", dir);
		return;
	}
	while((entry = readdir(dp)) != NULL){
		if(lstat(entry->d_name, &statbuf) == 0){
			if(statbuf.st_mode & S_IFDIR){
				if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
					continue;
				subdir = malloc(strlen(dir) + strlen(entry->d_name) + 2);
				strcpy(subdir, dir);
				strcat(subdir, "/");
				strcat(subdir, entry->d_name);
				
				listdir(subdir);
				free(subdir);
			} else{
				printf("%s/%s\n", dir, entry->d_name);
			}
		}
	}
	closedir(dp);
}
int main(const int argc, char ** argv)
{
	int choice = 0;	
	struct dirent *dp;
	struct stat statbuf;
	struct passwd *pwd;
	struct group *grp;
	char *dir = "../appel.1";
	DIR *dfd;
	
	int uidFlag = 0;	
	int pFlag = 0;
	int gidFlag = 0;
	int lFlag = 0;
	int iFlag = 0;
	int sFlag = 0;
	int dFlag = 0;
	int allFlag = 0;
	
	
	listdir(dir);
	//list("./");
	/*if(argc < 3)
		dir = ".";
	else
		dir = argv[2];
*/	//list(".");
	//listFiles(dir);
	//listDir(dir, 2);
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
	
			case 'L':
				lFlag = 1;
				break;
			case 'p':
				pFlag = 1;
				break;
			case 'u':
				uidFlag = 1;
				break;
			
			case 'g':
				gidFlag = 1;
				break;
			
			case 'i':
				iFlag = 1;
				break;			
			case 's':
				sFlag = 1;
				break;
			case 'd':
				dFlag = 1;
				break;
			case 'l':
				allFlag = 1;
				break;
		}
	}
	//int fileMode;
	//fileMode = statbuf.st_mode;
	if(pFlag == 1){
		//if(stat(dir, &statbuf) < 0)
		//	return 1;
		while((dp = readdir(dfd)) != NULL){
			if(stat(dp->d_name, &statbuf) == -1)
				continue;
			printf("%10s", dp->d_name);
			printf("\t");
			int fileMode;
			fileMode = statbuf.st_mode;
			if(fileMode & S_IRUSR)
				printf("r");
			else
				printf("-");
			if(fileMode & S_IWUSR)
				printf("w");
			else
				printf("-"); 
			if(fileMode & S_IXUSR)
				printf("x");
			else
				printf("-");
			if(fileMode & S_IRGRP)
				printf("r");
			else
				printf("-");
			if(fileMode & S_IWGRP)
				printf("w");
			else
				printf("-");
			if(fileMode & S_IXGRP)
				printf("x");
			else
				printf("-");
			if(fileMode & S_IROTH)
				printf("r");
			else
				printf("-");
			if(fileMode & S_IWOTH)
				printf("w");
			else
				printf("-");
			if(fileMode & S_IXOTH)
				printf("x   ");
			else
				printf("-   ");
			printf("\n");	
		}
	}
	if(uidFlag == 1){
		
		while((dp = readdir(dfd)) != NULL){
			if(stat(dp->d_name, &statbuf) == -1)
				continue;
			if((pwd = getpwuid(statbuf.st_uid)) == NULL){
				perror("getpwuid");
			}else{
				printf("%10s\t%d\n",dp->d_name, statbuf.st_uid);
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
				printf("%10s\t%d\n", dp->d_name, statbuf.st_gid);
			}
		}
	}
	if(iFlag == 1){
		while((dp = readdir(dfd)) != NULL){
			if(stat(dp->d_name, &statbuf) == -1)
				continue;
			printf("%10s\t%u\n", dp->d_name, statbuf.st_ino);
		}
	}
	if(sFlag == 1){
		while((dp = readdir(dfd)) != NULL){
			if(stat(dp->d_name, &statbuf) == -1)
				continue;
			if(statbuf.st_size > 1000){
				int kilo = statbuf.st_size / 1024;
				printf("%10s\t%dK\n", dp->d_name, kilo);
			}else if(statbuf.st_size > 1000000){
				int mega = statbuf.st_size / (1024 * 1024);
				printf("%10s\t%dM\n", dp->d_name, mega);
			}else if(statbuf.st_size > 1000000000){
				int gig = statbuf.st_size / (1024 * 1024 * 1024);
				printf("%10s\t%dG\n", dp->d_name, gig);
			}else{
				printf("%10s\t%ld bytes\n", dp->d_name, statbuf.st_size);
			}
		}
	}
	if(dFlag == 1){
		while((dp = readdir(dfd)) != NULL){
			if(stat(dp->d_name, &statbuf) == -1)
				continue;
			printf("%10s\t%s\n", dp->d_name, ctime(&statbuf.st_mtim.tv_sec));
		}
	}
	if(allFlag == 1){
		while((dp = readdir(dfd)) != NULL){
			if(stat(dp->d_name, &statbuf) == -1)
				continue;
			printf("%10s", dp->d_name);
			printf("\t");
			int fileMode;
			fileMode = statbuf.st_mode;
			if(fileMode & S_IRUSR)
				printf("r");
			else
				printf("-");
			if(fileMode & S_IWUSR)
				printf("w");
			else
				printf("-");
			if(fileMode & S_IXUSR)
				printf("x");
			else
				printf("-");
			if(fileMode & S_IRGRP)
				printf("r");
			else
				printf("-");
			if(fileMode & S_IWGRP)
				printf("w");
			else
				printf("-");
			if(fileMode & S_IXGRP)
				printf("x");
			else
				printf("-");
			if(fileMode & S_IROTH)
				printf("r");
			else
				printf("-");
			if(fileMode & S_IWOTH)
				printf("w");
			else
				printf("-");
			if(fileMode & S_IXOTH)
				printf("x   ");
			else
				printf("-   ");
			
			printf("%10d", statbuf.st_ino);
			if((pwd = getpwuid(statbuf.st_uid)) == NULL){
				perror("getpwuid");
			}else{
				printf("%7d", statbuf.st_uid);
			}
			if((grp = getgrgid(statbuf.st_gid)) == NULL){
				perror("getgrgid");
			}else{
				printf("%5d", statbuf.st_gid);
			}
			//printf("\t");
			if(statbuf.st_size > 1000){
				int kilo = statbuf.st_size / 1024;
				printf("%5dK", kilo);
			}else if(statbuf.st_size > 1000000){
				int mega = statbuf.st_size / (1024 * 1024);
				printf("%5dM", mega);
			}else if(statbuf.st_size > 1000000000){
				int gig = statbuf.st_size / (1024 * 1024 * 1024);
				printf("%5dG", gig);
			}else{
				printf("%5ldbytes", statbuf.st_size);
			}
			printf("\t");
			printf("%10s", ctime(&statbuf.st_mtim.tv_sec));	
			printf("\n");
		}
	}	
	/*lstat(dir, &statbuf);
	int link = S_ISLNK(statbuf.st_mode);
	if(lFlag == 1){
		while((dp = readdir(dfd)) != NULL){
			if(stat(dp->d_name, &statbuf) == -1)
				continue;
			if(lstat(dir, &statbuf) < 0){
				char err[80];
				sprintf(err, "Error: did not find %s", dir);
				perror(err);
			}else{
				printf("%10s%15s", dp->d_name, link);
			}
		}
	}*/
						
	/*if(optind >= argc){
		
		dir = ".";
	
	}else{
		dir = argv[2];
		
	}*/
	
	






return 0;
}


