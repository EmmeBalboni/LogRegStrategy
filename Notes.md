# Some Notes #
- The project compiles and runs without issues. 
- Plain programming, nothing really wrong ( a part  missing `const`!) but also nothing particularly challenging.
- The hard-coding of the number of threads forbids the user from running scaling tests. 
- Readme is superficial and many interesting possible extensions are left not implemented (see comments below for more details).
- `gradient()`, `fit()` and `accuracy()` do not modify the state of the class. They should be marked as `const`. Otherwise, you cannot call them on a constant `logistic_regression` object, and there is no reason why you should not.
- You include `<omp.h>` also in files where I do not see any parallel stuff. 
It is a pity because part of the code looks rather trivial to parallelize, and you have done quite little parallization. 
- You do not provide description of how to compile (the make file works well and it is intuitive, however description of how to compile was a requirement)
- You do not explain what you actually do in the `main` in the readme 
- Compilation goes well but you lack some relevant flags (like C++ standard and warnings. Indeed you would have caught many 'comparison of integer expressions of different signedness')
- The set of financial indicators that you calculate in the main function should have been provided by a class or a function in an appropriate namespace 
- You have implemented all you moving window algorithms in a "naive" way, that is with complexity `O(n window)`. They can be done much more efficiently, see for instance [the ascending minima algorithm](https://www.nayuki.io/page/sliding-window-minimum-maximum-algorithm). 
- You split the train-validation set by copying again the entire dataset into new vectors, this is very inefficient. A possible solution is for instance to implement the `LogisticRegression` to use vector iterators instead of vectors references. 
- The number of OpenMP threads is hard-coded: you either do not specify it so that it stays the default one (and can be changed with the env variable) or you make it a parameter passed at run-time.
- `weights` should be a member of `LogisticRegression`
- `LogisticRegression::fit` or `LogisticRegression::gradient` could have been parallelized
- `LogisticRegression` should have a method `evaluate` for a sample
- `LogisticRegression` should compute/show the (cross-entropy) loss
- `LogisticRegression::gradient` is only full batch
- `LogisticRegression::gradient`, `LogisticRegression::fit` and `LogisticRegression::accuracy` should have the `const` qualifier.


# Minor things #
- Some comments in the code, in particular documenting classes and methods, would have helped readability.
- Why are you including `iostream` in gbm.cpp if you are not using any stream in that source file?
- C style cast in `LogisticRegression::accuracy`
-You used `sqrt` and `exp` and not their `std::` version
-You could have used `auto` for many local variables and simplify coding 