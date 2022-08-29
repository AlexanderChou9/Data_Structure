# 《数据结构(MOOC)》算法题总结

该门课程来自于[学堂在线](https://www.icourse163.org/course/ZJU-93001), 是浙江大学陈越老师主导的课程(2022年夏), 相关刷题平台在[PTA](https://pintia.cn/problem-sets/dashboard)上. 本文对其中涉及的算法题进行总结. 题目包括3道函数题和29道编程题. 

## 03 一元多项式的乘法与加法运算

**题目要求**

设计函数分别求两个一元多项式的乘积与和。

**输入格式:**

输入分2行，每行分别先给出多项式非零项的个数，再以指数递降方式输入一个多项式非零项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。

**输出格式:**

输出分2行，分别以指数递降方式输出乘积多项式以及和多项式非零项的系数和指数。数字间以空格分隔，但结尾不能有多余空格。零多项式应输出`0 0`。

**输入样例:**

```c++
4 3 4 -5 2  6 1  -2 0
3 5 20  -7 4  3 1
```

**输出样例**

```c++
15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
5 20 -4 4 -5 2 9 1 -2 0
```

题目很明显, 需要解决以下问题: 存储多项式, 进行乘法运算, 进行加法运算, 输出多项式. 

如何**存储多项式**?

对于这种线性结构的数据, 通常采用数组或链表的方式存储. 从输入样例看出, 多项式的指数较为分散, 因此使用数组存储会造成空间上的浪费. 我们使用链表存储多项式, 每个项的节点包括: 系数 coef , 指数 expon , 指向下一个项的指针 link .

如何**进行乘法运算**?

其实有两种方法:

1.  P<sub>1</sub>( 假定包含 n 项 )的每一项逐个与整个P<sub>2</sub>相乘, 形成 n 个多项式, 相加( 使用之后定义的加法运算 ).
2.  P<sub>1</sub>( 假定包含 n 项 )的每一项与P<sub>2</sub>( 假定包含 m 项 )的每一项相乘( 共有 n * m 项 ), 将其添加到结果多项式 P 中.

第 1 种方法, 显然是一个嵌套的双层循环, 然后调用加法运算的函数. 在这里不对其进行赘述, 我们使用第 2 种方法. 

第 2 种方法的关键在于, **如何将乘积项添加到结果多项式 P 中?** 也就是确定其位置. 代码中, 因为多项式降幂排列, 我们使用 P<sub>1</sub>的第一项与整个P<sub>2</sub>相乘, 得到 P 的初始序列. 且 P 的第一项必然是最终结果序列的最高次数项. 因此, 之后相乘得到的项只有两个选择: 

1. 插入中间. 也就是对 P 从头开始逐个遍历, 寻找到次数与乘积项一样的项. 
2. 插到最后.  没找到那个项, hh, 也就是暂时没存入. 

如何进行**加法运算**?

题目要求, 结果多项式也要降幂排列. 采用 while 循环, 对 P<sub>1</sub>和P<sub>2</sub>从头到尾遍历, 将次数大的项尾插到结果多项式, 也就是代码中的 Attach ( ) 函数. P<sub>1</sub>和P<sub>2</sub>最低次数不同很正常, 将非空的多项式尾插到结果多项式, 完成操作. 

如何**输出多项式**?   

从头到尾, 遍历即可. 这里需要注意的是 **输出结果的规范**, 代码中通过设置一个 flag, 来区分第一项和其他项. 

**调试找出的错误**(已改正)：

1. Mult( )函数中构造初始序列的次数( 错将t2写为了t1 ), 因此 CLion 中显示下一行代码未执行. 导致内存满
2. PrintPoly( )函数在P=NULL的情况下输出的"0 0"( 不应该有换行符, 因为第二行后面不应该换行 )
3. Attach( )需要考虑相加之后系数为0的情况

**示例代码**

```c++
#include "stdio.h"
#include "malloc.h"

typedef struct PolyNode *Polynomial;
struct PolyNode {
    int coef;
    int expon;
    Polynomial link;
};

Polynomial ReadPoly();
Polynomial Mult(Polynomial P1, Polynomial P2);
void PrintPoly(Polynomial P);
Polynomial Add(Polynomial P1, Polynomial P2);
void Attach(int c, int e, Polynomial *pRear);

int main() {
    /* 总体逻辑：读入多项式1 读入多项式2 乘法运算并输出 加法运算并输出 */
    Polynomial P1, P2, PP, PS;

    P1 = ReadPoly();
    P2 = ReadPoly();
    PP = Mult(P1, P2);
    PrintPoly(PP);
    printf("\n");
    PS = Add(P1, P2);
    PrintPoly(PS);

    return 0;
}

Polynomial ReadPoly() {
    Polynomial P, Rear, t;
    int c, e, N;

    scanf("%d", &N);
    P = (Polynomial) malloc(sizeof (struct PolyNode));    /* 链表的空的头节点 */
    P->link = NULL;

    Rear = P;
    while (N--) {
        scanf("%d %d", &c, &e); 
        Attach(c, e, &Rear);    /* 将当前项插入多项式链表的尾部 */
    }

    t = P;
    P = P->link;
    free(t);    /* 删除临时生成的空的头节点 */

    return P;
}

Polynomial Mult(Polynomial P1, Polynomial P2) {
    if(!P1 || !P2) return NULL;
    Polynomial P;
    P = (Polynomial) malloc(sizeof (struct PolyNode));
    P->link = NULL;
    Polynomial Rear = P;
    Polynomial t1 = P1;
    Polynomial t2 = P2;
    int e = 0;
    int c = 0;
    Polynomial t = NULL;

    while (t2) {
        Attach(t1->coef * t2->coef, t1->expon + t2->expon, &Rear);
        t2 = t2->link;
    }                   /* 用t1的第一项乘以t2的所有项，构造一个初始队列 */
    t1 = t1->link;

    while (t1) {
        t2 = P2;
        Rear = P;
        while (t2) {
            e = t1->expon + t2->expon;
            c = t1->coef * t2->coef;        /* 相乘得到一项，然后遍历t2，看看插在哪里 */
            while (Rear->link && (Rear->link->expon > e)) {    
                Rear = Rear->link;          /* Rear永远指向t2中当前节点的前一项 */
            }
            if (Rear->link && (Rear->link->expon == e)) {      
                /* 刚好找到系数相同的那一项，要考虑系数相加是否为0 */
                if (Rear->link->coef + c) {
                    Rear->link->coef += c;
                } else {
                    t = Rear->link;
                    Rear->link = Rear->link->link;
                    free(t);
                }
            } else {
                t = (Polynomial) malloc(sizeof (struct PolyNode));
                t->coef = c;
                t->expon = e;
                t->link = Rear->link;
                Rear->link = t;
                Rear = Rear->link;
            }
            t2 = t2->link;
        }

        t1 = t1->link;
    }
    t = P;
    P = P->link;
    free(t);

    return P;
}

void PrintPoly(Polynomial P) {    /* 输出多项式 */
    if(!P) {
        printf("0 0");
        return;
    }

    int flag = 0;
    while (P) {
        if(!flag) flag = 1;
        else printf(" ");
        printf("%d %d", P->coef, P->expon);
        P = P->link;
    }
}

Polynomial Add(Polynomial P1, Polynomial P2) {
    Polynomial P;
    P = (Polynomial) malloc(sizeof (struct PolyNode));    /* 构造和多项式链表的空的头节点 */
    P->link = NULL;
    Polynomial Rear = P;
    Polynomial t1 = P1;
    Polynomial t2 = P2;

    while (t1 && t2) {
        if(t1->expon == t2->expon) {
            Attach(t1->coef + t2->coef, t1->expon, &Rear);    /* 次数相同，则系数合并 */
            t1 = t1->link;
            t2 = t2->link;
        } else if(t1->expon > t2->expon) {
            Attach(t1->coef, t1->expon, &Rear);               /* 次数不同，则取高次  */
            t1 = t1->link;
        } else {
            Attach(t2->coef, t2->expon, &Rear);
            t2 = t2->link;
        }
    }
    while (t1) {
        Attach(t1->coef, t1->expon, &Rear); /* 一方为空，将非空的链表逐个节点合并上去 */
        t1 = t1->link;                      /* 而不是直接拼接，为了方便删除列表后，进行回收 */
    }
    while (t2) {
        Attach(t2->coef, t2->expon, &Rear);
        t2 = t2->link;
    }

    t1 = P;
    P = P->link;
    free(t1);

    return P;

}

void Attach(int c, int e, Polynomial *pRear) {
    if(!c) return;
    Polynomial P;

    P = (Polynomial) malloc(sizeof(struct PolyNode));
    P->coef = c;
    P->expon = e;
    P->link = NULL;
    (*pRear)->link = P; /* 将P节点挂在Rear后面 */
    *pRear = P;         /* 修改pRear的值 */
}
```



## 05 Pop Sequence

**题目要求**

Given a stack which can keep *M* numbers at most. Push *N* numbers in the order of 1, 2, 3, ..., *N* and pop randomly. You are supposed to tell if a given sequence of numbers is a possible pop sequence of the stack. For example, if *M* is 5 and *N* is 7, we can obtain 1, 2, 3, 4, 5, 6, 7 from the stack, but not 3, 2, 1, 7, 5, 6, 4.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains 3 numbers (all no more than 1000): *M* (the maximum capacity of the stack), *N* (the length of push sequence), and *K* (the number of pop sequences to be checked). Then *K* lines follow, each contains a pop sequence of *N* numbers. All the numbers in a line are separated by a space.

**Output Specification:**

For each pop sequence, print in one line "YES" if it is indeed a possible pop sequence of the stack, or "NO" if not.

**Sample Input:**

```c++
5 7 5
1 2 3 4 5 6 7
3 2 1 7 5 6 4
7 6 5 4 3 2 1
5 6 4 3 7 2 1
1 7 6 5 4 3 2
```

**Sample Output:**

```c++
YES
NO
NO
YES
NO
```

本题第一行输入三个值: M N K, 表示限定一个M大小的栈, 判断K个出栈序列, 每个序列的长度为N. 

入栈序列必须为1~N的升序排列, 其中可以掺杂任意的出栈操作. 代码中使用cur变量的递增操作, 表示每次需要入栈的值. 判定合法, 等价于 1~N 序列的子序列反转问题( 在规定的栈容量内 )

因此, 我们可以使用c++的stack库方便的使用栈对象 s , 通过**栈顶元素(s.top())**和被检验**序列arr[ ]**的值比较, 判断是否非法, 进行入栈/出栈操作.  

代码的关键部分在19 ~ 32行. 针对arr[ ]序列的每一个元素逐个处理, for 循环里: 首先进行一个 while 循环, 按照顺序将 cur 压栈, 形成一个**以当前 arr[ ]值结束的子序列**; 然后进行一个判断, 判断条件和 while 循环的条件相同, 主要是为了观察 while 是否异常跳出( 序列非法 ). 如果 arr[ ] 上该元素经过考验( 此时栈非空, 并且 s.top == arr[ i ] ), 则栈顶元素出栈, arr[ ]序列进行下一个. 

**示例代码**

```C++
#include <iostream>
#include <stack>

using namespace std;

#define max 100000

int arr[max];

int main() {

    int m,n,k;                                   
    cin>>m>>n>>k;                            
    while(k--) {
        int f=1,cur=1;                           
        stack<int> s;                            

        for(int i=0;i<n;i++) cin>>arr[i];        
        for(int i=0;i<n;i++) {
            while(s.empty()||s.top()!=arr[i]) {   
                if(cur>n||s.size()>=m)
                    break;                       

                s.push(cur++);                
            }

            if(s.empty() || s.top()!=arr[i]) {    
                f=0;
                break;
            }
            else s.pop();                        
        }

        if(f)
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }

    return 0;
}
```

## 06 树的同构

给定两棵树T1和T2。如果T1可以通过若干次左右孩子互换就变成T2，则我们称两棵树是“**同构**”的。例如图1给出的两棵树就是同构的，因为我们把其中一棵树的结点A、B、G的左右孩子互换后，就得到另外一棵树。而图2就不是同构的。

![图1](D:\Documents\Wirte\cs\course\dataStructure_MOOC.assets\树的同构1.jpg)

![](D:\Documents\Wirte\cs\course\dataStructure_MOOC.assets\树的同构2.jpg)

现给定两棵树，请你判断它们是否是同构的。

**输入格式:**

输入给出2棵二叉树树的信息。对于每棵树，首先在一行中给出一个非负整数*N* (≤10)，即该树的结点数（此时假设结点从0到*N*−1编号）；随后*N*行，第*i*行对应编号第*i*个结点，给出该结点中存储的1个英文大写字母、其左孩子结点的编号、右孩子结点的编号。如果孩子结点为空，则在相应位置上给出“-”。给出的数据间用一个空格分隔。**注意：题目保证每个结点中存储的字母是不同的**。

**输出格式:**

如果两棵树是同构的，输出“Yes”，否则输出“No”。

**输入样例1（对应图1）:**

```c++
8
A 1 2
B 3 4
C 5 -
D - -
E 6 -
G 7 -
F - -
H - -
8
G - 4
B 7 6
F - -
A 5 1
H - -
C 0 -
D - -
E 2 -
```

**输出样例:**

```c++
Yes
```

关键问题有三个: 

1. 二叉树表示 
2. 建二叉树 
3. 同构判别

本题目, 需要特别注意的地方是: 判断是否同构的函数中, 如何全面考虑, 构造条件判断

调试找到的错误: 46行忘记写如果右子树为 '-' , 则赋为0 

**示例代码:**

```c++
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
```

## 07 List Leaves 列出叶节点

Given a tree, you are supposed to list all the leaves in the order of top down, and left to right.

**Input Specification:**

Each input file contains one test case. For each case, the first line gives a positive integer *N* (≤10) which is the total number of nodes in the tree -- and hence the nodes are numbered from 0 to *N*−1. Then *N* lines follow, each corresponds to a node, and gives the indices of the left and right children of the node. If the child does not exist, a "-" will be put at the position. Any pair of children are separated by a space.

**Output Specification:**

For each test case, print in one line all the leaves' indices in the order of top down, and left to right. There must be exactly one space between any adjacent numbers, and no extra space at the end of the line.

**Sample Input:**

```c++
8
1 -
- -
0 -
2 7
- -
- -
5 -
4 6
```

**Sample Output:**

```c++
4 1 5
```

由题目可得, 本题的目的是列举叶节点, 先从上到下, 同一层的叶节点从左到右. 这是一个层次遍历的顺序. 因此, 主要过程分为两个:

- 接收输入, 创建树
- 层次遍历

根据样例输入的格式, 完全可以采用类似于上一题的建树方法, 返回根节点的下标.

层次遍历是基于队列进行的, 使用c++提供的queue工具, 从根节点入队开始, 出队, 访问该元素, 将其非空的左右子树入队, 继续, 直到队空.  

**示例代码:**

```c++
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
```

## 09 是否同一棵二叉搜索树

给定一个插入序列就可以唯一确定一棵二叉搜索树(**Binary Search Tree**)。然而，一棵给定的二叉搜索树却可以由多种不同的插入序列得到。例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一样的结果。于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。

**输入格式:**

输入包含若干组测试数据。每组数据的第1行给出两个正整数*N* (≤10)和*L*，分别是每个序列插入元素的个数和需要检查的序列个数。第2行给出*N*个以空格分隔的正整数，作为初始插入序列。随后*L*行，每行给出*N*个插入的元素，属于*L*个需要检查的序列。

简单起见，我们保证每个插入序列都是1到*N*的一个排列。当读到*N*为0时，标志输入结束，这组数据不要处理。

**输出格式:**

对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，输出“Yes”，否则输出“No”。

**输入样例:**

```C++
4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0
```

**输出样例:**

```c++
Yes
No
No
```

由题意可得, 我们需要考虑以下工作:

1. **搜索树表示**. 根据输入顺序, 使用链表.
2. **建搜索树 T**.  进行待插入元素和树的逐个对比, 确定插入位置.
3. **判别一个序列是否与搜索树 T 一致**. 通过设置一个访问标记flag, 检查按照该序列插入的每一个元素是否在正确的相同位置

针对每组数据:
1. 读入 N 和 L.
2. 根据第一行的序列, 建树 T.
3. 依据树 T 分别判定后面的 L 个序列是否能与 T 形成同一棵搜索树, 输出结果. 

**调试找到的错误:**

- 针对每个序列进行的*BSTree_SameCheck()*函数中 for 循环的次数应该为 N - 1 次, 因为根节点已经比较了.

**示例代码:**

```c++
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
```

## 10 Root of AVL Tree

给出一个AVL树的插入序列, 要求返回最终AVL树的根节点的值.

**输入样例:**

```c++
5
88 70 61 96 120
```

**输出样例:**

```c++
70
```



需要做的事情: 

1. 读取一个插入的元素 
2. 插入
3. 旋转调整(使用**迭代**, 在回来的"**代**"的过程中, 遇到的**第一个不平衡节点**就是**目击者**节点)

LL: **插入点**在**目击者**的左子树的左子树,  对目击者**左单旋 (顺时针)**

RR: 插入点在目击者的右子树的右子树, 对目击者右单旋 (逆时针)

LR: 插入点在目击者的左子树的右子树, 对目击者的左子树右单旋(逆时针),  对目击者左单旋(顺时针)

RL: 插入点在目击者的右子树的左子树, 对目击者的右子树左单旋(顺时针),  对目击者右单旋(逆时针)

调试过程找到的错误: 

- AVL_Insertion()中考虑三种情况 if-else if- else if, 没有看准花括号, 错将第二个 else if包含在了第一个else if中



**示例代码:**

```c++
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
        t->left = AVL_Insertion(x, t->left);    
        // 迭代过程中, 第一次遇到不平衡是回来的时候, 也就是最底层的

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
```

## 11 Complete Binary Search Tree

给定一个 N 和一个二叉搜索树的插入序列, 要求用完全二叉树存储, 并且按照层次遍历输出该 " 完全二叉搜索树 ".

**输入样例:**

```c++
10
1 2 3 4 5 6 7 8 9 0
```

**输出样例:**

```c++
6 3 8 1 5 7 9 0 2 4
```

需要考虑的问题: 树的表示法:  链表还是数组?  数组！！

使用一个全局数组 A[ ]存储输入, "cmath"中的排序函数使其升序排列.

使用一个全局数组T[ ]存储完全二叉树, 根据完全二叉搜索树的特点逐个填入元素( 迭代进行 )

注意: 还有一个更简便的方法, 因为二叉搜索树的中序遍历就是从小到大的排列, 因此对 A[ ]排序后, 进行一次中序遍历即可解决问题.

**调试的错误, 来源于: GetLeftLength()中**

- exp2()函数的使用
-  log2()函数的使用
-  floor()返回double类型 , 向下取整函数
- min()只能处理相同类型的数据 

**示例代码:**

```c++
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
```

## 12 堆中的路径

堆的用途: 优先队列

堆的两个特性:

- 结构性: 用数组表示的**完全二叉树**
- 有序性: 任一节点的关键字是其子树所有结点的最大值(或最小值)

**本题目要求:**

将一系列给定数字依次插入一个初始为空的小顶堆`H[]`. 随后对任意给定的下标`i`, 打印从`H[i]`到根结点的路径.

需要完成的操作:

- 插入小顶堆
- 输出 元素->根的路径

**具体来说:**

1. 读入n和m; 
2. 根据输入序列建堆; 
3. 对m个要求: 打印H[i]到根的路径 

**调试找到的错误:** 

- PrintPath()中, 针对 m = 1 的情况, 没有考虑.

**示例代码:**

```c++
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

int main () {
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
```

# 13 network connection

N (2 <= N <= 10<sup>4</sup>)个节点, 进行两种操作: 建立连接 和 检查是否联通. 最后检查所有节点是否贯通.

**输入样例:**

```c++
5
C 3 2
I 3 2
C 1 5
I 4 5
I 2 4
C 3 5
S
```

**输出样例:**

```c++
no
no
yes
There are 2 components.
```

这是一个集合问题. 通过**并查集**的操作来处理, 逻辑结构用多个树来表示, 物理上用一个数组来存储(二维数组, 或者说结构数组).使用下面两种算法来优化:

**按秩归并算法**：(利用S[Root]存储信息)

- 比高度. 矮树贴到高树上.
- 比规模. 小树贴到大树上.

**路径压缩算法:**

每次 `Find()`操作的同时, 将经过的节点都修改为直接指向根节点.

**示例代码:**

```c++
#include "iostream"

using namespace std;
const int MaxSize = 10005;
typedef int Name_Of_Set;
typedef int SetType[MaxSize];

Name_Of_Set Find (SetType S, int X);    // 也就是说 SetType S == int S[MaxSize], 对
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
//普通 Find
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
```



# 14

哈夫曼树, 针对频率, 有大顶堆的特点, 但是不存放在完全二叉树.

判断是否为最优编码的方法:

1. WPL(带权路径长度)是否为最小带权路径长度.
2. 无歧义解码, 也就是前缀码
3. 没有度为1的节点





# 尾部
