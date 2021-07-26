//
//  main.cpp
//  gitdemo
//
//  Created by rg chen on 2021/7/21.

//for sort algorithm


#include <iostream>
#include <algorithm>
#define MAXSIZE 10
using namespace std;
typedef struct {
    int key;
    int otherinfo;
}Rcdtype;
typedef struct {
    Rcdtype r[MAXSIZE+1];
    int len;
}Sqtable;
//简单排序

// 1 。 选择排序 无论好坏都需要O(n^2), 因为每次选出最小值都需要遍历所有剩余元素。


void Selsort(Sqtable &L){
    int lowIndex , i ,j;
    for ( i = 1 ; i < L.len; i++) {
        lowIndex = i;
        for ( j = L.len; j > i; j--) {
            if (L.r[j].key < L.r[lowIndex].key) {
                lowIndex = j;
            }
        }
        swap(L.r[i],L.r[lowIndex]);
    }
}

//2 . 冒泡排序 最佳平均 最差运行时间接近 时间复杂度O(n^2)
void Bubsort(Sqtable &L){
    int i , j;
    for(i = 1;i < L.len;i++){
        for(j = L.len;j>i;j--){
            if(L.r[j].key < L.r[j-1].key){
                swap(L.r[j], L.r[j-1]);
            }
        }
    }
}
//冒泡的优化 鸡尾酒排序双向排
void bubble4(Sqtable &L){
    int beg = 1;
    int end = L.len;
    while(beg<end){
        int nbeg = beg, nend = end;
 
        //正向循环
        for(int i=beg;i<end;i++){
            if(L.r[i].key>L.r[i+1].key){
                nend=i;
                swap(L.r[i],L.r[i+1]);
            }
        }
        if(nend==end) break;
        end = nend;
 
        //逆向循环
        for(int i=end; i>beg;i--){
            if(L.r[i].key<L.r[i-1].key){
                nbeg=i;
                swap(L.r[i], L.r[i-1]);
            }
        }
        if(nbeg==beg) break;
        beg = nbeg;
 
    }
}

//3. 插入排序 最慢O(n^2)（逆向） 最快O(n)(正向）
void Inssort(Sqtable &L){
    int i ,j;
    for (i = 2; i <= L.len; i++) {
        if (L.r[i].key > L.r[i-1].key) {
            continue;
        }
        L.r[0] = L.r[i];
        for (j = i - 1; L.r[0].key <L.r[j].key; j--) {
            L.r[j+1] = L.r[j];
        }
        L.r[j+1] = L.r[0];
    }
}

//4.希尔排序(shell) 时间复杂与增量有关 Hibbard增量的希尔排序的时间复杂度为O(N3/2) 增量为1时就相当于插入 增量为数组大小时相当于冒泡
void InsSort2(Rcdtype A[],int n,int incr){
    for (int i = incr; i<=n; i+= incr) {
        for (int j = i; (j > incr)&&(A[j].key < A[j-incr].key); j -= incr) {
            swap(A[j], A[j-incr]);
        }
    }
}
void ShlSort(Sqtable &L){
    int n  = L.len;
    for (int i = n/2; i>2; i/=2) {
        for (int j = 1; j <= i ; j++) {
            InsSort2(&L.r[j],n+1-j,i);
        }
    }
    InsSort2(&L.r[1],n,1);//此时相当于做了一个插入排序
}

//5.快排
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
