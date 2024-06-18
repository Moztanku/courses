#!/usr/bin/env python3

import sys
import matplotlib.pyplot as plt

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

    class Record:
        def __init__(
                self,
                prim_u: float, prim_s: float,
                krus_u: float, krus_s: float):
            self.prim_u = prim_u
            self.prim_s = prim_s
            self.krus_u = krus_u
            self.krus_s = krus_s

    results: dict[int, Record] = {}

    with open(results_path, "r") as file:
        for line in file:
            if line.startswith("#"):
                continue

            n, pu, ps, ku, ks = line.split()

            results[int(n)] = Record(
                float(pu),
                float(ps), 
                float(ku), 
                float(ks)
            )

    plt.plot(
        list(results.keys()),
        [r.prim_u for r in results.values()],
        label="Prim unsorted"
    )
    plt.plot(
        list(results.keys()),
        [r.prim_s for r in results.values()],
        label="Prim sorted"
    )
    plt.plot(
        list(results.keys()),
        [r.krus_u for r in results.values()],
        label="Kruskal unsorted"
    )
    plt.plot(
        list(results.keys()),
        [r.krus_s for r in results.values()],
        label="Kruskal sorted"
    )

    plt.xlabel("Number of vertices")
    plt.ylabel("Number of rounds")

    plt.legend()
    # plt.savefig(output_path)
    plt.show()

if __name__ == "__main__":
    main()