#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    new->root = NULL;
    new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode *TreeAux = tree->root;
    TreeNode * aux = NULL;
    while(TreeAux != NULL){
        aux = TreeAux;
        int resultado = tree->lower_than(key,TreeAux->pair->key);
        if(resultado == 1){ 
            TreeAux = TreeAux->left;
        }else{ 
            if(resultado == 0){
                TreeAux = TreeAux->left;
            }else return;
        }
    }
    TreeNode * newNode = createTreeNode(key, value);
    newNode-> parent = aux;
    int resultado = tree->lower_than(key,aux->pair->key);
    if(aux == NULL){
        tree->root = newNode;
    }else{
        if(resultado == 1){
            aux->left = newNode;
        }else{
            if (resultado == 0){ 
                aux->right = newNode;
            }
            
        }
    }
    tree->current = newNode;
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode* aux = tree->root;
    while (aux){ 
        int resultado = tree->lower_than(key,aux->pair->key);
        if((is_equal(tree,key,aux->pair->key) == 1)){ 
            tree->current = aux;
            return tree->current->pair;
        }
        if(resultado == 0){ 
            aux = aux->right;
        }else{ 
            if(resultado == 1){
                aux = aux->left;
            }
        }
        if(aux == NULL) return NULL; 
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
