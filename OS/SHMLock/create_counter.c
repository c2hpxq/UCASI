/* pshm_ucase_bounce.c

    Licensed under GNU General Public License v2 or later.
*/
#include <ctype.h>
#include "counter.h"

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s /shm-path\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *shmpath = argv[1];
    //goto label;

    /* Create shared memory object and set its size to the size
        of our structure. */

    int fd = shm_open(shmpath, O_CREAT | O_EXCL | O_RDWR,
                        S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("shm_open");

    if (ftruncate(fd, sizeof(struct shmbuf)) == -1)
        errExit("ftruncate");

    /* Map the object into the caller's address space. */

    struct shmbuf *shmp = mmap(NULL, sizeof(*shmp),
                                PROT_READ | PROT_WRITE,
                                MAP_SHARED, fd, 0);
    if (shmp == MAP_FAILED)
        errExit("mmap");

    /* Initialize semaphores as process-shared, with value 0. */

    if (sem_init(&shmp->child_add_done, 1, 0) == -1)
        errExit("sem_init-sem1");

    if (sem_init(&shmp->child_add_start, 1, 0) == -1)
        errExit("sem_init-sem1");

    
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&shmp->lock, &attr);

    printf("parent init done\n");
    
    if (sem_wait(&shmp->child_add_start) == -1)
        errExit("sem_wait");

    printf("I add %d to counter\n", n);
    for (int i = 0; i < n; ++i) {
#ifdef NOLOCK
        ++shmp->cnt;
#else
        pthread_mutex_lock(&shmp->lock);
        ++shmp->cnt;
        pthread_mutex_unlock(&shmp->lock);
#endif
    }

    if (sem_wait(&shmp->child_add_done) == -1)
        errExit("sem_wait");

    printf("final count: %d\n", shmp->cnt);

    /* Unlink the shared memory object. Even if the peer process
        is still using the object, this is okay. The object will
        be removed only after all open references are closed. */

label:
    shm_unlink(shmpath);

    exit(EXIT_SUCCESS);
}
