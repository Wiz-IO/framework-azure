#ifndef	_SYS_MMAN_H
#define	_SYS_MMAN_H
#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>

#include <bits/alltypes.h>


#ifdef _GNU_SOURCE
#define MFD_CLOEXEC 0x0001U
#define MFD_ALLOW_SEALING 0x0002U
#define MFD_HUGETLB 0x0004U
#endif

#include <bits/mman.h>

#ifdef _GNU_SOURCE
int memfd_create (const char *, unsigned);
#endif


#ifdef __cplusplus
}
#endif
#endif
