#pragma once

#include <iostream>

template <class T>
class Node {
public:
    T data;
    Node *left = nullptr;
    Node *right = nullptr;

    explicit Node(const T &input) : data(input) {}

    ~Node() {
        delete left;
        delete right;
    }

    bool operator==(const Node<T> &rhs) const {
        return data == rhs.data;
    }

    bool operator!=(const Node<T> &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const Node<T> &rhs) const {
        return data < rhs.data;
    }

    bool operator>(const Node<T> &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Node<T> &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Node<T> &rhs) const {
        return !(*this < rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const Node &node) {
        os << node.data;
        return os;
    }
};

template <class T>
class BinarySearchTree {
private:
    Node<T> *root = nullptr;

    void copyConstructor(const Node<T> *sourceNode, Node<T> *&copyNode) {
        if(!sourceNode) {
            return;

        } else {
            copyNode = new Node<T>(sourceNode->data);
            copyConstructor(sourceNode->left, copyNode->left);
            copyConstructor(sourceNode->right, copyNode->right);
        }
    }

    void insertHelper(Node<T> *&node, const T &input) {
        if(!node) {
            node = new Node<T>(input);

        } else {
            if(input > node->data) {
                insertHelper(node->right, input);

            } else if(input < node->data) {
                insertHelper(node->left, input);
            }
        }
    }

    void existsHelper(const Node<T> *node, const T &input, bool &output) {
        if(node) {
            if(input == node->data) {
                output = true;
                return;

            } else if(input < node->data) {
                existsHelper(node->left, input, output);

            } else {
                existsHelper(node->right, input, output);
            }
        }
    }

    void getHelper(Node<T> *node, const T& input, T*& ptr) {
        if(node) {
            if(input == node->data) {
                ptr = &node->data;
                return;

            } else if(input < node->data) {
                getHelper(node->left, input, ptr);

            } else if(input > node->data) {
                getHelper(node->right, input, ptr);
            }
        }
    }

    void printHelper(const Node<T> *node) {
        if(node) {
            printHelper(node->left);
            std::cout << *node << std::endl;
            printHelper(node->right);
        }
    }

public:
    BinarySearchTree() = default;

    BinarySearchTree(const BinarySearchTree<T> &bst) {
        copyConstructor(bst.root, root);
    }

    ~BinarySearchTree() {
        delete root;
    }

    void insert(const T &input) {
        insertHelper(root, input);
    }

    bool exists(const T &input) {
        bool output = false;

        if(root) {
            existsHelper(root, input, output);
        }

        return output;
    }

    T* get(const T& input) {
        T* ptr = nullptr;
        getHelper(root, input, ptr);
        return ptr;
    }

    void print() {
        printHelper(root);
    }
};