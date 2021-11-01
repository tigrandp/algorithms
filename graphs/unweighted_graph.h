#include <algorithm>
#include <cassert>
#include <vector>
#include <cstdio>

class UnweightedGraph {
 public:
  explicit UnweightedGraph(int n) : n_(n) {
    adj_list_.clear();
    adj_list_.resize(n_);
  }

  void AddEdge(int u, int v) {
    adj_list_[u].push_back(v);
  }

  // Returns true if the graph has cycles.
  //
  // Runtime complexity: O(N + M).
  bool HasCycles() const {
    return FindCyclesInternal();
  }

  // Returns the list of nodes in toplogical traversal order.
  //
  // Runtime complexity: O(N + M).
  std::vector<int> TopsortTraversal() const {
    std::vector<int> traversal;
    bool has_cycle = FindCyclesInternal(&traversal);
    std::reverse(traversal.begin(), traversal.end());
    if (has_cycle) traversal.clear();

    return traversal;
  }

 private:
  // Potential colors during the depth first search traversal:
  //   * WHITE - the nodes hasn't been processed.
  //   * GREY - the node hasn't been fully processed, WIP.
  //   * BLACK - the node has been fully processed.
  enum DfsColors { WHITE, GREY, BLACK };

  bool FindCyclesInternal(std::vector<int>* traversal = nullptr) const {
    std::vector<DfsColors> nodes_colors(n_, DfsColors::WHITE);
    for (int v = 0; v < n_; ++v) {
      if (nodes_colors[v] == DfsColors::WHITE) {
        bool backwards_edge = false;
        Dfs(v, &backwards_edge, &nodes_colors, traversal);
        if (backwards_edge) return true;
      }
    }
    return false;
  }

  void Dfs(int v,
           bool* backwards_edge,
           std::vector<DfsColors>* nodes_colors,
           std::vector<int>* traversal) const {
    (*nodes_colors)[v] = DfsColors::GREY;
    for (int to : adj_list_[v]) {
      if ((*nodes_colors)[to] == DfsColors::GREY) {
        *backwards_edge = true;
      }
      if ((*nodes_colors)[to] == DfsColors::WHITE) {
        Dfs(to, backwards_edge, nodes_colors, traversal);
      }
    }
    (*nodes_colors)[v] = DfsColors::BLACK;
    if (traversal != nullptr) {
      traversal->push_back(v);
    }
  }

  // Number of nodes in the graph.
  int n_;
  // Adjacency list for each of the nodes.
  std::vector<std::vector<int>> adj_list_;
};
