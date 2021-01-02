
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

int n, m, k, r;
int ans[N][N];
vector <int> b[N];
char used[N];

bool solve(int step) {
    memset(used, 0, sizeof used);

    for (int it = 0, i = 0; it < r; it++, i = (i + step) % n) {
        while (used[i]) {
            i = (i + 1) % n;
        }

        for (int j = 0; j < n; j++) {
            ans[it][j] = b[i][j];
        }
        used[i] = 1;
        debug(step, b[i]);
    }

    bool flag = true;
    for (int j = 0; j < n; j++) {
        int cnt = 0;
        for (int i = 0; i < r; i++) {
            if (cnt == k) {
                ans[i][j] = 0;
            }
            cnt += (ans[i][j] > 0);
        }
        flag &= (cnt == k);
    }

    return flag;
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cout << fixed << setprecision(9);
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    cin >> n >> m >> k;
    r = (n * k + m - 1) / m;

    vector <int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = (i < m ? i + 1 : 0);
    }

    for (int i = 0; i < n; i++) {
        b[i] = a;

        debug(a);
        rotate(a.begin(), --a.end(), a.end());
    }

    for (int step = 1; step <= n; step++) {
        if (solve(step)) {
            cout << r << endl;
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < n; j++) {
                    cout << ans[i][j] << " ";
                }
                cout << "\n";
            }
            return 0;
        }
    }

    assert(false);

    return 0;
}

