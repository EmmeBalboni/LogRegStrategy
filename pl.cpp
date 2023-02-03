#include "pl.hpp"
#include "logistic_regression.hpp"
#include <numeric>

PL::PL(const std::vector<std::vector<double>>& X, const std::vector<double>& weights, double initial_sum)
        : X_(X), weights_(weights), initial_sum_(initial_sum) {}

void PL::compute() {
    unsigned int n = X_.size();
    double eur_amt = initial_sum_;
    double shares = 0;
    for (int i = 0; i < n; i++) {
        double y_pred = LogisticRegression::sigmoid(std::inner_product(X_[i].begin(), X_[i].end(), weights_.begin(), 0.0));
        int shares_ = floor(shares);
        if (y_pred >= 0.5 && eur_amt > 0) {
            shares = eur_amt / X_[i][0];
            eur_amt = 0;
            std::cout << "Bought shares at price: " << X_[i][0] << ". |  EUR amount: " << eur_amt << " |   #Shares: " << shares << std::endl;
        } else if (y_pred < 0.5 && shares_ != 0) {
            eur_amt = shares * X_[i][0];
            shares = 0;
            std::cout << "Sold shares at price (EUR): " << X_[i][0] << ". |  EUR amount: " << eur_amt << ". |   #Shares: " << shares << std::endl;
        }
    }
    std::cout << "Final P&L (EUR): " << eur_amt + shares * X_[n - 1][0] << std::endl;
}
