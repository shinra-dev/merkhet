#' bench class
#' 
#' Storage and methods benchmarking data.
#' 
#' @importFrom R6 R6Class
#' 
#' @rdname bench
#' @name bench
benchR6 = R6::R6Class("bench",
  public = list(
    #' @details
    #' Class initializer.
    #' @param header Printer header. A string or \code{NULL} to ignore.
    #' @param flops An optional numeric argument specifying the number of
    #' floating point operations for all timed operations.
    initialize = function(header=NULL, flops=NULL)
    {
      private$header = header
      private$flops = flops
      
      private$reps = integer(0)
      private$names = character()
      private$elapsed = numeric(0)
      private$n = 0
    },
    
    
    
    #' @details
    #' Time an expression using \code{system.time()}.
    #' @param expr Expression to time.
    #' @param reps Number of replications for each expression.
    #' @param name Optional name for the timed expression.
    #' @param env Environment where expression will be executed.
    time = function(expr, reps=1, name=NULL, env=parent.frame())
    {
      private$n = private$n + 1
      private$reps = c(private$reps, as.integer(reps))
      
      expr_subs = substitute(expr)
      
      if (is.null(name))
        name = deparse(substitute(expr))
      
      private$names = c(private$names, name)
      
      t = 0
      for (rep in 1:reps)
        t = t + system.time(eval(expr_subs, envir=env))[3]
      
      private$elapsed = c(private$elapsed, t)
      
      invisible(self)
    },
    
    
    
    #' @details
    #' Print current benchmark information.
    print = function()
    {
      if (!is.null(private$header))
        cat(paste("##", private$header, "\n"))
      
      if (private$n > 0)
        print(private$get_table())
      
      cat("\n")
      
      invisible(self)
    },
    
    
    
    #' @details
    #' Returns a table of the benchmark data.
    table = function()
    {
      tbl = as.data.frame(private$get_table())
      tbl = cbind(operation=factor(rownames(tbl)), tbl)
      rownames(tbl) = NULL
      tbl
    },
    
    
    
    #' @details
    #' Prints the benchmark table as a csv.
    #' @param sep Separator.
    #' @param header Print header?
    #' @param file A file to write to, or \code{NULL} to print to stdout.
    csv = function(sep=",", header=TRUE, file=NULL)
    {
      if (private$n == 0)
      {
        cn = private$get_colnames()
        tbl = matrix(nrow=0, ncol=length(cn))
        tbl = as.data.frame(tbl)
      }
      else
      {
        tbl = private$get_table()
        cn = colnames(tbl)
      }
      
      if (!is.null(file) && file.exists(file))
        file.remove(file)
      
      if (header)
      {
        private$cat("expr", sep, file=file)
        for (i in private$range(1, length(cn)))
        {
          private$cat(cn[i], file=file)
          if (i < length(cn))
          private$cat(sep, file=file)
        }
        private$cat("\n", file=file)
      }
      
      for (i in private$range(1, nrow(tbl)))
      {
        for (j in private$range(1, ncol(tbl)))
        {
          if (j == 1)
            private$cat("\"", rownames(tbl)[i], "\"", sep, file=file)
          
          private$cat(tbl[i, j], file=file)
          if (j < ncol(tbl))
            private$cat(sep, file=file)
        }
        private$cat("\n", file=file)
      }
      private$cat("\n", file=file)
      
      invisible(self)
    },
    
    
    
    #' @details
    #' Show a line plot of the benchmarks table.
    #' @param ... Additional arguments to \code{plot()}.
    plot = function(...)
    {
      if (private$n == 0)
      {
        barplot(height=0)
        return(invisible(self))
      }
      
      x = factor(private$names)
      y = private$elapsed / private$reps
      
      plot(x, y, ylab="Average Runtime (seconds)", ...)
      lines(y)
      
      invisible(self)
    },
    
    
    
    #' @details
    #' Show a barplot of the benchmarks table.
    #' @param ... Additional arguments to \code{barplot()}.
    barplot = function(...)
    {
      if (private$n == 0)
      {
        barplot(height=0)
        return(invisible(self))
      }
      
      tbl = private$get_table()
      
      barplot(
        tbl[, "avg"],
        names.arg=rownames(tbl),
        ylab="Average Runtime (seconds)",
        ...
      )
      
      invisible(self)
    }
  ),
  
  
  
  private = list(
    header = NULL,
    flops = NULL,
    reps = NULL,
    elapsed = NULL,
    names = NULL,
    n = NULL,
    
    get_colnames = function()
    {
      c("elapsed", "reps", "avg", "relative")
    },
    
    get_table = function()
    {
      m = max(1e-8, private$elapsed[which.min(private$elapsed)])
      
      avg = private$elapsed / private$reps
      
      relative = round(private$elapsed / m, 2)
      tbl = cbind(private$elapsed, private$reps, avg, relative)
      cn = private$get_colnames()
      
      if (!is.null(private$flops))
      {
        flops = private$flops / avg / 1000^3
        tbl = cbind(tbl, flops)
        cn = c(cn, "gflops")
      }
      
      colnames(tbl) = cn
      rownames(tbl) = private$names
      
      tbl
    },
    
    range = function(a, b)
    {
      if (a < b)
        a:b
      else
        integer(0)
    },
    
    cat = function(..., file)
    {
      if (is.null(file))
        base::cat(..., sep="")
      else
        base::cat(..., file=file, sep="", append=TRUE)
    }
  )
)



#' bench
#' 
#' Constructor for bench objects.
#' 
#' @param header Printer header. A string or \code{NULL} to ignore.
#' @param flops An optional numeric argument specifying the number of
#' floating point operations for all timed operations.
#' 
#' @return A bench class object.
#' 
#' @examples
#' library(merkhet)
#' 
#' b = bench()
#' 
#' b$time(Sys.sleep(.2), 2)
#' b
#' b$time(Sys.sleep(.35))
#' b
#' 
#' b$csv()
#' 
#' @rdname bench
#' @export
bench = function(header=NULL, flops=NULL)
{
  benchR6$new(header=header, flops=flops)
}
