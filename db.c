#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_back.h"

Node user_delete_key(Node list){
  printf("Enter key:");
  char* key = read_buffer();
  puts("Searching database...\n");
  Node value = cheak_for_key(list, key);
  if(value != NULL){
    char* old_value = get_value_of_node(value);
    Node new_list = db_delete_key(list, key);
    printf("Deleted the following entry:\nkey: %s\nvalue: %s", key, old_value);
    return new_list;
  }else 
    printf("Could not find an entry matching key \"%s\"!\n", key);
  return list;
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
    printf("key: %s\nvalue: %s\n", get_key_of_node(newNode), get_value_of_node(newNode));
    return newNode;
  }
  printf("key \"%s\" already exists!\n", buffer);
  return list;
}

void user_update_key(Node list){
  printf("Enter key: ");
  char* key = read_buffer();
  Node value = cheak_for_key(list, key);
  puts("Searching database...\n");
  if(value != NULL){
    puts("Matching entry found:");
    printf("key: %s\nvalue: %s\n\n", key, get_value_of_node(value));
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
      printf("key: %s\nvalue: %s\n", get_key_of_node(value), get_value_of_node(value));
      
  }else{
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }
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
      list = user_delete_key(list);
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
