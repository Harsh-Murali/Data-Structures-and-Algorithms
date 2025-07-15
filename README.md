# Data-Structures-and-Algorithms

### **Social Network Centrality and Hierarchical Clustering System – C**

- **Built** an inverted index of shortest paths using Dijkstra’s algorithm, tracking multiple predecessors per node to accurately support graphs with multiple shortest paths.
- **Calculated** closeness and betweenness centrality by aggregating path lengths and counts across all reachable nodes, optimizing for sparse graphs by skipping unreachable paths.
- **Implemented** Lance-Williams hierarchical agglomerative clustering with dynamic distance matrix updates, merging clusters without full recomputation to reduce time and space complexity.

### **Inverted Index and Dynamic Search Ranking System – C**

- **Built** a full inverted index from scratch using a binary search tree, inserting normalized words from multiple documents and linking them to sorted file lists based on word frequency, enabling O(log n) insertion, fast lookup, and ordered output without external libraries.
- **Used** a two-layer structure of binary search tree and linked file lists to track which words appear in which documents and how often, supporting efficient per-word tracking, file ranking, and clean alphabetic printing.
- **Implemented** dynamic search ranking by calculating document scores based on word frequency inside a file and word rarity across files, handling case normalization, punctuation removal, memory allocation, and live updates safely across the entire system.
