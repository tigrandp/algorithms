#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>
#include <cstdio>
#include <queue>

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

  std::vector<std::pair<int, int>> FindBridges() const {
    int timer = 0;
    std::vector<bool> used(n_, false);
    std::vector<int> tin(n_), fup(n_);
    std::vector<std::pair<int, int>> bridges;
    const std::function<void(int, int)>& add_bridge = [&bridges](int u, int v) {
      bridges.emplace_back(u, v);
    };
    for (int v = 0; v < n_; ++v) {
      if (!used[v]) {
        Dfs(v, timer, used, tin, fup, add_bridge);
      }
    }
    return bridges;
  }

  // Returns the shortests path between the given nodes.
  //
  // Runtime complexity: O(N + M).
  std::vector<int> ShortestPath(int source, int target) const {
    // Distance from source.
    std::vector<int> d(n_, -1);
    // Parent of nodes in the shortest path.
    std::vector<int> p(n_, -1);

    std::queue<int> q;
    q.push(source);
    d[source] = 0;

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (int to : adj_list_[u]) {
        if (d[to] == -1) {
          d[to] = d[u] + 1;
          q.push(to);
          p[to] = u;
        }
      }
    }

    // No path from source to target.
    if (d[target] == -1) {
      return std::vector<int>();
    }

    std::vector<int> answer;
    while (p[target] != -1) {
      answer.push_back(target);
      target = p[target];
    }
    answer.push_back(source);
    std::reverse(answer.begin(), answer.end());

    return answer;
  }

 private:
  // Potential colors during the depth first search traversal:
  //   * WHITE - the nodes hasn't been processed.
  //   * GREY - the node hasn't been fully processed, WIP.
  //   * BLACK - the node has been fully processed.
  enum DfsColors { WHITE, GREY, BLACK };

  void Dfs(int v,
           int& timer,
           std::vector<bool>& used,
           std::vector<int>& tin,
           std::vector<int>& fup,
           const std::function<void(int, int)>& bridge_func,
           int parent = -1) const {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (int to : adj_list_[v]) {
      if (to == parent) continue;
      if (used[to])
        fup[v] = std::min(fup[v], tin[to]);
      else {
        Dfs(to, timer, used, tin, fup, bridge_func, v);
        fup[v] = std::min(fup[v], fup[to]);
        if (fup[to] > tin[v]) {
          bridge_func(v, to);
        }
      }
    }
  }

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
