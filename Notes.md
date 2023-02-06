# Some Notes #
- `gradient()`, `fit()` and `accuracy()` do not modify the state of the class. They should be marked as `const`. Otherwise, you cannot call them on a constant `logistic_regression` object, and there is no reason why you should not.
- You include `<omp.h>` but I do not see any parallel stuff. It is a pity because part of the code looks rather trivial to parallelize. 
- Plain programming, nothing really wrong ( a part the missing `const`!) but also nothing particularly challenging. 

# Minor thinges #
- Some comments in the code, in particular documenting classes and methods, would have helped readability.
- Why are you including `iostream` in gbm.cpp if you are not using any stream in that source file?