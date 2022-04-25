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
    if(searchTreeMap(tree,key) != NULL) return;
    while(TreeAux != NULL){
        aux = TreeAux;
        int resultado = tree->lower_than(key,TreeAux->pair->key);
        if(resultado == 1){ 
            TreeAux = TreeAux->left;
        }else{ 
            if(resultado == 0){
                TreeAux = TreeAux->right;
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
    return;
}

TreeNode * minimum(TreeNode * x){
    while(x->left != NULL){
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    if((node->left == NULL) && (node->right == NULL)){//no tiene hijos
        TreeNode *parent = node->parent;
        //if(parent == NULL) tree->root == NULL;
        if(parent->left == node) parent->left = NULL;
        if(parent->right == node) parent->right = NULL;
    }else{//aprovecho de verificar altiro con los dos hijos 
        if((node->left != NULL) && (node->right != NULL)){//tiene 2 hijos
            TreeNode *auxNode = node->right; //Descienda al hijo derecho
            auxNode = minimum(auxNode);//obtenga el menor nodo del subárbol
            node->pair->key = auxNode->pair->key;//Reemplace los datos (key,value) de *node* con los del nodo "minimum"
            node->pair->value = auxNode->pair->value;//Reemplace los datos (key,value) de *node* con los del nodo "minimum"
            removeNode(tree,node);//Elimine el nodo minimum
            return;
        }//else{//se supone que en este momento se supone que tiene hijos pero no 2 es decir solo qtendria 1 hijo

        //}
    }
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
