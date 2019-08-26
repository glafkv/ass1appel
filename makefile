dt: dt.o
    gcc -o dt dt.o

dt.o: dt.c
      gcc -c dt.c

.PHONY: clean
clean:
	/bin/rm -f *.o *~ appel.1
