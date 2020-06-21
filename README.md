# merkeht 

* **Version:** 0.2-0
* **License:** [BSD 2-Clause](http://opensource.org/licenses/BSD-2-Clause)
* **Project home**: https://github.com/fml-fam/fmlr
* **Bug reports**: https://github.com/fml-fam/fmlr/issues

A "merkhet" is an ancient time-keeping device, which literally means "instrument of knowing".  The `merkhet` package offers some handy utilities for timings in R.



## Installation

<!-- You can install the stable version from [the HPCRAN](https://hpcran.org) using the usual `install.packages()`:

```r
install.packages("merkhet", repos="https://hpcran.org")
``` -->

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
# 10.34 seconds 
Sys.usrtime()
# 0.39 seconds 
Sys.systime()
# 0.38 seconds 
```

These three utilities combined allow you to do something akin to a post-hoc `system.time()`:

```r
post.system.time()
#    user  system elapsed 
#    0.42    0.38   17.34 
```



## Readable Timings

```r
wc.time(1+1)
# 0 seconds
 
wc.time(Sys.sleep(12.34567))
# 12.351 seconds
 
wc.time(Sys.sleep(123.4567))
# 2.059 minutes
```
