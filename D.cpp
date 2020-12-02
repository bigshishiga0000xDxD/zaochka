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
 
const int N = 5e2 + 10;
//const ll MOD = 998244353;
const ll MOD = 1e9 + 7;
const ld eps = 5e-8;
const pii dir[] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

int n, m, ans;
string s, a, cur;
vector <int> g[N];

void dfs(int u, int p = -1) {
    cur += a[u];
    ans += (cur <= s);

    for (int v : g[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }

    cur.pop_back();
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cout << fixed << setprecision(9);
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    cin >> n >> m >> s >> a;
    for (int i = 1, p; i < n; i++) {
        cin >> p;
        p--;

        g[i].push_back(p);
        g[p].push_back(i);
    } 

    for (int i = 0; i < n; i++) {
        dfs(i);
    }

    cout << ans << endl;

    return 0;
}

