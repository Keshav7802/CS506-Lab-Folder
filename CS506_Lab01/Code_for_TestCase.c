#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

void InsertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j])
        {
            int t = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = t;
            j--;
        }
    }
}

void SelectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] <= arr[i])
            {
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }
    }
}

void MergeSort(int arr[], int lo, int hi)
{
    if (hi == lo)
        return;
    int mid = (hi + lo) / 2;
    MergeSort(arr, lo, mid);
    MergeSort(arr, mid + 1, hi);
    int ans[hi - lo + 1];
    int i = lo, j = mid + 1, k = 0;
    while (i <= mid && j <= hi)
    {
        if (arr[i] <= arr[j])
        {
            ans[k++] = arr[i++];
        }
        else
            ans[k++] = arr[j++];
    }
    while (i <= mid)
    {
        ans[k++] = arr[i++];
    }
    while (j <= hi)
    {
        ans[k++] = arr[j++];
    }
    for (int k = lo; k <= hi; k++)
    {
        arr[k] = ans[k - lo];
    }
}

void QuickSort(int arr[], int lo, int hi)
{
    if (hi <= lo)
        return;
    int m = arr[hi];
    int a[hi - lo + 1];
    int x = 0, y = hi - lo;
    for (int i = lo; i < hi; i++)
    {
        if (arr[i] <= m)
            a[x++] = arr[i];
        else
            a[y--] = arr[i];
    }
    a[x] = m;
    for (int i = lo; i <= hi; i++)
        arr[i] = a[i - lo];
    QuickSort(arr, lo, lo + x - 1);
    QuickSort(arr, lo + x + 1, hi);
}

void BubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        bool isSame = true;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                isSame = false;
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
        if (isSame)
            break;
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T;i++){
        int N, S, k, p;
        scanf("%d %d %d %d", &N, &S, &k, &p);
        int arr[N];
        for (int i = 0; i < N; i++)
        {
            arr[i] = rand() % 100000000;
        }
        if(k){
            QuickSort(arr, 0, N - 1);
            if(k == 2){
                int i = 0, j = N - 1;
                while(i<j){
                    int t = arr[j];
                    arr[j] = arr[i];
                    arr[i] = t;
                    i++;
                    j--;
                }
            }
        }
        int prev[N];
        if(p == 2) {
            for (int i = 0; i < N;i++)
                prev[i] = arr[i];
        }
        clock_t start, end;
        double time;
        if(S == 0) {
            start = clock();
            BubbleSort(arr, N);
            end = clock();
            time = (double)(end - start);
        }
        if(S == 1){
            start = clock();
            SelectionSort(arr, N);
            end = clock();
            time = (double)(end - start);
        }
        if(S == 2){
            start = clock();
            InsertionSort(arr, N);
            end = clock();
            time = (double)(end - start);
        }
        if(S == 3){
            start = clock();
            MergeSort(arr, 0, N-1);
            end = clock();
            time = (double)(end - start);
        }
        if(S == 4){
            start = clock();
            QuickSort(arr, 0, N-1);
            end = clock();
            time = (double)(end - start);
        }
        if(p == 0) {
            printf("%f\n", time);
        }
        if(p == 1){
            printf("%f\n", time);
            for (int i = 0; i < N;i++) {
                if(i == 50)
                    break;
                printf("%d ", arr[i]);
            }
            printf("\n");
        }
        if(p == 2){
            printf("%f\n", time);
            for (int i = 0; i < N;i++) {
                if(i == 50)
                    break;
                printf("%d ", prev[i]);
            }
            printf("\n");
            for (int i = 0; i < N;i++) {
                if(i == 50)
                    break;
                printf("%d ", arr[i]);
            }
            printf("\n");
        }
    }
    return 0;
}