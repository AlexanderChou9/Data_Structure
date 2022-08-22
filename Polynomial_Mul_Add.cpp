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
    /* 调试找出的错误：Mult()函数中构造初始序列的次数（错将t2写为了t1） PrintPoly()函数在P=NULL的情况下输出的"0 0"（不应该有换行符，因为第二行后面不应该换行）
     * Attach()需要考虑相加之后系数为0的情况 */
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
        scanf("%d %d", &c, &e);                                        /* 在第二行数据读取的最后一组出错 */
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
    }                                                          /* 用t1的第一项乘以t2的所有项，构造一个初始队列 */
    t1 = t1->link;

    while (t1) {
        t2 = P2;
        Rear = P;
        while (t2) {
            e = t1->expon + t2->expon;
            c = t1->coef * t2->coef;                           /* 相乘得到一项，然后遍历t2，看看插在哪里 */
            while (Rear->link && (Rear->link->expon > e)) {    /* Rear永远指向t2中当前节点的前一项 */
                Rear = Rear->link;
            }
            if (Rear->link && (Rear->link->expon == e)) {      /* 刚好找到系数相同的那一项，要考虑系数相加是否为0 */
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
        Attach(t1->coef, t1->expon, &Rear);                   /* 一方为空，将非空的链表逐个节点合并上去 */
        t1 = t1->link;                                                    /* 而不是直接拼接，是为了方便删除列表后，进行回收 */
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