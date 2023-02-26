#ifndef A4CC471C_8362_4D3E_A84C_807C8A0A7E5F
#define A4CC471C_8362_4D3E_A84C_807C8A0A7E5F

#include <semaphore.h>

typedef struct _rwlock_t {
    sem_t lock;
    sem_t write_lock;
#ifdef FAIR
    int write_pending;
#endif
    int readers;
} rwlock_t;

void rwlock_init(rwlock_t *rw);
void rwlock_acquire_readlock(rwlock_t *rw);
void rwlock_release_readlock(rwlock_t *rw);
void rwlock_acquire_writelock(rwlock_t *rw);
void rwlock_release_writelock(rwlock_t *rw);


#endif /* A4CC471C_8362_4D3E_A84C_807C8A0A7E5F */
