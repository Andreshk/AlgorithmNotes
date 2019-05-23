#pragma once
#include <memory>      // std::unique_ptr
#include <cstddef>     // size_t
#include <istream>     // graph input
#include <type_traits> // std::is_void_v, std::conditional_t
// The libraries below are used only for random graph generation
#include <vector>
#include <chrono>
#include <random>
#include <sstream>
#include <algorithm> // std::swap. std::exchange

#include <cassert>
#define vassert assert

// As standard, vertices will be labeled with consecutive nonnegative numbers
using Vertex = size_t;
// A weighted edge will be represented by a simple
// tuple-like struct, and will be ordered by weight.
template <typename W>
struct Edge { Vertex u, v; W w; };
template <typename W>
bool operator<(const Edge<W>& lhs, const Edge<W>& rhs) { return (lhs.w < rhs.w); }

// An implementation class handles directionality. Not meant to be used directly (!)
namespace impl { template <typename W> class Graph; }

// The user-facing types are "Graph" (for unweighted graphs) and "WeightedGraph<T>"
using Graph = impl::Graph<void>;
template <typename W>
using WeightedGraph = impl::Graph<W>;

// Generate an undirected, unweighted graph with n vertices and m edges.
// Warning: uses hard O(n^2) time & space due to explicit generation of all possible edges.
inline Graph makeRandomUnweighted(const Vertex n, const Vertex m);
// Generate an undirected, weighted graph with n vertices and
// m edges with random weights of type W between wmin and wmax.
// Warning: uses hard O(n^2) time & space due to explicit generation of all possible edges.
template <typename W>
WeightedGraph<W> makeRandomWeighted(const Vertex n, const Vertex m, const W wmin, const W wmax);

namespace impl {
// A vertex-weight pair. Used both by the Graph internally, as well as
// for "predecessor-distance" pair in Dijkstra & Prim algorithms.
template <typename W>
struct AdjPair { Vertex v; W w; };
template <typename W>
bool operator<(const AdjPair<W>& lhs, const AdjPair<W>& rhs) { return (lhs.w < rhs.w); }

template <typename W>
class Graph {
public:
    static const bool isWeighted = !std::is_void_v<W>;
    using AdjPair  = std::conditional_t<isWeighted, impl::AdjPair<W>, Vertex>;
    using iterator = const AdjPair*;
private:
    std::unique_ptr<AdjPair[]> neighbours;
    std::unique_ptr< size_t[]> offsets;
    size_t n, m;
public:
    explicit Graph(std::istream& is) {
        is >> n;
        is >> m;
        offsets    = std::make_unique< size_t[]>(n + 1);
        neighbours = std::make_unique<AdjPair[]>(2 * m); // Each edge is present in the adjacency lists of both of it's vertices
        size_t currOff = 0;
        for (size_t i = 0; i < n; ++i) {
            offsets[i] = currOff;
            size_t numNeighbs = 0;
            is >> numNeighbs;
            for (size_t j = 0; j < numNeighbs; ++j) {
                Vertex v = 0; // Used for debugging purposes only
                if constexpr (isWeighted) {
                    is >> neighbours[currOff].v;
                    is >> neighbours[currOff].w;
                    v = neighbours[currOff].v;
                } else {
                    is >> neighbours[currOff];
                    v = neighbours[currOff];
                }
                vassert(v < n && "Invalid vertex index!");
                vassert(v != i && "A vertex cannot be its own neighbour");
                ++currOff;
            }
        }
        vassert(currOff == 2 * m);
        offsets[n] = currOff;
    }
    iterator vBegin(const Vertex v) const {
        vassert(v < numVertices());
        return (&neighbours[offsets[v]]);
    }
    iterator vEnd(const Vertex v) const {
        vassert(v < numVertices());
        return (&neighbours[offsets[v + 1]]);
    }
    size_t numVertices() const {
        return n;
    }
    size_t numEdges() const {
        return m;
    }
};

template <typename W, typename Distr>
Graph<W> makeRandom(const size_t n, const size_t m, Distr& distr) {
    const size_t nchk2 = n * (n - 1) / 2; // Maximum number of edges
    vassert(m <= nchk2);
    static std::mt19937_64 eng{ uint64_t(std::chrono::steady_clock::now().time_since_epoch().count()) };
    // Create an array, containing all possible edges
    using AdjPair = typename impl::Graph<W>::AdjPair;
    std::vector<std::pair<Vertex,AdjPair>> allEdges(nchk2);
    size_t idx = 0;
    for (Vertex i = 0; i < n; ++i)
        for (Vertex j = i + 1; j < n; ++j)
            if constexpr (impl::Graph<W>::isWeighted) {
                allEdges[idx++] = { i,{j,distr(eng)} };
            } else {
                allEdges[idx++] = { i,j };
            }
    // Use Fisher-Yates shuffle to generate a makeRandom subset of m edges.
    // (select either m or nchk2-m edges, depending on which is smaller)
    const size_t edgesToChoose = ((m < nchk2 / 2) ? m : nchk2 - m);
    for (size_t i = 0; i < edgesToChoose; ++i) {
        const auto choice = eng() % (nchk2 - i);
        std::swap(allEdges[i], allEdges[i + choice]);
    }
    // Locate the selected edges as a subrange of all edges
    const auto from = ((m < nchk2 / 2) ? allEdges.cbegin() : allEdges.cbegin() + nchk2 - m);
    const auto to   = ((m < nchk2 / 2) ? allEdges.cbegin() + m : allEdges.cend());
    // Separate each vertex's adjacency list
    std::vector<std::vector<AdjPair>> adjList(n);
    for (auto it = from; it != to; ++it) {
        auto& [u, p] = *it;
        if constexpr (impl::Graph<W>::isWeighted) {
            auto& [v, w] = p;
            adjList[u].push_back({ v, w });
            adjList[v].push_back({ u, w });
        } else {
            auto v = p;
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
    }
    // We don't need the edges anymore, and clear() may not deallocate the memory
    std::exchange(allEdges, {});
    // Serialize the adjacency list into the format, expected by impl::Graph<W> constructor
    std::stringstream result;
    result << n << ' ' << m << ' ';
    for (auto& lst : adjList) {
        result << lst.size() << ' ';
        for (const AdjPair& p : lst) {
            if constexpr (impl::Graph<W>::isWeighted) {
                result << p.v << ' ' << p.w << ' ';
            } else {
                result << p << ' ';
            }
        }
        // Clear up, one adjacency list at a time
        std::exchange(lst, {});
    }
    return Graph<W>{ result };
}
} // namespace impl

// We can now delegate generating of weighted & unweighted
// graphs to the single function in namespace impl.
Graph makeRandomUnweighted(const size_t n, const size_t m) {
    using Distr = std::uniform_int_distribution<int>;
    Distr dummy{}; // Dummy distribution, will not be used.
    return impl::makeRandom<void, Distr>(n, m, dummy);
}
template <typename W>
WeightedGraph<W> makeRandomWeighted(const size_t n, const size_t m, const W wmin, const W wmax) {
    static_assert(std::is_integral_v<W> || std::is_floating_point_v<W>,
        "Only numeric weights are supported for random graph generation!");
    using Distr = std::conditional_t<std::is_integral_v<W>, std::uniform_int_distribution<W>, std::uniform_real_distribution<W>>;
    Distr distr{ wmin,wmax };
    return impl::makeRandom<W, Distr>(n, m, distr);
}
