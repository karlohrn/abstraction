CC= gcc
FLAGS= -ggdb -Wall -std=c99 -Werror


main_tree:	db.o db_back_tree.o
	$(CC) -g db_back_tree.o db.o -o main_tree

main_list:	db.o db_back.o
	$(CC) -g db_back.o db.o -o main_list

%.o: %.c %.h
	$(CC) $(FLAGS) -c $< -o $@

db_back.o:	db_back.c db_back.h
	$(CC) $(FLAGS) -c db_back.c

db.o:	db.c db_back.h 
	$(CC) $(FLAGS) -c db.c     

db_back_tree.o:	db_back_tree.c db_back.h
	$(CC) $(FLAGS) -c db_back_tree.c

clean:
	rm -f db_back.o
	rm -f db.o
	rm -f db_back_tree.o
	rm -f *~

.PHONY: clean
