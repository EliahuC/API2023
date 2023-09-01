#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define HASH_SIZE 35000

typedef struct Car{
    int key;
    struct Car *next;
}Car;

typedef struct CarList {
    Car *list;
    Car *startingCar;
    Car *last;
    int size;
    int max;
} carTreeList ;


typedef struct Station{
    int distance;
    carTreeList* list;
    struct Station* next;
    struct Station* prev;
    struct Station* best;

}Station;

typedef struct Graph{
    Station* head;
    int size;
    Station *startingPoint;
    int skip_list[50];

}StationGraph;

typedef struct MapNode{
    int key;
    Station *station;
    struct MapNode *next;
}MapNode;

typedef struct HashMap{
    struct MapNode *buckets[HASH_SIZE];
}HashMap;
/**
 * Checks if the station is already in the temp (search function)
 * @param temp of the stations
 * @param distance of the station
 * @return true if there isn't any station with key==distance
 */

carTreeList *carInsert(carTreeList *cars, int autonomy, int i);

bool searchCar(carTreeList *cars, int autonomy);

carTreeList *removeCar(carTreeList *cars, int autonomy);


StationGraph *reorderList(StationGraph *graph);

int getInt(){
        int numero=0;
        char c;
        while (1) {
            c = getc(stdin);
            if (c >= '0' && c <= '9') {
                numero = numero * 10 + (c - '0');
            } else {
                break;
            }
        }


        return numero;
    }


Station * searchStation(HashMap *map,int start){
    MapNode *node=map->buckets[start%HASH_SIZE];
    while(node!=NULL){
        if(node->key==start)return node->station;
        node=node->next;
    }
    if(node==NULL)return NULL;
    if(node->key==start)return node->station;
    return NULL;


}

StationGraph* addStation(HashMap *map,Station *x, StationGraph *graph){
    graph->head=graph->startingPoint;
    int skips=graph->size/1000;
    int i=1;
    while(i<=skips){
        if(x->distance>graph->skip_list[i]) {
            graph->head = searchStation(map, graph->skip_list[i]);

        }
        i++;
    }
    while(graph->head->distance<x->distance && graph->head->next!=NULL){
        graph->head=graph->head->next;

    }

//case 1 : exit from while because next=null
    if(graph->head->next==NULL){
        if(graph->head->distance>x->distance){
            graph->head->prev->next=x;
            x->prev=graph->head->prev;
            graph->head->prev=x;
            x->next=graph->head;
        }
        else{
            x->prev=graph->head;
            graph->head->next=x;
        }
    }
//case 2 : exit from while because graph.head.distance>x.distance
    else{
        graph->head->prev->next=x;
        x->prev=graph->head->prev;
        graph->head->prev=x;
        x->next=graph->head;
    }

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
StationGraph * createStation(HashMap *map,StationGraph *graph, int distance, carTreeList* root){


    if(searchStation(map/*graph*/,distance)==NULL){
        Station *x = (Station *) malloc(sizeof(Station));

        x->list=root;
        x->distance=distance;
        x->prev=NULL;
        x->next=NULL;
        x->best=NULL;
        if(graph->size==0){
            graph->head->next=x;
            graph->head->next->prev=graph->head;
            graph->size++;
            //graph->head=graph->startingPoint;
            MapNode *node=map->buckets[x->distance % HASH_SIZE];
            MapNode *newNode=(struct MapNode*) malloc(sizeof (MapNode));
            newNode->key=distance;
            newNode->next=node;
            newNode->station=x;
            map->buckets[x->distance % HASH_SIZE]=newNode;
            return graph;
        }
        graph=addStation(map,x,graph);
        MapNode *node=map->buckets[x->distance % HASH_SIZE];
        MapNode *newNode=(struct MapNode*) malloc(sizeof (MapNode));
        newNode->key=distance;
        newNode->next=node;
        newNode->station=x;
        map->buckets[x->distance % HASH_SIZE]=newNode;
        graph->size++;
        if(graph->size%1000==0){
            graph->skip_list[graph->size/1000]=x->distance;
            graph=reorderList(graph);
        }


        return graph;
    }
    return graph;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

StationGraph *reorderList(StationGraph *graph) {
    int elements=graph->size/1000;
    int temp[elements+1];
    for(int i=0;i<=elements;i++){
      temp[i]=graph->skip_list[i] ;
    }
    qsort(temp,elements+1,sizeof(int),compare);
    for(int i=0;i<=elements;i++){
        graph->skip_list[i]=temp[i] ;
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
    x->list=NULL;
    x->next=NULL;
    x->prev=NULL;
    x->best=NULL;
    graph->head=x;
    graph->startingPoint=x;
    for(int i=0;i<50;i++){
        graph->skip_list[i]=-1;
    }
    graph->skip_list[0]=0;

    return graph;

}

/**
 * Function to remove a station
 * @param graph of the stations
 * @param distance of the station to remove
 * @return the updated graph
 */
StationGraph* removeStation(HashMap *map,StationGraph *graph,int distance){
   // if(graph->head->distance>distance)graph->head=graph->startingPoint;
    StationGraph *temp_graph=graph;
   /* while (temp_graph->head->distance<distance){
        temp_graph->head=temp_graph->head->next;
    }*/
    temp_graph->head= searchStation(map,distance);
    temp_graph->head->prev->next=temp_graph->head->next;
    if(temp_graph->head->next!=NULL){
        temp_graph->head->next->prev=temp_graph->head->prev;
    }
    int skips=graph->size/1000;
    for(int i =0;i<=skips;i++){
        if(graph->skip_list[i]==distance){
            graph->skip_list[i]= searchStation(map,distance)->prev->distance;
            graph= reorderList(graph);
            break;
        }
    }


     Station *s=graph->head;
     MapNode *node=map->buckets[s->distance%HASH_SIZE];
     MapNode *prev=node;
     while(node!=NULL){
       if(node->key==s->distance) break;
       prev=node;
       node=node->next;
     }
     if(prev==node){
         map->buckets[prev->key % HASH_SIZE]=prev->next;
     }
     prev->next=node->next;
    //free(s->list);
   // free(s);
    //free(node);
    printf("demolita\n");
   // graph->head=graph->startingPoint;
    graph->size--;
    return graph;


}

void shiftInput(){
    char input;
    input= getc(stdin);
    while(input!=' ' ){
        input= getc(stdin);
    }
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
void bestPath(HashMap *map,StationGraph *graph,int startingPoint,int arrivalPoint){

    Station *startingStation=searchStation(map,startingPoint);



    //percorso diretto
    if(startingPoint<arrivalPoint){
        Station* *queue =(Station **) malloc(sizeof(Station) * graph->size);
        int front = 0;
        int rear = 0;
        queue[rear++] = startingStation;
        Station *temp1=startingStation;

        int maxDistanceTouched=startingStation->distance;
        while (front < rear && maxDistanceTouched < arrivalPoint) {
            Station *curr =queue[front++];
            Station *temp=curr->next;
            int autonomy= curr->list->max;
            while(temp!=NULL&&temp->distance <= curr->distance+autonomy&&temp->distance<=arrivalPoint){

                if(temp->best==NULL){
                    temp->best=curr;
                    queue=addToQueue(queue,rear,temp);
                    rear++;
                }

                maxDistanceTouched=temp->distance;
                temp=temp->next;
            }
        }
        Station *finalStation= searchStation(map,arrivalPoint);
        if(finalStation->best==NULL){
            printf("nessun percorso\n");
        }
        else{
            int list[100];
            int i=0,capacity=1;
            while(finalStation!=NULL&&finalStation->distance>=startingPoint){
                list[i++]=finalStation->distance;
                capacity++;
                finalStation=finalStation->best;
            }
            for(int j=1;j<capacity-1;j++){
                printf("%d ",list[capacity-j-1]);
            }
            printf("%d\n",list[0]);

        }
        // free(queue);
        //RESET BEST PATH
        while(temp1!=NULL&&temp1->distance<=arrivalPoint){
            temp1->best=NULL;
            temp1=temp1->next;

        }
        graph->head=graph->startingPoint;
        return ;
    }
        //precorso inverso
    else {



        Station* *pilaNext =(Station **) malloc(sizeof(Station) * graph->size);
        Station* *pilaCurr =(Station **) malloc(sizeof(Station) * graph->size);
        int topPilaNext=-1;
        int topPilaCurr=0;
        pilaCurr[topPilaCurr]=startingStation;
        int lastTouched=startingPoint;
        Station *temp=startingStation->prev;
        while((topPilaCurr!=-1||topPilaNext!=-1)&&lastTouched!=arrivalPoint){
            if(topPilaCurr==-1){
                int i;
                int toCopy=topPilaNext;
                for(i=0;i<=toCopy;i++){
                    pilaCurr[i]=pilaNext[i];
                    pilaNext[i]=NULL;
                }
                topPilaCurr=topPilaNext;
                topPilaNext=-1;
            }
            Station *curr =pilaCurr[topPilaCurr];
            pilaCurr[topPilaCurr]=NULL;
            topPilaCurr--;

            int autonomy= curr->list->max;
            while(temp->distance >= curr->distance-autonomy&&temp->distance>=arrivalPoint){

                temp->best=curr;
                topPilaNext++;
                pilaNext[topPilaNext]=temp;
                lastTouched=temp->distance;

                temp=temp->prev;
            }
        }
        Station *finalStation= searchStation(map,arrivalPoint);
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
            for(int j=1;j<capacity-1;j++){
                printf("%d ",list[capacity-j-1]);
            }
            printf("%d\n",list[0]);
             //free(pilaNext);
           // free(pilaCurr);

            Station *temp1=startingStation;
            //RESET BEST PATH
            while(temp1->distance>=arrivalPoint){
                temp1->best=NULL;
                temp1=temp1->prev;
            }

        }
        graph->head=graph->startingPoint;
        return ;
    }


}

int main(){
    HashMap *map=(struct HashMap*) malloc(sizeof (struct HashMap));

    for(int i=0; i<HASH_SIZE;i++){
        map->buckets[i]=NULL;
    }

    StationGraph *graph= (StationGraph *)malloc(sizeof (StationGraph));
    graph=newGraph(graph);
    int size=12;


    char command[12];
    char firstLetter,ambiguitySolver;
    do {
        if(fgets(command, size, stdin)==NULL){
            return 0;
        }
        firstLetter = command[0];
        switch (firstLetter) {
            case 'a':{

                ambiguitySolver=command[9];
                //aggiungi-stazione
                if(ambiguitySolver=='s'){
                    shiftInput();
                    int distance, n_cars;
                    distance=getInt();
                    n_cars=getInt();
                    carTreeList *cars;
                    cars = (struct CarList *) malloc(sizeof(struct CarList));
                    cars->size=n_cars;
                    cars->max=-1;
                    Car *starter=(struct Car*) malloc(sizeof (struct Car));
                    starter->key=-1;
                    starter->next=NULL;
                    cars->startingCar=starter;
                    cars->list=starter;
                    int i;
                    for(i=0;i<n_cars;i++){
                        int key_;
                        key_=getInt();
                        Car *new=(struct Car*) malloc(sizeof (struct Car));
                        cars->list->next=new;
                        new->key=key_;
                        new->next=NULL;
                        cars->list=cars->list->next;
                        if(key_>cars->max)cars->max=cars->list->key;

                    }
                    cars->last=cars->list;
                    if(cars->size==0)cars->max=0;

                    int size_=graph->size;
                    graph= createStation(map,graph, distance, cars);
                    if(graph->size==size_+1) printf("aggiunta\n");
                    else printf("non aggiunta\n");
                    break;

                }
                    //aggiungi-auto
                else if(ambiguitySolver=='a'){
                    shiftInput();
                    int distance,autonomy;
                    distance=getInt();

                    autonomy=getInt();

                    Station *station= searchStation(map,distance);
                    if(station==NULL){
                        printf("non aggiunta\n");
                        break;
                    }
                    station->list= carInsert(station->list, autonomy, 1);
                    break;
                }
                break;}
            case 'd':{

                shiftInput();
                int distance;
                distance=getInt();
                Station *station= searchStation(map,distance);
                if(station==NULL){
                    printf("non demolita\n");
                    break;
                }
                graph= removeStation(map,graph,distance);
                break;

            }

            case 'r':{

                shiftInput();
                int distance,autonomy;
                distance=getInt();
                autonomy=getInt();
                Station *station= searchStation(map,distance);
                if(station==NULL){
                    printf("non rottamata\n");
                    break;
                }
                if(!searchCar(station->list, autonomy))printf("non rottamata\n");
                else{
                    station->list=removeCar(station->list, autonomy);
                }
                break;
            }

            case 'p':{

                shiftInput();
                int start,end;
                start=getInt();
                end=getInt();
                if(searchStation(map,start)==NULL|| searchStation(map,end)==NULL){
                    printf("nessun percorso\n");
                    break;

                }
                bestPath(map,graph,start,end);
                break;
            }
            default:
                break;
        }
    }while(command!=NULL);
}

carTreeList *removeCar(carTreeList *cars, int autonomy) {
    cars->list=cars->startingCar;
    Car *prev=NULL;
    while(cars->list->key != autonomy && cars->list->next != NULL){
        prev=cars->list;
        cars->list=cars->list->next;
    }
    prev->next=cars->list->next;
    if(cars->list==cars->last)cars->last=prev;
    cars->size--;
   //  Car *to_del=cars->list;
    cars->list=cars->startingCar;
    // free(to_del);
    if(cars->max==autonomy){
        cars->max=-1;
        while(cars->list->next!=NULL) {
            if (cars->max < cars->list->key)cars->max = cars->list->key;
            cars->list=cars->list->next;
        }
    }
    cars->list=cars->startingCar;
    printf("rottamata\n");
    return cars;
}

bool searchCar(carTreeList *cars, int autonomy) {
    cars->list=cars->startingCar;
    while(cars->list->next != NULL){
        if(cars->list->key==autonomy){
            return true;
        }
        cars->list=cars->list->next;
    }
    if(cars->list->key==autonomy){
        return true;
    }
    return false;
}

carTreeList *carInsert(carTreeList *cars, int autonomy, int i) {

    Car *newCar=(struct Car*) malloc(sizeof (struct Car));
    newCar->key=autonomy;
    newCar->next=NULL;
    cars->size++;
    cars->last->next=newCar;
    cars->last=newCar;
    cars->list=cars->last;
    if(autonomy>cars->max)cars->max=autonomy;
    if(i==1)printf("aggiunta\n");
    return cars;
}

