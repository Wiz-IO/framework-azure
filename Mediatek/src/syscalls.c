#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>

#undef errno
extern int errno;
extern int _end;

extern caddr_t _sbrk(int incr);
extern int link(char *old, char *new);
extern int _close(int file);
extern int _fstat(int file, struct stat *st);
extern int _isatty(int file);
extern int _lseek(int file, int ptr, int dir);
extern void _exit(int status);
extern void _kill(int pid, int sig);
extern int _getpid(void);

extern caddr_t _sbrk(int incr)
{
    return (caddr_t)-1;
}

extern int link(char *old, char *new)
{
    return -1;
}

extern int _close(int file)
{
    return -1;
}

extern int _fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;

    return 0;
}

extern int _isatty(int file)
{
    return 1;
}

extern int _lseek(int file, int ptr, int dir)
{
    return 0;
}

extern void _exit(int status)
{
    for (;;)
    {
    }
}

extern void _kill(int pid, int sig)
{
    return;
}

extern int _getpid(void)
{
    return -1;
}

void STD_Init(void) {

}
