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
 
#define int ll
 
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
 
const int N = 5e3 + 10;
//const ll MOD = 998244353;
const ll MOD1 = 1e9 + 7;
const ll MOD2 = 1e9 + 9;
const ld eps = 5e-8;
const pii dir[] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

struct SuffixArray {
    SuffixArray() {}

    int s[N], c[N];

    int operator[](int i) const {
        return s[i];
    }

    SuffixArray(const string& str) {
        int n = str.size();
        vector <vector <int>> cnt(max(n, 256LL)), cnt2(n);

        for (int i = 0; i < n; i++) {
            cnt[str[i]].push_back(i);
        }

        int ptr = 0, cls = 0;
        for (int i = 0; i < 256; i++) {
            for (int pos : cnt[i]) {
                s[ptr++] = pos;
                c[pos] = cls;
            }
            cls += (!cnt[i].empty());
        }

        vector <int> cnew(n);
        for (int pw = 1; pw <= n; pw *= 2) {
            for (int i = 0; i < n; i++) {
                cnt[i].clear();
                cnt2[i].clear();
            }

            for (int i = 0; i < n; i++) {
                cnt[c[(i + pw) % n]].push_back(i);
            }

            for (int i = 0; i < n; i++) {
                for (int j : cnt[i]) {
                    cnt2[c[j]].push_back(j);
                }
            }

            ptr = 0;
            for (int i = 0; i < n; i++) {
                for (int j : cnt2[i]) {
                    s[ptr++] = j;
                }
            }

            cls = cnew[s[0]] = 0;
            for (int i = 1; i < n; i++) {
                cls += !(c[s[i]] == c[s[i - 1]] && c[(s[i] + pw) % n] == c[(s[i - 1] + pw) % n]);
                cnew[s[i]] = cls;
            }

            for (int i = 0; i < n; i++) {
                c[i] = cnew[i];
            }
        }
    }
};

int n, m;
vector <int> g[N];
string t;
char s[N];

char used[N];
int sz[N];

void dfs_size(int u, int p = -1) {
    sz[u] = 1;
    for (int v : g[u]) {
        if (v != p && !used[v]) {
            dfs_size(v, u);
            sz[u] += sz[v];
        }
    }
}

int dfs_centroid(int u, int m, int p = -1) {
    for (int v : g[u]) {
        if (v != p && !used[v] && sz[v] > m / 2) {
            return dfs_centroid(v, m, u);
        }
    }
    return u;
}

bool strless(const string& x, const string& y) {
    for (int i = 0; i < int(min(x.size(), y.size())); i++) {
        if (x[i] != y[i]) {
            return x[i] < y[i];
        }
    }
    return false;
}

bool streq(const string& x, const string& y) {
    return y.substr(0, x.size()) == x;
}

string cur;

int dfs_less(int u, int p = -1) {
    cur = s[u] + cur;
    int res = strless(cur, t);

    for (int v : g[u]) {
        if (v != p && !used[v]) {
            res += dfs_less(v, u);
        }
    }

    cur.erase(cur.begin());

    return res;
}

map <int, int> depth;

void dfs_eq(int u, int mul, int p = -1, int d = 2) {
    cur = s[u] + cur;
    depth[d] += streq(cur, t) * mul;
    if (depth[d] == 0) {
        depth.erase(d);
    }

    for (int v : g[u]) {
        if (v != p && !used[v]) {
            dfs_eq(v, mul, u, d + 1);
        }
    }

    cur.erase(cur.begin());
}


int dfs_center(int u, int p = -1) {
    cur += s[u];
    int res = (cur <= t);

    for (int v : g[u]) {
        if (v != p && !used[v]) {
            res += dfs_center(v, u);
        }
    }

    cur.pop_back();

    return res;
}

int cnt[N];
vector <pii> st;
string str;

inline char get(int i, int j) {
    return (i + j < sz(str) ? str[i + j] : '$');
}

void dfs_add(int u, const SuffixArray& suff, int flag, int p = -1) {
    auto [l, r] = st.back();

    int lb = l - 1, rb = r, mid;
    while (rb - lb > 1) {
        mid = (lb + rb) / 2;

        if (get(suff[mid], sz(st) - 1) < s[u]) {
            lb = mid;
        }
        else {
            rb = mid;
        }
    }
    int L = rb;

    lb = l - 1, rb = r;
    while (rb - lb > 1) {
        mid = (lb + rb) / 2;

        if (get(suff[mid], sz(st) - 1) > s[u]) {
            rb = mid;
        }
        else {
            lb = mid;
        }
    }
    int R = rb;

    //debug(st, L, R, s[u]);

    st.push_back({ L, R });

    for (int i = L; i < sz(str); i++) {
        cnt[suff[i]] += flag;
    }

    for (int v : g[u]) {
        if (v != p && !used[v]) {
            dfs_add(v, suff, flag, u); 
        }
    }

    st.pop_back();
}

int dfs_depth(int u, int p = -1, int d = 1) {
    int res = d;
    for (int v : g[u]) {
        if (v != p && !used[v]) {
            res = max(res, dfs_depth(v, u, d + 1));
        }
    }
    return res;
}

ll dfs_decomposition(int u) {
    used[u] = 1;

    int d = 0;
    for (int v : g[u]) {
        if (!used[v]) {
            d = max(d, dfs_depth(v));
        }
    }
    int len = min(2 * d + 2, sz(t));
    
    //debug(u, len, sz(t));

    int usize = 1;
    for (int v : g[u]) {
        if (!used[v]) {
            dfs_size(v);
            usize += sz[v];
        }
    }

    ll ans = 0;
    cur = string(1, s[u]);

    for (int v : g[u]) {
        if (!used[v]) {
            ans += dfs_less(v) * (usize - sz[v]);
        }
    }

    depth.clear();
    for (int v : g[u]) {
        if (!used[v]) {
            dfs_eq(v, 1);
        }
    }

    for (auto [k, v] : depth) {
        ans += v;
    }

    str = t.substr(0, len) + '$';
    SuffixArray suff = SuffixArray(str);
    st = vector <pii> (1, make_pair(0, len + 1));

    for (int v : g[u]) {
        if (!used[v]) {
            dfs_eq(v, -1);

            dfs_add(v, suff, 1);

            for (auto [i, x] : depth) {
                ans += x * cnt[i];
            }

            dfs_add(v, suff, -1);
           
            dfs_eq(v, 1);
        }
    }

    cur.clear();
    ans += dfs_center(u); 

    //debug(u, ans);

    for (int v : g[u]) {
        if (!used[v]) {
            ans += dfs_decomposition(dfs_centroid(v, s[v]));
        }
    }
    
    return ans;
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cout << fixed << setprecision(9);
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    cin >> n >> m >> t;

    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    for (int i = 1, p; i < n; i++) {
        cin >> p;
        p--;

        g[i].push_back(p);
        g[p].push_back(i);
    }

    dfs_size(0);
    cout << dfs_decomposition(dfs_centroid(0, n)) << endl;

    return 0;
}

