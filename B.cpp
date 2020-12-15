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

int n, m, k;
int ans[N][N];

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cout << fixed << setprecision(9);
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    cin >> n >> m >> k;
    int r = (n * k + m - 1) / m;
    int t = (n + r - 1) / r * r;

    vector <int> a(n);
    iota(a.begin(), a.end(), 1);

    for (int i = 0; i < t; i++) {
        for (int j = 0; j < n; j++) {
            ans[i][j] = (a[j] <= m ? a[j] : 0);
        }
        rotate(a.begin(), --a.end(), a.end());
    }

    for (int j = 0; j < n; j++) {
        int cnt = 0;
        for (int i = 0; i < t; i += t / r) {
            if (cnt == k) {
                ans[i][j] = 0;
            }
            cnt += (ans[i][j] > 0);
        }
        //assert(cnt == k);
    }

    cout << r << endl;
    for (int i = 0; i < t; i += t / r) {
        for (int j = 0; j < n; j++) {
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}

