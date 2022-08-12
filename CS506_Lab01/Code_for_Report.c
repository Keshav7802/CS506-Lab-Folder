#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pbPlots.h"
#include "supportLib.h"

int PlotGraphs(int pts, double x[], double ISSy[], double ISUy[], double SSy[], double MSy[], double QSy[], double BSSy[], double BSy[])
{
    _Bool success;

    RGBABitmapImageReference *ISS = CreateRGBABitmapImageReference();
    RGBABitmapImageReference *ISU = CreateRGBABitmapImageReference();
    RGBABitmapImageReference *SS = CreateRGBABitmapImageReference();
    RGBABitmapImageReference *MS = CreateRGBABitmapImageReference();
    RGBABitmapImageReference *QS = CreateRGBABitmapImageReference();
    RGBABitmapImageReference *BSS = CreateRGBABitmapImageReference();
    RGBABitmapImageReference *BS = CreateRGBABitmapImageReference();
    StringReference *errorMessage = (StringReference *)malloc(sizeof(StringReference));
    success = DrawScatterPlot(ISS, 600, 400, x, pts, ISSy, pts, errorMessage);
    success = success && DrawScatterPlot(ISU, 600, 400, x, pts, ISUy, pts, errorMessage);
    success = success && DrawScatterPlot(SS, 600, 400, x, pts, SSy, pts, errorMessage);
    success = success && DrawScatterPlot(MS, 600, 400, x, pts, MSy, pts, errorMessage);
    success = success && DrawScatterPlot(QS, 600, 400, x, pts, QSy, pts, errorMessage);
    success = success && DrawScatterPlot(BSS, 600, 400, x, pts, BSSy, pts, errorMessage);
    success = success && DrawScatterPlot(BS, 600, 400, x, pts, BSy, pts, errorMessage);

    if (success)
    {
        size_t length;
        double *pngdata = ConvertToPNG(&length, ISS->image);
        WriteToFile(pngdata, length, "Insertion Sort - Simple.png");
        DeleteImage(ISS->image);

        pngdata = ConvertToPNG(&length, ISU->image);
        WriteToFile(pngdata, length, "Insertion Sort - Updated.png");
        DeleteImage(ISU->image);

        pngdata = ConvertToPNG(&length, SS->image);
        WriteToFile(pngdata, length, "Selection Sort.png");
        DeleteImage(SS->image);

        pngdata = ConvertToPNG(&length, MS->image);
        WriteToFile(pngdata, length, "Merge Sort.png");
        DeleteImage(MS->image);

        pngdata = ConvertToPNG(&length, QS->image);
        WriteToFile(pngdata, length, "Quick Sort.png");
        DeleteImage(QS->image);

        pngdata = ConvertToPNG(&length, BSS->image);
        WriteToFile(pngdata, length, "Bubble Sort - Simple.png");
        DeleteImage(BSS->image);

        pngdata = ConvertToPNG(&length, BS->image);
        WriteToFile(pngdata, length, "Bubble Sort.png");
        DeleteImage(BS->image);
    }
    else
    {
        fprintf(stderr, "Error: ");
        for (int i = 0; i < errorMessage->stringLength; i++)
        {
            fprintf(stderr, "%c", errorMessage->string[i]);
        }
        fprintf(stderr, "\n");
    }

    return success ? 0 : 1;
}

void InsertionSort(int arr[], int n, int ans[]){
    for (int i = 0; i < n;i++){
        for (int j = 0; j <= i;j++){
            if(j==i)
                ans[j] = arr[i];
            else{
                if(arr[i] <= ans[j]) {
                    for (int k = i; k > j;k--)
                        ans[k] = ans[k-1];
                    ans[j] = arr[i];
                    break;
                }
            }
        }
    }
    return;
}

void UpdatedIS(int arr[], int n){
    for (int i = 1; i < n;i++){
        int j = i;
        while(j>0 && arr[j-1] > arr[j]){
            int t = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = t;
            j--;
        }
    }
}

void SelectionSort(int arr[], int n){
    for (int i = 0; i < n - 1;i++){
        for (int j = i + 1; j < n;j++){
            if(arr[j] <= arr[i]){
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }
    }
}

void MergeSort(int arr[], int lo, int hi){
    if(hi == lo)
        return;
    int mid = (hi + lo) / 2;
    MergeSort(arr, lo, mid);
    MergeSort(arr, mid + 1, hi);
    int ans[hi - lo + 1];
    int i = lo, j = mid + 1, k = 0;
    while(i<=mid && j<=hi){
        if(arr[i] <= arr[j]) {
            ans[k++] = arr[i++];
        }
        else
            ans[k++] = arr[j++];
    }
    while(i<=mid){
        ans[k++] = arr[i++];
    }
    while(j<=hi) {
        ans[k++] = arr[j++];
    }
    for (int k = lo; k <= hi;k++){
        arr[k] = ans[k - lo];
    }
}

void QuickSort(int arr[], int lo, int hi){
    if(hi <= lo)
        return;
    int m = arr[hi];
    int a[hi - lo + 1];
    int x = 0, y = hi - lo;
    for (int i = lo; i < hi; i++){
        if(arr[i] <= m)
            a[x++] = arr[i];
        else
            a[y--] = arr[i];
    }
    a[x] = m;
    for (int i = lo; i <= hi;i++)
        arr[i] = a[i-lo];
    QuickSort(arr, lo, lo + x - 1);
    QuickSort(arr, lo + x + 1, hi);
}

void BubbleSort(int arr[], int n){
    for (int i = 0; i < n - 1;i++){
        bool isSame = true;
        for (int j = 0; j < n - i - 1;j++){
            if(arr[j] > arr[j+1]) {
                isSame = false;
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
        if(isSame)
            break;
    }
}

void BubbleSort_Simple(int arr[], int n){
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}


int main(){
    FILE *fp = fopen("output.txt", "w");
    if(fp == NULL) {
        printf("Error: File Not Created");
        exit(0);
    }
    int pts = 50;
    double x[pts], ISSy[pts], ISUy[pts], SSy[pts], MSy[pts], QSy[pts], BSSy[pts], BSy[pts];

    int n;
    for (n = 1000; n <= 50000; n = n + 1000)
    {
        printf("%d\n", n);
        x[n / 1000 - 1] = round(n);
        int mainarr[n];
        fprintf(fp, "Analysing for n = %d\n", n);
        for (int i = 0; i < n; i++)
        {
            mainarr[i] = rand() % 10000; // Generate a number between 0 and 9999
        }
        clock_t start, end;

        int arr[n], ans[n];
        for (int i = 0; i < n;i++)
            arr[i] = mainarr[i];
        start = clock();
        InsertionSort(arr, n, ans);
        end = clock();
        fprintf(fp, "For Insertion Sort - Simple: Time taken is = %f\n", (double)(end - start));
        ISSy[n / 1000 - 1] = (double) round(end - start);

        for (int i = 0; i < n; i++)
            arr[i] = mainarr[i];
        start = clock();
        UpdatedIS(arr, n);
        end = clock();
        fprintf(fp, "For Insertion Sort - Updated: Time taken is = %f\n", (double)(end - start));
        ISUy[n / 1000 - 1] = (double)round(end - start);

        for (int i = 0; i < n; i++)
            arr[i] = mainarr[i];
        start = clock();
        SelectionSort(arr, n);
        end = clock();
        fprintf(fp, "For Selection Sort: Time taken is = %f\n", (double)(end - start));
        SSy[n / 1000 - 1] = (double)round(end - start);

        for (int i = 0; i < n; i++)
            arr[i] = mainarr[i];
        start = clock();
        MergeSort(arr, 0, n-1);
        end = clock();
        fprintf(fp, "For Merge Sort: Time taken is = %f\n", (double)(end - start));
        MSy[n / 1000 - 1] = (double)round(end - start);

        for (int i = 0; i < n; i++)
            arr[i] = mainarr[i];
        start = clock();
        QuickSort(arr, 0, n-1);
        end = clock();
        fprintf(fp, "For Quick Sort: Time taken is = %f\n", (double)(end - start));
        QSy[n / 1000 - 1] = (double)round(end - start);

        for (int i = 0; i < n; i++)
            arr[i] = mainarr[i];
        start = clock();
        BubbleSort_Simple(arr, n);
        end = clock();
        fprintf(fp, "For Bubble: Time taken is = %f\n", (double)(end - start));
        BSSy[n / 1000 - 1] = (double)round(end - start);

        for (int i = 0; i < n; i++)
            arr[i] = mainarr[i];
        start = clock();
        BubbleSort(arr, n);
        end = clock();
        fprintf(fp, "For Bubble: Time taken is = %f\n", (double)(end - start));
        BSy[n / 1000 - 1] = (double)round(end - start);

        fprintf(fp, "\n");
    }
    fclose(fp);
    PlotGraphs(pts, x, ISSy, ISUy, SSy, MSy, QSy, BSSy, BSy);
}