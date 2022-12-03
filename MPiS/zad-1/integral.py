import matplotlib.pyplot as plot
from typing import Callable
import random
import math

def main():
    x = []
    y = []

    avgX = []
    avgY = []
    for n in range(50,5001,50):
        sum = 0.0
        for j in range(50):
            result = MonteCarlo(n,0,1,1,f3)
            x.append(n)
            y.append(result)
            sum+=result
        avgX.append(n)
        avgY.append(sum/50)
    plot.scatter(x,y,s=0.1,c='blue')
    plot.axline((0,0.2),(5000,0.2),c='green')
    plot.scatter(avgX,avgY,s=5,c='red')
    plot.show()

def MonteCarlo(n: int, a: float, b: float, M: float, f: Callable) -> float:
    C = 0
    for i in range(n):
        if(randomPoint(a,b,M,f) == True):
            C+=1
    return (C/n)*(b-a)*M

def randomPoint(a: float, b: float, M: float, f: Callable) -> bool:
    x = (random.random() * (b-a)) + a
    y = (random.random() * M)

    return y <= f(x)

def f1(x: float) -> float:
    return x**(1/3)

def f2(x: float) -> float:
    return math.sin(x)

def f3(x: float) -> float:
    return 4*x*((1-x)**3)

main()