#pragma once

#include <iostream>
#include <vector>
#include <iterator>

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

    void returnArrayHelper(const Node<T> *node, std::vector<T> &vector) {
        if(node) {
            returnArrayHelper(node->left, vector);
            vector.push_back(node->data);
            returnArrayHelper(node->right, vector);
        }
    }

    void removeHelper(Node<T> *&node, const T &input) {
        if(!node) {
            return;
        }

        if(input < node->data) {
            removeHelper(node->left, input);

        } else if(input > node->data) {
            removeHelper(node->right, input);

        } else {
            if(!node->right && !node->left) {
                delete node;
                node = nullptr;
                return;
            }

            if(!node->left) {
                Node<T> *temp = node->right;
                delete node;
                node = temp;
                return;

            } else if(!node->right) {
                Node<T> *temp = node->left;
                delete node;
                node = temp;
                return;
            }

            Node<T> *temp = node->right;
            while(temp->right) {
                temp = temp->left;
            }

            node->data = temp->data;
            removeHelper(node->right, temp->data);
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

    T* get(const T &input) {
        T* ptr = nullptr;
        getHelper(root, input, ptr);
        return ptr;
    }

    void returnArray(std::vector<T> &vector) {
        returnArrayHelper(root, vector);
    }

    void remove(const T &input) {
        removeHelper(root, input);
    }

    friend std::istream& operator>>(std::istream &in, BinarySearchTree<T> &tree) {
        for(std::istream_iterator<T> iterator(in);
            iterator != std::istream_iterator<T>();
            iterator++) {

            tree.insert(*iterator);
        }

        return in;
    }

    friend std::ostream& operator<<(std::ostream &out, BinarySearchTree<T> &tree) {
        std::vector<T> temp;
        tree.returnArray(temp);

        for(auto &output : temp) {
            out << output << '\n';
        }

        return out;
    }
};