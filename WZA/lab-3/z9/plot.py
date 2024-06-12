#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt

# Define the range for x and y values
x_vals = np.linspace(-10, 10, 400)
y_vals = np.linspace(-10, 10, 400)
X, Y = np.meshgrid(x_vals, y_vals)

# 1.
f1 = (X**2 + Y**2 + 4*Y)**2 - 16*(X**2 + Y**2)

# 2.
f2 = 2*(X**2 + 9)*(Y**2 - 16) + (X**2 - 9)**2 + (Y**2 - 16)**2

# 3.
f3 = 350*X**2*Y**2 - 225*(X**2 + Y**2) + 144*(X**4 + Y**4) + 81

# Create subplots
fig, axs = plt.subplots(1, 3, figsize=(15, 5))

# Draw the x and y axis
for ax in axs:
    ax.axhline(0, color='k', linestyle='--')
    ax.axvline(0, color='k', linestyle='--')

# Plot each equation
axs[0].contour(X, Y, f1, levels=[0], colors='b')
axs[0].set_title("Equation 1")
axs[1].contour(X, Y, f2, levels=[0], colors='g')
axs[1].set_title("Equation 2")
axs[2].contour(X, Y, f3, levels=[0], colors='r')
axs[2].set_title("Equation 3")

# Set common labels
for ax in axs:
    ax.set_xlabel("x")
    ax.set_ylabel("y")

plt.tight_layout()
plt.show()
