/* Automatically generated. Do not edit by hand. */

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <stdlib.h>

SEXP R_merkhet_system_uptime();
SEXP R_merkhet_process_usrtime();
SEXP R_merkhet_process_systime();
SEXP R_merkhet_process_runtime();

static const R_CallMethodDef CallEntries[] = {
  {"R_merkhet_process_runtime", (DL_FUNC) &R_merkhet_process_runtime, 0},
  {"R_merkhet_process_systime", (DL_FUNC) &R_merkhet_process_systime, 0},
  {"R_merkhet_process_usrtime", (DL_FUNC) &R_merkhet_process_usrtime, 0},
  {"R_merkhet_system_uptime", (DL_FUNC) &R_merkhet_system_uptime, 0},
  {NULL, NULL, 0}
};

void R_init_merkhet(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
