//#pragma GCC optimize("Ofast")
 
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
 
const int N = 1e6 + 10;
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
        vector <vector <int>> cnt(max(n, 4)), cnt2(n);

        for (int i = 0; i < n; i++) {
            cnt[str[i] - 'a' + 1].push_back(i);
        }

        int ptr = 0, cls = 0;
        for (int i = 0; i < 4; i++) {
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

            for (int i = 0, j = (pw >= n ? 0 : pw); i < n; i++, j = (j + 1 == n ? 0 : j + 1)) {
                cnt[c[j]].push_back(i);
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
                int x = s[i] + pw, y = s[i - 1] + pw;
                if (x >= n) x -= n;
                if (y >= n) y -= n;

                cls += !(c[s[i]] == c[s[i - 1]] && c[x] == c[y]);
                cnew[s[i]] = cls;
            }

            for (int i = 0; i < n; i++) {
                c[i] = cnew[i];
            }
        }
    }
};

struct Tree {
    int t[N], used[N], timer = 1, sum = 0;

    void update(int i, int x) {
        sum += x;
        for (; i < N; i |= i + 1) {
            if (used[i] < timer) {
                t[i] = x;
                used[i] = timer;
            }
            else {
                t[i] += x;
            }
        }
    }

    int get(int i) {
        int res = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1) {
            if (used[i] == timer) {
                res += t[i];
            }
        }
        return res;
    }

    inline int get_suff(int l) {
        return sum - (l ? get(l - 1) : 0);
    }

    inline void clear() {
        timer++;
        sum = 0;
    }
} depth;

template <typename T>
struct Vector {
    T a[N];
    int end = 0;

    T& operator[](int i) {
        return a[i];
    }

    inline void push_back(const T& x) {
        a[end++] = x;
    }

    inline T& back() {
        return a[end - 1];
    }

    inline void pop_back() {
        end--;
    }

    inline void clear() {
        end = 0;
    }

    inline int size() {
        return end;
    }
};

const ll base = 228;

ll pw1[N], g1[N];
ll pw2[N], g2[N];

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

Vector <char> cur;
Vector <ll> h1;
Vector <ll> h2;

SuffixArray suff;
vector <int> eq[N];

int dfs_less(int u, int i, int p = -1) {
    cur.push_back(s[u]);
    h1.push_back((h1.back() * base + (s[u] - 'a' + 1)) % MOD1);
    h2.push_back((h2.back() * base + (s[u] - 'a' + 1)) % MOD2);

    int l = 0, r = min(h1.size(), sz(t)), m;

    if (s[u] != t.front()) {
        r = 0;
    }

    while (r - l > 1) {
        m = (l + r) / 2;

        ll s1 = (h1.back() - (m == sz(h1) - 1 ? 0 : pw1[m + 1] * h1[sz(h1) - m - 2]) + MOD1 * MOD1) % MOD1;
        ll s2 = (h2.back() - (m == sz(h2) - 1 ? 0 : pw2[m + 1] * h2[sz(h2) - m - 2]) + MOD2 * MOD2) % MOD2;

        if (s1 == g1[m] && s2 == g2[m]) {
            l = m;
        }
        else {
            r = m;
        }
    }

    int res;
    if (r == min(h1.size(), sz(t))) {
        res = 0;
        if (h1.size() <= sz(t)) {
            eq[i].push_back(suff.c[h1.size()]);
        }
    }
    else {
        res = (cur[sz(cur) - r - 1] < t[r]);
    }

    for (int v : g[u]) {
        if (v != p && !used[v]) {
            res += dfs_less(v, i, u);
        }
    }

    h1.pop_back();
    h2.pop_back();
    cur.pop_back();

    return res;
}

Vector <pii> st;

inline char get(int i, int j) {
    return (i + j < sz(t) ? t[i + j] : 96);
}

ll dfs_add(int u, int p = -1) {
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

    lb = L - 1, rb = r;
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
    ll res = depth.get_suff(L);

    for (int v : g[u]) {
        if (v != p && !used[v]) {
            res += dfs_add(v, u); 
        }
    }

    st.pop_back();

    return res;
}

ll dfs_decomposition(int u) {
    used[u] = 1;

    int usize = 1;
    for (int v : g[u]) {
        if (!used[v]) {
            dfs_size(v);
            usize += sz[v];
        }
    }

    ll ans = 0;

    cur.clear();
    cur.push_back(s[u]);

    h1.clear(), h1.push_back(s[u] - 'a' + 1);
    h2.clear(), h2.push_back(s[u] - 'a' + 1);

    st.clear();
    st.push_back({ 0, sz(t) + 1 });

    depth.clear();

    for (int v : g[u]) {
        if (!used[v]) {
            eq[v].clear();

            ans += 1LL * dfs_less(v, v) * (usize - sz[v]);
            ans += sz(eq[v]);

            for (int x : eq[v]) {
                depth.update(x, 1);
            }
        }
    }

    if (s[u] < t.front()) {
        ans += usize;
    }
    else if (s[u] == t.front()) {
        depth.update(suff.c[1], 1);
        ans++;
    }

    for (int v : g[u]) {
        if (!used[v]) {
            for (int x : eq[v]) {
                depth.update(x, -1);
            }

            ans += dfs_add(v);

            for (int x : eq[v]) {
                depth.update(x, 1);
            }
        }
    }

    //debug(u, ans);

    for (int v : g[u]) {
        if (!used[v]) {
            ans += dfs_decomposition(dfs_centroid(v, sz[v]));
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

    pw1[0] = 1;
    pw2[0] = 1;
    for (int i = 1; i < N; i++) {
        pw1[i] = pw1[i - 1] * base % MOD1;
        pw2[i] = pw2[i - 1] * base % MOD2;
    }

    cin >> n >> m >> t;

    t += char(96);
    suff = SuffixArray(t);

    g1[0] = (t.front() - 'a' + 1);
    g2[0] = (t.front() - 'a' + 1);
    for (int i = 1; i < m; i++) {
        g1[i] = (g1[i - 1] + (t[i] - 'a' + 1) * pw1[i]) % MOD1;
        g2[i] = (g2[i - 1] + (t[i] - 'a' + 1) * pw2[i]) % MOD2;
    }

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

