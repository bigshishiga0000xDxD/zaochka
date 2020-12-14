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
 
const int N = 1e3 + 10;
const int M = (1 << 6) + 2;
//const ll MOD = 998244353;
const ll MOD = 1e9 + 7;
const ld eps = 5e-8;
const pii dir[] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

#define set _set

struct Elem {
    string s;
    int x, y;
};

int n, k;
char dp[N][M];
Elem a[N];

inline int get(int mask, int i) {
    return mask >> i & 1;
}

inline int set(int mask, int i, int val) {
    mask &= (~0 ^ (1 << i));
    mask |= (val << i);
    return mask;
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
            a[i] = { s, 0, 0 };
        }
        else if (s == "not") {
            int x;
            cin >> x;

            a[i] = { s, x, 0 };
        }
        else {
            int x, y;
            cin >> x >> y;

            a[i] = { s, x, y };
        }
    }

    for (int start = 0; start < (1 << k); start++) {
        memset(dp, 0, sizeof dp);
        dp[0][start] = 1;

        queue <pii> q;
        q.push({ 0, start });

        while (!q.empty()) {
            auto [i, mask1] = q.front();
            q.pop();

            auto [s, x, y] = a[i];
            int mask2, j = i + 1;

            if (s == "begin" || s == "end") {
                mask2 = mask1;
            }
            if (s == "and") {
                mask2 = set(mask1, x, get(mask1, x) & get(mask1, y));
            }
            if (s == "or") {
                mask2 = set(mask1, x, get(mask1, x) | get(mask1, y));
            }
            if (s == "xor") {
                mask2 = set(mask1, x, get(mask1, x) ^ get(mask1, y));
            }
            if (s == "move") {
                mask2 = set(mask1, x, get(mask1, y));
            }
            if (s == "set") {
                mask2 = set(mask1, x, y);
            }
            if (s == "not") {
                mask2 = set(mask1, x, !get(mask1, x));
            }
            if (s == "jump") {
                mask2 = mask1;
                j = (get(mask1, x) ? y : i + 1);
            }

            if (!dp[j][mask2]) {
                dp[j][mask2] = 1;
                if (j < n) {
                    q.push({ j, mask2 });
                }
            }
        }

        bool flag = false;
        for (int mask = 0; mask < (1 << k); mask++) {
            flag |= dp[n][mask];
        }

        if (!flag) {
            cout << "No\n";
            for (int i = 0; i < k; i++) {
                cout << get(start, i);
            }
            cout << endl;
            return 0;
        }
    }

    cout << "Yes\n";

    return 0;
}

