//
// Created by limou on 2022/8/7.
//
#include <iostream>
#include <stack>

using namespace std;

#define max 1000005

int arr[max];

int main() {

    int m,n,k;                                   /* m为栈的容量 n为1~n的元素 k组数据 */
    cin>>m>>n>>k;
                                                 /* 其实就是一个模拟出栈与入栈的过程, 该入栈时入栈, 该出栈时出栈, 判断出栈序列是否相同, 是否满足栈容量要求 */
    while(k--) {
        int f=1,cur=1;                           /* cur为压入栈的元素，从1开始，每次压栈后递增. f为flag, 表明被检查的序列是否合法 */
        stack<int> s;                            /* 一定要定义到while里面，因为每次都是一个新栈，防止上一次的操作对当前的影响 */

        for(int i=0;i<n;i++) cin>>arr[i];        /* 使用全局变量arr[]数组存储序列 */

        for(int i=0;i<n;i++) {
            while(s.empty()||s.top()!=arr[i]) {   /* 第一次进入、栈内元素刚好都被弹出(开始一个新的反转序列), 会因为s.empty()进入循环, 经过判断 1. 是否结束, 2. 进行压栈操作; */
                                                  /* 栈顶元素 != 序列当前元素, 也会进入循环. 判断两者大小, 1. 决定继续压栈, 2. 直接判定该序列非法 */
                if(cur>n||s.size()>=m)
                    break;                       /* 判断处理结束 || 超出栈大小的限制, 跳出后直接进行序列合法性的判断 */

                s.push(cur++);                /* 将cur压入栈中，直到当前栈顶为该元素 */
            }

            if(s.top()!=arr[i]||s.empty()) {     /* 栈顶不是当前元素、栈为空时则说明提前退出了while循环, 判定为非法, 退出 */
                f=0;
                break;
            }
            else s.pop();                        /* 找到序列当前值则将其从栈中pop掉, 继续下一次查找. */
        }

        if(f)
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }

    return 0;
}

