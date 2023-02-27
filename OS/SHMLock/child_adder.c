
/* pshm_ucase_send.c

    Licensed under GNU General Public License v2 or later.
*/
#include <string.h>
#include "counter.h"

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s /shm-path\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *shmpath = argv[1];

    /* Open the existing shared memory object and map it
        into the caller's address space. */

    int fd = shm_open(shmpath, O_RDWR, 0);
    if (fd == -1)
        errExit("shm_open");

    struct shmbuf *shmp = mmap(NULL, sizeof(*shmp),
                                PROT_READ | PROT_WRITE,
                                MAP_SHARED, fd, 0);
    if (shmp == MAP_FAILED)
        errExit("mmap");

    /* Copy data into the shared memory object. */

    /* Tell peer that it can now access shared memory. */

    if (sem_post(&shmp->child_add_start) == -1)
        errExit("sem_post");

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

    printf("child job done\n");
    /* Wait until peer says that it has finished accessing
        the shared memory. */

    if (sem_post(&shmp->child_add_done) == -1)
        errExit("sem_wait");

    /* Write modified data in shared memory to standard output. */


    exit(EXIT_SUCCESS);
}