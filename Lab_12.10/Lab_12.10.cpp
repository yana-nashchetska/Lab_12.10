#include <iostream>
#include <fstream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int value) 
{
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Memory allocation error!" << endl;
        return nullptr;
    }
    newNode->data = value;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

Node* insertNode(Node* root, int value)
{
    if (root == nullptr) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insertNode(root->left, value);
    }
    else {
        root->right = insertNode(root->right, value);
    }
    return root;
}

Node* findMinValueNode(Node* node)
{
    Node* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Node* deleteNode(Node* root, int value) 
{
    if (root == nullptr) {
        return root;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    }
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMinValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

bool searchNode(Node* root, int value) 
{
    if (root == nullptr) {
        return false;
    }
    if (value == root->data) {
        return true;
    }
    if (value < root->data) {
        return searchNode(root->left, value);
    }
    else {
        return searchNode(root->right, value);
    }
}

void prefixTraversal(Node* root) 
{
    if (root == nullptr) {
        return;
    }
    cout << root->data << " ";
    prefixTraversal(root->left);
    prefixTraversal(root->right);
}

void postfixTraversal(Node* root) 
{
    if (root == nullptr) {
        return;
    }
    postfixTraversal(root->left);
    postfixTraversal(root->right);
    cout << root->data << " ";
}

void infixTraversal(Node* root)
{
    if (root == nullptr) {
        return;
    }
    infixTraversal(root->left);
    cout << root->data << " ";
    infixTraversal(root->right);
}

int countNodesBetween(Node* root, int minValue, int maxValue)
{
    if (root == nullptr) {
        return 0;
    }

    if (root->data < minValue) {
        return countNodesBetween(root->right, minValue, maxValue);
    }
    else if (root->data > maxValue) {
        return countNodesBetween(root->left, minValue, maxValue);
    }
    else {
        return 1 + countNodesBetween(root->left, minValue, maxValue) + countNodesBetween(root->right, minValue, maxValue);
    }
}

void destroyTree(Node* root)
{
    if (root == nullptr) {
        return;
    }
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}

void PrintTree(Node* root, int level)
{
    if (root != NULL)
    {
        PrintTree(root->right, level + 1);
        for (int i = 1; i <= level; i++)
            cout << " ";
        cout << root->data << endl;
        PrintTree(root->left, level + 1);
    }
}

void PrintMenu()
{
    cout << "\n Choose an action:\n ";
    cout << " 1. Insert\n ";
    cout << " 2. Delete\n ";
    cout << " 3. Search\n ";
    cout << " 4. Count nodes between\n ";
    cout << " 5. Prefix traversal\n";
    cout << " 6. Postfix traversal\n";
    cout << " 7. Infix traversal\n";
    cout << " 8. Print tree\n";
    cout << " 0. Exit\n ";
}

int main() {
    Node* root = nullptr;

    // Зчитування значень вузлів з файлу
    ifstream inputFile("D:\\АП\\Лабораторні роботи\\Lab_12\\Lab_12.10\\tree_values.txt");
    int value;
    while (inputFile >> value) {
        root = insertNode(root, value);
    }
    inputFile.close();

    int option, nodeValue;
    int count; // Move the declaration outside the switch statement
    while (true) {
        PrintMenu();
        cin >> option;

        switch (option) {
        case 0:
            destroyTree(root);
            return 0;
        case 1:
            cout << "Enter value to insert: ";
            cin >> nodeValue;
            root = insertNode(root, nodeValue);
            break;
        case 2:
            cout << "Enter value to delete: ";
            cin >> nodeValue;
            root = deleteNode(root, nodeValue);
            break;
        case 3:
            cout << "Enter value to search: ";
            cin >> nodeValue;
            if (searchNode(root, nodeValue)) {
                cout << "Value " << nodeValue << " is found in the tree." << endl;
            }
            else {
                cout << "Value " << nodeValue << " is not found in the tree." << endl;
            }
            break;
        case 4:
            int minValue, maxValue;
            cout << "Enter the minimum value: ";
            cin >> minValue;
            cout << "Enter the maximum value: ";
            cin >> maxValue;
            count = countNodesBetween(root, minValue, maxValue); // Assign value to the previously declared count variable
            cout << "Number of nodes between " << minValue << " and " << maxValue << ": " << count << endl;
            break;
        case 5:
            cout << "Prefix traversal: ";
            prefixTraversal(root);
            cout << endl;
            break;
        case 6:
            cout << "Postfix traversal: ";
            postfixTraversal(root);
            cout << endl;
            break;
        case 7:
            cout << "Infix traversal: ";
            infixTraversal(root);
            cout << endl;
            break;
        case 8:
            cout << "Tree values: ";
            PrintTree(root, 0);
            cout << endl;
            break;
        default:
            cout << "Invalid option. Try again." << endl;
        }
    }

    return 0;
}
