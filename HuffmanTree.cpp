//
// Created by limou on 2022/8/25.
//
typedef struct TreeNode *HuffmanTree;
struct TreeNode {
    int Weight;
    HuffmanTree Left;
    HuffmanTree Right;
};


HuffmanTree Huffman (MinHeap H);
/* 使用小顶堆, 完成两次需最小值的操作 */
