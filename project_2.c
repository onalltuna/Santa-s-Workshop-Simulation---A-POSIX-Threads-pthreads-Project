#include "queue.c"
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

int simulationTime = 120;    // simulation time
int seed = 10;               // seed for randomness
int emergencyFrequency = 30; // frequency of emergency gift requests from New Zealand

void* ElfA(void *arg); // the one that can paint
void* ElfB(void *arg); // the one that can assemble
void* Santa(void *arg); 
void* ControlThread(void *arg); // handles printing and queues (up to you)

// pthread sleeper function
int pthread_sleep (int seconds)
{
    pthread_mutex_t mutex;
    pthread_cond_t conditionvar;
    struct timespec timetoexpire;
    if(pthread_mutex_init(&mutex,NULL))
    {
        return -1;
    }
    if(pthread_cond_init(&conditionvar,NULL))
    {
        return -1;
    }
    struct timeval tp;
    //When to expire is an absolute time, so get the current time and add it to our delay time
    gettimeofday(&tp, NULL);
    timetoexpire.tv_sec = tp.tv_sec + seconds; 
    timetoexpire.tv_nsec = tp.tv_usec * 1000;
    
    pthread_mutex_lock(&mutex);
    int res =  pthread_cond_timedwait(&conditionvar, &mutex, &timetoexpire);
    pthread_mutex_unlock(&mutex);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&conditionvar);
    
    //Upon successful completion, a value of zero shall be returned
    return res;
}
struct thread_data
{
   int	thread_id;
   int  sum;
   char *message;
};

// Queues
 Queue *packageQueue;
 Queue *deliveryQueue;
 Queue *paintQueue;
 Queue *assambleQueue;
 Queue *qAQueue;

 //mutexes
 pthread_mutex_t packageMutex;
 pthread_mutex_t deliveryMutex;

 int keepGoing = 1;

 FILE *simulationResult;


int main(int argc,char **argv){
    // -t (int) => simulation time in seconds
    // -s (int) => change the random seed
    for(int i=1; i<argc; i++){
            if(!strcmp(argv[i], "-t")) {simulationTime = atoi(argv[++i]);}
        else if(!strcmp(argv[i], "-s"))  {seed = atoi(argv[++i]);}
    }

    if (pthread_mutex_init(&packageMutex, NULL))   { 
        printf("\nInitiliazing mutex error.\n"); 
        return 1; 
   } 

    //keep track of task ID
    // int taskID = 1;


    struct thread_data data;
    data.sum = 5;

    pthread_t threads[2];
    int rc;
    // long t;
    rc = pthread_create(&threads[0], NULL, ElfA,NULL);
    if (rc) {
        printf("HERE\n");

         exit(-1);
      }
    // rc = pthread_create(&threads[1], NULL, *(ElfB), NULL);
    // rc = pthread_create(&threads[2], NULL, *(Santa), NULL);
    rc = pthread_create(&threads[1], NULL, ControlThread, NULL);
    if (rc) {
        printf("HERE\n");

         exit(-1);
      }

    // Current and finish time to hold the total execution time
//     struct timeval currentTime;
//     gettimeofday(&currentTime, NULL);
//     struct timespec finishTime;
//     finishTime.tv_sec = currentTime.tv_sec + simulationTime;

//     //random variable to decide gift types
//     int ran1;
//     int ran2 = 0;

//     /* Queue usage example
//        Queue *myQ = ConstructQueue(1000);
//        Task t;
//        t.ID = myID;
//        t.type = 2;
//        Enqueue(myQ, t);
//        Task ret = Dequeue(myQ);
//        DestructQueue(myQ);
//    */

    packageQueue = ConstructQueue(1000);
    deliveryQueue = ConstructQueue(1000);
    
    
//     pthread_sleep(1);

//     // until reach the execution time:
//     while (finishTime.tv_sec != currentTime.tv_sec)
//     {
    

    
//     // printf("CurrentTime : %ld\n", currentTime.tv_sec);
//     // sleep(3);
    
//     srand(seed + ran2); // feed the seed
//     ran1 = rand() % 10;
//     // printf("Rand: %d\n",ran1);

//     if(ran1 == 0)
//     {
//         printf("Bad kid! :-()\n");
//     }
//     else if(ran1 == 1 ||ran1 == 2 ||ran1 == 3 ||ran1 == 4)
//     {
//         // printf("Okay kid\n");
//         Task t;
//         t.ID = taskID;
//         taskID++;
//         t.type = 0;
//         pthread_mutex_lock(&packageMutex);
//         Enqueue(packageQueue, t);
//         pthread_mutex_unlock(&packageMutex);
//             pthread_sleep(1);

//         printf("Size: %d\n",packageQueue->size);
//     }
    
   

//     // // your code goes here
//     // // you can simulate gift request creation in here, 
//     // // but make sure to launch the threads first

//     ran2++;
//     // pthread_sleep(1);
//     gettimeofday(&currentTime, NULL);
//     // printf("CurrentTime : %ld\n", currentTime.tv_sec);
//     }

    for (int i = 0; i < 2; i++) {
        int* r;
        if (pthread_join(threads[i], (void**) &r) != 0) {
            perror("Failed to join thread");
        }
        
        // free(r);
    }
    pthread_mutex_destroy(&packageMutex); 
   
    return 0;
}



void* ElfA(void *arg){
    printf("HEREe\n");

    
    // simulationResult = fopen("./simulationResult.log", "w");

    // pthread_mutex_lock(&packageMutex);
    // printf("id: %d\n", packageQueue->size);
    // pthread_mutex_unlock(&packageMutex);

    struct timeval currentTime;

    while (keepGoing)
    {
        while(packageQueue->size != 0)
        {
            pthread_mutex_lock(&packageMutex);
            Task a = Dequeue(packageQueue);
            pthread_mutex_unlock(&packageMutex);
            printf("id: %d\n", a.ID);
            pthread_sleep(1);
            gettimeofday(&currentTime, NULL);
            a.turnAround = currentTime.tv_sec - a.taskArrival;

            fprintf(simulationResult,
            "%d             %d          %c              %d           %d         %d         %d              %c\n"
            ,a.ID, a.giftID, a.type, a.giftType, a.requestTime, a.taskArrival, a.turnAround, 'A');



        }
        
   
    }

    // int taskid, sum;
    // char *hello_msg;
    // struct thread_data *my_data;

    // sleep(1);
    // my_data = (struct thread_data *)arg;
    // // taskid = my_data->thread_id;
    // sum = my_data->sum;
    // printf("Sum is: %d\n",sum);
    // // hello_msg = my_data->message;
    // // printf("Thread %d: %s  Sum=%d\n", taskid, hello_msg, sum);

    // // while (TRUE)
    // // {
    // //     printf("Inside of ElfA\n");
    // //     printf("%c",arg[0]);
    // //     pthread_sleep(3);
    // // }

}

void* ElfB(void *arg){
    printf("Inside of ElfB\n");
}

// manages Santa's tasks
void* Santa(void *arg){

}

// the function that controls queues and output
void* ControlThread(void *arg){
    printf("HEREt\n");


    // FILE *simulationResult;
    simulationResult = fopen("./simulationResult.log", "w");
    fprintf(simulationResult, 
    "TaskID     GiftID     GiftType      TaskType      RequestTime        TaskArrival     TT      Responsable\n");
    fprintf(simulationResult,"____________________________________________________________________________________________________________\n");


    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    struct timespec finishTime;
    finishTime.tv_sec = currentTime.tv_sec + simulationTime;

    //random variable to decide gift types
    int ran1;
    int ran2 = 0;
    int taskID = 1;
    int giftID = 1;

    keepGoing = 1;
    // pthread_sleep(1);
    // until reach the execution time:
    while (finishTime.tv_sec != currentTime.tv_sec)
    {
    
    srand(seed + ran2); // feed the seed
    ran1 = rand() % 10;
    // // printf("Rand: %d\n",ran1);

    if(ran1 == 0)
    {
        printf("Bad kid! :-()\n");
    }
    else if(ran1 == 1 ||ran1 == 2 ||ran1 == 3 ||ran1 == 4)
    {
        // printf("Okay kid\n");
        Task t;
        t.ID = taskID;
        taskID++;
        t.type = 'C';
        t.giftID = giftID;
        giftID++;
        t.giftType = 1;
        gettimeofday(&currentTime, NULL);
        t.requestTime = currentTime.tv_sec;
        t.taskArrival = currentTime.tv_sec;

        pthread_mutex_lock(&packageMutex);
        Enqueue(packageQueue, t);
        pthread_mutex_unlock(&packageMutex);
        // pthread_sleep(1);

        printf("Size: %d\n",packageQueue->size);
    }
    
   

    // // // your code goes here
    // // // you can simulate gift request creation in here, 
    // // // but make sure to launch the threads first

    ran2++;
    pthread_sleep(1);
    gettimeofday(&currentTime, NULL);
    // printf("CurrentTime : %ld\n", currentTime.tv_sec);
    }
    keepGoing = 0;
    pthread_exit(0);



}