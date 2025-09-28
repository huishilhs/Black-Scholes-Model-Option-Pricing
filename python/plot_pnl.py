import pandas as pd
import matplotlib.pyplot as plt

# Load CSV
df = pd.read_csv("plots/PnL_results.csv")

# Plot PnL vs Time
plt.plot(df["Time"], df["PnL"], label="PnL")
plt.xlabel("Time")
plt.ylabel("PnL")
plt.title("PnL Over Time (Black-Scholes)")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()

