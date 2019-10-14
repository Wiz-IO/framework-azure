#include <stdio.h>

void retarget(int fd, void *file, int ex)
{
    *(int *)((char *)file + 60) = fd;
    if (ex)
        setvbuf(file, NULL, _IONBF, 0);
}