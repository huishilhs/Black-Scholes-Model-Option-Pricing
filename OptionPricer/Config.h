// include/Config.h
#pragma once

struct OptionParams {
    double S0;     // initial asset price
    double K;      // strike price
    double r;      // risk-free rate
    double sigma;  // volatility
    double T;      // time to maturity (years)
    int steps;     // number of time steps
    bool isCall;   // true = call, false = put
};
