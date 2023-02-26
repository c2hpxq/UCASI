// mostly from OSTEP
#include <semaphore.h>
#include "rwlock.h"

void rwlock_init(rwlock_t *rw) {
    rw->readers = 0;
    sem_init(&rw->lock, 0, 1);
    sem_init(&rw->write_lock, 0, 1);
#ifdef FAIR
    rw->write_pending = 1;
#endif
}

void rwlock_acquire_readlock(rwlock_t *rw) {
#ifdef FAIR
    while (rw->write_pending) {}
#endif
    sem_wait(&rw->lock);

    rw->readers++;
    // 0->1, 1st reader acquires write_lock
    if (rw->readers == 1) { sem_wait(&rw->write_lock); }

    sem_post(&rw->lock);
}

void rwlock_release_readlock(rwlock_t *rw) {
    sem_wait(&rw->lock);

    rw->readers--;
    // 1->0, last reader releases write_lock
    if (rw->readers == 0) { sem_post(&rw->write_lock); }

    sem_post(&rw->lock);
}

void rwlock_acquire_writelock(rwlock_t *rw) {
#ifdef FAIR
    rw->write_pending = 1;
#endif
    sem_wait(&rw->write_lock);
#ifdef FAIR
    rw->write_pending = 0;
#endif
}

void rwlock_release_writelock(rwlock_t *rw) {
    sem_post(&rw->write_lock);
}