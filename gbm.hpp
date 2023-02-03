#include <vector>
#include <random>

class GBM {
public:
    GBM(double mu, double sigma, double S0, double T, unsigned int seed);
    double simulate();
    std::vector<double> generate_prices(unsigned int n);
private:
    double mu_;
    double sigma_;
    double S0_;
    double T_;
    std::mt19937 generator_;
};