#include "Timer.h"
#include <iostream>
#include <string>

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

void linearSearch(Inventory &inv, string searchName)
{
    if (countProducts(inv) == 0)
    {
        cout << "Inventory is empty!\n";
        return;
    }

    auto start = chrono::high_resolution_clock::now();

    Node *current = getHead(inv);
    bool found = false;

    while (current != NULL)
    {
        if (current->data.name == searchName)
        {
            auto end = chrono::high_resolution_clock::now();
            long long elapsed = getElapsedMicroseconds(start, end);

            cout << "\nLinear Search - Found!\n";
            cout << "ID: " << current->data.id << ", Name: " << current->data.name
                 << ", Qty: " << current->data.quantity << ", Price: " << current->data.price << "\n";
            cout << "Time: " << elapsed << " microseconds (O(n))\n";

            found = true;
            return;
        }
        current = current->next;
    }

    auto end = chrono::high_resolution_clock::now();
    long long elapsed = getElapsedMicroseconds(start, end);

    cout << "\nLinear Search - Not Found!\n";
    cout << "Time: " << elapsed << " microseconds (O(n))\n";
}
