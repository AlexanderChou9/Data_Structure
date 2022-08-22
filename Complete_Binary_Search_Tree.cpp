//
// Created by limou on 2022/8/17.
//
/* 树的表示法:  链表还是数组?  数组！！*/
/* 调试的错误, 来源于 GetLeftLength()中的 exp2(), log2()函数的使用, floor()返回double类型, min()只能处理相同类型的数据 */
#include "iostream"
#include "algorithm"
#include "cmath"

using namespace std;

int T[1000];
int A[1000];

void solve(int ALeft, int ARight, int TRoot);
int GetLeftLength(int n);
int compare(const void* a, const void* b);

int main() {
    auto N = 0;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    qsort(A, N, sizeof (int), compare);
    solve(0, N - 1, 0);
    cout << T[0];
    for (int i = 1; i < N; ++i) {
        cout << ' ' << T[i];
    }
    return 0;
}

void solve(int ALeft, int ARight, int TRoot) {
    /* 初始调用为 solve(0, N-1, 0) */
    auto n = ARight - ALeft + 1;
    if (!n) return;
    auto L = GetLeftLength(n);
    T[TRoot] = A[ALeft + L];

    solve(ALeft, ALeft + L - 1, 2 * TRoot + 1);
    solve(ALeft + L + 1, ARight, 2 * TRoot + 2);
}
int GetLeftLength(int n) {
    auto H = 0;
    auto X = 0;
    auto L = 0;
    H = int(log2(n + 1));
    X = n - int(exp2(H)) + 1;
    X = min(X, int(exp2(H-1)));
    L = int(exp2(H-1)) - 1 + X;
    return L;
}
int compare(const void* a, const void* b) {
    return *(int *)a - *(int *)b;
}