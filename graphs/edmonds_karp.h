#include <vector>
#include <queue>

class Network {
 public:
  Network(int n) : n_(n), graph_(n) {}

  void AddEdge(int from, int to, int capacity) {
    Edge e = {from, to, capacity};
    Edge re = {to, from, capacity};

    graph_[e.from].push_back(edges_.size());
    edges_.push_back(e);
    graph_[e.to].push_back(edges_.size());
    edges_.push_back(re);
  }

  long long MaxFlow(int s, int t) {
    long long flow = 0;
    while (true) {
      int delta = TryAugment(s, t);
      if (delta == 0) break;

      flow += delta;
    }

    return flow;
  }

 private:
  struct Edge { 
    Edge() : from(0), to(0), capacity(0), flow(0) {}
    Edge(int f, int t, int cap) : from(f), to(t), capacity(cap), flow(0) {}

    void DeltaCap(int delta) {
      capacity += delta;
    }

    bool CanIncrement() const {
      return flow < capacity;
    }

    int GetIncrement() const {
      return capacity - flow;
    }

    int from, to;
    int capacity, flow;
  };

  void IncrementFlow(int i, int delta) {
    edges_[i].flow += delta;
    edges_[i ^ 1].flow -= delta;
  }

  int TryAugment(int s, int t) {
    std::queue<int> q;
    std::vector<int> d(n_, -1), p(n_, -1);

    q.push(s);
    d[s] = kInf;

    while (!q.empty()) {
      int v = q.front(); q.pop();

      for (int i = 0; i < graph_[v].size(); ++i) {
        int edge_index = graph_[v][i];
        const Edge& e = edges_[edge_index];
        if (d[e.to] == -1 && e.CanIncrement()) {
          d[e.to] = std::min(d[v], e.GetIncrement());
          q.push(e.to);
          p[e.to] = edge_index;
        }
      }
    }

    if (d[t] <= 0) return 0;

    int curr = t, delta = d[t];
    while (p[curr] != -1) {
      IncrementFlow(p[curr], delta);
      curr = edges_[p[curr]].from;
    }

    return delta;
  }

  int n_;
  const int kInf = 1000000007;
  std::vector<Edge> edges_;
  std::vector<std::vector<int>> graph_;
};

