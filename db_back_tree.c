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
    Node tree_left = tree->left;
    Node tree_right = tree->right;
    print_database(tree_left);
    print_database(tree_right);
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

Node search_for_key(Node tree, char* key){
  if(strcmp(tree->key, key) == 0){
    return tree;
  }else{
    if(tree->left != NULL){
     Node value = search_for_key(tree->left, key);
      if(value) return value;
    }
    if(tree->right != NULL){
     return search_for_key(tree->right, key);
    }
  }
  return NULL;
}


void reinsert(Node deleted_tree, Node tree){ 
  if(deleted_tree == NULL){
  }else{
    printf("%i\n", __LINE__);
    db_insert_key(tree, deleted_tree->key, deleted_tree->value);
    printf("%i\n", __LINE__);
    if(deleted_tree->right){
      printf("%i\n", __LINE__);
      reinsert(deleted_tree->right, tree);
    }
    if(deleted_tree->left){
      printf("%i\n", __LINE__);
      reinsert(deleted_tree->left, tree);
    }
  }
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
	if(prev){
	  if(strcmp(prev->key, key) > 0){
	    prev->left = NULL;
	  }else{
	    prev->right = NULL;
	  }
	}
	free(tree);
	reinsert(tree_left, prev);
	reinsert(tree_right, prev);
	break;
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


Node make_tree_empty(){
  return calloc(sizeof(struct node), 1);
}

Node new_node(char* key, char* value){
  Node the_node = malloc(sizeof(struct node));
  the_node->key = malloc(strlen(key)+1);
  strcpy(the_node->key, key);
  the_node->value = malloc(strlen(value)+1);
  strcpy(the_node->value, value);
  return the_node;
}

void db_insert_key(Node tree_node, char* key, char* value){
  if(tree_node->key == NULL){
    tree_node->key = malloc(strlen(key)+1);
    strcpy(tree_node->key, key);
    tree_node->value = malloc(strlen(value)+1);
    strcpy(tree_node->value, value);
  }else{
    while(1){
      if(strcmp(tree_node->key, key) > 0){
	if(tree_node->left == NULL){
	  Node newNode = new_node(key, value);
	  tree_node->left = newNode;
	  break;
	}else{
	tree_node = tree_node->left;
	}
      }else if(strcmp(tree_node->key, key) == 0){
	break;
      }
      else{
	if(tree_node->right == NULL){
	  Node newNode = new_node(key, value);
	  tree_node->right = newNode;
	  break;
	}else{
	  tree_node = tree_node->right;
	}
      }
    }
  }
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
  Node tree = make_tree_empty();
  while(!(feof(database))){
    readline(key, 128, database);
    readline(value, 128, database);
    db_insert_key(tree, key, value);
  }
  return tree;
}
