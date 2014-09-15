main:	db.o db_back.o
	gcc -g db_back.o db.o -o main

db_back.o: db_back.c db_back.h
	gcc -Wall -std=c99 -c -ggdb db_back.c

db.o: 	db.c db_back.h 
	gcc -std=c99 -c -Wall -ggdb db.c     

clean:
	rm -f db_back.o
	rm -f db.o