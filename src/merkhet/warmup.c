/* Copyright (c) 2015, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#include "merkhet.h"


static int busy_loop(uint32_t len)
{
  uint32_t i;
  static volatile val = 0;
  
  for (i=0; i<len; i++)
    val += 1.0; //rand();
  
  return val&1;
}



int merkhet_busy_loop(microseconds_t runlen)
{
  int ret = MERKHET_OK;
  
  int dummy;
  microseconds_t start, end;
  
  ret = merkhet_microtime_run(&start);
  chkret(ret, ret);
  
  end = start;
  
  while (end - start < runlen)
  {
    dummy = busy_loop(1000);
    merkhet_microtime_run(&end);
  }
  
  return ret;
}
