#ifndef db_back
#define db_back
typedef struct node{
  char *key;
  char *value;
  struct node *next;
}*Node;

void readline(char *dest, int n, FILE *source);
void print_database(Node list);
char* read_buffer();
Node cheak_for_key(Node list, char* buffer);
Node db_delete_key(Node list, char*key);
Node db_insert_key(Node list, char* buffer);
void db_update_value(Node list, char* value);
void welcome();
Node load_database(char *filename);
#endif

