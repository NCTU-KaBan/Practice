#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct State {
    int data[9];
    bool operator < (const State &s) const {
        for (int i = 0 ; i < 9 ; i++)
            if (data[i] != s.data[i])
                return data[i] < s.data[i];
        return false;
    }
    bool operator == (const State &s) const {
        for (int i = 0 ; i < 9 ; i++)
            if (s.data[i] != data[i]) return false;
        return true;
    }
};
struct Edge {
    State v; int w;
    bool operator > (const Edge &b) const {
        return w > b.w;
    }
};
const int INF = 0x3f3f3f3f;
vector<vector<int> > rule;
map<State, int> d;
int ch, cv;
int Dijk(State &s, State &t) {
    priority_queue<Edge, vector<Edge>, greater<Edge> > pq;
    d[s] = 0; pq.push((Edge){s, d[s]});
    while (pq.size()) {
        auto p = pq.top(); pq.pop();
        State u = p.v;
        if (d[u] < p.w) continue;
        if (u == t) return d[u];
        int idx = -1;
        for (int i = 0 ; i < 9 ; i++)
            if (u.data[i] == 0)
                idx = i;
        for (int i = 0 ; i < 4 ; i++) {
            int cost;
            if (i < 2) {
                cost = ch;
            } else 
                cost = cv;
            State next = u;
            swap(next.data[idx], next.data[rule[idx][i]]);
            if (d.count(next) == 0) d[next] = INF;
            if (d[next] > d[u] + cost) {
                d[next] = d[u] + cost;
                pq.push((Edge){next, d[next]});
            }
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    rule.resize(9);
    rule[0].push_back(1); rule[0].push_back(8); rule[0].push_back(6); rule[0].push_back(3);
    rule[1].push_back(2); rule[1].push_back(0); rule[1].push_back(7); rule[1].push_back(4);
    rule[2].push_back(3); rule[2].push_back(1); rule[2].push_back(5); rule[2].push_back(8);
    rule[3].push_back(4); rule[3].push_back(2); rule[3].push_back(0); rule[3].push_back(6);
    rule[4].push_back(3); rule[4].push_back(5); rule[4].push_back(1); rule[4].push_back(7);
    rule[5].push_back(6); rule[5].push_back(4); rule[5].push_back(2); rule[5].push_back(8);
    rule[6].push_back(7); rule[6].push_back(5); rule[6].push_back(0); rule[6].push_back(3);
    rule[7].push_back(6); rule[7].push_back(8); rule[7].push_back(1); rule[7].push_back(4);
    rule[8].push_back(0); rule[8].push_back(7); rule[8].push_back(2); rule[8].push_back(5);
    while (cin >> ch >> cv && (ch || cv)) {
        d.clear();
        State s; for (int i = 0 ; i < 9 ; i++) cin >> s.data[i];
        State t; for (int i = 0 ; i < 9 ; i++) cin >> t.data[i];
        cout << Dijk(s, t) << '\n';
    }

}
