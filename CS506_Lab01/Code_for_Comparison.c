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
    int m = arr[hi], p = lo;
    for (int i = lo; i < hi; i++)
    {
        if (arr[i] <= m){
            p++;
        }
    }
    int t = arr[p];
    arr[p] = m;
    arr[hi] = t;
    QuickSort(arr, lo, p-1);
    QuickSort(arr, p+1, hi);
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
    for (int i = 0; i < T; i++)
    {
        int N, S;
        scanf("%d %d", &N, &S);
        int arr[N], sarr[N], rsarr[N];
        for (int i = 0; i < N; i++)
        {
            arr[i] = rand() % 100000000;
            sarr[i] = arr[i];
        }
        QuickSort(sarr, 0, N - 1);
        for (int i = 0; i < N;i++){
            rsarr[i] = sarr[N - i - 1];
        }
        clock_t start, end;
        double time;
        if (S == 0)
        {
            printf("For Bubble Sort\n");
            start = clock();
            BubbleSort(arr, N);
            end = clock();
            time = (double)(end - start);
            printf("Time taken to sort random array = %f\n", time);

            start = clock();
            BubbleSort(sarr, N);
            end = clock();
            time = (double)(end - start);
            printf("Time taken to sort already sorted array = %f\n", time);

            start = clock();
            BubbleSort(rsarr, N);
            end = clock();
            time = (double)(end - start);
            printf("Time taken to sort reverse sorted array = %f\n", time);

        }
        if (S == 1)
        {
            printf("For Selection Sort\n");
            start = clock();
            SelectionSort(arr, N);
            end = clock();
            time = (double)(end - start);
            printf("Time taken to sort random array = %f\n", time);

            start = clock();
            SelectionSort(sarr, N);
            end = clock();
            time = (double)(end - start);
            printf("Time taken to sort already sorted array = %f\n", time);

            start = clock();
            SelectionSort(rsarr, N);
            end = clock();
            time = (double)(end - start);
            printf("Time taken to sort reverse sorted array = %f\n", time);
        }
        if (S == 2)
        {
            printf("For Insertion Sort\n");
            start = clock();
            InsertionSort(arr, N);
            end = clock();
            time = (double)(end - start);
            printf("Time taken to sort random array = %f\n", time);

            start = clock();
            InsertionSort(sarr, N);
            end = clock();
            time = (double)(end - start);
            printf("Time taken to sort already sorted array = %f\n", time);

            start = clock();
            InsertionSort(rsarr, N);
            end = clock();
            time = (double)(end - start);
            printf("Time taken to sort reverse sorted array = %f\n", time);
        }
        if (S == 3)
        {
            printf("For Merge Sort\n");
            start = clock();
            MergeSort(arr, 0, N - 1);
            end = clock();
            time = (double)(end - start);
            printf("Time taken to sort random array = %f\n", time);

            start = clock();
            MergeSort(sarr, 0, N - 1);
            end = clock();
            time = (double)(end - start);
            printf("Time taken to sort already sorted array = %f\n", time);

            start = clock();
            MergeSort(rsarr, 0, N - 1);
            end = clock();
            time = (double)(end - start);
            printf("Time taken to sort reverse sorted array = %f\n", time);
        }
        if (S == 4)
        {
            printf("For Quick Sort\n");
            start = clock();
            QuickSort(arr, 0, N-1);
            end = clock();
            time = (double)(end - start);
            printf("Time taken to sort random array = %f\n", time);

            start = clock();
            QuickSort(sarr, 0, N-1);
            end = clock();
            time = (double)(end - start);
            printf("Time taken to sort already sorted array = %f\n", time);

            start = clock();
            QuickSort(rsarr, 0, N-1);
            end = clock();
            time = (double)(end - start);
            printf("Time taken to sort reverse sorted array = %f\n", time);
        }
    }
    return 0;
}