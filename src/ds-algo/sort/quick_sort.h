#pragma once

#include <vector>
#include <algorithm>
#include <cstdlib>

// 传入数组为int *&arr;
void quick_sort_with_pivot(std::vector<int>& arr, const int l, const int r) {
    if (l < r) {
        int i = l, j = r;
        while (i < j) {
            while (i < j && arr[j] >= arr[l]) j--;
            while (i < j && arr[i] <= arr[l]) i++;
            std::swap(arr[i], arr[j]);
        }
        std::swap(arr[i], arr[l]);

        quick_sort_with_pivot(arr, l, i - 1);
        quick_sort_with_pivot(arr, i + 1, r);
    }
}

void quick_sort(std::vector<int>& arr, const int l, const int r) {
    if (l >= r) return;
    // 只需要将其他位置的值移动到arr[l]位置就行了，然后执行算法
    // std::swap(arr[k], arr[l]);
    int x = arr[l], i = l, j = r;
    while (i < j) {
        while (arr[i] < x) i++;
        while (arr[j] > x) j--;
        // 当两指针相遇后，还是得移动指针
        if (i < j) std::swap(arr[i++], arr[j--]);
    }

    quick_sort(arr, l, j);
    quick_sort(arr, j + 1, r);
}