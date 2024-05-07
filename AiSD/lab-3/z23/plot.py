#!/usr/bin/env python3

import matplotlib.pyplot as plt
import sys
import os

def print_help(status: int, exec: str):
    print("Usage: " + exec + " <filename> <c | a | c/n | a/n> <opt: out-file-path>")
    sys.exit(status)

class Result:
    def __init__(self, n: int, c: float, a: float):
        self.n = n
        self.c = c
        self.a = a

def read_file(filename: str) -> dict[str, list[Result]]:
    results: dict[str, list[Result]] = {}

    with open(filename, "r") as f:
        lines = f.readlines()
        for line in lines:
            words: list[str] = line.split()
            n: int = int(words[0])
            alg: str = words[1]
            c: float = float(words[2])
            a: float = float(words[3])

            result: Result = Result(n, c, a)

            if alg not in results:
                results[alg] = []

            results[alg].append(result)

    return results

def main():
    if len(sys.argv) not in [3, 4]:
        print_help(1, sys.argv[0])

    if sys.argv[1] == "-h" or sys.argv[1] == "--help":
        print_help(0, sys.argv[0])

    filename: str = sys.argv[1]
    if not os.path.isfile(filename):
        print("Error: " + filename + " does not exist.")
        sys.exit(1)

    mode: str = sys.argv[2]
    if mode not in ["c", "a", "c/n", "a/n"]:
        print("Error: " + mode + " is not a valid mode.")
        sys.exit(1)

    output: str = sys.argv[3] if len(sys.argv) == 4 else ""
    if output != "":
        if os.path.isdir(output):
            output = os.path.join(output, "figure-{}.png".format(mode))

    results: dict[str, list[Result]] = read_file(filename)

    plt.figure(figsize=(20,10))

    for alg in results:
        x: list[int] = []
        y: list[float] = []

        for result in results[alg]:
            x.append(result.n)

            if mode == "c":
                y.append(result.c)
            elif mode == "a":
                y.append(result.a)
            elif mode == "c/n":
                y.append(result.c / result.n)
            elif mode == "a/n":
                y.append(result.a / result.n)

        plt.plot(x, y, label=alg)

    plt.xlabel("n")
    plt.ylabel(mode)
    plt.legend()
    plt.grid(True)

    if output == "":
        plt.show()
    else:
        plt.savefig(output)

if __name__ == "__main__":
    main()