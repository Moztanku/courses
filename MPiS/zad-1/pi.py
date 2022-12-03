import matplotlib.pyplot as plot
import math
import random

def main():
    x = []
    y = []

    avgX = []
    avgY = []
    for n in range(50,5001,50):
        sum = 0.0
        for j in range(50):
            result = pi(n)
            x.append(n)
            y.append(result)
            sum+=result
        avgX.append(n)
        avgY.append(sum/50)
    plot.scatter(x,y,s=0.1,c='blue')
    plot.axline((0,3.14159),(5000,3.14159),c='green')
    plot.scatter(avgX,avgY,s=5,c='red')
    plot.show()

def pi(n: int) -> float:
    C = 0
    for i in range(n):
        if(randomPoint()):
            C+=1
    return (C/n)*4

def randomPoint() -> bool:
    x = random.random()
    y = random.random()

    return math.dist([x,y],[0.5,0.5]) <= 0.5

main()