//
// Created by Mr.D on 2022/8/23.
//
#include <iostream>

#define max(a, b) ((a) > (b) ? (a): (b))

using namespace std;

struct avl_node {
    int data;
    int height;
    avl_node *left;
    avl_node *right;
};
typedef avl_node *avl_tree;

avl_tree insert(avl_tree avlTree, int data);

avl_tree new_element(int data);

avl_tree left_right(avl_tree t);

avl_tree left_left(avl_tree t);

avl_tree right_left(avl_tree t);

avl_tree right_right(avl_tree t);

int get_height(avl_tree t);

//// single left
avl_tree left_right(avl_tree a) {
    avl_tree b = a->left;
    avl_tree c = b->right;
    b->right = c->left;
    a->left = c->right;
    c->left = b;
    c->right = a;
    b->height = max(get_height(b->left), get_height(b->right)) + 1;
    a->height = max(get_height(a->left), get_height(a->right)) + 1;
    c->height = max(get_height(c->left), get_height(c->right)) + 1;

    return c;
}

//// double left
avl_tree left_left(avl_tree a) {
    avl_tree b = a->left;
    a->left = b->right;
    b->right = a;
    a->height = max(get_height(a->left), get_height(a->right)) + 1;
    b->height = max(get_height(b->left), get_height(b->right)) + 1;

    return b;
}

////single right
avl_tree right_left(avl_tree a) {
    avl_tree b = a->right;
    avl_tree c = b->left;
    a->right = c->left;
    a->left = c->right;
    c->left = a;
    c->right = b;
    b->height = max(get_height(b->left), get_height(b->right)) + 1;
    a->height = max(get_height(a->left), get_height(a->right)) + 1;
    c->height = max(get_height(c->left), get_height(c->right)) + 1;
    return c;
}

////double right
avl_tree right_right(avl_tree a) {
    avl_tree b = a->right;
    a->right = b->left;
    b->left = a;
    a->height = max(get_height(a->left), get_height(a->right)) + 1;
    b->height = max(get_height(b->left), get_height(b->right)) + 1;

    return b;
}

//// get height
int get_height(avl_tree t){
    if(!t)
        return -1;
    else
        return t->height;
}


//// insert tree
avl_tree insert(avl_tree t, int data) {
    if (!t) {                                     // 找到了该插入的地方
        return new_element(data);
    } else {
        if (t->data > data) {
            t->left = insert(t->left, data);   // 对 t 左插, 则左子树高度增加
            if (get_height(t->left) - get_height(t->right) == 2) // 如果 t 的左子树高度 - 右子树高度 == 2  , 也就是 t 为目击者
                if (data < t->left->data)                              // 如果 data 比 t 的左子树的值小, 说明插入了 t 的左子树的左子树
                    t = left_left(t);
                else
                    t = left_right(t);

        } else if (t->data < data) {
            t->right = insert(t->right, data);
            if (get_height(t->left) - get_height(t->right) == -2)
                if (data < t->right->data)
                    t = right_left(t);
                else
                    t = right_right(t);

        } else {
            cout << "insert error" << endl;
            return NULL;
        }
        t->height = max(get_height(t->left), get_height(t->right)) + 1;
        return t;
    }
}

avl_tree new_element(int data) {
    avl_tree t = (avl_tree) malloc(sizeof(avl_node));
    t->data = data;
    t->height = 0;
    t->left = NULL;
    t->right = NULL;
    return t;
}

int main() {

    int len;
    cin >> len;
    avl_tree t = NULL;
    int data;
    for (int i = 0; i < len; i++) {
        cin >> data;
        t = insert(t, data);
    }
    cout << t->data;

    return 0;
}



