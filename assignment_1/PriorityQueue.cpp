#include <stddef.h>
#include<bits/stdc++.h>
using namespace std;

//node structure used for heap
class HeapNode {
public:

    //need left, right, and parent which is used to heapify
    int value;
    HeapNode* left;
    HeapNode* right;
    HeapNode* parent;

    //constructor
    HeapNode(int val){
        value = val;
        left = nullptr;
        right = nullptr;
        parent = nullptr;


    }
};


class MaxHeap {
private:
    HeapNode* root;

public:
    MaxHeap(){

        //root initialized as pointing nowhere
        root = nullptr;
    }

    /***
     * insert function
     * takes a value to insert, creates a node with that value, and puts it at the bottom of the tree
     * then calls heapify to push it up the tree to its correct place
    */
    void insert(int value) {
        HeapNode* nodeToInsert = new HeapNode(value);
        //if it's empty, put it at the root
        if (root == nullptr) {
            root = nodeToInsert;
        }
         else {

            //otherwise just insert it to the left of the suitable parent node
            //or to the right if left is full
            HeapNode* parent = findParentNode();
            if (parent->left == nullptr) {
                parent->left = nodeToInsert;
            } else {
                parent->right = nodeToInsert;
            }

            //now it's inserted at the bottom, but we need to heapify
            nodeToInsert->parent = parent;
            heapify(nodeToInsert);
        }
    }


    /**
     * findParentNode function
     * returns the suitable parent node for a node we want to insert
     * traverses as far down to the left as it can, only goes right when it needs to
    */
    HeapNode* findParentNode() {
        HeapNode* node = root;
        while (node->left != nullptr && node->right != nullptr) {

            //if left and right exist, go left
            if (node->left != nullptr && node->right != nullptr) {
                node = node->left;
            
            } 
            //otherwise you have to go right
            else {
                node = node->right;
            }
        }
        return node;
    }

    /**
     * heapifyUp function
     * takes a node as input
     * moves it up the tree by making reference to its parent node, until it is in its rightful place
    */
    void heapify(HeapNode* node) {
        while (node->parent != nullptr && node->value > node->parent->value) {

            //I couldn't find a simple way to do this without using the prebuilt swap function. hopefully that's allowed
            swap(node->value, node->parent->value);
            node = node->parent;
        }
    }


    /**
     * peek function
     * returns the max value in the heap, i.e. the top of the priority queue
     * if the heap is assembled corectly, this is always just the root node.
    */

    int peek(){

        if(root == nullptr){
            cout << "ERROR, queue has no elements! ";
            return -1;
        }
        return root ->value;
    }

    /***
     * extractMax function
     * returns the max value in the heap (top of queue) and removes it from the heap
     * replaces root value with value of last node, removes last node,
     * pushes new root value down using heapifyDown function
    */
int extractMax() {
    if (root == nullptr) {
        cout << "ERROR, queue has no elements! ";
        return -1;
    }

    // The value we want to return
    int maxValue = root->value;

    HeapNode* lastNode = getLastNode();

    // Replace root value with value of last node
    root->value = lastNode->value;

    // Update parent pointers of the last node's parent
    if (lastNode->parent != nullptr) {
        if (lastNode->parent->left == lastNode)
            lastNode->parent->left = nullptr;
        else
            lastNode->parent->right = nullptr;
    }

    delete lastNode;

    //needed to add this because it wasn't catching when there was nothing in the queue to extract
    if (root == lastNode) {
        // If root was the last node, heap is now empty
        root = nullptr;
    } else {
        heapifyDown(root);
    }

    return maxValue;
}



    /**
     * getLastNode function
     * traverses all the way down to the right, and left if it can't go right
     * this returns the last node in the tree
    */
HeapNode* getLastNode() {
    if (root == nullptr)
        return nullptr;

    HeapNode* lastNode = root;

    while (lastNode->right != nullptr || lastNode->left != nullptr) {
        //go right if you can
        if (lastNode->right != nullptr){
            lastNode = lastNode->right;
        }
        //otherwise go left
        else{
            lastNode = lastNode->left;
        }
    }
    return lastNode;
}



/**
 * heapifyDown function
 * just like heapifyUp, but moving down (except you need to find the larger child and use that one)
 * takes a node as input and pushes it down to its rightful place
*/

void heapifyDown(HeapNode* node) {
    // Continue until the node has at least one child
    while (node->left != nullptr || node->right != nullptr) {
        // Find the larger child node
        HeapNode* largerChild = nullptr;
        
        // Check if both left and right child nodes exist
        if (node->left != nullptr && node->right != nullptr) {
            // Select the larger child node
            largerChild = (node->left->value > node->right->value) ? node->left : node->right;
        } else if (node->left != nullptr) {
            // If only the left child exists
            largerChild = node->left;
        } else {
            // If only the right child exists
            largerChild = node->right;
        }
        
        // If the node is smaller than the larger child, swap them
        if (node->value < largerChild->value) {
            swap(node->value, largerChild->value);
            // Move to the larger child to continue heapifying down
            node = largerChild;
        } else {
            // Node is in the correct position, break the loop
            break;
        }
    }
}








};



            
int main() {
    MaxHeap heap;
    cout << "Inserting integers into queue: \n";
    heap.insert(5);
    heap.insert(1);
    heap.insert(7);
    heap.insert(0);
    heap.insert(9);
    heap.insert(-1);
    heap.insert(112);
    heap.insert(25);

    std::cout << "Peeking at max value: " << heap.peek() << "\n";

    std::cout << "Extracting max value: " << heap.extractMax() << "\n";
    std::cout << "Peeking at new max value: " << heap.peek() << "\n";
    std::cout << "Extracting: " << heap.extractMax() << "\n";
    std::cout << "Extracting several more times until the queue is empty and we get an error: ";
    for(int i= 0; i < 7; i++){ cout << heap.extractMax() << ", ";}
    cout <<"\n";
    cout << "(it says \"-1\" because that's what extractMax() returns when the queue is empty)\n";
    cout << "Peeking at empty queue: ";
    cout << heap.peek();
    cout <<"\n";

    return 0;
}