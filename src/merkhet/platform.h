/* Copyright (c) 2014-2017, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#ifndef __MERKHET_PLATFORM__
#define __MERKHET_PLATFORM__


// "portability"
#if (defined(__gnu_linux__) || defined(__linux__) || defined(__linux))
#define OS_LINUX 1
#else
#define OS_LINUX 0
#endif

#if (defined(__WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(__WIN64) || defined(__WIN64__) || defined(__TOS_WIN__) || defined(__WINNT) || defined(__WINNT__))
#define OS_WINDOWS 1
#else
#define OS_WINDOWS 0
#endif

#if (defined(__APPLE__) && defined(__MACH__))
#define OS_MAC 1
#else
#define OS_MAC 0
#endif

#if (defined(__FreeBSD__))
#define OS_FREEBSD 1
#else
#define OS_FREEBSD 0
#endif

#if (defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__))
#define OS_BSD 1
#else
#define OS_BSD 0
#endif

#if (defined(__sun) || defined(sun))
#define OS_SOLARIS 1
#else
#define OS_SOLARIS 0
#endif

// why the hell not
#if (defined(__GNU__) || defined(__gnu_hurd__))
#define OS_HURD 1
#else
#define OS_HURD 0
#endif

#if (OS_BSD || OS_HURD || OS_LINUX || OS_MAC || OS_SOLARIS)
#define OS_NIX 1
#else
#define OS_NIX 0
#endif



#include <stdint.h>


#if OS_LINUX

#include <sys/sysinfo.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#elif OS_MAC

#include <mach/vm_statistics.h>
#include <mach/mach.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/param.h>
#include <sys/mount.h>


#elif OS_WINDOWS

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <Psapi.h>

typedef BOOL (WINAPI *LPFN_GLPI)(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, PDWORD);


#elif OS_FREEBSD

#include <unistd.h>

#include <sys/types.h>
#include <sys/sysctl.h>
#include <vm/vm_param.h>



#elif OS_NIX

#include <unistd.h>

#endif


#endif
