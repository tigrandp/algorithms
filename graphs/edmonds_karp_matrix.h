#include <vector>
#include <queue>

class Network {
 public:
  Network(int n) : n_(n), mat_(n, std::vector<FlowStats>(n)) {}

  void AddEdge(int from, int to, int capacity) {
    mat_[from][to].DeltaCap(capacity);
    mat_[to][from].DeltaCap(capacity);
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
  struct FlowStats { 
    FlowStats() : capacity(0), flow(0) {}
    FlowStats(int cap) : capacity(cap), flow(0) {}

    void DeltaCap(int delta) {
      capacity += delta;
    }

    bool CanIncrement() const {
      return flow < capacity;
    }

    int GetIncrement() const {
      return capacity - flow;
    }

    int capacity;
    int flow;
  };

  void IncrementFlow(int from, int to, int delta) {
    mat_[from][to].flow += delta;
    mat_[to][from].flow -= delta;
  }

  int TryAugment(int s, int t) {
    std::queue<int> q;
    std::vector<int> d(n_, -1), p(n_, -1);

    q.push(s);
    d[s] = kInf;

    while (!q.empty()) {
      int v = q.front(); q.pop();

      for (int u = 0; u < n_; ++u) {
        if (d[u] == -1 && mat_[v][u].CanIncrement()) {
          d[u] = std::min(d[v], mat_[v][u].GetIncrement());
          q.push(u);
          p[u] = v;
        }
      }
    }

    if (d[t] <= 0) return 0;

    int curr = t, delta = d[t];
    while (p[curr] != -1) {
      IncrementFlow(p[curr], curr, delta);
      curr = p[curr];
    }

    return delta;
  }

  int n_;
  const int kInf = 1000000007;
  std::vector<std::vector<FlowStats>> mat_;
};

