#!/usr/bin/env python3

import matplotlib.pyplot as plt
import sys
import os

def print_help(status: int, exec: str):
    print("Usage: " + exec + " <filename> <out-dir>")
    sys.exit(status)

class Result:
    def __init__(
            self, N: int,
            total_cmp: int,
            total_reads: int,
            total_writes: int,

            max_cmp_per_op: int,
            max_reads_per_op: int,
            max_writes_per_op: int,

            tree_height: int,
        ):

        self.N = N
        self.total_cmp = total_cmp
        self.total_reads = total_reads
        self.total_writes = total_writes

        self.max_cmp_per_op = max_cmp_per_op
        self.max_reads_per_op = max_reads_per_op
        self.max_writes_per_op = max_writes_per_op

        self.tree_height = tree_height

def create_plot(results, attribute, out_dir):
    plt.figure(figsize=(20,10))

    for tree in results:
        x: list[int] = []
        y: list[int] = []

        for result in results[tree]:
            x.append(result.N)
            y.append(getattr(result, attribute))

        plt.plot(x, y, label=tree)

    plt.xlabel("N")
    plt.ylabel(attribute)
    plt.legend()
    plt.grid()

    plt.savefig(
        os.path.join(out_dir, attribute + ".png")
    )

def read_file(filename: str) -> dict[str, list[Result]]:
    results: dict[str, list[Result]] = {}

    with open(filename, "r") as f:
        lines = f.readlines()

        curr_tree: str = ""
        for line in lines:
            
            if line.startswith("#"):
                curr_tree = line.rstrip('\n')[1:]
                continue

            words: list[str] = line.split()

            n                   = int(words[0])
            total_cmp           = int(words[1])
            total_reads         = int(words[2])
            total_writes        = int(words[3])
            max_cmp_per_op      = int(words[4])
            max_reads_per_op    = int(words[5])
            max_writes_per_op   = int(words[6])
            tree_height         = int(words[7])

            result: Result = Result(
                n, total_cmp, total_reads, total_writes,
                max_cmp_per_op, max_reads_per_op, max_writes_per_op,
                tree_height
            )

            if curr_tree not in results:
                results[curr_tree] = []

            results[curr_tree].append(result)
    
    return results

def main():
    if len(sys.argv) != 3:
        print_help(1, sys.argv[0])

    if sys.argv[1] == "-h" or sys.argv[1] == "--help":
        print_help(0, sys.argv[0])

    filename: str = sys.argv[1]
    out_dir: str = sys.argv[2]

    if not os.path.isfile(filename):
        print("Error: " + filename + " does not exist.")
        sys.exit(1)

    if not os.path.isdir(out_dir):
        print("Error: " + out_dir + " does not exist.")
        sys.exit(1)

    results: dict[str, list[Result]] = read_file(filename)

    create_plot(results, "total_cmp", out_dir)
    create_plot(results, "total_reads", out_dir)
    create_plot(results, "total_writes", out_dir)
    create_plot(results, "max_cmp_per_op", out_dir)
    create_plot(results, "max_reads_per_op", out_dir)
    create_plot(results, "max_writes_per_op", out_dir)
    create_plot(results, "tree_height", out_dir)

if __name__ == "__main__":
    main()