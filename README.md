# merkeht [![Build Status](https://travis-ci.org/shinra-dev/merkhet.png)](https://travis-ci.org/shinra-dev/merkhet) [![License](http://img.shields.io/badge/license-BSD%202--Clause-orange.svg?style=flat)](http://opensource.org/licenses/BSD-2-Clause)

My brain hates staring at large numbers, and scientific
notation isn't always how I want to think about orders of magnitude.
That's why I added the approximate sizer:

```r
approx.size(12345)
# 12.3 Thousand
 
approx.size(123456789)
# 123.5 Million
 
approx.size(123456789, unit.names="short")
# 123.5m
 
approx.size(123456789, unit.names="comma")
# 123,456,789
```


I also hate staring at timings in seconds.  I don't got all day
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
library(devtools)
install_github("wrathematics/lineSampler")
```



## License

    Copyright (c) 2015, Drew Schmidt
    All rights reserved.
    
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    
    1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
    
    2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.


