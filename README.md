# merkeht 

* **Version:** 0.3-0
* **License:** [BSD 2-Clause](http://opensource.org/licenses/BSD-2-Clause)
* **Project home**: https://github.com/shinra-dev/merkhet
* **Bug reports**: https://github.com/shinra-dev/merkhet/issues

The name "merkhet" is an ancient word for a kind of timekeeping device, which means the "instrument of knowing." The package contains several timing utilities useful for benchmarking and performance monitoring.



## Installation

You can install the stable version from [the HPCRAN](https://hpcran.org) using the usual `install.packages()`:

```r
install.packages("merkhet", repos="https://hpcran.org")
```

The development version is maintained on GitHub:

```r
remotes::install_github("shinra-dev/merkhet")
```



## Special Timers

System uptime:

```r
Sys.uptime()
# 1.853 days 
```

There are also some utilities for seeing how long the current R process has been running (by the various standard measures):

```r
Sys.runtime()
# 10 seconds 
Sys.usrtime()
# 0.39 seconds 
Sys.systime()
# 0.38 seconds 
```

These three utilities combined allow you to do something akin to a post-hoc `system.time()`:

```r
post.system.time()
#    user  system elapsed 
#    0.42    0.38   17.00
```



## Readable Timings

The `wc.time()` function is a simple wrapper around `system.time()` to measure the wallclock time with the output in a hunman-readable time:

```r
wc.time(1+1)
# 0 seconds
 
wc.time(Sys.sleep(12.34567))
# 12.351 seconds
 
wc.time(Sys.sleep(123.4567))
# 2.059 minutes
```

You can also take a time and convert it to a human-readable time using `readable.time()`

```r
readable.time(500)
## 8.333 minutes 
readable.time(5000)
## 1.389 hours 
readable.time(50000)
## 13.889 hours 
readable.time(500000)
## 5.787 days 
```



## Benchmarking

The package also includes a simple benchmarking wrapper around `system.time()`. It uses an R6 class so you can add timed expressions iteratively, each with different numbers of replications.

```r
library(merkhet)

b = bench()

b$time(Sys.sleep(.3), reps=2)
b
## ## Benchmark of 1 operations
##                elapsed reps    avg relative
## Sys.sleep(0.3)   0.301    2 0.1505        1

b$time(Sys.sleep(.5))
b
## ## Benchmark of 2 operations
##                elapsed reps    avg relative
## Sys.sleep(0.3)   0.301    2 0.1505     1.00
## Sys.sleep(0.5)   0.501    1 0.5010     1.66
```

There is also an option to dump the data to csv (file or stdout):

```r
b$csv()
## expr,elapsed,reps,avg,relative
## "Sys.sleep(0.3)",0.301,2,0.1505,1
## "Sys.sleep(0.5)",0.501,1,0.501,1.66
```

as well as make simple boxplots

```r
b$plot()
```
