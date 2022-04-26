#include <pthread.h>
#include <semaphore.h>

class monitorClass{
    public:
        // primitives for synchronizing access
        pthread_mutex_t bufferLock;
        pthread_cond_t condVarPro;
        pthread_cond_t condVarCon;
        sem_t bufferEmpty;
        sem_t bufferFull;
        // buffer
        int dataBuffer[10];
        int bufferSpaces;
        bool fullBool, emptyBool;
        int count = 0;
        // variables for circling through buffer
        int pos = 0;
        int output = 0;
};

void *Producer(void *paramPro);
void *Consumer(void *paramCon);