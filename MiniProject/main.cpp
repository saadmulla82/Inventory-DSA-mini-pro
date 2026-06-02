#include <iostream>
#include <string>
#include <iomanip>
#include "Timer.h"

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

Inventory createInventory();
void deleteAllProducts(Node *head);
void addProduct(Inventory &inv, Product p);
void deleteProduct(Inventory &inv, int id);
void updateProduct(Inventory &inv, int id);
void displayProducts(Inventory &inv);
int countProducts(Inventory &inv);
Node *getHead(Inventory &inv);
void linearSearch(Inventory &inv, string searchName);
void binarySearch(Inventory &inv, string searchName);
void bubbleSort(Inventory &inv, int sortBy);
void mergeSortInventory(Inventory &inv, int sortBy);
void saveToCSV(Inventory &inv);
void loadFromCSV(Inventory &inv);

void displayMainMenu()
{
    cout << "\nGrocery Inventory System\n";
    cout << "1. Add Product\n";
    cout << "2. View All Products\n";
    cout << "3. Delete Product\n";
    cout << "4. Update Product\n";
    cout << "5. Search Product\n";
    cout << "6. Sort Products\n";
    cout << "7. Exit\n";
    cout << "Enter choice: ";
}

void displaySearchMenu()
{
    cout << "\nSearch by Product Name (Linear & Binary)\n";
}

void displaySortMenu()
{
    cout << "\nSort By: 1=Price, 2=Quantity\n";
    cout << "(Both Bubble & Merge Sort will run)\n";
    cout << "Enter: ";
}

int main()
{
    Inventory inv = createInventory();
    loadFromCSV(inv);
    int choice;
    bool running = true;

    while (running)
    {
        displayMainMenu();
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Enter 1-7.\n";
            continue;
        }
        cin.ignore();

        if (choice == 1)
        {
            Product newProduct;
            cout << "\nProduct Name: ";
            getline(cin, newProduct.name);
            cout << "Quantity: ";
            cin >> newProduct.quantity;
            cin.ignore();
            cout << "Price: ";
            cin >> newProduct.price;
            cin.ignore();

            addProduct(inv, newProduct);
            saveToCSV(inv);
            displayProducts(inv);
        }
        else if (choice == 2)
        {
            displayProducts(inv);
        }
        else if (choice == 3)
        {
            displayProducts(inv);
            cout << "Product ID to Delete: ";
            int deleteId;
            cin >> deleteId;
            deleteProduct(inv, deleteId);
            saveToCSV(inv);
            displayProducts(inv);
        }
        else if (choice == 4)
        {
            displayProducts(inv);
            cout << "Product ID to Update: ";
            int updateId;
            cin >> updateId;
            updateProduct(inv, updateId);
            saveToCSV(inv);
            displayProducts(inv);
        }
        else if (choice == 5)
        {
            displaySearchMenu();
            cout << "Enter Product Name to Search: ";
            string searchName;
            getline(cin, searchName);

            linearSearch(inv, searchName);
            binarySearch(inv, searchName);
        }
        else if (choice == 6)
        {
            displaySortMenu();
            int sortBy;
            cin >> sortBy;
            cin.ignore();

            if (sortBy == 1 || sortBy == 2)
            {
                bubbleSort(inv, sortBy);
                mergeSortInventory(inv, sortBy);
            }
            else
            {
                cout << "Invalid choice!\n";
            }
        }
        else if (choice == 7)
        {
            saveToCSV(inv);
            cout << "Thank You!\n";
            deleteAllProducts(inv.head);
            running = false;
        }
        else
        {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
