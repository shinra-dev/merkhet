/* Copyright (c) 2015, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#include "platform.h"
#include "merkhet.h"


int merkhet_microtime_run(microseconds_t *time)
{
  int ret = MERKHET_OK;
  *time = 0;
  
  #if OS_LINUX
  struct timeval t;
  gettimeofday(&t, NULL);
  
  *time = (microseconds_t) t.tv_sec * 1000000 + t.tv_usec;
  #else
  return PLATFORM_ERROR;
  #endif
  
  return ret;
}

