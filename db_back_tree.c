#include <stdio.h>
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
/*
Node find_min(Node tree){
  if (tree->left != NULL){
    return find_min(tree->left);
  }
  return tree;
}
*/
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

void db_delete_key(Node tree, char* key){
  Node prev = NULL;
  while(tree){
    if(strcmp(tree->key, key) < 0){
      prev = tree;
      tree = tree->right;
    }else if(strcmp(tree->key, key) > 0){
      prev = tree;
      tree = tree->left;
    }else{
      break;
    }
  }

  // Not found.
  if (tree == NULL)
    return;

  // Fall 3. två barn vvvvv  
  if(tree->left != NULL && tree->right != NULL){
    Node tmp_tree = tree->left;
    while(tmp_tree->right != NULL){
      tmp_tree = tmp_tree->right;
    }
    char* value = tree->value;
    tree->key = tmp_tree->key;
    tree->value = tmp_tree->value;
    tmp_tree->key = key;
    tmp_tree->value = value;
    db_delete_key(tree->right, key);
  }
  // Fall 2. ett barn
  else if(tree->left == NULL && tree->right != NULL){
    if(strcmp(prev->key, tree->key) < 0){
      prev->right = tree->right;
      free(tree);
    }else{
      prev->left = tree->right;
      free(tree);
    }
  }
  // Fall 2. ett barn
  else if(tree->left != NULL && tree->right == NULL){
    if(strcmp(prev->key, tree->key) < 0){
      prev->right = tree->left;
    }else{
      prev->left = tree->left;
    }
  }else{
    // Fall 1. noll barn
    if(prev == NULL){
      tree->key = NULL;
      tree->value = NULL;
    }else if(strcmp(prev->key, tree->key) < 0){
      puts("hej");
      prev->right = NULL;
      puts("1");
      free(tree);
      puts("2");
    }else{
      prev->left = NULL;
      free(tree);
    }
  }
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
/*
void db_insert_key(Node tree, char* key, char* value){
  
  if (tree == NULL){
    tree = new_node(key, value);
    return;
  }
  if (tree->key == NULL){
    tree->key = malloc(strlen(key)+1);
    strcpy(tree->key, key);
    tree->value = malloc(strlen(value)+1);
    strcpy(tree->value, value);
    return;
  }
  if (strcmp(tree->key, key) > 0){
    if(tree->left == NULL){
      tree->left = new_node(key, value);
    }else{
      db_insert_key(tree->left, key, value);
    }
    return;
  }
  else if (strcmp(tree->key, key) < 0){
    if (tree->right == NULL){
      tree->right = new_node(key, value);
    }else{
      db_insert_key(tree->right, key, value);
    }  
    return;
  }
  return;
}
*/

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


/*
  Uppdaterar värdet på en node i trädet.
  tar in noden den väl ändre på tar bort värdet och allocelar nytt mine och skriver in ett ny värde.

  skriven av Karl Öhrn 
*/

void db_update_value(Node tree, char* value){
  free(tree->value);
  tree->value = malloc(strlen(value) +1);
  strcpy(tree->value, value);
}

/*
  laddar in databasen genom att anropa inster funktionen med data den hämtar från en fil.
  Den tar in datan som ska lagras i data strukturen från filename.

  Skriven av Karl Öhrn
*/

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
