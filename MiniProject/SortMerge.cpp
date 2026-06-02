#include "Timer.h"
#include <iostream>
#include <iomanip>

using namespace std;

struct Product
{
    int id;
    string name;
    int quantity;
    float price;
};

struct Node
{
    Product data;
    Node *next;
};

struct Inventory
{
    Node *head;
};

int countProducts(Inventory &inv);
Node *getHead(Inventory &inv);

void merge(Product *array, int left, int mid, int right, int sortBy)
{
    int lSize = mid - left + 1;
    int rSize = right - mid;
    Product *lArr = new Product[lSize];
    Product *rArr = new Product[rSize];

    for (int i = 0; i < lSize; i++)
        lArr[i] = array[left + i];
    for (int i = 0; i < rSize; i++)
        rArr[i] = array[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < lSize && j < rSize)
    {
        bool lSmaller = (sortBy == 1) ? (lArr[i].price <= rArr[j].price) : (lArr[i].quantity <= rArr[j].quantity);
        if (lSmaller)
            array[k++] = lArr[i++];
        else
            array[k++] = rArr[j++];
    }
    while (i < lSize)
        array[k++] = lArr[i++];
    while (j < rSize)
        array[k++] = rArr[j++];

    delete[] lArr;
    delete[] rArr;
}

void mergeSortHelper(Product *array, int left, int right, int sortBy)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSortHelper(array, left, mid, sortBy);
        mergeSortHelper(array, mid + 1, right, sortBy);
        merge(array, left, mid, right, sortBy);
    }
}

void mergeSortInventory(Inventory &inv, int sortBy)
{
    int count = countProducts(inv);

    if (count == 0)
    {
        cout << "Inventory is empty!\n";
        return;
    }

    Product *array = new Product[count];
    Node *current = getHead(inv);
    int index = 0;

    while (current != NULL)
    {
        array[index] = current->data;
        index++;
        current = current->next;
    }

    auto start = chrono::high_resolution_clock::now();
    mergeSortHelper(array, 0, count - 1, sortBy);
    auto end = chrono::high_resolution_clock::now();
    long long elapsed = getElapsedMicroseconds(start, end);

    string sortType = (sortBy == 1) ? "Price" : "Quantity";
    cout << "Merge Sort by " << sortType << ":\n";
    cout << "Time: " << elapsed << " microseconds (O(n log n))\n\n";

    cout << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Qty"
         << setw(10) << "Price\n";
    cout << string(45, '-') << "\n";
    for (int i = 0; i < count; i++)
    {
        cout << setw(5) << array[i].id << setw(20) << array[i].name
             << setw(10) << array[i].quantity << setw(10)
             << fixed << setprecision(2) << array[i].price << "\n";
    }
    cout << "\n";

    delete[] array;
}
