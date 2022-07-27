#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Dijkstra Algorithm
struct Edge
{
    int node;
    int cost;
    bool operator<(const Edge &ref) const
    {
        // Min heap으로 동작
        return this->cost > ref.cost;
    }
};

const int INF = 987654321;
int N, M;
int S, D;
int answer;
int graph[500][500];
;
vector<int> dist, parent[500];

int dijkstra()
{
    priority_queue<Edge> pq;
    fill(dist.begin(), dist.end(), INF);

    pq.push({S, 0});
    dist[S] = 0;

    while (!pq.empty())
    {
        Edge curr = pq.top();
        pq.pop();

        if (curr.cost > dist[curr.node])
            continue;

        for (int i = 0; i < N; ++i)
        {
            if (graph[curr.node][i] != 0 && dist[i] > dist[curr.node] + graph[curr.node][i])
            {
                dist[i] = dist[curr.node] + graph[curr.node][i];
                parent[i].clear();
                parent[i].push_back(curr.node);
                pq.push({i, dist[i]});
            }
            else if (graph[curr.node][i] != 0 && dist[i] == dist[curr.node] + graph[curr.node][i])
            {
                parent[i].push_back(curr.node);
            }
        }
    }

    return dist[D];
}

void removePath()
{
    queue<int> q;
    q.push(D);
    bool visit[500] = {
        false,
    };
    visit[D] = true;
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        for (int k : parent[curr])
        {
            graph[k][curr] = 0;

            if (!visit[k])
            {
                q.push(k);
                visit[k] = true;
            }
        }
    }
    return;
}

int main()
{
    while (1)
    {
        cin >> N >> M;

        if (N == 0 && M == 0)
            return 0;
        cin >> S >> D;

        memset(graph, 0, sizeof(graph));
        dist.resize(N);
        for (int i = 0; i < N; ++i)
            parent[i].clear();

        int u, v, cost;
        for (int i = 0; i < M; ++i)
        {
            cin >> u >> v >> cost;
            graph[u][v] = cost;
        }

        // BFS - Dijkstra
        answer = dijkstra();
        removePath();
        answer = dijkstra();

        if (answer == INF)
            cout << "-1\n";
        else
            cout << answer << "\n";
    }

    return 0;
}