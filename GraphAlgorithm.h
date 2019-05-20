#pragma once
#include "Graph.h"
#include "UnionFind.h"
#include "pairing_heap.h" // from Andreshk/AdvancedDataStructures repo
#include <vector>
#include <algorithm> // std::sort

// Example usage:
//   const auto g = makeRandomWeighted<int>(8, 15, 1, 5);
//   const auto mstEdges = Kruskal(g);
//   int totalWeight = 0;
//   std::cout << g << "MST edges:";
//   for (const auto& e : mstEdges) {
//       std::cout << " (" << e.u << ',' << e.v << "){" << e.w << '}';
//       totalWeight += e.w;
//   }
//   std::cout << "\nMST weight = " << totalWeight << "\n\n";
template <typename W>
std::vector<Edge<W>> Kruskal(const WeightedGraph<W>& graph) {
    // First, build the list of all edges
    std::vector<Edge<W>> edges(graph.numEdges());
    size_t idx = 0;
    for (Vertex u = 0; u < graph.numVertices(); ++u) {
        const auto from = graph.vBegin(u);
        const auto to = graph.vEnd(u);
        for (auto it = from; it != to; ++it) {
            const auto& [v, w] = *it;
            if (u < v) { // Do not count the edges twice (!)
                edges[idx++] = { u,v,w };
            }
        }
    }
    // Sort the edges by weight
    std::sort(edges.begin(), edges.end());
    const size_t n = graph.numVertices();
    // Initialize the disjoint set with n elements, each in its own component
    UnionFind uf{ n };
    std::vector<Edge<W>> treeEdges;
    treeEdges.reserve(n - 1);
    // Until n-1 edges have been added (or the list is exhausted)
    for (const auto& e : edges) {
        if (treeEdges.size() == n - 1)
            break;
        // Union uses Find internally to determine whether the two vertices are already
        // in the same component, and returns true on successful union (false otherwise).
        if (uf.Union(e.u, e.v)) {
            treeEdges.push_back(e);
        }
    }
    return treeEdges;
}

// Example usage:
//   const auto g = makeRandomWeighted<int>(8, 15, 1, 5);
//   const auto dists = Dijkstra(g, 0);
//   std::cout << "Distances from vertex 0:";
//   for (size_t i = 0; i < dists.size(); ++i) {
//       std::cout << ' ' << i << "<-" << dists[i].first << '{' << dists[i].second << '}';
//   }
//   std::cout << "\n\n";
template <typename W>
std::vector<typename WeightedGraph<W>::AdjPair> Dijkstra(const WeightedGraph<W>& graph, const Vertex u) {
    using AdjPair = typename WeightedGraph<W>::AdjPair;
    const size_t n = graph.numVertices();
    const W infinity = std::numeric_limits<W>::max();
    // The result: for each vertex i, result[i].first is the predecessor of i,
    // and result[i].second is the minimum distance from the starting vertex to i.
    // Of course, if the predecessors aren't needed, this can be simplified to vector<W>.
    std::vector<AdjPair> result(n);
    for (Vertex i = 0; i < n; ++i) {
        result[i] = { i, infinity };
    }
    // The data structure is at the core of the algorithm
    PairingHeap<AdjPair> ph{};
    // These proxies allow us to access the values, stored in the heap for each vertex.
    std::vector<decltype(ph)::proxy> proxies(n);
    std::vector<bool> visited(n, false);
    // In the beginning, all vertices are at distance infinity.
    proxies[u] = ph.insert({ u,0 });
    while (!ph.empty()) {
        const auto [v, dist] = ph.extractMin();
        // Once a vertex is extracted, we know it's final distance from the start.
        result[v].w = dist;
        visited[v] = true;
        proxies[v] = decltype(ph)::proxy{}; // the proxy is invalid anyways
        const auto from = graph.vBegin(v);
        const auto to   = graph.vEnd(v);
        // Try inserting/relaxing each unvisited neighbour of the current vertex.
        for (auto it = from; it != to; ++it) {
            const auto& [v1, w] = *it;
            if (!visited[v1]) {
                const AdjPair newEdge{ v1,dist + w };
                if (!proxies[v1]) { // Insert a vertex into the heap
                    proxies[v1] = ph.insert(newEdge);
                    result[v1].v = v;
                } else if (ph.decreaseKey(proxies[v1], newEdge)) {
                    // If decreaseKey() was successful, then v1 should have a new predecessor.
                    result[v1].v = v;
                }
            }
        }
    }
    return result;
}

// Example usage: same as Kruskal's algorithm
template <typename W>
std::vector<Edge<W>> Prim(const WeightedGraph<W>& graph) {
    using AdjPair = typename WeightedGraph<W>::AdjPair;
    const size_t n = graph.numVertices();
    const W infinity = std::numeric_limits<W>::max();
    // For each vertex i, preds[i].v is the vertex, whose edge to i is included
    // in the MST when adding i, and preds[i].w is this edge's weight.
    std::vector<AdjPair> preds(n);
    for (Vertex i = 0; i < n; ++i) {
        preds[i] = { i, infinity };
    }
    // The data structure is at the core of the algorithm
    PairingHeap<AdjPair> ph{};
    // These proxies allow us to access the values, stored in the heap for each vertex.
    std::vector<decltype(ph)::proxy> proxies(n);
    std::vector<bool> visited(n, false);
    // In the beginning, all vertices are at distance infinity.
    proxies[0] = ph.insert({ 0,0 });
    while (!ph.empty()) {
        const auto [v, dist] = ph.extractMin();
        // Once a vertex is extracted, it is considered added to the MST.
        preds[v].w = dist;
        visited[v] = true;
        proxies[v] = decltype(ph)::proxy{}; // the proxy is invalid anyways
        const auto from = graph.vBegin(v);
        const auto to   = graph.vEnd(v);
        // Try inserting/relaxing each unvisited neighbour of the current vertex.
        for (auto it = from; it != to; ++it) {
            const auto& [v1, w] = *it;
            if (!visited[v1]) {
                const AdjPair newEdge{ v1, w };
                if (!proxies[v1]) { // Insert a vertex into the heap
                    proxies[v1] = ph.insert(newEdge);
                    preds[v1].v = v;
                } else if (ph.decreaseKey(proxies[v1], newEdge)) {
                    // If decreaseKey() was successful, then v1 should have a new predecessor.
                    preds[v1].v = v;
                }
            }
        }
    }
    std::vector<Edge<W>> treeEdges;
    treeEdges.reserve(n - 1);
    // Skip vertex 0, since we started building the MST from it.
    for (Vertex i = 1; i < n; ++i) {
        const auto& [v, w] = preds[i];
        if (w != infinity) {
            treeEdges.push_back({ i,v,w });
        }
    }
    return treeEdges;
}
