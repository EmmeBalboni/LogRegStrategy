#include <vector>

class LogisticRegression {
public:
    LogisticRegression(int num_features, int num_iterations, double learning_rate);
    static double sigmoid(double x);
    std::vector<double> gradient(const std::vector<std::vector<double>>& X, const std::vector<double>& y, const std::vector<double>& weights);
    std::vector<double> fit(const std::vector<std::vector<double>>& X, const std::vector<double>& y);
    double accuracy(const std::vector<std::vector<double>>& X, const std::vector<double>& y, const std::vector<double>& weights);
private:
    int num_features;
    int num_iterations;
    double learning_rate;
};