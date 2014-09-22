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

void print_database(Node tree){
  if(tree == NULL){
  }else{
    puts(tree->key);
    puts(tree->value);
    if(tree->left != NULL){
      print_database(tree->left);
    }
    if(tree->right != NULL){
      print_database(tree->right);
    }
  }
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

Node cheak_for_key(Node tree, char* buffer){
  node value = NULL;
  if(strcmp(tree->key, buffer) == 0){
    value = tree;
    return tree;
  }else{
    if(tree->left != NULL){
      cheak_for_key(tree->left, buffer);
    }
    if(tree->right != NULL){
      cheak_for_key(tree->right, buffer);
    }
  }
  return value;
}


Node db_delete_key(Node tree, char* key){
  Node prev = NULL;
  if (tree == NULL){
    return NULL;
  }
  else{
    while(tree){
      if(strcmp(tree->key, key) == 0){
	Node tree_left = tree->left;
	Node tree_right = tree->right;
	free(tree);
	reinsert(Tree_left, prev);
	reinsert(Tree_right, prev);
	
      }else{
	if(strcmp(tree->key, key) > 0){
	  prev = tree;
	  tree = tree->left;
	}else{
	  if(strcmp(tree->key, key) < 0){
	    prev = tree;
	    tree = tree->right;
	  }
	}
      }
    }
  }  
  return tree;
}

void reinsert(Node deleted_tree, Node tree){
  if(tree == NULL){
  }else{
    char* key = deleted_tree->key;
    char* value = deleted_tree->value;
    db_insert_key(tree, key, value);
    tree_right = deleted_tree->right;
    tree_left = deleted_tree->left;
    reinsert(tree_right, tree);
    reinsert(tree_left, tree);
  }
}

Node db_insert_key(Node tree, char* key, char* value){
  Node newNode = malloc(sizeof(struct node));
  newNode->key = malloc(strlen(key)+1);
  strcpy(newNode->key, key);
  newNode->value = malloc(strlen(value)+1);
  strcpy(newNode->value, value);
  if(tree == NULL){
    tree = newNode;
  }else{
    Node tmp_tree = tree;
    while(tmp_tree){
      if(strcmp(tmp_tree->key, newNode->key) > 0){
	tmp_tree = tmp_tree->left;
      }else{
	if(strcmp(tmp_tree->key, newNode->key) =< 0){
	  if(tmp_tree->key == newNode->key){
	    return list;
	  }else{
	    tmp_tree = tmp_tree->right;
	  }
	}
      }
    }
    tmp_tree = newNode;
    tree = tmp_tree;
  }
  return tree;
}

void db_update_value(Node tree, char* value){
  Node cursor = tree;
  free(cursor->value);
  cursor->value = malloc(strlen(value) +1);
  strcpy(cursor->value, value);
}

Node load_database(char *filename){
  FILE *database = fopen(filename, "r");
  char value[128];
  char key[128];
  Node tree = NULL;
  while(!(feof(database))){
    readline(key, 128, database);
    readline(value, 128, database);
    insert(tree, key, value); 
  }
  return tree;
}
