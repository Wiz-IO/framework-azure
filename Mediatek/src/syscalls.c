#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

void __attribute__((weak)) LogToUart(const char *format, ...);
void __attribute__((weak)) mon_putchar(char c); /* used for OS_DEBUG */

#undef errno
extern int errno;
extern int _end;

void abort(void)
{
    LogToUart("[ABORT]\n");
    while (1)
        ;
}

void _exit(int status) { abort(); }

caddr_t _sbrk(int incr) { return (caddr_t)-1; }

void _kill(int pid, int sig) { return; }

int _getpid(void) { return -1; }

int _getpid_r(void) { return -1; }

int link(const char *old, const char *new) { return -1; }

int _close(int file) { return -1; }

int _read(int file, char *ptr, int len) { return 0; }

/* enable OS_DEBUG */
#ifdef RETARGET

int _write(int file, char *buf, int nbytes)
{
    /* We only handle stdout and stderr */
    if ((file != STDOUT_FILENO) && (file != STDERR_FILENO))
    {
        errno = EBADF;
        return -1;
    }
    /* Output character at at time */
    for (int i = 0; i < nbytes; i++)
        mon_putchar(buf[i]);
    return nbytes;
}

int _fstat(int file, struct stat *st)
{
    if ((STDOUT_FILENO == file) || (STDERR_FILENO == file))
    {
        st->st_mode = S_IFCHR;
        return 0;
    }
    else
    {
        errno = EBADF;
        return -1;
    }
}

int _isatty(int file)
{
    if ((file == STDOUT_FILENO) || (file == STDERR_FILENO))
    {
        return 1;
    }
    else
    {
        errno = EBADF;
        return -1;
    }
}

int _lseek(int file, int offset, int whence)
{
    if ((STDOUT_FILENO == file) || (STDERR_FILENO == file))
    {
        return 0;
    }
    else
    {
        errno = EBADF;
        return (long)-1;
    }
}

#else

int _write(int file, char *buf, int nbytes) { return 0; }
int _fstat(int file, struct stat *st) { return -1; }
int _isatty(int file) { return -1; }
int _lseek(int file, int offset, int whence) { return (long)-1; }

#endif
