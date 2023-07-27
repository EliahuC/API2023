///////////////////////////////////////////////////////////////////////////////////////////////
// AUTHOR: Eliahu Itamar Cohen
// PROJECT:         Final project of Algorithms and  Principles of Computer Science
//                  SearchPath
///////////////////////////////////////////////////////////////////////////////////////////////



#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct carNode {
    int key ;
    struct carNode* p ;
    struct carNode* left;
    struct carNode* right;

} carTreeNode ;


/**
 * Creation of CarNodes
 * @param s key of the carNode
 * @return the new carNode
 */
carTreeNode* carTreeNodeCreation(int s){
    carTreeNode *x;
    x = (struct carNode*)malloc(sizeof(struct carNode));
    x->key=s;
    x->left=NULL;
    x->right=NULL;
    return x;
}


 /**
  * Insert of CarNode Function
  * @param root of the tree
  * @param s key of the new carNode
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
 * Lowest Autonomy Car Function
 * @param root of the tree
 * @return the car with the lowest autonomy
 */
carTreeNode * lowestAutonomyCar(carTreeNode *root){
    carTreeNode *cur=root;
    while(cur->left==NULL){
        cur=cur->left;
    }
    return cur;
}

/**
 * Function that finds the successor of x
 * @param x car
 * @return successor
 */
carTreeNode * nextCar(carTreeNode *x){
    if(x->right!=NULL){
        return lowestAutonomyCar(x->right);
    }
    carTreeNode *y=x->p;
    while(y!=NULL && y->right==x){
        x=y;
        y=y->p;
    }
    return y;

}

/**
 * Funcion to Remove a Car from the tree
 * @param root of the tree
 * @return root
 */
carTreeNode* removeCar(carTreeNode *root, int key){
    carTreeNode *x=searchCar(root,key);
    carTreeNode *to_del,*subtree;

    //find the carNode to delete
    if(x->left==NULL||x->right==NULL){
        to_del=x;
    }
    else to_del=nextCar(x);

    //find the subtree to move
    if(to_del->left != NULL){
        subtree=to_del->left;
    }
    else subtree=to_del->right;
    if(subtree!=NULL){
        subtree->p=to_del->p;
    }

    //correct the father reference
    if(to_del->p==NULL){
        root=subtree;
    }
    else if (to_del == to_del->p->left){
        to_del->p->left=subtree;
    }
    else to_del->p->right=subtree;

    //copy the key value
    if(to_del != x){
        x->key=to_del->key;
    }
    free(to_del);
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

typedef struct Edge{
    int start;
    int destination;
    struct Edge* next;
}Edge;

typedef struct Station{
    int distance;
    carTreeNode* root;
    Edge* edges;
}Station;

typedef struct Graph{
    Station* head;
}StationGraph;

Station *addEdges(Station *station, StationGraph graph) {
    Edge* edges;
    int maxDistance=highestAutonomyCar(station->root);
    int stationDistance=station->distance;
    int stationMaxEdge=stationDistance+maxDistance;
    StationGraph temporaryGraph=graph;
    //TODO settare grafo a stazione successiva
    while(temporaryGraph.head->distance > stationDistance && temporaryGraph.head->distance<stationMaxEdge){


    }
}

Station* createStation(StationGraph graph,int distance, carTreeNode* root){
   Station *x;
    x = (struct Station *)malloc(sizeof(struct Station));
    x->root=root;
    x->distance=distance;
    x= addEdges(x, graph);
    return x;
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