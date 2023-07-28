///////////////////////////////////////////////////////////////////////////////////////////////
// AUTHOR: Eliahu Itamar Cohen
// PROJECT:         Final project of Algorithms and  Principles of Computer Science
//                  SearchPath
///////////////////////////////////////////////////////////////////////////////////////////////



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


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

typedef struct Path{
    int start;
    int destination;
    struct Station* destinationStation;
}Path;

typedef struct Vertex{
    int distance;
    carTreeNode* root;
    struct Vertex* next;
    struct Vertex* prev;
    Path* paths;
    int numberOfPaths;
}Station;

typedef struct Graph{
    Station* head;
    int size;
}StationGraph;

/**
 * Checks if the station is already in the graph (search funtion)
 * @param graph of the stations
 * @param distance of the station
 * @return true if there isn't any station with key==distance
 */
bool notInTheGraph(StationGraph *graph, int distance) {
    //TODO SEARCH IN THE GRAPH
}



/**
 * Adds all the egdes of a certain station
 * @param station to get the edges
 * @param graph of the stations
 * @return graph
 */
Path *addEdges(Station *station, StationGraph graph) {
    Path *edges;

    //edges=(struct Path *)malloc(station->numberOfPaths * (sizeof (struct Path)));
    int maxDistance=highestAutonomyCar(station->root);
    int stationDistance=station->distance;
    int stationMaxEdge=stationDistance+maxDistance;
    StationGraph temporaryGraph=graph;
    //TODO settare grafo a stazione successiva
    while(temporaryGraph.head->distance > stationDistance && temporaryGraph.head->distance<stationMaxEdge){



    }
    return edges;
}

Station* nextStation(Station *x,StationGraph graph){

}
Station* prevStation(Station *x,StationGraph graph){

}

/**
 * Insert in the graph
 * @param graph
 * @param distance from the beginning of the road
 * @param root of the tree
 * @return graph
 */
StationGraph * createStation(StationGraph *graph,int distance, carTreeNode* root){
   Station *x;
   if(notInTheGraph(graph,distance)){
    x =  (struct Station*) malloc(sizeof(struct Station*));
    x->root=root;
    x->distance=distance;
    if(graph->head->distance==0){
        graph->head=x;
        graph->size++;
        return graph;
    }
    x->paths = addEdges(x, *graph);
    x->next=nextStation(x,*graph);
    x->prev=prevStation(x,*graph);
    graph->size++;
    return graph;
   }
    return NULL;
}

/**
 * Initialize a new graph
 * @param graph to initialize
 * @return graph
 */
StationGraph * newGraph(StationGraph *graph) {
    Station *x = malloc(sizeof(Station*));
    graph->size = 0;
    x->distance=0;
    x->root=NULL;
    x->paths=NULL;
    x->numberOfPaths=0;
    x->next=NULL;
    x->prev=NULL;
    graph->head=x;
    return graph;

}


int main(){
    StationGraph *graph= malloc(sizeof (StationGraph));
    newGraph(graph);
    //TODO Implementare grafi per stazione 70%
    //TODO Funzione aggiungi-stazione  50%
    //TODO Funzione demolisci-stazione 0%
    //TODO Funzione aggiungi-auto 80%
    //TODO Funzione rottama-auto 80%
    //TODO Funzione pianifica-percorso 0%
    //TODO funzione main 0%
    return 0;
}