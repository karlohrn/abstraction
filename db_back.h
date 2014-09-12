#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
  char *key;
  char *value;
  struct node *next;
} *Node;

void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

void print_database(Node list){
  Node cursor = list;
  while(cursor != NULL){
    puts(cursor->key);
    puts(cursor->value);
    cursor = cursor->next;
  }
}

char* read_buffer(){
  char* buffer = malloc(sizeof(char)*128);
  readline(buffer, 127, stdin);
  buffer[128] = '\0';
  return buffer;
}

Node cheak_for_key(Node list, char* buffer){
  int found = 0;
  Node cursor = list;
  Node value = NULL;
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      value = cursor;
      found = 1;
    }else{
      cursor = cursor->next;
    }
  }
  return value;
}
 
char* db_delete_key(Node list, char*key){
  int found = 0;
  Node cursor = list;
  Node prev = NULL;
  char* value = NULL;
  while(!found && cursor != NULL){
    if(strcmp(key, cursor->key) == 0){
      value = cursor->value;
      if(prev == NULL){ // Delete first node
        list = cursor->next;
	return (char*) list->value;
      }else{
        prev->next = cursor->next;
      }
      found = 1;
    }else{
      prev = cursor;
      cursor = cursor->next;
    }
  }
  return value;
}

Node db_insert_key(Node list, char* buffer){
  Node newNode = malloc(sizeof(struct node));
  newNode->key = malloc(strlen(buffer) + 1);
  strcpy(newNode->key, buffer);
  readline(buffer, 128, stdin);
  newNode->value = malloc(strlen(buffer) + 1);
  strcpy(newNode->value, buffer);
  newNode->next = list;
  return newNode;
}

void db_update_value(Node list, char* value){
  Node cursor = list;
  free(cursor->value);
  cursor->value = malloc(strlen(value) + 1);
  strcpy(cursor->value, value);
}

void welcome(){
  puts("Welcome to");
  puts(" ____    ____       ");
  puts("/\\  _`\\ /\\  _`\\     ");
  puts("\\ \\ \\/\\ \\ \\ \\L\\ \\   ");
  puts(" \\ \\ \\ \\ \\ \\  _ <\\ ");
  puts("  \\ \\ \\_\\ \\ \\ \\L\\ \\ ");
  puts("   \\ \\____/\\ \\____/ ");
  puts("    \\/___/  \\/___/  ");
  puts("");
}

Node load_database(char *filename){
  printf("Loading database \"%s\"...\n\n", filename);
  FILE *database = fopen(filename, "r");
  char buffer[128];
  Node list = NULL;
  while(!(feof(database))){
    Node newNode = malloc(sizeof(struct node));
    readline(buffer, 128, database);
    newNode->key = malloc(strlen(buffer) + 1);
    strcpy(newNode->key, buffer);
    readline(buffer, 128, database);
    newNode->value = malloc(strlen(buffer) + 1);
    strcpy(newNode->value, buffer);
    newNode->next = list;
    list =newNode;
  }
  return list;
}


