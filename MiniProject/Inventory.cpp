#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

static int nextProductID = 1;

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

Inventory createInventory()
{
    Inventory inv;
    inv.head = NULL;
    return inv;
}

void deleteAllProducts(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        delete temp;
    }
}

void addProduct(Inventory &inv, Product p)
{
    p.id = nextProductID++;
    Node *newNode = new Node();
    newNode->data = p;
    newNode->next = NULL;

    if (inv.head == NULL)
    {
        inv.head = newNode;
    }
    else
    {
        Node *current = inv.head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }

    cout << "Added! (ID: " << p.id << ")\n";
}

void deleteProduct(Inventory &inv, int id)
{
    if (inv.head == NULL)
    {
        cout << "Empty!\n";
        return;
    }

    if (inv.head->data.id == id)
    {
        Node *temp = inv.head;
        inv.head = inv.head->next;
        delete temp;
        cout << "Deleted!\n";
        return;
    }

    Node *current = inv.head;
    while (current->next != NULL)
    {
        if (current->next->data.id == id)
        {
            Node *temp = current->next;
            current->next = temp->next;
            delete temp;
            cout << "Deleted!\n";
            return;
        }
        current = current->next;
    }

    cout << "\nProduct not found!\n\n";
}

void updateProduct(Inventory &inv, int id)
{
    Node *current = inv.head;
    while (current != NULL)
    {
        if (current->data.id == id)
        {
            int choice;
            cout << "\n--- Update Product ---\n";
            cout << "1. Update Name\n";
            cout << "2. Update Quantity\n";
            cout << "3. Update Price\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1)
            {
                cout << "New Name: ";
                getline(cin, current->data.name);
            }
            else if (choice == 2)
            {
                cout << "New Quantity: ";
                cin >> current->data.quantity;
            }
            else if (choice == 3)
            {
                cout << "New Price: ";
                cin >> current->data.price;
            }
            else
            {
                cout << "Invalid choice!\n";
            }

            cout << "\nProduct Updated Successfully!\n\n";
            return;
        }
        current = current->next;
    }

    cout << "\nProduct not found!\n\n";
}

void displayProducts(Inventory &inv)
{
    if (inv.head == NULL)
    {
        cout << "No products!\n";
        return;
    }

    cout << "\n"
         << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Qty"
         << setw(10) << "Price\n";
    cout << string(45, '-') << "\n";

    Node *current = inv.head;
    while (current != NULL)
    {
        cout << setw(5) << current->data.id << setw(20) << current->data.name
             << setw(10) << current->data.quantity << setw(10)
             << fixed << setprecision(2) << current->data.price << "\n";
        current = current->next;
    }
    cout << "\n";
}

int countProducts(Inventory &inv)
{
    int count = 0;
    Node *current = inv.head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

Node *getHead(Inventory &inv)
{
    return inv.head;
}

void saveToCSV(Inventory &inv)
{
    ofstream file("inventory.csv");
    file << "id,name,quantity,price\n";

    Node *current = inv.head;
    while (current != NULL)
    {
        file << current->data.id << ","
             << current->data.name << ","
             << current->data.quantity << ","
             << current->data.price << "\n";
        current = current->next;
    }

    file.close();
    cout << "\nInventory saved to inventory.csv\n\n";
}

void loadFromCSV(Inventory &inv)
{
    ifstream file("inventory.csv");

    if (!file.is_open())
    {
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        int id, quantity;
        float price;
        string name;

        int pos1 = line.find(',');
        int pos2 = line.find(',', pos1 + 1);
        int pos3 = line.find(',', pos2 + 1);

        id = stoi(line.substr(0, pos1));
        name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        quantity = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        price = stof(line.substr(pos3 + 1));

        if (id >= nextProductID)
        {
            nextProductID = id + 1;
        }

        Product p;
        p.id = id;
        p.name = name;
        p.quantity = quantity;
        p.price = price;

        Node *newNode = new Node();
        newNode->data = p;
        newNode->next = NULL;

        if (inv.head == NULL)
        {
            inv.head = newNode;
        }
        else
        {
            Node *current = inv.head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    file.close();
}
