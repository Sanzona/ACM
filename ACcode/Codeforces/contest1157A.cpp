#include <bits/stdc++.h>
#define LL long long
#define P pair<int, int>
#define lowbit(x) (x & -x)
#define mem(a, b) memset(a, b, sizeof(a))
#define mid ((l + r) >> 1)
#define lc rt<<1
#define rc rt<<1|1
#define endl '\n'
const int maxn = 1e5 + 5;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;
using namespace std;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    LL n;
    cin >> n;
    set<int> st;
    st.insert(n);
    while (1) {
    	n++;
    	while (n % 10 == 0) n /= 10;
    	if (st.find(n) != st.end()) break;
    	st.insert(n);
    }
    LL ans = st.size();
    cout << ans<< endl;

    return 0;
}