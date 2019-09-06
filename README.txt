ass1
Author: Gabi Appel
Due date: 9/5/2019

I don't really know how I'm supposed to prove I used version control, but here's my github:
github.com/glafkv

Purpose:
	The purpose of this program is to familiarize myself with using getopt and perror while practicing system calls.

How to Run:
	
	make		//to compile
	
	./dt <opt> [../filename]
	File name must be given in ../filename format or it won't be recognized as a directory
	./dt -h		//to print the help message
	./dt -I n	//to change indentation to n spaces for each level
	./dt -L		//to follow any symbolic links
	./dt -t		//to print information on file type
	./dt -p		//to print permission bits as rwxrwxrwx
	./dt -i		//to print the number of links to file in inode table
	./dt -u		//to print the UID associated with the file
	./dt -g		//to print the GID associated with the file
	./dt -s		//to print the size of the file in bytes
	./dt -d		//to show the time of the last modification
	./dt -l		//to print information on the file as if the options tpiugs are all specified

	make clean	//to remove all the object and executable files	

ISSUES:
	1. I couldn't get the symbolic link one to work
	2. I saved the -I n indentation one for last, unfortunately, I did not figure that one out either
	3. I tried a million different variations of a depth first directory search, but none of them were working out for me. 
	   I can't figure out why they aren't working out. I'm being driven crazy.
	4. I tried it on a variety of different directories, but the answers were not coming out exactly how I imagined them to.

Good news is... I feel better acquainted with getopt and the project is doing a lot better than where I was at at 11am today. 
