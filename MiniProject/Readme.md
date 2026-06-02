# Grocery Inventory Management System

A simple C++ console application for managing grocery inventory using data structures (linked lists) and algorithms (searching, sorting).

## Features

- **Add Products** - Auto-generated IDs, no user input required
- **View Products** - Display all products in table format
- **Delete Products** - Remove by product ID
- **Update Products** - Modify name, quantity, or price
- **Search Products** - Two algorithms side-by-side:
  - Linear Search: O(n)
  - Binary Search: O(log n)
- **Sort Products** - Two algorithms with comparison:
  - Bubble Sort: O(n²)
  - Merge Sort: O(n log n)
- **CSV Storage** - Auto-save to `inventory.csv`
- **Sample Data** - `sampleinventory.csv` with 100 items

## Compilation

```bash
g++ -std=c++11 main.cpp Inventory.cpp SearchLinear.cpp SearchBinary.cpp SortBubble.cpp SortMerge.cpp -o grocery
```

## Running

```bash
./grocery
```

## File Structure

| File | Purpose |
|------|---------|
| `main.cpp` | Main menu and user interface |
| `Inventory.cpp` | Linked list implementation, add/delete/update products |
| `SearchLinear.cpp` | Linear search algorithm |
| `SearchBinary.cpp` | Binary search algorithm |
| `SortBubble.cpp` | Bubble sort algorithm |
| `SortMerge.cpp` | Merge sort algorithm |
| `Timer.h` | Timing utility for performance measurement |
| `inventory.csv` | Active inventory data |
| `sampleinventory.csv` | Sample data (100 items) |

## Data Structure

**Product Struct:**
```cpp
struct Product {
    int id;           // Auto-generated
    string name;
    int quantity;
    float price;
};
```

**Linked List:**
```cpp
struct Node {
    Product data;
    Node *next;
};

struct Inventory {
    Node *head;
};
```

## Usage

### Menu Options

```
1. Add Product        - Enter name, qty, price (ID auto-generated)
2. View All Products  - Display table of products
3. Delete Product     - Enter product ID
4. Update Product     - Enter ID, choose field to update
5. Search Product     - Enter product name (runs both searches)
6. Sort Products      - Choose price/quantity (runs both sorts)
7. Exit               - Save and quit
```

### Example Session

```
Grocery Inventory System
1. Add Product
...
Enter choice: 1

Product Name: Apple
Quantity: 50
Price: 2.50
Added! (ID: 1)

ID  Name           Qty  Price
----------------------------------------
1   Apple          50   2.5

Enter choice: 5

Search by Product Name (Linear & Binary)
Enter Product Name to Search: Apple

Linear Search - Found!
ID: 1, Name: Apple, Qty: 50, Price: 2.5
Time: 45 microseconds (O(n))

Binary Search - Found!
ID: 1, Name: Apple, Qty: 50, Price: 2.5
Time: 12 microseconds (O(log n))
```

## Using Sample Data

```bash
cp sampleinventory.csv inventory.csv
./grocery
```

The sample file contains 100 grocery items (fruits, vegetables, dairy, meat, etc.) for testing.

## Algorithms Explained

### Search
- **Linear**: Checks each product sequentially - simple but slower for large datasets
- **Binary**: Divides search space in half - faster but requires sorted data

### Sort
- **Bubble**: Repeatedly swaps adjacent elements - easy to understand, slow for large datasets
- **Merge**: Divide-and-conquer approach - faster, consistent performance

## CSV Format

```
id,name,quantity,price
1,Apple,100,2.50
2,Banana,150,1.50
3,Tomato,200,1.50
```

Auto-saves on:
- Add product
- Delete product
- Update product
- Exit (option 7)

## Notes

- IDs are auto-generated and never reused
- Product names are case-sensitive in search
- CSV persists across sessions
- All timing is in microseconds
- Simple, minimal output for clarity