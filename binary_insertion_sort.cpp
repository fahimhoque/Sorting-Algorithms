/*
We can use binary search to reduce the number of comparisons in normal insertion sort. 
    Binary Insertion Sort uses binary search to find the proper location to insert the selected item at each iteration. 
    In normal insertion sort, it takes O(n) comparisons (at nth iteration) in the worst case. 
    We can reduce it to O(log n) by using binary search.
Scenario:
Time Complexity: The algorithm as a whole still has a running worst-case running time of O(n2) 
                 because of the series of swaps required for each insertion. 

*/

#include <iostream>
using namespace std;

int binarySearch(int arr[], int item, int low, int high)
{
    if (high <= low)
        return (item > arr[low]) ? (low + 1) : low;

    int mid = (low + high) / 2;

    if (item == arr[mid])
        return mid + 1;

    if (item > arr[mid])
        return binarySearch(arr, item, mid + 1, high);
    return binarySearch(arr, item, low, mid - 1);
}

void insertionSort(int arr[], int n)
{
    int i, loc, j, k, selected;

    for (i = 1; i < n; ++i)
    {
        j = i - 1;
        selected = arr[i];

        loc = binarySearch(arr, selected, 0, j);

        while (j >= loc)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = selected;
    }
}

int main()
{
    int arr[] = {37, 23, 0, 17, 12, 72, 31, 46, 100, 88, 54};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;
    cout << "Before sorting: ";
    for (i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    insertionSort(arr, n);

    cout << "After sorting: ";
    for (i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}