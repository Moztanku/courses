#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt

# r(θ) = sin(2θ)
def r(θ):
    return np.sin(2 * θ)

def main():
    # Create data
    θ = np.linspace(0, 2 * np.pi, 100)

    # Transform polar coordinates to cartesian
    x = r(θ) * np.cos(θ)
    y = r(θ) * np.sin(θ)

    # Plot data
    plt.plot(x, y)
    plt.show()

if __name__ == '__main__':
    main()