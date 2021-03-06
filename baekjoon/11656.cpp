#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#define MAXN 1010

using namespace std;

struct Suffix {
    string s;
    int SA[MAXN], N;

    void suffix_array() {
        int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN], pnt = 1;

        memset(ord, 0, sizeof(ord));
        memset(aux, 0, sizeof(aux));
        memset(nord, 0, sizeof(nord));
        for(int i = 0; i < N; i++) {
            SA[i] = i;
            ord[i] = s[i];
        }

        for(int p = 1; p < N; p *= 2) {
            memset(cnt, 0, sizeof(cnt));
            for(int i = 0; i < N; i++) cnt[ord[min(i + p, N)]]++;
            for(int i = 1; i <= N || i <= 255; i++) cnt[i] += cnt[i - 1];
            for(int i = N - 1; i >= 0; i--) aux[--cnt[ord[min(i + p, N)]]] = i;

            memset(cnt, 0, sizeof(cnt));
            for(int i = 0; i < N; i++) cnt[ord[i]]++;
            for(int i = 1; i <= N || i <= 255; i++) cnt[i] += cnt[i - 1];
            for(int i = N - 1; i >= 0; i--) SA[--cnt[ord[aux[i]]]] = aux[i];

            if(pnt == N) break;
            pnt = 1;
            nord[SA[0]] = 1;
            for(int i = 1; i < N; i++) {
                if(ord[SA[i - 1]] != ord[SA[i]] || ord[SA[i - 1] + p] != ord[SA[i] + p]) pnt++;
                nord[SA[i]] = pnt;
            }

            memcpy(ord, nord, sizeof(int) * N);
        }
    }
} S;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> S.s;
    S.N = S.s.size();

    S.suffix_array();
    for(int i = 0; i < S.N; i++) {
        for(int j = S.SA[i]; j < S.s.size(); j++) cout << S.s[j];
        cout << '\n';
    }

    return 0;
}
