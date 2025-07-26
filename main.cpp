#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <cmath>
#include "OptionPricer/BlackScholes.h"
#include "OptionPricer/Config.h"
#include "OptionPricer/NormalDistribution.h"

// Read OptionParams from CSV
OptionParams readOptionParamsFromCSV(const std::string& path) {
    std::ifstream file(path);
    std::string line;
    std::getline(file, line); // Skip header

    OptionParams opt;
    std::getline(file, line);
    std::stringstream ss(line);
    char comma;

    int isCallInt;
    ss >> opt.S0 >> comma >> opt.K >> comma >> opt.r >> comma
       >> opt.sigma >> comma >> opt.T >> comma >> opt.steps >> comma >> isCallInt;

    opt.isCall = (isCallInt != 0);
    return opt;
}

int main() {
    // Load option parameters
    OptionParams opt = readOptionParamsFromCSV("data/input.csv");

    int steps = opt.steps;
    int numPaths = 1000;         // Number of simulations
    double dt = opt.T / steps;

    std::mt19937 gen(42);        // Random number generator (fixed seed for reproducibility)
    std::normal_distribution<> dist(0.0, 1.0);

    std::vector<double> finalPnls;

    double initialOptionValue = blackScholesPrice(opt, opt.S0, 0.0);

    for (int path = 0; path < numPaths; ++path) {
        double spot = opt.S0;

        // Simulate one GBM path
        for (int i = 0; i < steps; ++i) {
            double Z = dist(gen);
            spot *= std::exp((opt.r - 0.5 * opt.sigma * opt.sigma) * dt + opt.sigma * std::sqrt(dt) * Z);
        }

        double finalOptionValue = blackScholesPrice(opt, spot, opt.T);
        double pnl = finalOptionValue - initialOptionValue;
        finalPnls.push_back(pnl);
    }

    // Output PnL distribution to CSV
    std::ofstream out("plots/PnL_distribution.csv");
    out << "FinalPnL\n";
    for (double pnl : finalPnls) {
        out << pnl << "\n";
    }
    out.close();

    std::cout << "✅ Simulated " << numPaths << " PnL paths. Results saved to plots/PnL_distribution.csv\n";
    return 0;
}