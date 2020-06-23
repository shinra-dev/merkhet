checkret = function(ret)
{
  if (ret < 0)
    stop("platform not supported at this time")
}



#' uptime
#' 
#' Returns the amount of time to the nearest second in human-readable units
#' since the system was booted.
#' 
#' @return 
#' A readabletime object.
#' 
#' @examples
#' \dontrun{
#' library(memuse)
#' 
#' Sys.uptime()
#' }
#' 
#' @useDynLib merkhet R_merkhet_system_uptime
#' @name uptime
#' @rdname uptime
#' @export
Sys.uptime = function()
{
  ret = .Call(R_merkhet_system_uptime)
  checkret(ret)
  readable.time(round(ret, 0))
}



#' usrtime
#' 
#' Returns the amount of time in human-readable units that the current process
#' has been in user mode.
#' 
#' @return 
#' A readabletime object.
#' 
#' @examples
#' \dontrun{
#' library(memuse)
#' 
#' Sys.usrtime()
#' }
#' 
#' @useDynLib merkhet R_merkhet_process_usrtime
#' @name usrtime
#' @rdname usrtime
#' @export
Sys.usrtime = function()
{
  ret = .Call(R_merkhet_process_usrtime)
  checkret(ret)
  readable.time(ret)
}



#' systime
#' 
#' Returns the amount of time in human-readable units that the current process
#' has been in kernel mode.
#' 
#' @return 
#' A readabletime object.
#' 
#' @examples
#' \dontrun{
#' library(memuse)
#' 
#' Sys.systime()
#' }
#' 
#' @useDynLib merkhet R_merkhet_process_systime
#' @name systime
#' @rdname systime
#' @export
Sys.systime = function()
{
  ret = .Call(R_merkhet_process_systime)
  checkret(ret)
  readable.time(ret)
}



#' runtime
#' 
#' Returns the amount of time to the nearest second in human-readable units that
#' the current R process has been active, i.e. the wall-clock time of the
#' process.
#' 
#' @return 
#' A readabletime object.
#' 
#' @examples
#' \dontrun{
#' library(memuse)
#' 
#' Sys.runtime()
#' }
#' 
#' @useDynLib merkhet R_merkhet_process_runtime
#' @name usrtime
#' @rdname usrtime
#' @export
Sys.runtime = function()
{
  ret = .Call(R_merkhet_process_runtime)
  checkret(ret)
  readable.time(round(ret, 0))
}



#' post.system.time
#' 
#' Returns the user, kernel, and wallclock time that the current process has
#' been active. Like a kind of post-hoc \code{system.time()}.
#' 
#' @return 
#' A proc_time object (same as \code{system.time()}).
#' 
#' @examples
#' \dontrun{
#' library(memuse)
#' 
#' post.system.time()
#' }
#' 
#' @name post-system-time
#' @rdname post-system-time
#' @export
post.system.time = function()
{
  usr = .Call(R_merkhet_process_usrtime)
  sys = .Call(R_merkhet_process_systime)
  elapsed = round(.Call(R_merkhet_process_runtime), 0)
  
  ret = c(usr, sys, elapsed)
  names(ret) = c("user.self", "sys.self", "elapsed")
  class(ret) = "proc_time"
  
  ret
}
