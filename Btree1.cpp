#include <iostream>
using namespace std;

template <typename T, int Order>
class Btree
{
private:
    struct Node
    {
        T keys[Order];             // Array to store keys
        Node *children[Order + 3]; // Array to store children pointers
        Node *parent;              // Pointer to parent node
        int keyCount;              // Number of keys currently in the node
        int childCount;
        bool isLeaf; // Whether the node is a leaf

        Node()
        {
            parent = nullptr;
            keyCount = 0;
            childCount = 0;
            isLeaf = true;
            for (int i = 0; i < Order; ++i)
                children[i] = nullptr;
        }
    };

    Node *root;

public:
    Btree() : root(nullptr) {}

    void insert(T value)
    {
        if (root == nullptr)
        {
            root = new Node();
            root->keys[0] = value;
            root->keyCount = 1;
        }
        else
        {
            int inx = 0;
            pair<Node *, int> p = search(root, value, inx);
            Node *leaf = p.first;
            inx = p.second;
            insertInNode(leaf, value);
            if (leaf->keyCount == Order)
            {
                split(leaf, inx);
            }
        }
    }

    void print()
    {
        printTree(root, 0);
    }

private:
    void printTree(Node *node, int depth)
    {
        if (node == nullptr)
            return;

        for (int i = 0; i < depth; ++i)
            cout << "  ";

        for (int i = 0; i < node->keyCount; ++i)
            cout << node->keys[i] << " ";
        cout << endl;

        for (int i = 0; i <= node->keyCount; ++i)
            printTree(node->children[i], depth + 1);
    }

    pair<Node *, int> search(Node *tmp, T value, int &inx)
    {
        if (tmp->isLeaf)
        {
            return {tmp, inx};
        }
        inx = 0;
        while (inx < tmp->keyCount && tmp->keys[inx] < value)
        {
            ++inx;
        }
        return search(tmp->children[inx], value, inx);
    }

    void insertInNode(Node *node, T value)
    {
        node->keys[node->keyCount] = value;
        node->keyCount++;
        for (int j = node->keyCount - 1; j > 0; j--)
        {
            if (node->keys[j] < node->keys[j - 1])
                swap(node->keys[j], node->keys[j - 1]);
        }
    }

    void split(Node *node, int inx)
    {
        if (node->keyCount < Order)
            return;

        // Split the node into two children
        Node *left = new Node();
        Node *right = new Node();

        int midIndex = Order / 2;
        T middleKey = node->keys[midIndex];
        // populate the left
        for (int i = 0; i < midIndex; ++i)
        {
            left->keys[i] = node->keys[i];
            ++left->keyCount;
        }
        // populate right
        for (int i = midIndex + 1; i < node->keyCount; ++i)
        {
            right->keys[i - midIndex - 1] = node->keys[i];
            ++right->keyCount;
        }
        if (!node->isLeaf)
        {
            int sz = node->childCount - 1;
            for (int i = 0; i <= sz / 2; ++i)
            {
                left->children[i] = node->children[i];
                left->children[i]->parent = left;

                left->childCount++;
                node->children[i] = nullptr;
                node->childCount--;
            }
            for (int i = (sz / 2) + 1, j = 0; i <= sz; ++i, ++j)
            {
                right->children[j] = node->children[i];
                right->children[j]->parent = right;
                right->childCount++;
                node->children[i] = nullptr;
                node->childCount--;
            }
            node->children[0] = left;
            node->children[1] = right;
            left->isLeaf = false;
            right->isLeaf = false;
        }
        if (node->parent == nullptr)
        {
            Node *newRoot = new Node();
            newRoot->keys[0] = middleKey;
            newRoot->keyCount = 1;
            newRoot->children[0] = left;
            newRoot->children[1] = right;
            newRoot->childCount += 2;
            left->parent = newRoot;
            right->parent = newRoot;
            this->root = newRoot;
            newRoot->isLeaf = false;
            delete node;
        }
        else
        {
            Node *parent = node->parent;
            insertInNode(parent, middleKey);
            for (int i = 0; i < Order + 2; ++i)
            {
                if (parent->children[i] == nullptr)
                {
                    parent->children[i] = left;
                    parent->children[i + 1] = right;
                    left->parent = parent;
                    right->parent = parent;
                    break;
                }
            }
            parent->childCount += 2;
            int x = parent->childCount - 1;
            if (parent->children[inx] != node)
            {

                for (int i = 0; i < parent->childCount; ++i)
                {
                    if (parent->children[i] == node)
                    {
                        inx = i;
                        break;
                    }
                }
            }
            for (int i = inx; i < parent->childCount - 1; ++i)
            {
                if (parent->children[i + 1] == nullptr)
                {
                    parent->children[i] = nullptr;
                    x = i;
                    break;
                }
                swap(parent->children[i], parent->children[i + 1]);
            }
            parent->children[x] = nullptr;
            parent->childCount -= 1;
            // sort functiom
            for (int i = 0; i < parent->childCount - 1; ++i)
            {
                for (int j = 0; j < parent->childCount - i - 1; ++j)
                {

                    if (parent->children[j]->keys[0] > parent->children[j + 1]->keys[0])
                    {
                        // Swap the children if their keys are not in order
                        swap(parent->children[j], parent->children[j + 1]);
                    }
                }
            }
            if (parent->keyCount == Order)
                split(parent, inx);
            delete node;
        }
    }
};

int main()
{
    Btree<int, 3> t1;
    // for (int i = 0; i < 50; ++i)
    // {
    //     t1.insert(i);
    // }
    // t1.print();
    // t1.insert(1);
    // t1.insert(5);
    // t1.insert(0);
    // t1.insert(4);
    // t1.insert(3); // Now it should work without infinite loop
    // t1.insert(2); // Add more inserts to trigger splits
    // t1.print();

    Btree<char, 5> t;

    // Look at the example in our lecture:
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
