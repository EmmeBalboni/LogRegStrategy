#include "gbm.hpp"
#include <cmath>
#include <iostream>

GBM::GBM(double mu, double sigma, double S0, double T, unsigned int seed)
        : mu_(mu), sigma_(sigma), S0_(S0), T_(T), generator_(seed) {}

double GBM::simulate() {
    std::normal_distribution<double> normal(0, 1);
    double Wt = sqrt(T_) * normal(generator_);
    return S0_ * exp((mu_ - 0.5 * sigma_ * sigma_) * T_ + sigma_ * Wt);
}

std::vector<double> GBM::generate_prices(unsigned int n) {
    std::vector<double> prices(n);

#pragma omp parallel for num_threads(8)
    for (int i = 0; i < n; i++) {
        prices[i] = simulate();
    }
    return prices;
}
