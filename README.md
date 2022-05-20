# float-issue-recreation
Clone the repo:

```
git clone git@github.com:ugGit/float-issue-recreation.git
```

## Requirements
The issue has been debugged so far in an environment using the following modules, which must be available when during the building phase:

* gcc/11.2.0
* nvhpc/22.3 (using CUDA 11.6)

## Information about the setup
The code has been tested on an Nvidia A6000 and a GeForce RTX 2080.

This project contains the minimal required modules and code to recreate the issue encountered.

## Issue description
The code consist of two independent `std::for_each_n` loops. 
The first loop uses a `std::exection` policy, but does itself no relevant computation.
The second loop performs a single precision floating point division.
Since both operands are the same float (`w`), the result is expected to yield `1.0` but it differs slightly.

## Execute the code
```
nvc++ -stdpar=gpu -O3 -o main main.cpp && ./main
```

Resulting output:
```
  w = 0.61043554544448852539
w/w = 0.99999994039535522461
```

## Observations
The following list resumes the observations made during the creation of the minimal reproducible example:
* The issue persists when using compiling for multicore (i.e. `-stdpar=multicore`) and when using the `-nostdpar` flag.
* Using another optimization level (`-O2`,`-O1`,`-O3 -g`) produce correct outputs.
* Removing the execution policy from the first loop resolves the issue.
* The result is wrong, indifferent of the execution policies used for the first loop.
* Using `double` for `w` solves the issue.
* Using different values for `w` suggest a problem with the handling of floating point numbers:
  ```
  // input:
  float w = 0.6104355605587131;
  // output:
    w = 0.61043554544448852539
  w/w = 0.99999994039535522461
  ```

  ```
  // input:
  float w = 0.61043556;
  // output:
    w = 0.61043554544448852539
  w/w = 0.99999994039535522461
  ```

  ```
  // input:
  float w = 0.6104355;
  // output:
    w = 0.61043548583984375000
  w/w = 1.00000000000000000000
  ```

  However, neglecting the limitation in precision of floats, the result for `w/w` should always stay the same.
   
