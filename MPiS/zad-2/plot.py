import math
import matplotlib.pyplot as plot
import numpy as np
import math
import csv

def main():
    n = []
    Bn = []
    Un = []
    Ln = []
    Cn = []
    Dn = []
    Diff = []
    with open('data.csv', newline='\n') as csvfile:
        reader = csv.DictReader(csvfile,delimiter=';')
        for row in reader:
            n.append(row['N'])
            Bn.append(row['Bn'])
            Un.append(row['Un'])
            Ln.append(row['Ln'])
            Cn.append(row['Cn'])
            Dn.append(row['Dn'])
            Diff.append(row['Diff'])


    fig,ax = plot.subplots()
    
    #ax.scatter(np.array(n,int),np.array(Diff,int),s=1.0,c='blue')
    ax.ticklabel_format(style='plain')
    AvgX = np.arange(1000,101000,1000)
    AvgY = avg(np.array(Diff,int))
    # ax.scatter(AvgX,AvgY,s=4.0,c='red')

    plot.xlabel("N")
    plot.ylabel("d(n)-c(n)/n^2")

    plot.grid(True)

    ax.plot(AvgX,AvgY)
    plot.show()

def avg(x : np.array):
    tab = []
    for i in range(0,100):
        sum = 0
        for k in range(50):
            sum+=x[i*50+k]
        n = i*1000+1000
        tab.append((sum/50)/(n*n))
    return tab




main()