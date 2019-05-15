#pragma once
#include "Graph.h"
#include "UnionFind.h"
#include "pairing_heap.h" // from Andreshk/AdvancedDataStructures repo
#include <vector>
#include <algorithm> // std::sort

// Example usage:
//   const auto g = makeRandomWeighted<int>(8, 15, 1, 5);
//   const auto mstEdges = MST(g);
//   int totalWeight = 0;
//   std::cout << g << "MST edges:";
//   for (const auto& e : mstEdges) {
//       std::cout << " (" << e.u << ',' << e.v << "){" << e.w << '}';
//       totalWeight += e.w;
//   }
//   std::cout << "\nMST weight = " << totalWeight << "\n\n";
template <typename W>
std::vector<Edge<W>> MST(const WeightedGraph<W>& graph) {
    std::vector<Edge<W>> edges(graph.numEdges());
    size_t idx = 0;
    for (Vertex u = 0; u < graph.numVertices(); ++u) {
        const auto from = graph.vBegin(u);
        const auto to = graph.vEnd(u);
        for (auto it = from; it != to; ++it)
            if (u < it->first) { // Do not count the edges twice (!)
                edges[idx++] = { u,it->first,it->second };
            }
    }
    std::sort(edges.begin(), edges.end());
    const size_t n = graph.numVertices();
    UnionFind uf{ n };
    std::vector<Edge<W>> treeEdges;
    treeEdges.reserve(n - 1);
    for (const auto& e : edges) {
        if (treeEdges.size() == n - 1)
            break;
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
    std::vector<AdjPair> result(n);
    for (Vertex i = 0; i < n; ++i) {
        result[i] = { i, infinity };
    }
    PairingHeap<AdjPair> ph{};
    std::vector<decltype(ph)::proxy> proxies(n);
    std::vector<bool> visited(n, false);
    proxies[u] = ph.insert({ u,0 });
    while (!ph.empty()) {
        const auto [v, dist] = ph.extractMin();
        result[v].second = dist;
        visited[v] = true;
        proxies[v] = decltype(ph)::proxy{};
        const auto from = graph.vBegin(v);
        const auto to   = graph.vEnd(v);
        for (auto it = from; it != to; ++it) {
            const auto& [v1, w] = *it;
            if (!visited[v1]) {
                const AdjPair newEdge{ v1,dist + w };
                if (!proxies[v1]) {
                    proxies[v1] = ph.insert(newEdge);
                    result[v1].first = v;
                } else if (ph.decreaseKey(proxies[v1], newEdge)) {
                    result[v1].first = v;
                }
            }
        }
    }
    return result;
}
