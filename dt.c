#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>


/*void listdir(const char *name, int indent){
	DIR *dir;
	struct dirent *entry;

	if(!(dir = opendir(name)))
		return;
	
	while((entry = readdir(dir)) != NULL){
		if(entry->d_type == DT_DIR){
			char path[1024];
			if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
			snprintf(path,sizeof(path), "%s/%s", name, entry->d_name);
			printf("%*s[%s]\n", indent, "", entry->d_name);
			listdir(path, indent + 2);
			} else {
				printf("%*s- %s\n", indent, "", entry->d_name);
			}
		}
		closedir(dir);
}*/
int main(int argc, char *argv[])
{
	//listdir(".",0);	

	printf("Hello world");
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
	
			case 'I':
				
		}
	}










return 0;
}


char* permissions(char *file){
	struct stat st;
	char *modeval = malloc(sizeof(char) * 9 + 1);
	if(stat(file, &st) == 0){
		mode_t perm = st.st_mode;
		modeval[0] = (perm & S_IRUSR) ? 'r' : '-';
		modeval[1] = (perm & S_IWUSR) ? 'w' : '-';
		modeval[2] = (perm & S_IXUSR) ? 'x' : '-';
		modeval[3] = (perm & S_IRGRP) ? 'r' : '-';
		modeval[4] = (perm & S_IWGRP) ? 'w' : '-';
		modeval[5] = (perm & S_IXGRP) ? 'x' : '-';
		modeval[6] = (perm & S_IROTH) ? 'r' : '-';
		modeval[7] = (perm & S_IWOTH) ? 'w' : '-';
		modeval[8] = (perm & S_IXOTH) ? 'x' : '-';
		modeval[9] = '\0';
		return modeval;
	}
	else{
		return strerror(errno);
	}
}
