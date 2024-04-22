#!/usr/bin/env python3

import copy
import random
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt

def create_graph():
    G = nx.Graph()

    E = [
        (0, (1,5,6)),
        (1, (0,2)),
        (2, (1,3,7)),
        (3, (2,4)),
        (4, (3,9)),
        (5, (0,10)),
        (6, (0,7,11)),
        (7, (2,6,8)),
        (8, (4,7,13)),
        (9, (4,14)),
        (10, (5,15)),
        (11, (6,12,15)),
        (12, (11,13,17)),
        (13, (8,12,19)),
        (14, (9,19)),
        (15, (10,11,16)),
        (16, (15,17)),
        (17, (12,16,18)),
        (18, (17,19)),
        (19, (13,14,18)),
    ]

    for v, es in E:
        for e in es:
            G.add_edge(v, e)

    return G

def create_flow_matrix(G: nx.Graph) -> np.ndarray:
    n: int = G.number_of_nodes()
    M: np.ndarray = np.zeros((n, n))

    for x,y in np.ndindex(M.shape):
        if x == y:
            continue

        M[x,y] = random.randint(1, 10)

    return M

def set_a(G: nx.Graph, M: np.ndarray):
    nx.set_edge_attributes(G, 0, "a")

    for x,y in np.ndindex(M.shape):
        path = nx.shortest_path(G, x, y)
        for i in range(len(path) - 1):
            u = path[i]
            v = path[i+1]
            G[u][v]["a"] += M[x,y]

def set_c(G: nx.Graph, Capacity: int):
    nx.set_edge_attributes(G, Capacity, "c")

def T(G: nx.Graph, N: np.ndarray, m: int) -> float:
    sum: int = N.sum()
    t: float = 0

    for e in G.edges:
        u = e[0]
        v = e[1]

        t += G[u][v]["a"] / ((G[u][v]["c"] / m) - G[u][v]["a"])

    return t / sum

def reliability(G: nx.Graph, N: np.ndarray, T_max: float, p: float, m: int, iterations = 100, intervals = 5) -> float:
    counter: float = 0.0

    for _ in range(iterations):
        G_copy = copy.deepcopy(G)

        for _ in range(intervals):
            to_del = []

            for e in G_copy.edges:
                if random.random() > p:
                    to_del.append(e)

            for e in to_del:
                G_copy.remove_edge(*e)

            if not nx.is_connected(G_copy):
                break

            set_a(G_copy, N)

            t = T(G_copy, N, m)

            if 0 < t < T_max:
                counter += 1

    return counter / (iterations * intervals)

def plot_graph(G: nx.Graph):
    pos = {
        0: (0, 0),
        1: (1, 0),
        2: (2, 0),
        3: (3, 0),
        4: (4, 0),
        5: (0, 1),
        6: (1, 1),
        7: (2, 1),
        8: (3, 1),
        9: (4, 1),
        10: (0, 2),
        11: (1, 2),
        12: (2, 2),
        13: (3, 2),
        14: (4, 2),
        15: (0, 3),
        16: (1, 3),
        17: (2, 3),
        18: (3, 3),
        19: (4, 3),
    }

    # Set edge labels to attributes "a" and "c"
    # edge_labels_a = nx.get_edge_attributes(G, "a")
    # edge_labels_c = nx.get_edge_attributes(G, "c")

    # edge_labels = {k: f"a: {edge_labels_a[k]}, c: {edge_labels_c[k]}" for k in edge_labels_a}

    nx.draw(G, pos, with_labels=True, node_size=500, node_color="skyblue", font_size=8, font_weight="bold")
    # nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_color="black", font_size=8, font_weight="bold")

    # Draw both edge labels

    plt.show()

def test_1(G: nx.Graph, N: np.ndarray, m: int):
    G_copy = copy.deepcopy(G)
    N_copy = copy.deepcopy(N)

    n: int = 15
    i: int = 10

    p: float = 0.95
    T_max: float = 0.5

    results: list[(int, float)] = []

    k: int = 1
    for _ in range(n):
        k *= 2
        N_copy *= 2

        r: float = 0
        for _ in range(i):
            r += reliability(G_copy, N_copy, T_max, p, m)

        results.append((k, r / i))

    plt.plot([r[0] for r in results], [r[1] for r in results])
    plt.show()

def test_2(G: nx.Graph, N: np.ndarray, m: int):
    G_copy = copy.deepcopy(G)
    N_copy = copy.deepcopy(N)

    n: int = 10
    i: int = 10

    p: float = 0.99
    T_max: float = 0.5

    Capacity: int = 8*256

    results: list[(int, float)] = []

    k: int = 1
    for _ in range(n):
        k += 1
        set_c(G_copy, Capacity * k)

        r: float = 0
        for _ in range(i):
            r += reliability(G_copy, N_copy, T_max, p, m)

        results.append((k, r / i))

    plt.plot([r[0] for r in results], [r[1] for r in results])
    plt.show()

def test_3(G: nx.Graph, m: int):
    G_copy = copy.deepcopy(G)

    n: int = 20
    i: int = 10
    
    p: float = 0.9
    T_max: float = 0.5

    results: list[(int, float)] = []

    k: int = 0
    for _ in range(n):
        k += 1

        u, v = 0, 0
        # Check if u and v are different and if there isn't already an edge between them
        while u == v or G_copy.has_edge(u, v):
            u = random.randint(0, 19)
            v = random.randint(0, 19)

        G_copy.add_edge(u, v)
        N: np.ndarray = create_flow_matrix(G_copy)

        set_a(G_copy, N)
        set_c(G_copy, m*1000*1024)

        r: float = 0

        for _ in range(i):
            r += reliability(G_copy, N, T_max, p, m)

        results.append((k, r / i))

    plt.plot([r[0] for r in results], [r[1] for r in results])
    plt.show()

def main():
    G: nx.Graph = create_graph()
    N: np.ndarray = create_flow_matrix(G)

    print(N)

    m: int = 8

    set_a(G, N)
    set_c(G, m*1000*1024)

    # plot_graph(G)

    # test_1(G, N, m)
    # test_2(G, N, m)
    # test_3(G, m)

if __name__ == "__main__":
    main()