//Robert Donohue
//maxBST.cpp

//Implement a function to find the maximum element in a binary search tree (BST). Assume the tree contains at least one node.


#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    Node* root;
    BinarySearchTree() : root(nullptr) {}

    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else {
            node->right = insert(node->right, value);
        }
        return node;
    }


    //findMax function
    //the max of a BST is always just the rightmost element, right?
    //should traverse the tree, if right child exists, recursive call on right child
    //else return node
    //super simple actually, don't even need to make a recursive call, just use a while loop.
    //we assume there's at least one node so it's easy
    int findMax() {
        // TODO: Implement the function to find the maximum element in the BST

        while(root->right != nullptr){
            root = root -> right;
        }

        return root -> data;

    }
};


int main() {
    BinarySearchTree bst;
    bst.root = bst.insert(bst.root, 10);
    bst.insert(bst.root, 5);
    bst.insert(bst.root, 15);
    bst.insert(bst.root, 20);
    bst.insert(bst.root, 17);
    bst.insert(bst.root, 21);
    bst.insert(bst.root, -1);

    cout << "Maximum element in the BST is: " << bst.findMax() << endl;
    return 0;
}

