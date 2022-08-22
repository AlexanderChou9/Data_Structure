//
// Created by limou on 2022/8/13.
//
/* 1. 搜索树表示; 2. 建搜索树 T ; 3. 判别一个序列是否与搜索树 T 一致 */
/* 调试找到的错误: 针对每个序列进行的AVL_SameCheck()函数中 for 循环的次数应该为 N - 1 次, 因为根节点已经比较了 */
#include "iostream"

using namespace std;
typedef struct TreeNode *Tree;
struct TreeNode {
    int v;
    Tree Left;
    Tree Right;
    int flag;
};
/* 对每组数据
 * 1. 读入N和L
 * 2. 根据第一行序列建树 T
 * 3. 依据树 T 分别判定后面的 L 个序列是否能与 T 形成同一棵搜索树, 输出结果 */
Tree Build_BSTree(int N);
Tree NewNode(int V);
Tree Insert(Tree T, int V);
int BSTree_SameCheck(Tree T, int N);
int Check_Node(Tree T, int V);
void Reset_T(Tree T);
void Free_T(Tree T);

int main() {
    int N = 0;
    int L = 0;
    Tree T = NULL;
    int print_flag = 0;
    cin >> N;

    while (N) {
        cin >> L;
        T = Build_BSTree(N);
        for (int i = 0; i < L; ++i) {
            if (!print_flag) {
                print_flag = 1;
            } else cout << endl;
            if (BSTree_SameCheck(T, N)) cout << "Yes";
            else cout << "No";
            Reset_T(T);
        }
        Free_T(T);
        cin >> N;
    }
    return 0;
}

Tree Build_BSTree(int N) {
    Tree T;
    int V = 0;
    cin >> V;
    T = NewNode(V);
    for (int i = 1; i < N; ++i) {
        cin >> V;
        T = Insert(T, V);
    }
    return T;
}
Tree NewNode(int V) {
    Tree T = (Tree) malloc(sizeof (struct TreeNode));
    T->v = V;
    T->Left = NULL;
    T->Right = NULL;
    T->flag = 0;
    return T;
}
Tree Insert(Tree T, int V) {
    if (!T) T = NewNode(V);
    else {
        if (V > T->v) T->Right = Insert(T->Right, V);
        else T->Left = Insert(T->Left, V);
    }
    return T;
}


int BSTree_SameCheck(Tree T, int N) {
    int V = 0;
    int flag = 0;
    cin >> V;
    if (V != T->v) flag = 1;
    else T->flag = 1;

    for (int i = 0; i < N - 1; ++i) {
        cin >> V;
        if (!flag)  // flag为1时, 不做check, 只读取输入
            if (!Check_Node(T, V))
                flag = 1;
    }

    if (flag) return 0;
    else return 1;
}
// 根据被检查序列, 查找元素, 要求: 途中经过的元素必须是被检查序列中该元素之前遇到过的元素.
int Check_Node(Tree T, int V) {
    if (T->flag) {
        if (V < T->v) return Check_Node(T->Left, V);
        else if (V > T->v) return Check_Node(T->Right, V);
        else return 0;    // 序列中该节点重复
    } else {
        if (V != T->v) return 0;    //AVL树中搜索时出现未遇到的元素, 而且和该值不同
        else {
            T->flag = 1;
            return 1;
        }
    }
}

void Reset_T(Tree T) {
    if (T->Left) Reset_T(T->Left);
    if (T->Right) Reset_T(T->Right);
    T->flag = 0;
}

void Free_T(Tree T) {
    if (T->Left) Free_T(T->Left);
    if (T->Right) Free_T(T->Right);
    free(T);
}