/*
Algorithm:
In 3 Way QuickSort, an array arr[l..r] is divided in 3 parts:
a) arr[l..i] elements less than pivot.
b) arr[i+1..j-1] elements equal to pivot.
c) arr[j..r] elements greater than pivot.


Differences between quicksort and 3 way quicksort:
In simple QuickSort algorithm, we select an element as pivot, partition the array around a 
    pivot and recur for subarrays on the left and right of the pivot. 
Consider an array which has many redundant elements. 
    For example, {1, 4, 2, 4, 2, 4, 1, 2, 4, 1, 2, 2, 2, 2, 4, 1, 4, 4, 4}. If 4 is picked as a pivot in Simple Quick Sort,
    we fix only one 4 and recursively process remaining occurrences.
The idea of 3 way Quick Sort is to process all occurrences of the pivot and is based on Dutch National Flag algorithm.

Scenario:

*/
#include <bits/stdc++.h>
using namespace std;

void partition(int a[], int l, int r, int &i, int &j)
{
    i = l - 1, j = r;
    int p = l - 1, q = r;
    int v = a[r];

    while (true)
    {

        while (a[++i] < v)
            ;

        while (v < a[--j])
            if (j == l)
                break;

        if (i >= j)
            break;

        swap(a[i], a[j]);

        if (a[i] == v)
        {
            p++;
            swap(a[p], a[i]);
        }

        if (a[j] == v)
        {
            q--;
            swap(a[j], a[q]);
        }
    }

    swap(a[i], a[r]);

    j = i - 1;
    for (int k = l; k < p; k++, j--)
        swap(a[k], a[j]);

    i = i + 1;
    for (int k = r - 1; k > q; k--, i++)
        swap(a[i], a[k]);
}

void quicksort(int a[], int l, int r)
{
    if (r <= l)
        return;

    int i, j;

    partition(a, l, r, i, j);

    quicksort(a, l, j);
    quicksort(a, i, r);
}

void printarr(int a[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d  ", a[i]);
    printf("\n");
}

// Driver code
int main()
{
    int a[] = {4, 9, 4, 4, 1, 9, 4, 4, 9, 4, 4, 1, 4};
    int size = sizeof(a) / sizeof(int);

    cout << "Before sort: ";
    printarr(a, size);
    quicksort(a, 0, size - 1);
    cout << "After sort: ";
    printarr(a, size);
    return 0;
}