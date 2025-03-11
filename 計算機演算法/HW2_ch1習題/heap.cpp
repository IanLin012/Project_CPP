#include <stdio.h>
#include <stdbool.h>

bool isHeap(int arr[], int n) {
    for (int i = 0; i <= (n - 2) / 2; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[i] < arr[left])
            return false;
        if (right < n && arr[i] < arr[right])
            return false;
    }
    return true;
}

int main() {
    int heapCandidate[] = {90, 15, 10, 7, 12, 2, 7};
    int n = sizeof(heapCandidate) / sizeof(heapCandidate[0]);

    if (isHeap(heapCandidate, n))
        printf("This binary tree is a heap\n");
    else
        printf("This binary tree is not a heap\n");

    return 0;
}
