CC= gcc
FLAGS= -ggdb -Wall -std=c99


main:	db.o db_back.o db_back_tree db.c
	$(CC) -g db_back.o db.o -o main

db_back.o: db_back.c db_back.h
	$(CC) $(FLAGS) -c db_back.c

db.o: 	db.c db_back.h 
	$(CC) $(FLAGS) -c db.c     

db_back_tree: db_back_tree.c
	$(CC) $(FLAGS) -o db_back_tree db_back_tree.c

clean:
	rm -f db_back.o
	rm -f db.o
	rm -f db_back_tree.o
	rm -f *~

.PHONY: clean
