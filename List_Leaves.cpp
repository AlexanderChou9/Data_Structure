//
// Created by limou on 2022/8/11.
//
#include "iostream"
using namespace std;
#include "queue"
#define Null -1;
#define MaxSize 11

struct BTreeNode {
    int left;
    int right;
}T[MaxSize];

int Build_BTree();
void List_Leaves(int BT);

int main() {
    int BT = Build_BTree();
    List_Leaves(BT);

    return 0;
}

int Build_BTree() {
    int N = 0;
    cin >> N;
    int root = Null;
    if (N) {
        int check[N];
        for (int i = 0; i < N; ++i) {
            check[i] = 0;
        }

        char left, right;
        for (int i = 0; i < N; ++i) {

            cin >> left>> right;
            if (left != '-') {
                T[i].left = left - '0';
                check[T[i].left] = 1;
            } else T[i].left = Null;
            if (right != '-') {
                T[i].right = right - '0';
                check[T[i].right] = 1;
            } else T[i].right = Null;
        }
        for (int i = 0; i < N; ++i) {
            if (!check[i]) {
                root = i;
                break;
            }
        }

    }
    return root;
}

void List_Leaves(int BT) {
    if (BT == -1) return;
    int flag = 0;
    queue<int> q;
    q.push(BT);
    int tmp;
    while (!q.empty()) {
        tmp = q.front();
        q.pop();
        if (T[tmp].left == -1 && T[tmp].right == -1) {
            if (flag) {
                cout << ' ' << tmp;
            } else {
                flag = 1;
                cout << tmp;
            }
        }
        if (T[tmp].left != -1) q.push(T[tmp].left);
        if (T[tmp].right != -1) q.push(T[tmp].right);
    }
}