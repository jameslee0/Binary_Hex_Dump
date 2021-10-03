#James Lee
#cssc3719
#CS520-01 Spring 2021
#Assignment 1, Hex/Binary Dump Source Code


dump: dump.o
	gcc dump.o -o dump

dump.o: dump.c
	gcc -c dump.c

clean:
	rm -f *.o dump
