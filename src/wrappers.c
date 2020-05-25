/*
  Copyright (c) 2015, Schmidt
  All rights reserved.
  
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  
  1. Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
  
  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
  
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "RNACI/RNACI.h"
#include "merkhet/merkhet.h"


SEXP R_merkhet_system_uptime()
{
  R_INIT;
  int ret;
  SEXP uptime;
  newRvec(uptime, 1, "dbl");
  
  runtime_t time;
  ret = merkhet_system_uptime(&time);
  
  DBL(uptime) = ret==MERKHET_OK ? (double)time : (double)ret;
  
  R_END;
  return uptime;
}



SEXP R_merkhet_process_usrtime()
{
  R_INIT;
  int ret;
  SEXP usrtime;
  newRvec(usrtime, 1, "dbl");
  
  runtime_t usr;
  ret = merkhet_process_usrtime(&usr);
  
  if (ret == MERKHET_OK)
    DBL(usrtime) = (double) usr;
  else
    DBL(usrtime) = (double) ret;
  
  R_END;
  return usrtime;
}



SEXP R_merkhet_process_systime()
{
  R_INIT;
  int ret;
  SEXP systime;
  newRvec(systime, 1, "dbl");
  
  runtime_t sys;
  ret = merkhet_process_systime(&sys);
  
  if (ret == MERKHET_OK)
    DBL(systime) = (double) sys;
  else
    DBL(systime) = (double) ret;
  
  R_END;
  return systime;
}



SEXP R_merkhet_process_runtime()
{
  R_INIT;
  int ret;
  SEXP runtime;
  newRvec(runtime, 1, "dbl");
  
  runtime_t time;
  ret = merkhet_process_runtime(&time);
  
  DBL(runtime) = ret==MERKHET_OK ? (double)time : (double)ret;
  
  R_END;
  return runtime;
}
