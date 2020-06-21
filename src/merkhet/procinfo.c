/* Copyright (c) 2015, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#include "platform.h"
#include "merkhet.h"


/**
 * @file
 * @brief 
 * Process Utilization Time --- User
 *
 * @details
 * This function looks up the user time of the current
 * process in seconds.
 *
 * @param usr
 * Output, passed by reference.  On successful return, the value
 * is set to the number of seconds the current process has been 
 * in user mode.
 *
 * @return
 * The return value indicates the status of the function.
 */
int merkhet_process_usrtime(runtime_t *usr)
{
  int ret = MERKHET_OK;
  *usr = 0.;
  
  
#if OS_LINUX
  ret = read_proc_self_stat(usr, 14);
  chkret(ret, FAILURE);
  
  *usr = (runtime_t) *usr / sysconf(_SC_CLK_TCK);
#elif OS_MAC
  struct task_thread_times_info info;
  mach_msg_type_number_t info_count = TASK_BASIC_INFO_COUNT;
  
  ret = task_info(mach_task_self(), TASK_THREAD_TIMES_INFO, (task_info_t)&info, &info_count);
  
  *usr = (runtime_t) info.user_time; // time_value_t
#elif OS_WINDOWS
  FILETIME create_ft, exit_ft, sys_ft, cpu_ft;
  ret = GetProcessTimes(GetCurrentProcess(), &create_ft, &exit_ft, &sys_ft, &cpu_ft); 
  winchkret(ret, FAILURE);
  
  ULARGE_INTEGER usr_uli;
  FILETIMEtoULI(&cpu_ft, &usr_uli);
  
  *usr = (runtime_t) usr_uli.QuadPart * 1e-7;
  
  return MERKHET_OK;
#else
  return PLATFORM_ERROR;
#endif
  
  return ret;
}



/**
 * @file
 * @brief 
 * Process Utilization Time --- System
 *
 * @details
 * This function looks up the system time of the current
 * process in seconds.
 *
 * @param sys
 * Output, passed by reference.  On successful return, the value
 * is set to the number of seconds the current process has been 
 * in kernel mode.
 *
 * @notes
 * TODO kernel mode, etc.
 *
 * @return
 * The return value indicates the status of the function.
 */
int merkhet_process_systime(runtime_t *sys)
{
  int ret = MERKHET_OK;
  *sys = 0.;
  
  
#if OS_LINUX
  ret = read_proc_self_stat(sys, 15);
  chkret(ret, FAILURE);
  
  *sys = (runtime_t) *sys / sysconf(_SC_CLK_TCK);
#elif OS_MAC
  struct task_thread_times_info info;
  mach_msg_type_number_t info_count = TASK_BASIC_INFO_COUNT;
  
  ret = task_info(mach_task_self(), TASK_THREAD_TIMES_INFO, (task_info_t)&info, &info_count);
  
  *sys = (runtime_t) info.system_time;
#elif OS_WINDOWS
  FILETIME create_ft, exit_ft, sys_ft, cpu_ft;
  ret = GetProcessTimes(GetCurrentProcess(), &create_ft, &exit_ft, &sys_ft, &cpu_ft); 
  winchkret(ret, FAILURE);
  
  ULARGE_INTEGER sys_uli;
  FILETIMEtoULI(&sys_ft, &sys_uli);
  
  *sys = (runtime_t) sys_uli.QuadPart * 1e-7;
  
  return MERKHET_OK;
#else
  return PLATFORM_ERROR;
#endif
  
  return ret;
}



/**
 * @file
 * @brief 
 * Process Runtime
 *
 * @details
 * This function looks up the 'real' (wallclock) runtime of the
 * current process in seconds.
 *
 * @param usr
 * Output, passed by reference.  On successful return, the value
 * is set to the number of seconds the current process has been 
 * in user mode.
 *
 * @return
 * The return value indicates the status of the function.
 */
int merkhet_process_runtime(runtime_t *runtime)
{
  int ret = MERKHET_OK;
  *runtime = 0.;
  
  
#if OS_LINUX
  // process runtime = system uptime - (time after boot process started in jiffies / clock ticks per cycle (HZ))
  runtime_t sys_uptime, proc_start_time;
  ret = merkhet_system_uptime(&sys_uptime);
  chkret(ret, FAILURE);
  
  ret = read_proc_self_stat(&proc_start_time, 22);
  chkret(ret, FAILURE);
  
  *runtime = (runtime_t) sys_uptime - (proc_start_time / sysconf(_SC_CLK_TCK));
#elif OS_MAC
  pid_t pid = getpid();
  struct proc_bsdinfo info;
  
  int st = proc_pidinfo(pid, PROC_PIDTBSDINFO, 0, &info, PROC_PIDTBSDINFO_SIZE);
  
  if (st != PROC_PIDTBSDINFO_SIZE)
    return FAILURE;
  
  uint64_t nixtime = time(NULL);
  *runtime = (runtime_t) (nixtime - info.pbi_start_tvsec);
#elif OS_WINDOWS
  // https://msdn.microsoft.com/en-us/library/windows/desktop/ms683223%28v=vs.85%29.aspx
  FILETIME create_ft, exit_ft, sys_ft, cpu_ft;
  ret = GetProcessTimes(GetCurrentProcess(), &create_ft, &exit_ft, &sys_ft, &cpu_ft); 
  winchkret(ret, FAILURE);
  
  FILETIME nowtime_ft;
  GetSystemTimeAsFileTime(&nowtime_ft);
  
  *runtime = FILETIMEdiff(&nowtime_ft, &create_ft);
  return MERKHET_OK;
#else
  return PLATFORM_ERROR;
#endif
  
  return ret;
}
