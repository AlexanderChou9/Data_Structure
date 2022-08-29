//
// Created by https://blog.csdn.net/u011386173/article/details/95651745
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HeapCapacity 64
typedef struct TreeNode *HuffmanTree;
struct TreeNode
{
    int Weight;
    HuffmanTree Left;
    HuffmanTree Right;
};

typedef struct HeapNode *MinHeap;
struct HeapNode
{
    HuffmanTree *Data; //堆中存放TreeNode结点的数组
    int Size;
};

MinHeap createHeap(); //创建最小堆
HuffmanTree createHuffman(); //创建Huffman树
MinHeap initHeap(int N, int F[]); //读取数据，并将数据插入到最小堆中
HuffmanTree deleteMin(MinHeap H); //堆的删除，获取最小堆中的最小值
void insertHeap(MinHeap H, HuffmanTree huff); //堆的插入
HuffmanTree huffman(MinHeap H);//Huffman树的构造
int WPL(HuffmanTree huff, int depth);//计算Huffman树的编码长度
int checkSubmit(char code[], HuffmanTree current); //检查学生的提交

int main()
{
    int N;
    scanf("%d", &N);
    int F[N];
    MinHeap H = initHeap(N, F);
    HuffmanTree huff = huffman(H);
    int codeLen = WPL(huff, 0);
    int M;
    scanf("%d", &M);
    char ch;
    char code[N+1];
    int i;
    for(i = 0; i < M; i++) {
        int counter = 0;
        int result = 1;
        int flag = 0;
        HuffmanTree head = createHuffman();
        HuffmanTree current;
        int k;
        for(k = 0; k < N; k++) {
            current = head;
            getchar();
            scanf("%c", &ch);
            scanf("%s", code);
            counter += strlen(code) * F[k]; //记录总的编码长度
            if(flag == 0) {
                result = checkSubmit(code, current);
                if(result == 0)
                    flag = 1;
            }
        }
        if(counter == codeLen && result == 1) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}

MinHeap createHeap()
{
    MinHeap H = (MinHeap)malloc(sizeof(struct HeapNode));
    H->Data = (HuffmanTree*)malloc(sizeof(struct TreeNode) * HeapCapacity); //最小堆存储数据是从下标为1开始的
    H->Size = 0;
    HuffmanTree huff = createHuffman();
    H->Data[0] = huff;
    return H;
}

HuffmanTree createHuffman()
{
    HuffmanTree T = (HuffmanTree)malloc(sizeof(struct TreeNode));
    T->Weight = 0;
    T->Left = NULL;
    T->Right = NULL;
    return T;
}

MinHeap initHeap(int N, int F[])
{
    MinHeap H = createHeap();
    HuffmanTree huff;
    char c;
    int f;
    int i;
    for(i = 0; i < N; i++) {
        getchar();
        scanf("%c %d", &c, &f);
        F[i] = f; //将频率保存到数组freq中
        huff = createHuffman();
        huff->Weight = f;
        insertHeap(H, huff); //将频率插入到堆中
    }
    return H;
}

HuffmanTree deleteMin(MinHeap H)
{
    HuffmanTree minItem = H->Data[1];
    HuffmanTree temp = H->Data[H->Size--];
    int parent, child;
    for(parent = 1; parent * 2 <= H->Size; parent = child) {
        child = parent * 2;
        if((child != H->Size) && (H->Data[child]->Weight > H->Data[child + 1]->Weight))
            child++;
        if(temp->Weight <= H->Data[child]->Weight)
            break;
        H->Data[parent] = H->Data[child];
    }
    H->Data[parent] = temp;
    return minItem;
}


void insertHeap(MinHeap H,HuffmanTree huff) //堆的插入操作
{
    int i = ++H->Size;
    for(; H->Data[i/2]->Weight > huff->Weight; i/=2) {
        H->Data[i] = H->Data[i/2];
    }
    H->Data[i] = huff;
}


HuffmanTree huffman(MinHeap H) //形成Huffman树
{
    HuffmanTree huff;
    int i;
    int times = H->Size; //一定要用临时变量记录，因为在deleteMin函数执行时，H->Size发生了变化
    for(i = 1; i < times; i++) {
        huff = createHuffman();
        huff->Left = deleteMin(H);
        huff->Right = deleteMin(H);
        huff->Weight = huff->Left->Weight + huff->Right->Weight;
        insertHeap(H, huff); //重新插入堆中
    }
    huff = deleteMin(H);
    return huff;
}

int WPL(HuffmanTree huff, int depth)
{
    if(huff->Left == NULL && huff->Right == NULL)
        return depth * huff->Weight;
    else
        return WPL(huff->Left,depth + 1) + WPL(huff->Right, depth + 1);
}

int checkSubmit(char code[], HuffmanTree current) //建树的过程中检查是否满足前缀码要求
{
    int i;
    for(i = 0; i < strlen(code); i++) {
        if(code[i] == '0') {//向左拓展一层
            if(current->Left == NULL) {
                current->Left = createHuffman();
            } else if(current->Left->Weight == -1) { //已经访问到之前访问过的结点，即之前访问过的结点编码是当前字符串的前缀
                return 0;
            }
            current = current->Left;
        } else if (code[i] == '1') {
            if(current->Right == NULL) {
                current->Right = createHuffman();
            } else if(current->Right->Weight == -1) {
                return 0;
            }
            current = current->Right;
        }
    }
    current->Weight = -1; //当前字符串遍历结束后，给当前结点赋值-1，那么后续一旦访问到结点的Weight = -1，就表明之前访问的某个字符串是当前字符串编码的前缀，就可以直接判断结果
    if(current->Left == NULL && current->Right == NULL) //如果字符串遍历结束时，当前是叶子结点，那么当前字符串的编码是正确的
        return 1;
    else
        return 0;
}