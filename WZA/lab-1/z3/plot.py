#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt

# V(z - x^2 - y^2) z = x^2 + y^2
def V1(x, y) -> tuple:
    return x**2 + y**2

# V(z^2 - x^2 - y^2) z = +-sqrt(x^2 + y^2)
def V2(x, y) -> tuple:
    return np.sqrt(x**2 + y**2), -np.sqrt(x**2 + y**2)

# V(z - x^2 + y^2)
def V3(x, y) -> tuple:
    return x**2 - y**2

def plot_V1(fig, ax, x, y):
    X, Y = np.meshgrid(x, y)
    Z = V1(X, Y)

    # Plot data
    ax.plot_surface(X, Y, Z, cmap='viridis')

def plot_V2(fig, ax, x, y):
    X, Y = np.meshgrid(x, y)
    Z1, Z2 = V2(X, Y)

    # Plot data
    
    ax.plot_surface(X, Y, Z1, cmap='viridis')
    ax.plot_surface(X, Y, Z2, cmap='viridis')

def plot_V3(fig, ax, x, y):
    X, Y = np.meshgrid(x, y)
    Z = V3(X, Y)

    # Plot data
    ax.plot_surface(X, Y, Z, cmap='viridis')

def plot_V4(fig, ax, x, y, z):
    X, Z = np.meshgrid(x, z)
    Y = np.zeros_like(X)

    # Plot data
    ax.plot_surface(X, Y, Z)
    ax.plot(np.zeros_like(y), y, np.zeros_like(y))


def main():
    # Create figure and axis
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Create data
    x = np.linspace(-5, 5, 100)
    y = np.linspace(-5, 5, 100)
    z = np.linspace(-5, 5, 100)
    X, Y = np.meshgrid(x, y)

    # plot_V1(fig, ax, x, y)
    # plot_V2(fig, ax, x, y)
    # plot_V3(fig, ax, x, y)
    plot_V4(fig, ax, x, y, z)

    # Show plot
    plt.show()

if __name__ == "__main__":
    main()