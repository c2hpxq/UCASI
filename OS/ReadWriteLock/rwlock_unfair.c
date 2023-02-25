#include <semaphore.h>

typedef struct _rwlock_unfair_t {
    sem_t lock;
    sem_t write_lock;
    int readers;
} rwlock_unfair_t;

void rwlock_unfair_init(rwlock_unfair_t *rw) {
    rw->readers = 0;
    sem_init(&rw->lock, 0, 1);
    sem_init(&rw->write_lock, 0, 1);
}

void rwlock_unfair_acquire_readlock(rwlock_unfair_t *rw) {
    sem_wait(&rw->lock);

    rw->readers++;
    // 0->1, 1st reader acquires write_lock
    if (rw->readers == 1) { sem_wait(&rw->write_lock); }

    sem_post(&rw->lock);
}

void rwlock_unfair_release_readlock(rwlock_unfair_t *rw) {
    sem_wait(&rw->lock);

    rw->readers--;
    // 1->0, last reader releases write_lock
    if (rw->readers == 0) { sem_post(&rw->write_lock); }

    sem_post(&rw->lock);
}

void rwlock_unfair_acquire_writelock(rwlock_unfair_t *rw) {
    sem_wait(&rw->write_lock);
}

void rwlock_unfair_release_writelock(rwlock_unfair_t *rw) {
    sem_post(&rw->write_lock);
}