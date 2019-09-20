/*
    WizIO 2019

        need for wolfSLL
*/


#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_

#ifdef __cplusplus
extern "C" {
#endif

// DONT USE - UNKNOWN STRUCT 
// musl/arch/arm/bits/stat.h
struct stat
{
#if 1
	int none;	
#else
	dev_t st_dev;
	int __st_dev_padding;
	long __st_ino_truncated;
	mode_t st_mode;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	dev_t st_rdev;
	int __st_rdev_padding;
	off_t st_size;
	blksize_t st_blksize;
	blkcnt_t st_blocks;
	struct timespec st_atim;
	struct timespec st_mtim;
	struct timespec st_ctim;
	ino_t st_ino;
#endif	
};

#ifdef __cplusplus
}
#endif

#endif /* !_SYS_STAT_H_ */