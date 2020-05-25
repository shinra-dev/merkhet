/* Copyright (c) 2014-2015, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#include "merkhet.h"
#include "platform.h"


#if OS_LINUX

int read_proc_self_stat(runtime_t *val, const int n)
{
  size_t i;
  int spaces = 0, last_space = 0;
  char *line = NULL;
  size_t linelen = 0;
  char *end;
  
  uint64_t tmp = 0L;
  *val = 0.;
  
  FILE* fp = fopen("/proc/self/stat", "r");
  if (fp == NULL)
    return FAILURE;
  
  linelen = getline(&line, &linelen, fp);
  
  for (i=0; i<linelen; i++)
  {
    if (line[i] == ' ')
    {
      spaces++;
      
      if (spaces == n)
        tmp = strtoull(line+last_space, &end, 10);
      else
        last_space = i;
    }
  }
  
  *val = (runtime_t) tmp;
  
  free(line);
  fclose(fp);
  
  return MERKHET_OK;
}



#elif OS_WINDOWS

void FILETIMEtoULI(FILETIME *ft, ULARGE_INTEGER *uli)
{
  uli->LowPart   = ft->dwLowDateTime;
  uli->HighPart  = ft->dwHighDateTime;
}

// ft1 - ft2
runtime_t FILETIMEdiff(FILETIME *ft1, FILETIME *ft2)
{
  runtime_t ut;
  
  ULARGE_INTEGER uli1, uli2;
  
  FILETIMEtoULI(ft1, &uli1);
  FILETIMEtoULI(ft2, &uli2);
  
  ut = (runtime_t) (uli1.QuadPart - uli2.QuadPart) * 1e-7;
  
  return ut;
}

#endif
