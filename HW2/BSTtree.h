//
//  BSTtree.h
//  hw3
//
//  Created by Ahmet Büyükaksoy on 22.04.2023.
//

#ifndef BSTtree_h
#define BSTtree_h
#include <iostream>
using namespace std;

template <typename T>
class BSTtree {
private:
    struct Node {
        T value;
        int height;
        Node *left, *right;
        
        Node(T value) : value(value), height(1), left(nullptr), right(nullptr) {}
    };
    
    Node *root;
    
    void printName(const T& obj, ostream& out) {
        out << obj.firstname << " " << obj.lastname ;
    }
    
    int getHeight(Node* n) {
        if (n==nullptr) return 0;
        return max(getHeight(n->left), getHeight(n->right)) + 1;
    }
    Node* search(T value, Node* node) {
        if (!node) {
            return nullptr;
        }
        
        if (value < node->value) {
            return search(value, node->left);
        } else if (value > node->value) {
            return search(value, node->right);
        } else {
            return node;
        }
    }
    
    Node *insert(T value, Node *node) {
        if (!node) {
            return new Node(value);
        }
        
        if (value < node->value) {
            node->left = insert(value, node->left);
        } else if (value > node->value) {
            node->right = insert(value, node->right);
        }
        else {
            cout << "Given value, " << node->value << " ,is already in the tree" << endl;
        }
    
        return node;
    }
    
    
    
    bool remove(T value, Node *&node) {
        bool removed = false; // Initialize the removed variable to false
        
        if (!node) {
            return removed;
        }
        
        if (value < node->value) {
            removed = remove(value, node->left);
        } else if (value > node->value) {
            removed = remove(value, node->right);
        } else {
            if (!node->left || !node->right) {
                Node *temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
                removed = true; // Set removed to true
            } else {
                Node *temp = minValueNode(node->right);
                node->value = temp->value;
                removed = remove(temp->value, node->right);
            }
        }
        
        return removed; // Return the value of removed
    }

    Node *minValueNode(Node *node) {
        Node *current = node;
        
        while (current->left) {
            current = current->left;
        }
        
        return current;
    }
    void printPreorderHelper(Node* node, ofstream& outputFile) const {
            if (node == nullptr) {
                return;
            }

        outputFile << node->value << endl; // Print the current node to the file
            printPreorderHelper(node->left, outputFile); // Recursively print the left subtree
            printPreorderHelper(node->right, outputFile); // Recursively print the right subtree
        }
    void printInorderHelper(Node* node, ofstream& outputFile) const {
            if (node == nullptr) {
                return;
            }

            printInorderHelper(node->left, outputFile); // Recursively print the left subtree
        outputFile << node->value << endl; // Print the current node to the file
            printInorderHelper(node->right, outputFile); // Recursively print the right subtree
        }
    
    void printInorder(Node *node) const {
        if (!node) {
            return;
        }
        printInorder(node->left);
        cout << node->value;
        printInorder(node->right);
    }
    void printPreorder(Node *node, string filename) const {
        if (!node) {
            return;
        }
        cout << node->value;
        printPreorder(node->left);
        printPreorder(node->right);
    }
    void drawTreeHelper(Node* root, ofstream& outputFile, bool isRoot = true, string prefix = "", bool isLeft = false) {
        if (root != nullptr) {
            outputFile << prefix;
            outputFile << (isLeft ? "|-- " : "|__ ");
            printName(root->value,outputFile);
            outputFile << endl;

            if (root->left != nullptr || root->right != nullptr) {
                drawTreeHelper(root->left, outputFile, false, prefix + (isLeft && !isRoot ? "|   " : "    "), true);
                drawTreeHelper(root->right, outputFile, false, prefix + (isLeft && !isRoot ? "|   " : "    "), false);
            }
        }
    }

public:
    BSTtree() : root(nullptr) {}
    
    Node* getRoot(){return root;}
    void insert(T value) {
        root = insert(value, root);
    }
   
    
    
    bool remove(T value) {
        return remove(value, root);
    }
    
    
    void printInorder() const {
        printInorder(root);
    }
    void printPreorder() const{
        printPreorder(root);
    }
    
    
    
    void Search(T item) {
        Node* temp =  search(item, root);
        if(temp)
            cout << temp->value;
        else cout << "Value not found\n";
    }
    void printPreorderToFile(const string& filename) const {
            ofstream outputFile(filename);
            if (outputFile.is_open()) {
                printPreorderHelper(root, outputFile);
                outputFile.close();
            } else {
                cout << "Unable to open the file " << filename << "." << endl;
            }
        }
    void printInorderToFile(const string& filename) const {
            ofstream outputFile(filename);
            if (outputFile.is_open()) {
                printInorderHelper(root, outputFile);
                outputFile.close();
            } else {
                cout << "Unable to open the file " << filename << "." << endl;
            }
        }
    
    friend void search_contact(BSTtree<T>::Node* , string query);
    
    void fixHeights(){
        root->height = getHeight(root);
        root->left->height = getHeight(root->left);
        root->right->height = getHeight(root->right);

    }
    void drawTree(ofstream& out,string prefix = "", bool isLeft = true){
        drawTreeHelper(root,out);
    }
    
};



   



#endif /* BSTtree_h */
