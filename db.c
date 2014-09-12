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

void user_delete_key(Node list){
  printf("Enter key:");
  char* key = read_buffer();
  puts("Searching database...\n");
  //Node value = cheak_for_key(list, key);
  //vet inte hur jag ska använda cheak_for value() trots att jag ska hitta noden.
  char* value = db_delete_key(list, key);
  if(value != NULL){
    printf("Deleted the following entry:\nkey: %s\nvalue: %s", key, value);
  }else 
    printf("Could not find an entry matching key \"%s\"!\n", key);
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

Node user_insert_key(Node list){
  printf("Enter key: ");
  char* buffer = read_buffer();
  puts("Searching database for duplicate keys...");
  Node found  = cheak_for_key(list, buffer);
  if(found == NULL){
    puts("Key is unique!\n");
    printf("Enter value: ");
    Node newNode = db_insert_key(list, buffer);
    puts("");
    puts("Entry inserted successfully:");
    printf("key: %s\nvalue: %s\n", list->key, list->value);
    return newNode;
  }
  printf("key \"%s\" already exists!\n", buffer);
  return list;
}

void db_update_value(Node list, char* value){
  Node cursor = list;
  free(cursor->value);
  cursor->value = malloc(strlen(value) + 1);
  strcpy(cursor->value, value);
}

void user_update_key(Node list){
  printf("Enter key: ");
  char* key = read_buffer();
  Node value = cheak_for_key(list, key);
  puts("Searching database...\n");
  if(value != NULL){
    puts("Matching entry found:");
    printf("key: %s\nvalue: %s\n\n", key, value->value);
    printf("Enter new value: ");
    char* new_value = read_buffer();
    db_update_value(value, new_value);
    puts("Value inserted successfully!");
  }else{
    printf("Could not find an entry matching key \"%s\"!\n", key);
  }
}

void user_query_key(Node list){
  printf("Enter key: ");
  char* buffer = read_buffer();
  puts("Searching database...\n");
  Node value = cheak_for_key(list, buffer);
  if(value != NULL){
      puts("Found entry:");
      printf("key: %s\nvalue: %s\n", value->key, value->value);
      
  }else{
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }
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
int main(int argc, char *argv[]){
  if (argc < 2){
    puts("Usage: db [FILE]");
    return -1;
  }
  welcome();

  // Read the input file

  char *filename = argv[1];
  Node list = load_database(filename);

  // Main loop

  int choice = -1;
  while(choice != 0){
    puts("Please choose an operation");
    puts("1. Query a key");
    puts("2. Update an entry");
    puts("3. New entry");
    puts("4. Remove entry");
    puts("5. Print database");
    puts("0. Exit database");
    printf("? ");
    scanf("%d", &choice);
    while(getchar() != '\n'); // Clear stdin
    switch(choice){
    case 1:
      user_query_key(list);
      break;
    case 2:
      user_update_key(list);
      break;
    case 3:
      list = user_insert_key(list);
      break;
    case 4:
      user_delete_key(list);
      break;
    case 5:
      print_database(list);
      break;
    case 0:

      // Exit

      puts("Good bye!");
      break;
    default:

      // Please try again

      puts("Could not parse choice! Please try again");
    }
    puts("");
  }
  return 0;
}
