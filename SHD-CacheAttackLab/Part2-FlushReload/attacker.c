#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#include "util.h"


int main() {
    int flag = -1;

    // buf is shared between the attacker and the victim
    char *buf = allocate_shared_buffer();

    // [2.1] TODO: Put your capture-the-flag code here

    printf("Flag: %d\n", flag);

    deallocate_shared_buffer(buf);
    return 0;
}