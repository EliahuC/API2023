///////////////////////////////////////////////////////////////////////////////////////////////
// AUTHOR: Eliahu Itamar Cohen
// PROJECT:         Final project of Algorithms and  Principles of Computer Science
//                  SearchPath
///////////////////////////////////////////////////////////////////////////////////////////////



#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct node {
    int key ;
    struct node* p ;
    struct node* left;
    struct node* right;

} carTreeNode ;


/**
 * Creation of CarNodes
 * @param s key of the node
 * @return the new node
 */
carTreeNode* carTreeNodeCreation(int s){
    carTreeNode *x;
    x = (struct node*)malloc(sizeof(struct node));
    x->key=s;
    x->left=NULL;
    x->right=NULL;
    return x;
}


 /**
  * Insert of CarNode Function
  * @param root of the tree
  * @param s key of the new node
  * @return root
  */
carTreeNode * carInsert (carTreeNode *root , int s)
{
    carTreeNode *pre, *cur, *x;
    x=carTreeNodeCreation(s);
    pre=NULL;
    cur=root;
    while ((cur!=NULL)&&(cur->key != NULL))
    {
        pre=cur;
        if (x->key<cur->key)cur=cur->left;
        else cur=cur->right;
    }
    x->p=pre;
    if (pre==NULL) root=x;
    else
    {
        if (x->key<pre->key) pre->left = x;
        else pre->right=x;
    }
    return root;
}


/**
 * Search Car Function
 * @param root of the tree
 * @param x key to search
 * @return root
 */
carTreeNode * searchCar(carTreeNode *root, int x)
{
    while((root != NULL) && (x!= root->key)  )
    {
        if(x < root->key)  root=root->left;
        else root=root->right;
    }
    return root;
}

/**
 * Highest Autonomy Car Function
 * @param root of the tree
 * @return the car with the highest autonomy
 */
int highestAutonomyCar(carTreeNode *root){
    carTreeNode *cur=root;
    while(cur->right==NULL){
        cur=cur->right;
    }
    return cur->key;
}

int main(){
    //TODO Implementare grafi per stazione
    //TODO Funzione aggiungi.stazione
    //TODO Funzione demolisci-stazione
    //TODO Funzione aggiungi-auto
    //TODO Funzione rottama-auto
    //TODO Funzione pianifica-percorso
    //TODO funzione main
    return 0;
}