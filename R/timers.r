#' uptime
#' 
#' Returns the amount of time, in human-readable units, since
#' the system was booted.
#' 
#' All of the C-level source code for these methods (in src/meminfo of the root
#' directory of the memuse source tree) is licensed under the permissive
#' 2-Clause BSD license.
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
#' @name uptime
#' @rdname uptime
#' @export
Sys.uptime <- function()
{
  ret <- .Call(R_merkhet_system_uptime)
  
  if (ret < 0)
    stop("platform not supported at this time")
  
  ret <- readable.time(ret)
  
  return( ret )
}



#' usrtime
#' 
#' Returns the amount of time, in human-readable units, the
#' current process has been in user mode.
#' 
#' All of the C-level source code for these methods (in src/meminfo of the root
#' directory of the memuse source tree) is licensed under the permissive
#' 2-Clause BSD license.
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
#' @name usrtime
#' @rdname usrtime
#' @export
Sys.usrtime <- function()
{
  ret <- .Call(R_merkhet_process_usrtime)
  
  if (ret < 0)
    stop("platform not supported at this time")
  
  ret <- readable.time(ret)
  
  return( ret )
}



#' systime
#' 
#' Returns the amount of time, in human-readable units, the
#' current process has been in kernel mode.
#' 
#' All of the C-level source code for these methods (in src/meminfo of the root
#' directory of the memuse source tree) is licensed under the permissive
#' 2-Clause BSD license.
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
#' @name systime
#' @rdname systime
#' @export
Sys.systime <- function()
{
  ret <- .Call(R_merkhet_process_systime)
  
  if (ret < 0)
    stop("platform not supported at this time")
  
  ret <- readable.time(ret)
  
  return( ret )
}



#' runtime
#' 
#' Returns the amount of time, in human-readable units, the
#' current R process has been active (the wall-clock time of the
#' process).
#' 
#' All of the C-level source code for these methods (in src/meminfo of the root
#' directory of the memuse source tree) is licensed under the permissive
#' 2-Clause BSD license.
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
#' @name usrtime
#' @rdname usrtime
#' @export
Sys.runtime <- function()
{
  ret <- .Call(R_merkhet_process_runtime)
  
  if (ret < 0)
    stop("platform not supported at this time")
  
  ret <- readable.time(ret)
  
  return( ret )
}



#' post.system.time
#' 
#' Returns the user, kernel, and wallclock time that the current
#' process has been active.  Like a kind of post-hoc \code{system.time()}.
#' 
#' All of the C-level source code for these methods (in src/meminfo of the root
#' directory of the memuse source tree) is licensed under the permissive
#' 2-Clause BSD license.
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
post.system.time <- function()
{
  usr <- .Call(R_merkhet_process_usrtime)
  sys <- .Call(R_merkhet_process_systime)
  elapsed <- .Call(R_merkhet_process_runtime)
  
  ret <- c(usr, sys, elapsed)
  names(ret) <- c("user.self", "sys.self", "elapsed")
  class(ret) <- "proc_time"
  
  return(ret)
}



# ---------------------------------------------------------
# Print handling
# ---------------------------------------------------------

title_case <- function(x) gsub(x, pattern="(^|[[:space:]])([[:alpha:]])", replacement="\\1\\U\\2", perl=TRUE)


#' print.sysinfo
#' 
#' Print method for sysinfo objects.
#' 
#' @param x 
#' An sysinfo object.
#' @param ... Additional arguments (ignored).
#' 
#' @name print-sysinfo
#' @rdname print-sysinfo
#' @method print sysinfo
#' @export
print.sysinfo <- function(x, ...)
{
  # So ugly it's beautiful
  maxlen <- max(sapply(names(x), nchar))
  names <- gsub(names(x), pattern="_", replacement=" ")
  names <- title_case(x=names)
  spacenames <- simplify2array(lapply(names, function(str) paste0(str, ":", paste0(rep(" ", maxlen-nchar(str)), collapse=""))))
  
  maxlen <- max(sapply(x, function(y) nchar(paste(y))))
  prespaces <- simplify2array(lapply(x, function(y) paste0(rep(" ", maxlen-nchar(paste(y))), collapse="")))
  
  lapply(1:length(x), function(i) cat(paste(spacenames[i], prespaces[i], x[[i]], sep=" ", collapse="\n"), "\n"))
#  cat("\n")
  
  invisible()
}



#' @export
"[.sysinfo" <- function(x, i)
{
  class(x) <- NULL
  ret <- x[i]
  if (length(ret) > 0)
    class(ret) <- "sysinfo"
  else
    return(numeric(0))
  
  return(ret)
}

