#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>

template <class T>
class BST;

template <class T>
class Node {
private:
    T value;
    Node<T>* left;
    Node<T>* right;

public:
    Node(T val) : value(val), left(nullptr), right(nullptr) {}

    friend class BST<T>;
};

template <class T>
class BST {
private:
    Node<T>* root;

    Node<T>* addRecursive(Node<T>* node, T val) {
        if (node == nullptr) {
            return new Node<T>(val);
        }
        if (val < node->value) {
            node->left = addRecursive(node->left, val);
        } else if (val > node->value) {
            node->right = addRecursive(node->right, val);
        }
        return node;
    }

    bool findRecursive(Node<T>* node, T val) const {
        if (node == nullptr) {
            return false;
        }
        if (node->value == val) {
            return true;
        }
        if (val < node->value) {
            return findRecursive(node->left, val);
        }
        return findRecursive(node->right, val);
    }

    void clearRecursive(Node<T>* node) {
        if (node != nullptr) {
            clearRecursive(node->left);
            clearRecursive(node->right);
            delete node;
        }
    }

    void inorderRecursive(Node<T>* node) const {
        if (node != nullptr) {
            inorderRecursive(node->left);
            std::cout << node->value << " ";
            inorderRecursive(node->right);
        }
    }

public:
    BST() : root(nullptr) {}
    ~BST() {
        removeAll();
    }

    bool empty() const {
        return root == nullptr;
    }

    void add(T val) {
        root = addRecursive(root, val);
    }

    bool find(T val) const {
        return findRecursive(root, val);
    }

    void removeAll() {
        clearRecursive(root);
        root = nullptr;
    }

    void printInorder() const {
        inorderRecursive(root);
        std::cout << "\n";
    }
};

#endif