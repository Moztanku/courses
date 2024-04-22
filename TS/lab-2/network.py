#!/usr/bin/env python3

import copy
import random
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt

def add_edges(G: nx.Graph):
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

def create_flow_matrix(G: nx.Graph) -> np.ndarray:
    n: int = G.number_of_nodes()
    M: np.ndarray = np.zeros((n, n))

    for x,y in np.ndindex(M.shape):
        if x == y:
            continue

        M[x,y] = random.randint(1, 10)

    return M

def assign_ac(G: nx.Graph, M: np.ndarray):
    nx.set_edge_attributes(G, 0, "a")

    for x,y in np.ndindex(M.shape):
        path = nx.shortest_path(G, x, y)
        for i in range(len(path) - 1):
            u = path[i]
            v = path[i+1]
            G[u][v]["a"] += M[x,y]

    nx.set_edge_attributes(G, 0, "c")

    for u,v in G.edges:
        G[u][v]["c"] = G[u][v]["a"] // 5 * 50 + 50

def T(G: nx.Graph, N: np.ndarray, m: int) -> float:
    g: int = N.sum()
    t: float = 0

    for e in G.edges:
        t += G[e[0]][e[1]]["a"] / ((G[e[0]][e[1]]["c"] / m) - G[e[0]][e[1]]["a"])

    t /= g
    return t

def reliability(G: nx.Graph, N: np.ndarray, T_max: float, p: float, m: int, n: int, i: int) -> float:
    success: int = 0
    t: float = T(G, N, m)

    for _ in range(n):
        c = copy.deepcopy(G)
        for _ in range(i):
            broken = [e for e in c.edges if random.random() < p]
            c.remove_edges_from(broken)

            if not nx.is_connected(c):
                break
            
            assign_ac(c, N)
            t = T(c, N, m)

            if t >= T_max:
                break

            success += 1
    
    return success / (n * i)

# def test1(G: nx.Graph, N: np.ndarray, T_max: float, p: float, m: int, n: int, s: int) -> list[float]:


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
    edge_labels_a = nx.get_edge_attributes(G, "a")
    edge_labels_c = nx.get_edge_attributes(G, "c")

    edge_labels = {k: f"a: {edge_labels_a[k]}, c: {edge_labels_c[k]}" for k in edge_labels_a}

    nx.draw(G, pos, with_labels=True, node_size=500, node_color="skyblue", font_size=8, font_weight="bold")
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_color="black", font_size=8, font_weight="bold")

    # Draw both edge labels

    plt.show()


def main():
    G = nx.Graph()
    add_edges(G)

    N = create_flow_matrix(G)
    assign_ac(G, N)

    plot_graph(G)

if __name__ == "__main__":
    main()