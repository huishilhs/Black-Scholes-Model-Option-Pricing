# Black-Scholes Option Pricing and Risk Simulation

This project implements a **C++ option pricing and PnL simulation engine**, connected to **live market data** via Python.  
It bridges theory and practice by combining the **Black–Scholes model**, **Monte Carlo simulation**, and **risk analysis** with real data from Yahoo Finance.

---

## 🚀 Features

- **Black–Scholes Pricing** for European call and put options
- **Monte Carlo Simulation** of underlying price paths via Geometric Brownian Motion
- **PnL Distribution Analysis** with histogram, mean, and Value at Risk (VaR)
- **Live Market Data Integration** using Python (`yfinance`)  
  - Fetch stock price, strike, expiry, and implied volatility
- **Python Visualization** of PnL results and risk metrics

---

## 📊 Example Output

- Histogram of final PnL distribution across 1000 simulated paths
- Blue dotted line = expected PnL  
- Red dashed line = 5% Value at Risk (VaR)

![Generated Chart](https://github.com/huishilhs/Black-Scholes-Model-Option-Pricing/blob/main/PnL%20Distribution%20Graph.png)

---

## ⚙️ How to Run

1. **Fetch live option parameters** (Python → generates `data/input.csv`):
   python3 python/fetch_config.py

2. **Build and run the C++ simulation** :
make clean
make
./BSOptionPricer

3. **Visualize PnL distribution**:
python3 python/plot_distribution.py

---

## 📦 Requirements
- C++17 compiler (e.g. g++, clang++)
- Python 3.9+ with packages:
  - yfinance
  - pandas
  - numpy
  - matplotlib

---

## 📚 Learning Outcomes

This project helped me to:

- Implement the Black–Scholes model in C++ efficiently
- Connect live financial data to a custom pricing engine
- Perform Monte Carlo simulations for PnL and risk analysis
- Visualize and interpret risk metrics such as VaR



