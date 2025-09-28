import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv("plots/PnL_distribution.csv")
pnls = df["FinalPnL"]

# Value at Risk (5% percentile)
var_95 = np.percentile(pnls, 5)

# Plot histogram
plt.hist(pnls, bins=50, edgecolor="black", alpha=0.7)
plt.axvline(var_95, color="red", linestyle="--", label=f"5% VaR = {var_95:.2f}")
plt.axvline(np.mean(pnls), color="blue", linestyle=":", label=f"Mean = {np.mean(pnls):.2f}")
plt.title("Final PnL Distribution (Monte Carlo)")
plt.xlabel("Final PnL")
plt.ylabel("Frequency")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

