/* Copyright (c) 2014-2015, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#ifndef __MERKHET__
#define __MERKHET__


#include <stdint.h>
#include "platform.h"


#define chkret(ret,val) if(ret)return(val)
#if OS_WINDOWS
// Windows.h functions return non-zero if successful IN SPITEFUL DEFIANCE OF THE FUCKING C STANDARD
#define winchkret(ret,val) if(!ret)return(val)
#endif

#define MERKHET_OK       0
#define FAILURE         -1   // internal error
#define PLATFORM_ERROR  -10  // platform not supported


typedef double runtime_t;
typedef uint64_t microseconds_t;


// platform.c
#if OS_LINUX
int read_proc_self_stat(runtime_t *val, const int n);
#elif OS_WINDOWS
void FILETIMEtoULI(FILETIME *ft, ULARGE_INTEGER *uli);
runtime_t FILETIMEdiff(FILETIME *ft1, FILETIME *ft2);
#endif

// procinfo.c
int merkhet_process_usrtime(runtime_t *usr);
int merkhet_process_systime(runtime_t *sys);
int merkhet_process_runtime(runtime_t *runtime);

// sysinfo.c
int merkhet_system_uptime(runtime_t *uptime);


#endif
