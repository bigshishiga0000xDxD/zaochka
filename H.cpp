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
 
const int N = 2e5 + 10;
//const ll MOD = 998244353;
const ll MOD = 1e9 + 7;
const ld eps = 5e-8;
const pii dir[] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

#define left left228
#define right right228

int n, a[N];

int left[N], right[N];

bool solve(int x, int y) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += (y > a[i]);
        if (a[i] < y && a[i]) {
            int p = left[i];
            int q = right[i];
            int len = q - p - 1;
            if (len < y) {
                return false;
            }
        }
    }

    return (cnt < n);
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cout << fixed << setprecision(9);
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int mn = 2e9;
    for (int i = 0; i < n; i++) {
        if (a[i]) {
            mn = min(mn, a[i]);
        }
    }

    int x = 2e9;
    vector <int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] >= a[i]) {
            st.pop_back();
        }

        left[i] = (st.empty() ? -1 : st.back());

        int d = (st.empty() ? i + 1 : i - st.back());
        if (i == n - 1 || a[i + 1] < a[i]) {
            x = min(x, d);
        }

        st.push_back(i);
    }

    st.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.back()] >= a[i]) {
            st.pop_back();
        }

        right[i] = (st.empty() ? n : st.back());

        st.push_back(i);
    }

    int l = 0, r = 1e9 + 10, m, y;
    while (r - l > 1) {
        m = (l + r) / 2;

        if (solve(x, m)) {
            l = m;
        }
        else {
            r = m;
        }
    }
    y = l;

    debug(x, y);

    if (x > y) swap(x, y);

    x = min(x, mn);

    cout << x * y << endl;

    return 0;
}

