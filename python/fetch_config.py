import yfinance as yf
import datetime
import csv

# === User Configuration ===
ticker_symbol = "AAPL"
target_days_to_expiry = 90          # Target approx. 3 months
is_call = 1                         # 1 = call, 0 = put
steps = 100                         # Time steps for simulation
r = 0.045                           # Approximate risk-free rate (can also fetch from FRED)
# ===========================

# Create output directory if needed
import os
os.makedirs("data", exist_ok=True)

# Fetch live data
ticker = yf.Ticker(ticker_symbol)
spot = ticker.history(period="1d")["Close"].iloc[-1]

# Choose nearest expiration
expiries = ticker.options
if not expiries:
    raise ValueError("No options available for this ticker.")

# Select expiry closest to target
today = datetime.date.today()
expiry_dates = [datetime.datetime.strptime(date, "%Y-%m-%d").date() for date in expiries]
expiry = min(expiry_dates, key=lambda d: abs((d - today).days - target_days_to_expiry))
T = (expiry - today).days / 365
expiry_str = expiry.strftime("%Y-%m-%d")

print(f"Using expiration date: {expiry_str} ({(expiry - today).days} days to expiry)")

# Get option chain for selected expiry
opt_chain = ticker.option_chain(expiry_str)
options = opt_chain.calls if is_call else opt_chain.puts

# Pick strike closest to ATM
options["distance"] = abs(options["strike"] - spot)
selected = options.sort_values("distance").iloc[0]

K = selected["strike"]
sigma = selected["impliedVolatility"]

# Round values
S0 = round(spot, 2)
K = round(K, 2)
sigma = round(sigma, 4)
T = round(T, 4)

# Write to CSV
with open("data/input.csv", mode="w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["S0", "K", "r", "sigma", "T", "steps", "isCall"])
    writer.writerow([S0, K, r, sigma, T, steps, is_call])

print("✅ input.csv saved:")
print(f"  Spot:   {S0}")
print(f"  Strike: {K}")
print(f"  Vol:    {sigma}")
print(f"  T:      {T} years")
