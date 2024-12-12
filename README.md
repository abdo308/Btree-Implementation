# B-Tree Implementation in C++

This project provides a templated implementation of a **B-Tree** in C++ for efficient storage and retrieval of data. The B-Tree is a self-balancing search tree commonly used in database systems and file systems. The implementation supports generic data types and allows for insertion and splitting of nodes based on a given order.

---

## Features

1. **Generic Implementation**:
   - The B-Tree can handle any data type (e.g., integers, characters) through templates.
   
2. **Configurable Order**:
   - The order of the tree (maximum number of keys per node) is defined at compile-time.

3. **Node Splitting**:
   - Handles splitting of nodes when they exceed the maximum number of keys.

4. **Insertion**:
   - Supports insertion of keys while maintaining B-Tree properties.

5. **Visualization**:
   - Prints the tree in a structured format to the console.

---

## Code Explanation

### 1. **Template Definition**
The class is templated with two parameters:
- `T`: The data type of the keys.
- `Order`: The order of the B-Tree, determining the maximum number of keys per node.

### 2. **Node Structure**
The `Node` structure represents a node in the B-Tree:
- `keys`: Array to store keys in the node.
- `children`: Array of pointers to child nodes.
- `parent`: Pointer to the parent node.
- `keyCount`: Tracks the number of keys in the node.
- `childCount`: Tracks the number of children.
- `isLeaf`: Boolean flag indicating if the node is a leaf.

### 3. **Core Functions**

#### **Insert**
Handles inserting a new key into the tree:
- Finds the appropriate leaf node.
- Inserts the key while maintaining sorted order.
- Splits the node if it exceeds the maximum number of keys.

#### **Split**
Handles splitting a node into two when the number of keys exceeds the order:
- The middle key is promoted to the parent.
- The keys are distributed between two new nodes.

#### **Search**
Finds the appropriate node where a key should be located.
- Used internally during insertion to determine the correct position.

#### **Print**
Recursively prints the tree structure:
- Each level of the tree is indented for clarity.

---

## How to Use

1. **Include the Header**
   - Ensure the B-Tree implementation is included in your project.

2. **Instantiate a Tree**
   - Create a B-Tree with the desired type and order. For example:
     ```cpp
     Btree<int, 3> intTree; // A B-Tree of integers with order 3
     Btree<char, 5> charTree; // A B-Tree of characters with order 5
     ```

3. **Insert Data**
   - Use the `insert` method to add data:
     ```cpp
     intTree.insert(10);
     intTree.insert(20);
     ```

4. **Print the Tree**
   - Use the `print` method to visualize the structure:
     ```cpp
     intTree.print();
     ```

---

## Example

The following example demonstrates the use of the B-Tree:

```cpp
#include "Btree.h"

int main() {
    Btree<char, 5> t;

    t.insert('G');
    t.insert('I');
    t.insert('B');
    t.insert('J');
    t.insert('C');
    t.insert('A');
    t.insert('K');
    t.insert('E');
    t.insert('D');
    t.insert('S');
    t.insert('T');
    t.insert('R');
    t.insert('L');
    t.insert('F');
    t.insert('H');
    t.insert('M');
    t.insert('N');
    t.insert('P');
    t.insert('Q');

    t.print();
    return 0;
}
```

Output:
```
G
  B C
    A
    D E
  K R
    H I J
    L M N P Q
    S T
```

---

## Limitations

- The current implementation supports insertion but does not handle deletion.
- The `Order` is fixed at compile-time and cannot be changed dynamically.

---

## Future Enhancements

- Add support for deletion while maintaining B-Tree properties.
- Implement search functionality to find specific keys.
- Optimize memory management for large trees.

---

## License
This implementation is provided under the MIT License. Feel free to use and modify it as needed.

---

## Acknowledgments
This project is inspired by standard B-Tree algorithms and designed for educational purposes.

