# LogRegStrategy

LogRegStrategy is an ML-based trading strategy for the equity space.

The problem is formulated as a classification.
First a Geometric Brownian Motion is created in order to simulate a vector of stock prices. Time span is 4 years (each with 220 trading days). Then a set of financial indicators, namely:

1. Moving Average (MA);
2. Bollinger Bands (BB);
3. Stochastic Oscillator;
4. D-line;
5. Williams R;

is employed as predictors to a Logistic Regression model. Target variable is computed as the increment of decrement of the stock price at each time.
The learning and prediction phase of the Logistic Regression are implemented from scratch. Accuracy measures out-of-sample performance for the algorithm.
A P&L function computes the dynamics of the portfolio.
