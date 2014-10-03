#ifndef db_back
#define db_back
#include <stdio.h>
typedef struct node *Node;
void readline(char* dest, int n, FILE *source);
void print_database(Node list);
char* get_value_of_node(Node value);
char* get_key_of_node(Node key);
Node search_for_key(Node list, char* buffer);
Node db_delete_key(Node list, char*key);
void db_insert_key(Node list, char* key, char*value);
void db_update_value(Node list, char* value);
Node load_database(char *filename);
#endif

