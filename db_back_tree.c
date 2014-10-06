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
/*
D9
I22
M37
*/
/*
rekuserar igenom hela trädet och skriver ut det.
*/

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
  
/*
retunerar value på noden
*/

char* get_value_of_node(Node value){
  if(value == NULL){
    return NULL;
  }else{
    return value->value;
  }
}

/*
retunerar nycken på noden
*/

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

/*
letar i träddet tills den antigen hittar noden eller retunerar null om den inte finns.

in data 
Node tree
char* key

ut data
node value om den hittar noden
annars
NULL om noden inte fanns
*/

Node search_for_key(Node tree, char* key){
  if(tree == NULL){ 
    return NULL;
  }else while(tree){
      if(strcmp(tree->key, key) == 0){
	return tree;
      }else if(strcmp(tree->key, key) < 0){
	tree = tree->right;
      }else{
	tree = tree->left;
      }
    }
  return NULL;
}
/*
Node search_for_key(Node tree, char* key){
  if(tree == NULL){
    return NULL;
  }else if(strcmp(tree->key, key) == 0){
    return tree;
  }else{
    if(tree->left != NULL){
      Node value = search_for_key(tree->left, key);
      if(value) return value;
    }
    if(tree->right != NULL){
      Node value =search_for_key(tree->right, key);
      if(value) return value;
    }
  }
  return NULL;
}
*/
/*
db_delete_key går igenom trädet tills den hittar rätt node som man vill ta bort, där efter beror det på vilket fall noden är i om den har noll, ett eller 2 barn beroende på vad den gör. vid två barn bytter den plats med barnet ett steg till höger och sen så långt ner i vänstra trädet som möjligt, efter det rekuserar den om i funktionen.

om noden man försöker ta bort bara har ett barn pekar funktionen om noden innan till att peka på nästa barn och sen kör den free på node man ville tabort.

om barnet inte har något barn kör funktionen free på noden.

in data
Node tree
char* key 
*/

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
    db_delete_key(tree, key);
  }
  // Fall 2. ett barn
  else if(tree->left == NULL && tree->right != NULL){
    if(strcmp(prev->key, tree->key) < 0){
      prev->right = tree->right;
      tree->left = NULL;
      tree->left = NULL;
      tree->right = NULL;
      free(tree);
    }else{
      prev->left = tree->right;
      tree->left = NULL;
      tree->right = NULL;
      free(tree);
    }
  }
  // Fall 2. ett barn
  else if(tree->left != NULL && tree->right == NULL){
    if(strcmp(prev->key, tree->key) < 0){
      prev->right = tree->left;
      tree->left = NULL;
      tree->right = NULL;
      free(tree);
    }else{
      prev->left = tree->left;
      tree->left = NULL;
      tree->right = NULL;
      free(tree);
    }
  }else{
    // Fall 1. noll barn
    if(prev == NULL){
      tree->key = NULL;
      tree->value = NULL;
      tree->left = NULL;
      tree->right = NULL;
    }else if(strcmp(prev->key, tree->key) < 0){
      prev->right = NULL;
      tree->left = NULL;
      tree->right = NULL;
      free(tree);
    }else{
      prev->left = NULL;
      tree->left = NULL;
      tree->right = NULL;
      free(tree);
    }
  }
}

/*
make_tree_empyt skpar en tom trä nod som den sen retunerar

in data 
ut data 
Node tom_node
*/

Node make_tree_empty(){
  return calloc(sizeof(struct node), 1);
}

/*
funktionen new_node tar in en nykel och ett värde som den allocerar minne för på heapen och läger in värdet och nycklen i träd noden. vilket den sen retunerar.

in data 
char* key
char* value

ut data
Node noden_du_har_skapat

*/

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

/*
insert funktionen tar in en träd node, nyckle och value. Går igenom trädet tills den hittar en ledding plats att läga in den nya noden och allocerar mine och lägger in det

Den måste alltid ha ett träd att läga in data i även om trädet skulle vara tomt.

in data 
Node tree (i det trädet du skulle vilja läga in den nya noden, får inte vara NULL)
char* key (det nya nycklen)
char* value (det nya värdet)
*/

void db_insert_key(Node tree_node, char* key, char* value){
  if(tree_node == NULL){
  }else if(tree_node->key == NULL){
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
  Uppdaterar värdet på en node i trädet. Genom att först avallocera värdet på noden, där efter allocera nytt och läga in det nya värdet.

in data 
Noden tree (den noden man vill uppdatera värdet på)
char* value (det nya värdet)

ut data 
den retunerar inget

  skriven av Karl Öhrn 
*/

void db_update_value(Node tree, char* value){
  if(tree == NULL){
  }else 
  free(tree->value);
  tree->value = malloc(strlen(value) +1);
  strcpy(tree->value, value);
}

/*
  laddar in databasen genom att anropa inster funktionen med data den hämtar från en fil. Lägger in alla nycklar och värden i en trädstruktur. Funktionen ger tillbaka en Node pekare till rotten i trädet.

in data är
Char* filename

ut data är
Node tree

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
