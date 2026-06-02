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

void bubbleSort(Inventory &inv, int sortBy)
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

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - 1 - i; j++)
        {
            bool swap = (sortBy == 1) ? (array[j].price > array[j + 1].price) : (array[j].quantity > array[j + 1].quantity);
            if (swap)
            {
                Product temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    long long elapsed = getElapsedMicroseconds(start, end);

    string sortType = (sortBy == 1) ? "Price" : "Quantity";
    cout << "\nBubble Sort by " << sortType << ":\n";
    cout << "Time: " << elapsed << " microseconds (O(n^2))\n\n";

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
