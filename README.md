# merkeht 

* **Version:** 0.2-0
* **License:** [BSD 2-Clause](http://opensource.org/licenses/BSD-2-Clause)
* **Project home**: https://github.com/shinra-dev/merkhet
* **Bug reports**: https://github.com/shinra-dev/merkhet/issues

A "merkhet" is an ancient time-keeping device, which literally means "instrument of knowing".  The `merkhet` package offers some handy utilities for timings in R.



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
