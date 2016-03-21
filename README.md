# merkeht 

* **Version:** 0.2
* **Status:** [![Build Status](https://travis-ci.org/shinra-dev/merkhet.png)](https://travis-ci.org/shinra-dev/merkhet)
* **License:** [![License](http://img.shields.io/badge/license-BSD%202--Clause-orange.svg?style=flat)](http://opensource.org/licenses/BSD-2-Clause)
* **Author:** Drew Schmidt

A "merkhet" is an ancient time-keeping device, which literally
means "instrument of knowing".  The `merkhet` package offers
some handy utilities for timings in R.


## Package Utilities

#### Run Times

System uptime:

```r
Sys.uptime()
# 1.853 days 
```

There are also some utilities for seeing how long the current R
process has been running (by the various standard measures):

```r
Sys.runtime()
# 10.34 seconds 
Sys.usrtime()
# 0.39 seconds 
Sys.systime()
# 0.38 seconds 
```

These three utilities combined allow you to do something akin to a
post-hoc `system.time()`:

```r
post.system.time()
#    user  system elapsed 
#    0.42    0.38   17.34 
```



#### Readable Timings

I hate staring at timings in seconds.  I don't got all day
to be dividing by WHO KNOWS what kind of numbers to make the output
of `system.time()` readable!  That's why I added this simple wrapper
to get the wall-clock time in a readable format:

```r
wc.time(1+1)
# 0 seconds
 
wc.time(Sys.sleep(12.34567))
# 12.351 seconds
 
wc.time(Sys.sleep(123.4567))
# 2.059 minutes
```




## Installation

```r
devtools::install_github("wrathematics/merkhet")
```

