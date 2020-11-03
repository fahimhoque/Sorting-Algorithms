/*
THE MOST COMMON SORTING ALGORITHM IN STL: sort()
Introsort begins with quicksort and if the recursion depth goes more than a particular limit it switches to Heapsort to a
    void Quicksort’s worse case O(N2) time complexity. It also uses insertion sort when the number of elements to sort is quite less.
So first it creates a partition. Three cases arises from here.

If the partition size is such that there is a possibility to exceed the maximum depth limit then the Introsort switches to Heapsort. 
    We define the maximum depth limit as 2*log(N)
If the partition size is too small then Quicksort decays to Insertion Sort.
    We define this cutoff as 16 (due to research). So if the partition size is less than 16 then we will do insertion sort.
If the partition size is under the limit and not too small (i.e- between 16 and 2*log(N)), then it performs a simple quicksort.

**Why is it better than simple Quicksort or Why the need of Introsort?**
Since Quicksort can have a worse case O(N2) time complexity and it also increases the recursion stack space (O(log N) 
    if tail recursion applied), so to avoid all these, we need to switch the algorithm from Quicksort to another if there 
    is a chance of worse case. So Introsort solves this problem by switching to Heapsort.

**Why is Insertion Sort used (and not Bubble Sort, etc)?**
Insertion sort offers following advantages.
    1. It is a known and established fact that insertion sort is the most optimal comparison-based sorting algorithm for small arrays.
    2. It has a good locality of reference
    3. It is an adaptive sorting algorithm, i.e- it outperforms all the other algorithms if the array elements are partially sorted.

**Why is Heapsort used (and not Mergesort etc)?**
This is solely because of memory requirements. Merge sort requires O(N) space whereas Heapsort is an in-place O(1) space algorithm.
Scenario:
Unstable(because of quicksort)
Time Complexity
Best Case – O(N log N)
Average Case- O(N log N)
Worse Case- O(N log N)
where, N = number of elements to be sorted.

Auxiliary Space
Just like quicksort, it may use O(log N) auxiliary recursion stack space.

*/

#include <bits/stdc++.h>
using namespace std;
void swapValue(int *a, int *b)
{
    int *temp = a;
    a = b;
    b = temp;
    return;
}

void InsertionSort(int arr[], int *begin, int *end)
{
    int left = begin - arr;
    int right = end - arr;

    for (int i = left + 1; i <= right; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }

    return;
}

int *Partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {

        if (arr[j] <= pivot)
        {
            i++;

            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (arr + i + 1);
}

int *MedianOfThree(int *a, int *b, int *c)
{
    if (*a < *b && *b < *c)
        return (b);

    if (*a < *c && *c <= *b)
        return (c);

    if (*b <= *a && *a < *c)
        return (a);

    if (*b < *c && *c <= *a)
        return (c);

    if (*c <= *a && *a < *b)
        return (a);

    if (*c <= *b && *b <= *a)
        return (b);
}
void IntrosortUtil(int arr[], int *begin, int *end, int depthLimit)
{

    int size = end - begin;

    if (size < 16)
    {
        InsertionSort(arr, begin, end);
        return;
    }

    if (depthLimit == 0)
    {
        make_heap(begin, end + 1);
        sort_heap(begin, end + 1);
        return;
    }

    int *pivot = MedianOfThree(begin, begin + size / 2, end);

    swapValue(pivot, end);

    int *partitionPoint = Partition(arr, begin - arr, end - arr);
    IntrosortUtil(arr, begin, partitionPoint - 1, depthLimit - 1);
    IntrosortUtil(arr, partitionPoint + 1, end, depthLimit - 1);

    return;
}

void Introsort(int arr[], int *begin, int *end)
{
    int depthLimit = 2 * log(end - begin);

    IntrosortUtil(arr, begin, end, depthLimit);

    return;
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int arr[] = {3, 1, 23, -9, 233, 23, -313, 32, -9};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Before Sort: ";
    printArray(arr, n);
    cout << endl;
    Introsort(arr, arr, arr + n - 1);
    cout << "After Sort: ";
    printArray(arr, n);
    return (0);
}