#include <bits/stdc++.h>
const int maxn = 1e5 + 5;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;
using namespace std;
char s[maxn];
struct ac{
    int T[maxn<<2], lazy[maxn<<2];
    void pushup(int rt) {T[rt] = T[rt<<1] + T[rt<<1|1];}
    void pushdown(int rt, int l, int r, int mid) {
        if (lazy[rt] == -1) return;
        lazy[rt<<1] = lazy[rt<<1|1] = lazy[rt];
        if (lazy[rt] == 0) {
            T[rt<<1] = T[rt<<1|1] = 0;
        }else {
            T[rt<<1] = mid - l + 1;
            T[rt<<1|1] = r - mid;
        }
        lazy[rt] = -1;
    }
    void build(int rt, int l, int r) {
        if (l == r) {
            T[l] = 0;
            lazy[l] = -1;
            return;
        }
        int mid = (l + r) >> 1;
        build(rt<<1, l, mid);
        build(rt<<1|1, mid+1, r);
        pushup(rt);
    }
    void update(int rt, int l, int r, int ql, int qr, int d) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            if (d == 0) lazy[rt] = T[rt] = 0;
            else {
                if (lazy[rt] < 1) lazy[rt] = d;
                else lazy[rt] += d; 
                T[rt] += d * (r - l + 1);
            }
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(rt, l, r, mid);
        update(rt<<1, l, mid, ql, qr, d);
        update(rt<<1|1, mid+1, r, ql, qr, d);
        pushup(rt);
    }
    int query(int rt, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return T[rt];
        int mid = (l + r) >> 1;
        pushdown(rt, l, r, mid);
        int L = query(rt<<1, l, mid, ql, qr);
        int R = query(rt<<1|1, mid+1, r, ql, qr);
        return L + R;
    }
}seg[26];
int cnt[30];
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    scanf("%s", s);
    for (int i = 0; i < 26; ++i) seg[i].build(1, 1, n);
    for (int i = 0; i < n; ++i) seg[s[i]-'a'].update(1, 1, n, i+1, i+1, 1);
    for (int i = 0, l,r,k; i < m; ++i) {
        scanf("%d %d %d", &l, &r, &k);
        fill(cnt, cnt+30, 0);
        for (int j = 0; j < 26; ++j) {
            cnt[j] += seg[j].query(1, 1, n, l, r);
            seg[j].update(1, 1, n, l, r, 0);
        }
        int pre = 0;
        if (k == 0) {
            for (int j = 25; j >= 0; --j) {
                if (cnt[j] == 0) continue;
                seg[j].update(1, 1, n, pre+l, pre+cnt[j]+l-1, 1);
                pre += cnt[j];
            }
        }else {
            for (int j = 0; j < 26; ++j) {
                if (cnt[j] == 0) continue;
                seg[j].update(1, 1, n, pre+l, pre+cnt[j]+l-1, 1);
                pre += cnt[j];
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (seg[j].query(1, 1, n, i, i)) {
                printf("%c", j+'a');
                goto here;
            }
        }
        here:;
    }
    puts("");
    return 0;
}