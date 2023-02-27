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
    
    shm_unlink(shmpath);

    exit(EXIT_SUCCESS);
}
