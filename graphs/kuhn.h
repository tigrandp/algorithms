#include <algorithm>
#include <vector>

class BipartiteGraph {
 public:
  BipartiteGraph(int num_left_nodes, int num_right_nodes)
    : n_(num_left_nodes), k_(num_right_nodes),
      graph_(n_), matching_(k_, -1), used_(n_) {}

  void AddEdge(int lhs, int rhs) {
    graph_[lhs].push_back(rhs);
  }

  int MaxMatchingSize() {
    for (int v = 0; v < n_; ++v) {
      used_.assign(n_, false);
      Kuhn(v);
    }

    int matching_size = 0;
    for (int i = 0; i < k_; ++i) {
      if (matching_[i] != -1) {
        matching_size++;
      }
    }
    return matching_size;
  }

 private:
  bool Kuhn(int v) {
    if (used_[v]) return false;
    used_[v] = true;

    for (int to : graph_[v]) {
      if (matching_[to] == -1 || Kuhn(matching_[to])) {
        matching_[to] = v;
        return true;
      }
    }

    return false;
  }

  int n_, k_;
  std::vector<char> used_;
  std::vector<int> matching_;
  std::vector<std::vector<int>> graph_;
};
