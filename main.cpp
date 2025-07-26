#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
#include "OptionPricer/BlackScholes.h"
#include "OptionPricer/Config.h"
#include "OptionPricer/NormalDistribution.h"



int main() {
    OptionParams opt{100.0, 100.0, 0.05, 0.2, 1.0, 100, true};

    int steps = opt.steps;
    double dt = opt.T / steps;

    std::vector<double> time, S, V, PnL;

    double spot = opt.S0;
    double initialOptionValue = blackScholesPrice(opt, spot, 0.0);

    // RNG
    std::mt19937 gen(42);
    std::normal_distribution<> dist(0.0, 1.0);

    time.push_back(0.0);
    S.push_back(spot);
    V.push_back(initialOptionValue);
    PnL.push_back(0.0);

    for (int i = 1; i <= steps; ++i) {
        double Z = dist(gen);
        spot *= std::exp((opt.r - 0.5 * opt.sigma * opt.sigma) * dt + opt.sigma * std::sqrt(dt) * Z);
        double t = i * dt;
        double optionValue = blackScholesPrice(opt, spot, t);
        double pnl = optionValue - initialOptionValue;

        time.push_back(t);
        S.push_back(spot);
        V.push_back(optionValue);
        PnL.push_back(pnl);
    }

    // Output to CSV
    std::ofstream out("plots/PnL_results.csv");
    out << "Time,Underlying,OptionValue,PnL\n";
    for (size_t i = 0; i < time.size(); ++i) {
        out << time[i] << "," << S[i] << "," << V[i] << "," << PnL[i] << "\n";
    }
    out.close();

    std::cout << "PnL simulation complete. Results written to plots/PnL_results.csv\n";
    return 0;
}
