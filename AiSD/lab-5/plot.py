#!/usr/bin/env python3

import sys
import matplotlib.pyplot as plt
import math

def print_help(exec: str, status: int):
    print(f"Usage: {exec} <results-path> <output-path>")
    exit(status)

def main():
    args: list = sys.argv

    if len(args) == 2 and args[1] in ["-h", "--help"]:
        print_help(args[0], 0)

    if len(args) != 3:
        print_help(args[0], 1)

    results_path = args[1]
    output_path = args[2]

    prim_results: dict[int, float] = {}
    kruskal_results: dict[int, float] = {}

    with open(results_path, "r") as file:
        for line in file:
            if line.startswith("#"):
                continue

            n, prim_time, kruskal_time = line.split()
            prim_results[int(n)] = float(prim_time)
            kruskal_results[int(n)] = float(kruskal_time)

    plt.plot(list(prim_results.keys()), list(prim_results.values()), label="Prim")
    plt.plot(list(kruskal_results.keys()), list(kruskal_results.values()), label="Kruskal")

    # prim_log = [y / (x * math.log(x)) for x, y in prim_results.items()]
    # kruskal_log = [y / (x * math.log(x)) for x, y in kruskal_results.items()]

    # plt.plot(list(prim_results.keys()), prim_log, label="Prim")
    # plt.plot(list(kruskal_results.keys()), kruskal_log, label="Kruskal")

    plt.xlabel("Number of vertices")
    plt.ylabel("Time (ms)")

    plt.legend()
    # plt.savefig(output_path)
    plt.show()

if __name__ == "__main__":
    main()