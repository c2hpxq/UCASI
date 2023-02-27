#ifndef E376F56E_0CA1_46C6_BC57_C7F4C023415E
#define E376F56E_0CA1_46C6_BC57_C7F4C023415E

#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define n 50000000

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

#define BUF_SIZE 1024   /* Maximum size for exchanged string */

/* Define a structure that will be imposed on the shared
    memory object */

struct shmbuf {
    pthread_mutex_t  lock;            
    sem_t  child_add_done;            /* POSIX unnamed semaphore */
    sem_t  child_add_start;            /* POSIX unnamed semaphore */
    volatile int cnt;             /* Number of bytes used in 'buf' */
};

#endif /* E376F56E_0CA1_46C6_BC57_C7F4C023415E */
