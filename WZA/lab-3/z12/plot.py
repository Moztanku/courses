#!/usr/bin/env python3

import math
import numpy as np
import matplotlib.pyplot as plt

def f(a: float):
    def g(t: float):
        return (1 / np.cos(t)) + a * np.cos(t)
    
    return g

def plot(ax, a, t):
    r = f(a)(t)
    x = r * np.cos(t)
    y = r * np.sin(t)

    ax.plot(x, y)
    ax.set_title(f"a = {a}")

# Define the parameter t
t = np.linspace(0, 2 * math.pi, 1000)

# A list of values for a
a_vals = [-4, -2, 0, 1, 2, 3]
a_size = len(a_vals)

# Create subplots
fig, axs = plt.subplots(2, a_size // 2, figsize=(15, 10))

# Draw the x and y axis
for ax in axs.flat:
    ax.axhline(0, color='k', linestyle='--')
    ax.axvline(0, color='k', linestyle='--')

# Plot each equation
for i, a in enumerate(a_vals):
    plot(axs[i // 3, i % 3], a, t)

# Set common labels
for ax in axs.flat:
    ax.set_xlabel("x")
    ax.set_ylabel("y")

# Set limits (-5.0, 5.0) for x and y axis
for ax in axs.flat:
    ax.set_xlim(-5, 5)
    ax.set_ylim(-5, 5)

plt.tight_layout()
plt.show()