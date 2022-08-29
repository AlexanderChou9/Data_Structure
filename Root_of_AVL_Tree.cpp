//
// Created by limou on 2022/8/14.
//

/* 找到的错误: AVL_Insertion()中考虑三种情况 if-else if- else if, 没有看准花括号, 错将第二个 else if包含在了第一个else if中 */
/* 需要做的事情: 读取一个插入的元素, 插入, 旋转调整(使用迭代, 在回来的"代"的过程中, 遇到的第一个不平衡节点就是目击者节点) */
/* LL: 插入点在目击者的左子树的左子树, 对目击者左单旋 (顺时针)
 * RR: 插入点在目击者的右子树的右子树,对目击者右单旋 (逆时针)
 * LR: 插入点在目击者的左子树的右子树,对目击者的左子树右单旋(逆时针), 对目击者左单旋(顺时针)
 * RL: 插入点在目击者的右子树的左子树,对目击者的右子树左单旋(顺时针), 对目击者右单旋(逆时针)*/

#include "iostream"
using namespace std;
typedef struct AVLNode* AVLTree;
struct AVLNode {
    int val;
    AVLTree left;
    AVLTree right;
};
int getHeight(AVLTree t);
AVLTree Left_Rotation(AVLTree a);
AVLTree Right_Rotation(AVLTree a);
AVLTree AVL_Insertion(int x, AVLTree t);

int main() {
    auto N = 0;
    cin >> N;
    AVLTree avl = nullptr;
    for (int i = 0, tmp = 0; i < N; ++i) {
        cin >> tmp;
        avl = AVL_Insertion(tmp, avl);
    }
    cout << avl->val;
    return 0;
}

int getHeight(AVLTree t) {
    if (t) return max(getHeight(t->left), getHeight(t->right)) + 1;
    else return 0;
}

////// get height
//int get_height(avl_tree t){
//    if(!t)
//        return -1;
//    else
//        return t->height;
//}
AVLTree Left_Rotation(AVLTree a) {
    AVLTree b = a->left;
    a->left = b->right;
    b->right = a;
    return b;
}
AVLTree Right_Rotation(AVLTree a) {
    AVLTree b = a->right;
    a->right = b->left;
    b->left = a;
    return b;
}
AVLTree AVL_Insertion(int x, AVLTree t) {
    if (!t) {
        t = (AVLTree) malloc(sizeof (AVLNode));
        t->val = x;
        t->left = nullptr;
        t->right = nullptr;
        //t->height = 0;
    } else if (x < t->val) {
        t->left = AVL_Insertion(x, t->left);    // 迭代过程中, 第一次遇到不平衡是回来的时候, 也就是最底层的

        if (getHeight(t->left) - getHeight(t->right) == 2) {
            if (x < t->left->val) t = Left_Rotation(t);    // 左子树的左子树
            else if (x > t->left->val) {                      // 左子树的右子树
                t->left = Right_Rotation(t->left);
                t = Left_Rotation(t);
            }
        }
    } else if (x > t->val) {
        t->right = AVL_Insertion(x, t->right);

        if (getHeight(t->left) - getHeight(t->right) == -2) {
            if (x > t->right->val) t = Right_Rotation(t);    //右子树的右子树
            else if (x < t->right->val) {                       //右子树的左子树
                t->right = Left_Rotation(t->right);
                t = Right_Rotation(t);
            }
        }
    }
    return t;
}
