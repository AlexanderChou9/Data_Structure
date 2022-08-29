//
// Created by limou on 2022/8/25.
//
#include "iostream"

using namespace std;
const int MaxSize = 10005;
typedef int Name_Of_Set;
typedef int SetType[MaxSize];

Name_Of_Set Find (SetType S, int X);    // 也就是说 SetType S == int S[MaxSize]  ??
void Union (SetType S, Name_Of_Set Root1, Name_Of_Set Root2);
void Initialization (SetType S, int n);
void Input_connection(SetType S);
void Check_connection(SetType S);
void Check_network(SetType S, int n);

int main () {
    SetType S;
    auto n = 0;
    auto ic = 'C';
    cin >> n;
    cin >> ic;
    Initialization(S, n);
    while (ic != 'S') {
        if (ic == 'I')
            Input_connection(S);
        else if (ic == 'C')
            Check_connection(S);
        else
            cout << "Input error!" << endl;
        cin >> ic;
    }
    Check_network(S, n);
    return 0;


    return 0;
}

//Name_Of_Set Find (SetType S, int X) {
//    for ( ; S[X] >= 0; X = S[X]) ;
//    return X;
//}

//简单归并
// void Union (SetType S, Name_Of_Set Root1, Name_Of_Set Root2) {
//    S[Root2] = Root1;
//}

// 按高度归并
// void Union (SetType S, Name_Of_Set Root1, Name_Of_Set Root2) {
//    if (S[Root2] < S[Root1])    // 存放树的高度, 而不是树的节点数目
//        S[Root1] = Root2;
//    else if (S[Root2] > S[Root1])
//        S[Root2] = Root1;
//    else {
//        --S[Root1];
//        S[Root2] = Root1;
//    }
//}

// 按规模归并
 void Union (SetType S, Name_Of_Set Root1, Name_Of_Set Root2) {
    if (S[Root2] < S[Root1]) {   // 存放树的节点数目
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }
    else if (S[Root2] >= S[Root1]) {
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    }
}

//路径压缩
Name_Of_Set Find (SetType S, int X) {
    if (S[X] < 0)
        return X;  //找到根节点
    else
        return S[X] = Find(S, S[X]);  //返回根, 并且将经过的节点都指向根
}

void Initialization (SetType S, int n) {
    for (int i = 0; i < n; ++i) {
        S[i] = -1;
    }
}
void Input_connection(SetType S) {
    auto u = 0;
    auto v = 0;
    cin >> u >> v;
    auto Root1 = Find(S, u - 1);
    auto Root2 = Find(S, v - 1);

    if (Root1 != Root2)
        Union(S, Root1, Root2);
}
void Check_connection(SetType S) {
    auto u = 0;
    auto v = 0;
    cin >> u >> v;
    auto Root1 = Find(S, u - 1);
    auto Root2 = Find(S, v - 1);

    if (Root1 != Root2)
        cout << "no" << endl;
    else
        cout << "yes" << endl;
}
void Check_network(SetType S, int n) {
    auto component = 0;

    for (int i = 0; i < n; ++i)
        if (S[i] < 0)
            ++component;

    if (component == 1)
        cout << "The network is connected.";
    else
        cout << "There are " << component << " components.";
}