#include "logistic_regression.hpp"


LogisticRegression :: LogisticRegression(int num_features, int num_iterations, double learning_rate)
            : num_features(num_features), num_iterations(num_iterations), learning_rate(learning_rate) {}

     double ogisticRegression ::sigmoid(double x) {
        return 1.0 / (1.0 + exp(-x));
    }

    std::vector<double> LogisticRegression ::gradient(const std::vector<std::vector<double>>& X, const std::vector<double>& y, const std::vector<double>& weights) {
        unsigned int n = X.size();
        std::vector<double> gradient(num_features, 0.0);
        for (int i = 0; i < n; i++) {
            double y_pred = sigmoid(std::inner_product(X[i].begin(), X[i].end(), weights.begin(), 0.0));
            for (int j = 0; j < num_features; j++) {
                gradient[j] += (y_pred - y[i]) * X[i][j];
            }
        }
        return gradient;
    }

    std::vector<double> LogisticRegression ::it(const std::vector<std::vector<double>>& X, const std::vector<double>& y) {
        std::vector<double> weights(num_features, 0.0);
        for (int t = 0; t < num_iterations; t++) {
            auto grad = gradient(X, y, weights);
            for (int i = 0; i < num_features; i++) {
                weights[i] -= learning_rate * grad[i];
            }
        }
        return weights;
    }

    double LogisticRegression ::accuracy(const std::vector<std::vector<double>>& X, const std::vector<double>& y, const std::vector<double>& weights) {
        unsigned n = X.size();
        int num_correct = 0;
        for (int i = 0; i < n; i++) {
            double y_pred = sigmoid(std::inner_product(X[i].begin(), X[i].end(), weights.begin(), 0.0));
            if ((y_pred >= 0.5 && y[i] == 1.0) || (y_pred < 0.5 && y[i] == 0.0)) {
                num_correct++;
            }
        }
        return (double) num_correct / n;
    }