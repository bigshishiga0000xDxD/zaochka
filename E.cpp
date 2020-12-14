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
 
//#define int short
 
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
 
const int N = 1e3 + 10;
const int M = (1 << 12) + 2;
//const ll MOD = 998244353;
const ll MOD = 1e9 + 7;
const ld eps = 5e-8;
const pii dir[] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

#define set _set

struct Elem {
    int type, x, y;
};

int n, k;
char used[N][M];
Elem a[N];

inline int get(int mask, int i) {
    return mask >> i & 1;
}

inline int set(int mask, int i, int val) {
    mask &= (~0 ^ (1 << i));
    mask |= (val << i);
    return mask;
}

pii calc(int i, int mask1) {
    auto [type, x, y] = a[i];
    int mask2, j;

    if (type == 0) {
        mask2 = mask1, j = i + 1;
    }
    else if (type == 1) {
        mask2 = set(mask1, x, get(mask1, x) && get(mask1, y)), j = i + 1;
    }
    else if (type == 2) {
        mask2 = set(mask1, x, get(mask1, x) || get(mask1, y)), j = i + 1;
    }
    else if (type == 3) {
        mask2 = set(mask1, x, get(mask1, x) ^ get(mask1, y)), j = i + 1;
    }
    else if (type == 4) {
        mask2 = set(mask1, x, get(mask1, y)), j = i + 1;
    }
    else if (type == 5) {
        mask2 = set(mask1, x, y), j = i + 1;
    }
    else if (type == 6) {
        mask2 = mask1 ^ (1 << x), j = i + 1;
    }
    else {
        mask2 = mask1, j = (get(mask1, x) ? y : i + 1);
    }

    return { j, mask2 };
}

void dfs(int i, int mask1, int mask) {
    used[i][mask1] = 1;

    auto [j, mask2] = calc(i, mask1);
    if (used[j][mask2] == 1) {
        cout << "No\n";
        for (int it = 0; it < k; it++) {
            cout << get(mask, it);
        }
        cout << endl;
        exit(0);
    }

    if (j < n && !used[j][mask2]) {
        dfs(j, mask2, mask);
    }

    used[i][mask1] = 2;
}

int convert(string s) {
    if (s == "begin" || s == "end") return 0;
    if (s == "and") return 1;
    if (s == "or") return 2;
    if (s == "xor") return 3;
    if (s == "move") return 4;
    if (s == "set") return 5;
    if (s == "not") return 6;
    if (s == "jump") return 7;
    assert(false);
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cout << fixed << setprecision(9);
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        if (s == "begin" || s == "end") {
            a[i] = { convert(s), 0, 0 };
        }
        else if (s == "not") {
            int x;
            cin >> x;

            a[i] = { convert(s), x, 0 };
        }
        else {
            int x, y;
            cin >> x >> y;

            a[i] = { convert(s), x, y };
        }
    }

    for (int mask = 0; mask < (1 << k); mask++) {
        if (!used[0][mask]) {
            dfs(0, mask, mask);
        }
    }

    cout << "Yes\n";

    return 0;
}

