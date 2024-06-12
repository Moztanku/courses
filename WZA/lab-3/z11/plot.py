#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt

# Define the parameter t
t1 = np.linspace(-1, 1, 1000)
t2 = np.linspace(-10, 10, 5000)
t3 = np.linspace(-100, 100, 10000)

def plot(ax, t, title):
    x = (1 - t**2) / (1 + t**2)
    y = (2 * t) / (1 + t**2)

    ax.plot(x, y)
    ax.set_title(title)

# Create subplots
fig, axs = plt.subplots(1, 3, figsize=(15, 5))

# Draw the x and y axis
for ax in axs:
    ax.axhline(0, color='k', linestyle='--')
    ax.axvline(0, color='k', linestyle='--')

# Plot each equation
plot(axs[0], t1, "t ∈ [-1, 1]")
plot(axs[1], t2, "t ∈ [-10, 10]")
plot(axs[2], t3, "t ∈ [-100, 100]")

# Set common labels
for ax in axs:
    ax.set_xlabel("x")
    ax.set_ylabel("y")

# Set limits (-1.1, 1.1) for x and y axis
for ax in axs:
    ax.set_xlim(-1.1, 1.1)
    ax.set_ylim(-1.1, 1.1)

plt.tight_layout()
plt.show()
