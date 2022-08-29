//
// Created by limou on 2022/8/23.
//
#include "iostream"

using namespace std;

int H[1001];
int Heapsize;

void Create ();
void Insert (int X);
void PrintPath (int i);
/* 调试找到的错误: PrintPath()中, 针对 m = 1 的情况, 没有考虑.  */

int main () {
    /* 1.读入n和m; 2.根据输入序列建堆; 3.对m个要求: 打印H[i]到根的路径 */
    auto n = 0;
    auto m = 0;
    auto temp = 0;
    auto flag = false;
    cin >> n >> m;

    Create();
    for (int i = 0; i < n; ++i) {
        cin >> temp;
        Insert(temp);
    }

    for (int i = 0; i < m; ++i) {
        if (!flag)
            flag = true;
        else
            cout << endl;
        cin >> temp;
        PrintPath(temp);
    }

    return 0;
}


void Create () {
    Heapsize = 0;
    H[0] = -10002;
}
void Insert (int X) {
    Heapsize = Heapsize + 1;
    auto i = Heapsize;
    for ( ; H[i / 2] > X; i /= 2)
        H[i] = H[i / 2];
    H[i] = X;
}
void PrintPath (int i) {
    if (i > 1) {
        cout << H[i];
        for ( i = i / 2; i > 1; i = i /2)
            cout << " " << H[i] ;
        cout << " " << H[1];
    } else cout << H[1];
}