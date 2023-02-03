#include <iostream>
#include <vector>
#include <cmath>

class PL {
public:
    PL(const std::vector<std::vector<double>>& X, const std::vector<double>& weights, double initial_sum);

    void compute();

private:
    const std::vector<std::vector<double>>& X_;
    const std::vector<double>& weights_;
    double initial_sum_;
};