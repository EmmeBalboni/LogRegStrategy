# LogRegStrategy

LogRegStrategy is an ML-based trading strategy for equities.


## Background

The problem is formulated as a classification.

Our software's task is learning how to optimally trade in a complex non-stationary environment as the Equity market, in order to maximize profit. This is done employing a Logistic Regression based on a group of financial indicators as predictors for the price to go up or down.


## Strategy

First a class for a Geometric Brownian Motion (GBM) is created in order to simulate a vector of stock prices. 
Time span is artificial (could be infraday).

Then I create a set of financial indicators, namely:

1. Moving Average (MA)
2. Bollinger Bands (BB)
3. Stochastic Oscillator
4. D-line
5. Williams R

which is employed as predictors to a Logistic Regression model. Target variable y is computed as the increment of decrement of the stock price at each time.
These technical indicators are computed and grouped together in the training/test dataset in the main function.

The learning and prediction phase of the Logistic Regression are implemented from scratch in C++ in the class Logistic Regression


## Performance

Accuracy measures out-of-sample performance for the algorithm.
A PL class implements methods for computing the dynamics of the portfolio.

Extension with a Neural Network (using mlpack) is currently under construction and being tested.
