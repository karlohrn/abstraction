#include <stdio.h>
//#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "db_back.h"

struct node{
  char* key;
  char* value;
  struct node *left;
  struct node *right;
};

char* read_buffer(){
  char* buffer = malloc(sizeof(char)*128);
  readline(buffer, 127, stdin);
  buffer[128] = '\0';
  return buffer;
}

void print_database(Node list){
}

char* get_value_of_node(Node value){
  if(value == NULL){
    return NULL;
  }else{
    return value->value;
  }
}

char* get_key_of_node(Node key){
  if(key == NULL){
    return NULL;
  }else{
    return key->key;
  }
}

Node cheak_for_key(Node list, char* buffer){
  return list;
}

Node db_delete_key(Node list, char*key){
  return list;
}

Node db_insert_key(Node list, char* buffer){
  return list;
}

void db_update_value(Node list, char* value){
}

Node load_database(char *filename){
  FILE *database = fopen(filename, "r");
  char buffer[128];
  Node tree = NULL;
  while(!(feof(database))){
    Node newNode = malloc(sizeof(struct node));
    readline(buffer, 128, database);
    newNode->key = malloc(strlen(buffer) + 1);
    strcpy(newNode->key, buffer);
    readline(buffer, 128, database);
    strcpy(newNode->value, buffer);
    if(tree == NULL){
      tree = newNode;
    }else{
      Node tmp_tree = tree;
      while(tmp_tree != NULL){
	if(tmp_tree->value > newNode->value){
	  tmp_tree = tmp_tree->left;
	}else{
	  if(tmp_tree->value <= newNode->value){
	    if(tmp_tree->value == newNode->value)
	      puts("allreaady have that value");
	    else{ 
	      tmp_tree = tmp_tree->right;		  
	    }
	  }
	}
      }
      tmp_tree = newNode;
      tree = tmp_tree;
    }
  }
  return tree;
}
