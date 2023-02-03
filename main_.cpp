#include "gbm.hpp"
#include "logistic_regression.hpp"
#include "pl.hpp"
#include <algorithm>
#include <numeric>
#include <omp.h>


int main() {

    // N.B. GBM parameters should be market observed estimates
    GBM gbm(0.1, 0.2, 100, 1, 42);

    std::vector<double> prices = gbm.generate_prices(100000);
    unsigned int n = prices.size();
    std::cout << "Number of trading days: " << n << std::endl;

    // Check prices does not contain any negative elements
    auto iter = std::min_element( std::begin(prices), std::end(prices) );
    auto min = *iter;
    bool hasNeg = min < 0 ? 1 : 0;
    if (hasNeg) {
        std::cout << "Time series contains negative values. Be careful with GBM parameters" << n << std::endl;
    }

    /*  Plot time series if needed
    for (int i = 0; i < prices.size(); i++) {
        std::cout << prices[i] << std::endl;
    }
    */

    // Calculation of basic financial indicators / model inputs
    //  Moving Average and Bollinger bands
    std::vector<double> moving_average(n);
    std::vector<double> bollinger_bands(n);

    int window = 30;
    for (int i = window-1; i < n; i++) {
        double sum = 0;
        for (int j = i-window+1; j <= i; j++) {
            sum += prices[j];
        }
        moving_average[i] = sum / window;
        double deviation = 0;
        for (int j = i-window+1; j <= i; j++) {
            deviation += (prices[j] - moving_average[i]) * (prices[j] - moving_average[i]);
        }
        deviation = sqrt(deviation / window);
        bollinger_bands[i] = (prices[i] - moving_average[i]) / deviation;
    }

    // Stochastic Oscillator
    std::vector<double> stochastic_oscillator(n);
    int k_window = 14;
    int d_window = 3;
    for (int i = window-1; i < n; i++) {
        double min_price = *std::min_element(prices.begin() + i - k_window + 1, prices.begin() + i + 1);
        double max_price = *std::max_element(prices.begin() + i - k_window + 1, prices.begin() + i + 1);
        stochastic_oscillator[i] = (prices[i] - min_price) / (max_price - min_price);
    }

    // Moving Average of Stochastic Oscillator (d line)
    std::vector<double> d_line(n);
    for (int i = window-1; i < n; i++) {
        double sum = 0;
        for (int j = i-d_window+1; j <= i; j++) {
            sum += stochastic_oscillator[j];
        }
        d_line[i] = sum / d_window;
    }

    // Williams %R
    std::vector<double> williams_r(n);
    int r_window = 14;
    for (int i = window-1; i < n; i++) {
        double min_price = *std::min_element(prices.begin() + i - r_window + 1, prices.begin() + i + 1);
        double max_price = *std::max_element(prices.begin() + i - r_window + 1, prices.begin() + i + 1);
        williams_r[i] = (max_price - prices[i]) / (max_price - min_price) * -100.0;
    }

    // Prepare target variable y and matrix of features X
    std::vector<double> y(n-window);
    for (int i = window; i < n; i++) {
        y[i-window] = (prices[i] > prices[i-1]) ? 1.0 : 0.0;
    }

    std::vector<std::vector<double>> X(n-window, std::vector<double>(6));
    for (int i = window; i < n; i++) {
        X[i-window][0] = prices[i];
        X[i-window][1] = moving_average[i];
        X[i-window][2] = bollinger_bands[i];
        X[i-window][3] = stochastic_oscillator[i];
        X[i-window][4] = d_line[i];
        X[i-window][5] = williams_r[i];
    }

    // int n = X.size();
    // 80-20 rule for train test split
    int train_set_size = 0.8 * n;
    std::vector<std::vector<double>> X_train(X.begin(), X.begin() + train_set_size);
    std::vector<double> y_train(y.begin(), y.begin() + train_set_size);
    std::vector<std::vector<double>> X_test(X.begin() + train_set_size, X.end());
    std::vector<double> y_test(y.begin() + train_set_size, y.end());

    LogisticRegression lr(6, 500, 0.01);
    auto weights = lr.fit(X_train, y_train);
    double train_accuracy = lr.accuracy(X_train, y_train, weights);
    double test_accuracy = lr.accuracy(X_test, y_test, weights);

    std::cout << "Train accuracy: " << train_accuracy << std::endl;
    std::cout << "Test accuracy: " << test_accuracy << std::endl;

    // P&L
    PL pl(X, weights, 1000.00);
    pl.compute();
}
