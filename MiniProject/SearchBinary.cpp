#include "Timer.h"
#include <iostream>

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

void binarySearch(Inventory &inv, string searchName)
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

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - 1 - i; j++)
        {
            if (array[j].name > array[j + 1].name)
            {
                Product temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    auto start = chrono::high_resolution_clock::now();

    int left = 0, right = count - 1, foundIndex = -1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (array[mid].name == searchName)
        {
            foundIndex = mid;
            break;
        }
        else if (array[mid].name < searchName)
            left = mid + 1;
        else
            right = mid - 1;
    }

    auto end = chrono::high_resolution_clock::now();
    long long elapsed = getElapsedMicroseconds(start, end);

    if (foundIndex != -1)
    {
        cout << "\nBinary Search - Found!\n";
        cout << "ID: " << array[foundIndex].id << ", Name: " << array[foundIndex].name
             << ", Qty: " << array[foundIndex].quantity << ", Price: " << array[foundIndex].price << "\n";
        cout << "Time: " << elapsed << " microseconds (O(log n))\n";
    }
    else
    {
        cout << "\nBinary Search - Not Found!\n";
        cout << "Time: " << elapsed << " microseconds (O(log n))\n";
    }

    delete[] array;
}
