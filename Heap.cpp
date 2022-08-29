//
// Created by limou on 2022/8/22.
//
#include "iostream"
#include "malloc.h"

using namespace std;
#define MaxData 1000;
typedef struct HeapStruct *MaxHeap;
struct HeapStruct {
    int *Elements;
    int Size;
    int Capacity;
};

MaxHeap Create (int MaxSize) {
    auto H = (MaxHeap) malloc(sizeof (HeapStruct));
    H->Elements = (int *) malloc((MaxSize + 1) * sizeof (int));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Elements[0] = MaxData;      // 哨兵, 避免插入元素比整个堆都大时，对 i > 1 的情况的考虑

    return H;
}

bool IsFull(MaxHeap H) {
    return H->Size >= H->Capacity;
}

void Insert(MaxHeap H, int Item) {
    if (IsFull(H)) {
        cout << "最大堆已满" << endl;
        return;
    } else {
        H->Size = H->Size + 1;
        auto i = H->Size;
        for ( ; H->Elements[i / 2] < Item ; i /= 2) {
            H->Elements[i] = H->Elements[i / 2];
        }
        H->Elements[i] = Item;
    }
}

bool IsEmpty (MaxHeap H) {
    return !(H->Size);
}

int DeleteMax (MaxHeap H) {
    auto MaxItem = 0;
    if (IsEmpty(H)) {
        cout << "最大堆已空" << endl;
        MaxItem = MaxData;
    } else {
        MaxItem = H->Elements[1];

        auto Parent = 1;
        auto Child = 2;
        auto temp = H->Elements[H->Size];
        H->Size = H->Size - 1;

        for ( ; (Parent * 2) <= H->Size; Parent = Child) {
            Child = Parent * 2;
            if ((Child != H->Size) && (H->Elements[Child] < H->Elements[Child + 1]))
                Child ++;
            if (temp >= H->Elements[Child])
                break;
            else
                H->Elements[Parent] = H->Elements[Child];
        }
        H->Elements[Parent] = temp;
    }
    return MaxItem;
}

