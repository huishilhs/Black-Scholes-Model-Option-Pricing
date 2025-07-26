// src/BlackScholes.cpp
#include "BlackScholes.h"
#include "NormalDistribution.h"
#include <cmath>
#include <algorithm>


double blackScholesPrice(const OptionParams& opt, double S, double t) {
    double T = opt.T - t;
    if (T <= 0) return std::max((opt.isCall ? (S - opt.K) : (opt.K - S)), 0.0);

    double d1 = (std::log(S / opt.K) + (opt.r + 0.5 * opt.sigma * opt.sigma) * T) / (opt.sigma * std::sqrt(T));
    double d2 = d1 - opt.sigma * std::sqrt(T);

    if (opt.isCall)
        return S * normalCDF(d1) - opt.K * std::exp(-opt.r * T) * normalCDF(d2);
    else
        return opt.K * std::exp(-opt.r * T) * normalCDF(-d2) - S * normalCDF(-d1);
}
