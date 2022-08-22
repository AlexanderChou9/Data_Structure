//
// Created by limou on 2022/8/8.
//
/* 关键问题有三个: 1. 二叉树表示 2. 建二叉树 3. 同构判别 */
/* 调试找到的错误: 51行忘记写右子树为 '-' , 赋为0 */
#include "iostream"
using namespace std;
#define MaxTree 10
#define Null -1

struct TreeNode {
    char Element;
    int Left;
    int Right;
}T1[MaxTree], T2[MaxTree];    /* 使用两个全局数组, 存储树 */

int BuildTree (struct TreeNode T[]);
int Isomorphic (int R1, int R2);

int main() {
    /* 建二叉树1; 建二叉树2; 判别是否同构并输出 */
    int R1, R2;

    R1 = BuildTree(T1);                        /* 使用全局数组存储树, 建树后返回根节点的下标 */
    R2 = BuildTree(T2);
    if (Isomorphic(R1, R2)) cout << "Yes";
    else cout << "No";

    return 0;
}

int BuildTree(struct TreeNode T[]) {
    int N = 0;
    cin >> N;
    int Root = -1;

    if(N) {
        int check[MaxTree] = {0};            /* check[]数组用来寻找根节点 */
        int i = 0;
        char cl, cr;
        for (i = 0; i < N; i++) check[i] = 0;    /* 没有节点指向的, 就是根 */
        for (i = 0; i < N; i++) {
            cin >> T[i].Element >> cl >> cr;
            if (cl != '-') {                     /* 判断左子树是否存在 */
                T[i].Left = cl - '0';
                check[T[i].Left] = 1;
            } else T[i].Left = Null;
            if (cr != '-') {
                T[i].Right = cr - '0';
                check[T[i].Right] = 1;
            } else T[i].Right = Null;
        }
        for (i = 0; i < N; i++) {
            if (!check[i]) break;
        }
        Root = i;
    }
    return Root;
}

int Isomorphic (int R1, int R2) {    // 题目保证每个节点的字母标识不同
    if ((R1 == Null) && (R2 == Null)) return 1;
    if ((R1 == Null) && (R2 != Null)) return 0;
    if ((R1 != Null) && (R2 == Null)) return 0;
    if (T1[R1].Element != T2[R2].Element) return 0;
    if ((T1[R1].Left == Null) && T2[R2].Left == Null) return Isomorphic(T1[R1].Right, T2[R2].Right);
    if (((T1[R1].Left != Null) && (T2[R2].Left) != Null) && (T1[T1[R1].Left].Element == T2[T2[R2].Left].Element)) //不需要交换左右子树的情况
        return (Isomorphic(T1[R1].Left, T2[R2].Left) && Isomorphic(T1[R1].Right, T2[R2].Right));
    else return (Isomorphic(T1[R1].Left, T2[R2].Right) && Isomorphic(T1[R1].Right, T2[R2].Left)); //需要交换左右子树的情况
}