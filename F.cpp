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
 
const int N = 500 + 10;
//const ll MOD = 998244353;
const ll MOD = 1e9 + 7;
const ld eps = 5e-8;
const pii dir[] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

template <typename T>
struct Vector {
    T a[2 * N], end = 0;

    inline void push_back(T x) {
        a[end++] = x;
    }

    inline void clear() {
        end = 0;
    }

    inline int size() {
        return end;
    }

    T& operator[](short i) {
        return a[i];
    }
};

short n, m, a[N], p[N];
ll x[N], y[N], X[N], Y[N];

Vector <short> g[N];

short mt[2 * N], used[N], matched[N], timer;

bool dfs(short u) {
    if (used[u] == timer) return false;
    used[u] = timer;

    for (short i = 0; i < g[u].size(); i++) {
        short v = g[u][i];
        if (mt[v] == -1 || dfs(mt[v])) {
            mt[v] = u;
            return true;
        }
    }
    return false;
}

ll distance(ll x1, ll y1, ll x2, ll y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

bool check(ll t) {
    for (short i = 0; i < n; i++) {
        g[i].clear();
        for (short j = 0; j < m; j++) {
            if (distance(x[i], y[i], X[j], Y[j]) <= t) {
                for (short k = 0; k < a[j]; k++) {
                    g[i].push_back(p[j] + k);
                }
            }
        }
    }

    short cnt = 0;
    memset(mt, -1, sizeof mt);
    memset(matched, 0, sizeof matched);

    for (int u = 0; u < n; u++) {
        for (int j = 0; j < g[u].size(); j++) {
            int v = g[u][j];
            if (mt[v] == -1) {
                mt[v] = u;
                matched[u] = 1;
                cnt++;
                break;
            }
        }
    }

    for (short i = 0; i < n; i++) {
        if (!matched[i]) {
            timer++;
            cnt += dfs(i);
        }
    }

    return (cnt == n);
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cout << fixed << setprecision(10);
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (short i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    for (short i = 0; i < m; i++) {
        cin >> X[i] >> Y[i] >> a[i];
        p[i + 1] = p[i] + a[i];
    }

    ll l = -1, r = 2e12 + 5;
    while (r - l > 1) {
        ll m = (l + r) / 2;

        if (check(m)) {
            r = m;
        }
        else {
            l = m;
        }
    }

    cout << sqrt(r) << endl;

    return 0;
}

