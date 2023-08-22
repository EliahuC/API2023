///////////////////////////////////////////////////////////////////////////////////////////////
// AUTHOR: Eliahu Itamar Cohen
// PROJECT:         Final project of Algorithms and  Principles of Computer Science
//                  SearchPath
///////////////////////////////////////////////////////////////////////////////////////////////

//TODO Implementare grafi per stazione 99%
//TODO Funzione aggiungi-stazione  80%
//TODO Funzione demolisci-stazione 0%
//TODO Funzione aggiungi-auto 80%
//TODO Funzione rottama-auto 80%
//TODO Funzione pianifica-percorso 0%
//TODO funzione main 0%

#include <stdio.h>
#include <stdlib.h>
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
  * Insert of CarNode Function
  * @param root of the tree
  * @param s key of the new carNode
  * @return root
  */
carTreeNode * carInsert (carTreeNode *root , int s,int print)
{

    carTreeNode *pre, *cur, *x;
    x=carTreeNodeCreation(s);
    pre=NULL;
    cur=root;
    while (cur!=NULL)
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
        if(print==1) printf("aggiunta\n");
    return root;
    }


/**
 * Lowest Autonomy Car Function
 * @param root of the tree
 * @return the car with the lowest autonomy
 */
carTreeNode * lowestAutonomyCar(carTreeNode *root){
    carTreeNode *cur=root;
    while(cur->left!=NULL){
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
    printf("rottamata\n");
    return root;
}


/**
 * Highest Autonomy Car Function
 * @param root of the tree
 * @return the car with the highest autonomy
 */
int highestAutonomyCar(carTreeNode *root){
    carTreeNode *cur=root;
    while(cur->right!=NULL){
        cur=cur->right;
    }
    return cur->key;
}



typedef struct Station{
    int distance;
    carTreeNode* root;
    struct Station* next;
    struct Station* prev;
    struct Station* best;

}Station;

typedef struct Graph{
    Station* head;
    int size;
    Station *startingPoint;
}StationGraph;

/**
 * Checks if the station is already in the temp (search function)
 * @param temp of the stations
 * @param distance of the station
 * @return true if there isn't any station with key==distance
 */

bool notInTheGraph(StationGraph *graph, int distance) {
    while((graph->head!=NULL)||(graph->head->next!=NULL)||(graph->head->distance<distance) ) {
        graph->head=graph->head->next;
        if(graph->head==NULL)return true;
    }

    if(graph->head->distance==distance)return false;
    return true;
}




StationGraph* addStation(Station *x, StationGraph *graph) {
    /*graph->head = graph->startingPoint;

    while (graph->head->next != NULL){
        if(graph->head->next->distance > x->distance) break;
        graph->head = graph->head->next;
    }
    x->next=graph->head->next;
    graph->head->next=x;

    graph->head=graph->startingPoint;
    return graph;*/
    Station *prev=graph->head;

    while((graph->head!=NULL)&&(graph->head->distance<x->distance && graph->head->next!=NULL)){
        prev=graph->head;
        graph->head=graph->head->next;

    }
    if(prev->distance<x->distance){
        x->prev=prev;
       prev->next=x;
    }
    x->next=graph->head;
    graph->head->prev=x;
    graph->head=graph->startingPoint;
    return graph;
}

/**
 * Insert in the graph
 * @param graph
 * @param distance from the beginning of the road
 * @param root of the tree
 * @return graph or NULL if the station is already present
 */
StationGraph * createStation(StationGraph *graph,int distance, carTreeNode* root){


   if(notInTheGraph(graph,distance)){
   Station *x = (Station *) malloc(sizeof(Station));
    graph->head=graph->startingPoint;
    x->root=root;
    x->distance=distance;
    x->prev=NULL;
    x->next=NULL;
    if(graph->size==0){
        graph->head->next=x;
        graph->head->next->prev=graph->head;
        graph->size++;
        graph->head=graph->startingPoint;
        return graph;
    }
    graph=addStation(x,graph);
    graph->size++;
    return graph;
   }
    return graph;
}

/**
 * Initialize a new graph
 * @param graph to initialize
 * @return graph
 */
StationGraph * newGraph(StationGraph *graph) {
    Station *x =(Station *) malloc(sizeof(Station));
    graph->size = 0;
    x->distance=-1;
    x->root=NULL;
    x->next=NULL;
    x->prev=NULL;
    graph->head=x;
    graph->startingPoint=x;
    return graph;

}

Station * searchStation(StationGraph *graph,int start){
    StationGraph *temp=graph;
    while(temp->head->next!=NULL&&temp->head->distance<start){
        temp->head=temp->head->next;
    }
    if(temp->head->distance==start){
        Station *station=graph->head;
        graph->head=graph->startingPoint;
        return station;
    }
    graph->head=graph->startingPoint;
    return NULL;
}
/**
 * Function to remove a station
 * @param graph of the stations
 * @param distance of the station to remove
 * @return the updated graph
 */
StationGraph* removeStation(StationGraph *graph,int distance){

   StationGraph *temp_graph=graph;
    while (temp_graph->head->distance<distance){
        temp_graph->head=temp_graph->head->next;
    }
    temp_graph->head->prev->next=temp_graph->head->next;
    if(temp_graph->head->next!=NULL){
        temp_graph->head->next->prev=temp_graph->head->prev;
    }

    graph->head=graph->startingPoint;


   // free(s->root);
  //  free(s);
    printf("demolita\n");

    return graph;


}

void shiftInput(){
    char input;
    input= getc(stdin);
    while(input!=' ' ){
        input= getc(stdin);
    }
}

carTreeNode* createCarTree(int cars[],int n,carTreeNode *root){
    if(n==0) return root;
    int i;
    root->key=cars[0];
    for(i=1;i<n;i++){

        root= carInsert(root,cars[i],0);
    }
    return root;
}


/**
 * adds a new station to the queue
 * @param queue
 * @param rear
 * @param temp
 * @return new queue
 */
Station **addToQueue(Station **queue, int rear, Station *temp) {
    Station *toBeAdded=temp;
    queue[rear++]= toBeAdded;
    return queue;
}


/**
 * Function to find the best path for the trip
 * @param graph of the stations
 * @param startingPoint starting station
 * @param arrivalPoint final station
 *
 */
void bestPath(StationGraph *graph,int startingPoint,int arrivalPoint){
    Station* *queue =(Station **) malloc(sizeof(Station) * graph->size);
    int front = 0;
    int rear = 0;
    Station *startingStation=searchStation(graph,startingPoint);

    queue[rear++] = startingStation;

    //percorso diretto
    if(startingPoint<arrivalPoint){
        Station *temp1=startingStation;
        //RESET BEST PATH
        while(temp1!=NULL&&temp1->distance<=arrivalPoint){
            temp1->best=NULL;
            temp1=temp1->next;

        }
        int maxDistanceTouched=startingStation->distance;
        while (front < rear && maxDistanceTouched < arrivalPoint) {
                Station *curr =queue[front++];

                Station *temp=curr->next;
                int autonomy= highestAutonomyCar(curr->root);
                while(temp->distance <= curr->distance+autonomy&&temp->distance<=arrivalPoint){
                    if(temp->distance==arrivalPoint){
                        temp->best=curr;
                        break;
                    }
                    if(temp->best==NULL){
                        temp->best=curr;
                        queue=addToQueue(queue,rear,temp);
                        rear++;
                    }

                    maxDistanceTouched=temp->distance;
                    temp=temp->next;
                }
        }
        Station *finalStation= searchStation(graph,arrivalPoint);
        if(finalStation->best==NULL){
            printf("nessun percorso\n");
        }
        else{
            int list[100];
            int i=-1,capacity=0;
            while(finalStation!=NULL&&finalStation->distance>=startingPoint){
                list[i++]=finalStation->distance;
                capacity++;
                finalStation=finalStation->best;
            }
            for(int j=1;j<capacity;j++){
                printf("%d ",list[capacity-j-1]);
            }
           // free(list);
        }
        free(queue);
        return ;
    }

    //precorso inverso
    else {
        Station *temp1=startingStation;
        //RESET BEST PATH
        while(temp1->distance>=arrivalPoint){
            temp1->best=NULL;
            temp1=temp1->prev;
        }
        while (front < rear) {
            Station *curr =queue[front++];
            Station *temp=curr->prev;
            int autonomy= highestAutonomyCar(curr->root);
            while(temp->distance >= curr->distance-autonomy&&temp->distance>=arrivalPoint){
                if(temp->best==NULL ){
                    temp->best=curr;
                    queue=addToQueue(queue,rear,temp);
                    rear++;
                }
                else if(curr->best!=temp->best){
                    temp->best=curr;
                }
                temp=temp->prev;
            }
        }
        Station *finalStation= searchStation(graph,arrivalPoint);
        if(finalStation->best==NULL){
            printf("nessun percorso\n");
        }
        else{
            int list[100];
            int i=0,capacity=1;
            while(finalStation!=NULL&&finalStation->distance<=startingPoint){
                list[i]=finalStation->distance;
                i++;
                capacity++;
                finalStation=finalStation->best;
            }
            for(int j=1;j<capacity;j++){
                printf("%d ",list[capacity-j-1]);
            }
            printf("\n");
            //free(list);
        }
        free(queue);
        return ;
    }

}


int main(){
    StationGraph *graph= (StationGraph *)malloc(sizeof (StationGraph));
    graph=newGraph(graph);
    int size=12;


    char command[12];
    char firstLetter,ambiguitySolver;
    do {
        if(fgets(command, size, stdin)==NULL)return 0;
        firstLetter = command[0];
        switch (firstLetter) {
            case 'a':{

                ambiguitySolver=command[9];
                //aggiungi-stazione
                if(ambiguitySolver=='s'){
                    shiftInput();
                    int distance, n_cars;
                  if(scanf("%d",&distance)<0);
                  getc(stdin);
                  if(scanf("%d",&n_cars)<0);
                  getc(stdin);
                  int cars[n_cars];
                  int i;
                  for(i=0;i<n_cars;i++){
                      if(scanf("%d",&cars[i]));
                      getc(stdin);
                  }
                    carTreeNode *root;
                    root = (struct carNode *) malloc(sizeof(struct carNode));
                    root->p=NULL;
                    root->right=NULL;
                    root->left=NULL;
                    root=createCarTree(cars,n_cars,root);
                    int size=graph->size;
                    graph= createStation(graph,distance,root);
                    if(graph->size==size+1) printf("aggiunta\n");
                    else printf("non aggiunta\n");
                    break;

                }
                //aggiungi-auto
                else if(ambiguitySolver=='a'){
                    shiftInput();
                    int distance,autonomy;
                    if(scanf("%d",&distance)<0);
                    getc(stdin);
                    if(scanf("%d",&autonomy)<0);
                    getc(stdin);
                    Station *station= searchStation(graph,distance);
                    if(station==NULL){
                        printf("non aggiunta\n");
                        break;
                    }
                    station->root= carInsert(station->root,autonomy,1);

                    break;
                }
                break;}
            case 'd':{

                shiftInput();
                int distance;
                if(scanf("%d",&distance)<0);
                getc(stdin);
                Station *station= searchStation(graph,distance);
                if(station==NULL){
                    printf("non demolita\n");
                    break;
                }
                graph= removeStation(graph,distance);
                break;

            }

            case 'r':{

                shiftInput();
                int distance,autonomy;
                if(scanf("%d",&distance)<0);
                getc(stdin);
                if(scanf("%d",&autonomy)<0);
                getc(stdin);
                Station *station= searchStation(graph,distance);
                if(station==NULL){
                    printf("non rottamata\n");
                    break;
                }
                if(searchCar(station->root,autonomy)==NULL)printf("non rottamata\n");
                else{
                    station->root=removeCar(station->root,autonomy);
                }
                break;
            }

            case 'p':{

                shiftInput();
                int start,end;
                if(scanf("%d",&start)<0);
                getc(stdin);
                if(scanf("%d",&end)<0);
                getc(stdin);
                if(searchStation(graph,start)==NULL|| searchStation(graph,end)==NULL){
                    printf("nessun percorso\n");
                    break;

                }
                bestPath(graph,start,end);
                break;
            }
            default:
                break;
        }
    }while(command!=NULL);
    return 0;
}
    //TODO Implementare grafi per stazione 90%
    //TODO Funzione aggiungi-stazione  80%
    //TODO Funzione demolisci-stazione 90%
    //TODO Funzione aggiungi-auto 80%
    //TODO Funzione rottama-auto 80%
    //TODO Funzione pianifica-percorso 0%
    //TODO funzione main 50%
