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
//typedef struct {
//    int key;
//    int otherinfo;
//}Rcdtype;
#define D 2
#define R 10


typedef struct {
    int keys[D];
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

//5.快排（基于二叉树查找思想进行排序）
//最好的情况是pivot都是中点 -- O(n log n) (平均情况也是如此，所以有些快排算法会在一开始随意打乱数列)
//最差的情况是本来就是有序数列 -- O(n^2)
int FindPivot(Sqtable &L,int i ,int j){
    return  (i+j)/2;
}
int partition(Sqtable &L,int i ,int r ,int pivot){
    int l = i - 1;
    do {
        while (L.r[++l].key < pivot);
        while (r >= i &&L.r[--r].key > pivot);
        swap(L.r[l], L.r[r]);
    } while (l<r);
    swap(L.r[l], L.r[r]);
    return  1;
}
void quiSort(Sqtable &L,int i,int j){
    int pivotIndex = FindPivot(L, i, j);
    swap(L.r[pivotIndex], L.r[j]);
    int k = partition(L, i,j,L.r[j].key);
    swap(L.r[k], L.r[j]);
    if ((k-i) > 1) quiSort(L, i, k-1);
    if ((j-k) > 1) quiSort(L, k+1, j);
}

//6.Heap Sort 堆排序：基于堆数据结构 k(i)<=k(2i) k(i)<=k(2i+2) 小顶堆
//                               k(i)>=k(2i) k(i)>=k(2i+2) 大顶堆

typedef Sqtable Heaplist;

void HeapAdjust(Heaplist &L,int s,int t){
    //L中除L.r[s]不满大顶堆定义外其他均满足 此函数即调整使这个L.r[s]为顶的堆成为大顶堆
    Rcdtype w = L.r[s];
    for (int i = 2 * s; i <= t; i *= 2) {
        if (i<t) {
            i = (L.r[i].key > L.r[i+1].key) ? i:i+1;
        }
        if (w.key >= L.r[i+1].key) {
            break;
        }
        L.r[s] = L.r[i];
        s = i;
    }
    L.r[s] = w;
}
void HeapSort(Heaplist &L){
    for (int i = L.len/2; i >= 1; i--) {
        HeapAdjust(L, i, L.len);
    }
    for (int i = L.len; i > 1; i--) {
        swap(L.r[1], L.r[i]);
        HeapAdjust(L, 1, i-1);
    }
}

//7.归并排序 采用分治算法
void Merge(Rcdtype rs[],Rcdtype rt[],int s , int m, int t){
    int i,j,k;
    for ( i = s,j = m+1,k = i ;i <= m&&j <= t ; k ++) {
        if (rs[i].key <= rs[j].key) {
            rt[k] = rs[i++];
        }
        else rt[k] =rs [j++];
    }
    for (; i <= m; ) {
        rt[k++] = rs[i++];
    }
    for (; j <= t; ) {
        rt[k++] = rs[j++];
    }
}//merge
void MSortPass(Rcdtype rs[],Rcdtype rt[],int s,int t){
    Rcdtype rtmp[MAXSIZE+1];
    if (s == t) {
        rt[s] = rs[s];
        return;
    }
    int m = (s+t)/2;
    MSortPass(rs, rtmp, s, m);
    MSortPass(rs, rtmp, m+1, t);
    Merge(rtmp, rt, s, m, t);
}
void MergeSort(Sqtable &L){
    MSortPass(L.r, L.r, 1, L.len);
}

//8.基数排序 按位数从低向高排
void RadPass(Rcdtype r[],Rcdtype t[],int n,int k){
    int j,count[11];
    for( j = 0;j<R;j++) count[j] = 0;
    for( j = 1;j <= n;j++) count[r[j].keys[k]]++;
    for( j = 1;j < R;j++)  count[j] = count [j-1] + count[j];
    for (j = n; j >= 1; j--) {
        int  p = r[j].keys[k];
        t[count[p]] = r[j];
        count[p]--;
    }
}

void RadSort(Sqtable &L){
    Rcdtype t[L.len+1];
    int k = D-1;
    while (k>=0) {
        RadPass(L.r, t, L.len, k);
        k--;
        if (k>=0) {
            RadPass(t, L.r, L.len, k);
            k--;
        }
        else
            for (j = 1; j <= L.len; j++) {
                L.r[j] = t[j];
            }
    }//while
}//RadSort
