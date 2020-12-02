//#pragma GCC optimize("Ofast,unroll-loops")
 
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
 
const int N = 1.5e5 + 10;
//const ll MOD = 998244353;
const ll MOD = 1e9 + 7;
const ld eps = 5e-8;
const pii dir[] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

int n, m, k, s;
ll d[N];
vector <pii> g[N];

struct Tree {
    pair <ll, int> t[4 * N];

    void build() {
        for (int i = 4 * N - 1; i > 0; i--) {
            t[i] = { 1e18, 0 };
        }
    }

    void update(int pos, ll val) {
        for (t[pos += n] = { val, pos }; pos > 1; pos >>= 1) {
            t[pos >> 1] = min(t[pos], t[pos ^ 1]);
        }
    }

    inline pair <ll, int> query() {
        return t[1];
    }
} tree;


signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cout << fixed << setprecision(9);
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    cin >> n >> m >> k >> s;

    for (int i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w;
        u--, v--;

        g[u].push_back({ v, w });
        g[v].push_back({ u, w });
    }

    vector <int> a(n);
    for (int i = 0, u; i < k; i++) {
        cin >> u;
        a[u - 1] = 1;
    }

    tree.build();

    fill(d, d + N, 1e18);
    d[0] = 0;
    tree.update(0, 0);

    while (true) {
        auto [c, u] = tree.query();
        if (c == 1e18) {
            break;
        }

        tree.update(u, 1e18);

        if (a[u] && d[u] <= s) {
            d[u] = 0;
        }

        for (auto [v, w] : g[u]) {
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                tree.update(v, d[v]);
            }
        }
    }

    vector <int> ans;
    for (int i = 0; i < n; i++) {
        if (d[i] <= s) {
            ans.push_back(i + 1);
        }
    }

    cout << sz(ans) << endl;
    for (int x : ans) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

