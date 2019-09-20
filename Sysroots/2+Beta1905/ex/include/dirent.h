/*
    WizIO 2019
    
        need for wolfSLL
*/

#ifndef _DIRENT_H
#define _DIRENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

// UNKNOW STRUCT
struct __dirstream      
{
	int fd;             
	off_t tell;         
	int buf_pos;        
	int buf_end;        
	int lock[2];        
	char buf[2048];     
};

typedef struct __dirstream DIR;

#define DT_UNKNOWN 0
#define DT_FIFO 1
#define DT_CHR 2
#define DT_DIR 4
#define DT_BLK 6
#define DT_REG 8
#define DT_LNK 10
#define DT_SOCK 12
#define DT_WHT 14

// UNKNOW STRUCT
struct dirent
{
	unsigned int ino;
	unsigned int off;
	unsigned short len;	
	char name[256];     // UNKNOW size
    unsigned char type;
};

int            closedir(DIR *);
DIR           *fdopendir(int);
DIR           *opendir(const char *);
struct dirent *readdir(DIR *);
int            readdir_r(DIR *__restrict, struct dirent *__restrict, struct dirent **__restrict);
void           rewinddir(DIR *);
void           seekdir(DIR *, long);
long           telldir(DIR *);
int            dirfd(DIR *);


#ifdef __cplusplus
}
#endif

#endif