#pragma once
#include "Graph.h"
#include "UnionFind.h"
#include <vector>
#include <algorithm> // std::sort

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
