#!/usr/bin/env python3
import numpy as np
import subprocess as sp
import matplotlib.pyplot as plt

K: int = 100
N: int = 50
Step: int = 10

color: map = {
    'quick': 'red',
    'double_quick': 'orange',
    'merge': 'blue',
    'insertion': 'green'
}

avgColor: map = {
    'quick': 'darkred',
    'double_quick': 'darkorange',
    'merge': 'darkblue',
    'insertion': 'darkgreen'
}

def plot(ax: plt.subplot, bx: plt.subplot, cx: plt.subplot, dx: plt.subplot, x: np.array, comp: np.array, swap: np.array, s: str) -> None:

    ax.set_title('Comparisions')
    ax.scatter(x, comp, label='Comparisions', color=color[s], marker='x', s=5)

    avgComp = np.zeros(int(N/Step))
    for i in range(Step, N+1, Step):
        for j in range(K):
            avgComp[int(i/Step)-1] += comp[int(i/Step-1)*K+j]
        avgComp[int(i/Step)-1] = int(avgComp[int(i/Step)-1]/K)

    ax.plot(np.arange(Step, N+1, Step), avgComp, color=avgColor[s], label='Average')

    cx.set_title('Comparisions/n')
    cx.scatter(x, comp/x, label='Comparisions/n', color=color[s], marker='x', s=5)
    cx.plot(np.arange(Step, N+1, Step), avgComp/np.arange(Step, N+1, Step), color=avgColor[s], label='Average')

    bx.set_title('Swaps')
    bx.scatter(x, swap, label='Swaps', color=color[s], marker='x', s=5)

    avgSwap = np.zeros(int(N/Step))
    for i in range(Step, N+1, Step):
        for j in range(K):
            avgSwap[int(i/Step)-1] += swap[int(i/Step-1)*K+j]
        avgSwap[int(i/Step)-1] = int(avgSwap[int(i/Step)-1]/K)

    bx.plot(np.arange(Step, N+1, Step), avgSwap, color=avgColor[s], label='Average')

    dx.set_title('Swaps/n')
    dx.scatter(x, swap/x, label='Swaps/n', color=color[s], marker='x', s=5)
    dx.plot(np.arange(Step, N+1, Step), avgSwap/np.arange(Step, N+1, Step), color=avgColor[s], label='Average')

def test(n: int, comp: np.array, swap: np.array, s: str) -> np.array:
    
    for i in range(K):
        p1 = sp.run(['./generate', str(n)], stdout=sp.PIPE, check=True)
        p2 = sp.run(['./sort', s, 'silent'], input=p1.stdout, stdout=sp.PIPE, check=True)

        [numSwap, numComp] = p2.stdout.decode().split()
        comp = np.append(comp, int(numComp))
        swap = np.append(swap, int(numSwap))

    return [comp, swap]

def main():
    quickComparisions = np.array([], dtype=np.int64)
    doubleQuickComparisions = np.array([], dtype=np.int64)
    mergeComparisions = np.array([], dtype=np.int64)
    insertionComparisions = np.array([], dtype=np.int64)

    quickSwaps = np.array([], dtype=np.int64)
    doubleQuickSwaps = np.array([], dtype=np.int64)
    mergeSwaps = np.array([], dtype=np.int64)
    insertionSwaps = np.array([], dtype=np.int64)

    for n in range(Step, N+1, Step):
        print("Performing tests for n = " + str(n) + "...")
        [quickComparisions, quickSwaps] = test(n, quickComparisions, quickSwaps, 'quick')
        [doubleQuickComparisions, doubleQuickSwaps] = test(n, doubleQuickComparisions, doubleQuickSwaps, 'double_quick')
        [mergeComparisions, mergeSwaps] = test(n, mergeComparisions, mergeSwaps, 'merge')
        [insertionComparisions, insertionSwaps] = test(n, insertionComparisions, insertionSwaps, 'insertion')

    fig = plt.figure()
    ax = fig.add_subplot(221)
    bx = fig.add_subplot(222)
    cx = fig.add_subplot(223)
    dx = fig.add_subplot(224)

    n = np.arange(Step, N+1, Step)
    x = np.array([], dtype=np.int64)

    for i in n:
        for j in range(K):
            x = np.append(x, i)

    plot(ax, bx, cx, dx, x, quickComparisions, quickSwaps, 'quick')
    plot(ax, bx, cx, dx, x, doubleQuickComparisions, doubleQuickSwaps, 'double_quick')
    plot(ax, bx, cx, dx, x, mergeComparisions, mergeSwaps, 'merge')
    plot(ax, bx, cx, dx, x, insertionComparisions, insertionSwaps, 'insertion')

    plt.show()

    return 0

if __name__ == '__main__':
    main()