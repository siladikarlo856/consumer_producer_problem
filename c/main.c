#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define SHARED 1

void *Producer(); //Make Declaration of Producer
void *Consumer(); //Make Declaration of Consumer

sem_t empty, full, sm; //Declare semaphores to be used
int data; // data variable

/**
 * @brief 
 * 
 * @return int 
 */
int main()
{
    pthread_t ptid, ctid; 
    printf("\nMain started");
    
    sem_init(&empty, SHARED, 1);
    sem_init(&full, SHARED, 0);
    sem_init(&sm, SHARED, 1);

    pthread_create(&ptid, NULL, Producer, NULL);
    pthread_create(&ctid, NULL, Consumer, NULL);

    pthread_join(ptid, NULL);
    pthread_join(ctid, NULL);
    
    printf("\nMain done\n");
    return 0;
}

void *Producer()
{
    const int MAX_PRODUCT_NUMBER = 10;
    const int NO_PRODUCT_NUMBER = 0;
    int produced;
    printf("\nProducer created");
    printf("\nProducer id is %ld\n", pthread_self());

    for(produced = NO_PRODUCT_NUMBER; produced < MAX_PRODUCT_NUMBER; produced++)
    {
        sem_wait(&empty);
        // LOCK starts
            sem_wait(&sm);
                // critical section starts
                    data = produced;
                // critical section ends
            sem_post(&sm);
        printf("\nProduced: %d", data);
        // LOCK ends
        sem_post(&full);
    }
}

void *Consumer()
{   
    const int NO_PRODUCT_NUMBER = 0;
    const int MAX_PRODUCT_NUMBER = 10;
    int consumed, total=0;
    printf("\nConsumer created");
    printf("\nConsumer id is %ld\n", pthread_self());

    for(consumed = NO_PRODUCT_NUMBER; consumed < MAX_PRODUCT_NUMBER; consumed++)
    {
        sem_wait(&full);
        // LOCK starts
            sem_wait(&sm);
                // CRITICAL SECTION STARTS
                    total = total + data;
                // CRITICAL SECTION ENDS
            sem_post(&sm);
            printf("\nConsumed: %d", data);
        // LOCK ends
        sem_post(&empty);
    }
}