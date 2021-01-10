//#pragma GCC optimize("O3")
 
#ifdef LOCAL
#include "debug.h"
#else
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define debug(x...)
#endif

using namespace std;
 
//#define int ll
 
typedef long long ll;
typedef long double ld;
typedef pair <int, int> pii;
#define sz(x) int((x).size())
 
template <typename T>
using ordered_set = __gnu_pbds::tree <T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
 
#ifdef ONLINE_JUDGE
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#else
mt19937 rng(1000 - 7);
#endif
 
const int N = 1e5 + 10;
const int W = 1e6 + 10;
//const ll MOD = 998244353;
const ll MOD = 1e9 + 7;
const ld eps = 5e-8;
const pii dir[] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

int n;
vector <pii> g[N];
char used[N];
int sz[N];

void dfs_size(int u, int p = -1) {
    sz[u] = 1;
    for (auto [v, w] : g[u]) {
        if (v != p && !used[v]) {
            dfs_size(v, u);
            sz[u] += sz[v];
        }
    }
}

int dfs_centroid(int u, int m, int p = -1) {
    for (auto [v, w] : g[u]) {
        if (v != p && !used[v] && sz[v] > m / 2) {
            return dfs_centroid(v, m, u);
        }
    }
    return u;
}

template <typename T>
struct Array {
    T a[W];
    int time[W], timer = 1;

    T& operator[](int i) {
        if (time[i] < timer) {
            a[i] = 0;
            time[i] = timer;
        }
        return a[i];
    }

    inline void clear() {
        timer++;
    }
};

vector <int> d[W];
ll paths[W];

struct Solver {
    Array <int> cnt;

    void clear() {
        cnt.clear();
    }

    void add(int x) {
        for (int y : d[x]) {
            cnt[y]++;
        }
    }

    void solve(int x) {
        for (int y : d[x]) {
            paths[y] += 2 * (cnt[y] + 1);
        }
    }
} solver;

void dfs_add(int u, vector <int>& a, int cur, int p = -1) {
    a.push_back(cur); 
    for (auto [v, w] : g[u]) {
        if (v != p && !used[v]) {
            dfs_add(v, a, __gcd(cur, w), u);
        }
    }
}

vector <int> b;

void dfs_decomposition(int u) {
    used[u] = 1;

    solver.clear();
    for (auto [v, w] : g[u]) {
        if (!used[v]) {
            b.clear();
            dfs_add(v, b, w);

            for (int x : b) {
                solver.solve(x);
            }
            for (int x : b) {
                solver.add(x);
            }
        }
    }

    for (auto [v, w] : g[u]) {
        if (!used[v]) {
            dfs_size(v);
            dfs_decomposition(dfs_centroid(v, sz[v]));
        }
    }
}

void calc() {
    for (int i = 1; i < W; i++) {
        if (i % 6 == 0) {
            d[i].reserve(50);
        }
        else {
            d[i].reserve(25);
        }
    }

    for (int i = W - 1; i; i--) {
        for (int x = i; x < W; x += i) {
            d[x].push_back(i);
        }
    }
    //exit(0);
}

ll dp[W];

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cout << fixed << setprecision(9);
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    calc();

    cin >> n;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;

        g[u].push_back({ v, w });
        g[v].push_back({ u, w });
    }

    b.reserve(n);

    dfs_size(1);
    dfs_decomposition(dfs_centroid(1, n));

    ll ans = 0;
    for (int i = W - 1; i; i--) {
        dp[i] = paths[i];
        for (int j = 2 * i; j < W; j += i) {
            dp[i] -= dp[j];
        }
        ans += i * dp[i];
    }

    cout << ans << endl;

    return 0;
}

