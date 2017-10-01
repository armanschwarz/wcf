# wcf
### A constant-time line counting tool for the command line
This program was inspired by its namesake, the line-counting functionality in
the ubiquitous ['wc' application](https://en.wikipedia.org/wiki/Wc_(Unix))
found on most UNIX systems.

__wcf__ provides fuzzy line-count estimates that can instantaneously provide
results and, optionally, continue refining the estimate while you wait.

The _f_ in __wcf__ stands a little bit for _fast_, but mostly it stands for _fuzzy_
:p.

### Documentation
```
arman@arman-desktop:~$ wcf --help
fast and fuzzy line counts, with optional best-guesses while you wait:
  -h [ --help ]                      Display this help screen
  -f [ --file ] arg                  Input file to count lines from
  -l [ --live ]                      Update the best guess after each interval,
                                     and return when the actual line count is 
                                     known. This overrides default behavior, 
                                     where wcf simply returns after the first 
                                     interval with the line count guess
  -s [ --simple-output ]             Output only the guess value without 
                                     accuracy estimation. If live mode is 
                                     disabled this will cause wcf to only 
                                     output the guess value once
  -t [ --time-interval ] arg (=0.25) Time in seconds between line count 
                                     updates. Set to 0 to only display the line
                                     count once the whole file has been read.
```
