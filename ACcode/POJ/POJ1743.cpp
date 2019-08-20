#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
using namespace std;
struct SuffixArray{ // 下标1
	int cntA[maxn], cntB[maxn], A[maxn], B[maxn];
	int Sa[maxn], tsa[maxn], height[maxn], Rank[maxn]; // Sa[i] 排名第i的下标， Rank[i] 下标i的排名
	int n, dp[maxn][21];
	void init(int *buf, int len) { // 预处理，sa，rank，height
		n = len;
		for (int i = 0; i < 256; ++i) cntA[i] = 0;
		for (int i = 1; i <= n; ++i) cntA[buf[i]]++;
		for (int i = 1; i < 256; ++i) cntA[i] += cntA[i-1];
		for (int i = n; i >= 1; --i) Sa[ cntA[buf[i]]-- ] = i;
		Rank[ Sa[1] ] = 1;
		for (int i = 2; i <= n; ++i) {
			Rank[Sa[i]] = Rank[Sa[i-1]];
			if (buf[Sa[i]] != buf[Sa[i-1]]) Rank[Sa[i]]++;
		}
		for (int l = 1; Rank[Sa[n]] < n; l <<= 1) {
			for (int i = 0; i <= n; ++i) cntA[i] = 0;
			for (int i = 0; i <= n; ++i) cntB[i] = 0;
			for (int i = 1; i <= n; ++i) {
				cntA[ A[i] = Rank[i] ]++;
				cntB[ B[i] = (i + l <= n) ? Rank[i+l] : 0]++;
			}
			for (int i = 1; i <= n; ++i) cntB[i] += cntB[i-1];
			for (int i = n; i >= 1; --i) tsa[ cntB[B[i]]-- ] = i;
			for (int i = 1; i <= n; ++i) cntA[i] += cntA[i-1];
			for (int i = n; i >= 1; --i) Sa[ cntA[A[tsa[i]]]-- ] = tsa[i];
			Rank[ Sa[1] ] = 1;
			for (int i = 2; i <= n; ++i) {
				Rank[Sa[i]] = Rank[Sa[i-1]];
				if (A[Sa[i]] != A[Sa[i-1]] || B[Sa[i]] != B[Sa[i-1]]) Rank[Sa[i]]++;
			}
		}
		for (int i = 1, j = 0; i <= n; ++i) {
			if (j) --j;
			int tmp = Sa[Rank[i] - 1];
			while (i + j <= n && tmp + j <= n && buf[i+j] == buf[tmp+j]) ++j;
			height[Rank[i]] = j;
		}
	}
	void st() {
		for (int i = 1; i <= n; ++i) {
	        dp[i][0] = height[i];
	    }
	    for (int j = 1; j <= log2(n); ++j) {
		    for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
		        dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
		    }
		}
	}
	int rmq(int l, int r) {
	    int len = r - l + 1;
	    int x = log2(len);
	    return min(dp[l][x], dp[r - (1 << x) + 1][x]);
	}
	int lcp(int x, int y) { // 最长公共前缀
		int l = Rank[x];
		int r = Rank[y];
		if (l > r) swap(l, r);
		return rmq(l+1, r);
	}
	int check(int len) {
		int mi = 1e9, mx = -1e9;
		for (int i = 1; i <= n; ++i) {
			if (height[i] >= len) {
				mi = min(mi, min(Sa[i], Sa[i-1])), mx = max(mx, max(Sa[i], Sa[i-1]));
				if (mx - mi > len) return 1;
			}else mi = mx = Sa[i];
		}
		return 0;
	}
}S;
int s[maxn], t[maxn];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n;
	while (scanf("%d", &n), n) {
		for (int i = 1; i <= n; ++i) scanf("%d", &s[i]);
		for (int i = 2; i <= n; ++i) t[i-1] = s[i] - s[i-1] + 90;
		--n;
		S.init(t, n);
		int l = 0, r = n / 2;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (S.check(mid)) l = mid + 1;
			else r = mid - 1;
		}
		if (r < 4) r = -1;
		printf("%d\n", r+1);
	}
	return 0;
}