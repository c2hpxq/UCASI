#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "rwlock.h"

#define NR 7
#define WGOAL 1000000
#define RGRANU 1000
#define WGRANU 100

rwlock_t rwu;
int counter = 0;
int shared_content = 0;

void *read_routine(void *arg) {

    int x;
    while (counter < WGOAL) {
        rwlock_acquire_readlock(&rwu);
        for (int i = 0; i < RGRANU; i++) {
            x = shared_content;
        }
        //printf("read\n");
        rwlock_release_readlock(&rwu);
    }

    return NULL;

}

int main() {

    rwlock_init(&rwu);

    pthread_t reader[NR];
    for (int i = 0; i < NR; i++) {
        pthread_create(&reader[i], NULL, read_routine, NULL);
    }

    printf("write starts.\n");
    while (counter < WGOAL) {
        rwlock_acquire_writelock(&rwu);
        for (int i = 0; i < WGRANU; i++) {
            shared_content += rand();
        }
        counter++;
        //if (counter%100 == 0) {
        //    printf("%d\n", counter);
        //}
        rwlock_release_writelock(&rwu);
    }

    return 0;
}