#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt

# Generate data points
u = np.linspace(-2, 2, 100)
v = np.linspace(-2, 2, 100)
u, v = np.meshgrid(u, v)

x = u * v
y = u
z = v**2

# Plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(x, y, z, cmap='viridis')

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()