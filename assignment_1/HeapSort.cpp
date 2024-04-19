#include <stddef.h>
#include<bits/stdc++.h>
using namespace std;

class MinHeap {
private:
    vector<int> array;

    /**
     * heapifyUp function
     * takes index to push up as input
     * swaps value at index moving up the array while array[index] < array[parent_index]
    */
    void heapifyUp(int index) {
        //can't push the top element up
        while (index > 0) {
            int parent_index = (index - 1) / 2;
            if (array[index] < array[parent_index]) {
                swap(array[index], array[parent_index]);
                index = parent_index;
            } else {
                break;
            }
        }
    }

    /**
     * heapifyDown function
     * takes index to push down as input
     * has to decide whether to push left or right (odd or even index) based on which is smaller
    */
    void heapifyDown(int index) {
        int n = array.size();
        while (leftChild(index) < n) {
            int left = leftChild(index);
            int right = rightChild(index);
            int smallest = index;
            if (left < n && array[left] < array[smallest]) {
                smallest = left;
            }
            if (right < n && array[right] < array[smallest]) {
                smallest = right;
            }
            if (smallest == index) {
                break;
            }
            swap(array[index], array[smallest]);
            index = smallest;
        }
    }

public:
    /***
     * insert function
     * uses push_back to append value to end of array, and then heapifies it up
    */
    void insert(int val) {
        //hopefully this is allowed so I don't have to deal with resizing arrays and whatnot
        array.push_back(val);
        heapifyUp(array.size() - 1);
    }

    /**
     * extractMin function
     * pulls the minimum element and updates the heap with it gone
     * we need this to do the sort algorithm
    */
int extractMin() {
    if (array.empty()) {
        return -1;
    }

    //Store the minimum value for later
    int minVal = array[0];

    //Move the last element to the root
    array[0] = array.back();
    array.pop_back();

    //Heapify down from the root
    int index = 0;
    while (index < array.size()) {
        int left = leftChild(index);
        int right = rightChild(index);
        int smallest = index;

        if (left < array.size() && array[left] < array[smallest]) {
            smallest = left;
        }
        if (right < array.size() && array[right] < array[smallest]) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }
        swap(array[index], array[smallest]);
        index = smallest;
    }

    return minVal;
}

// Helper functions to find children indices
int leftChild(int index){
    return 2 * index + 1;
    }

int rightChild(int index){
    return 2 * index + 2;
    }


    // Function to check if the heap is empty
    bool isEmpty() {
        return array.empty();
    }
};

class HeapSort {
private:
    vector<int> array;

public:
    // Constructor
    HeapSort(const vector<int>& arr) {
        array = arr;
    }   


    /**
     * heapSort function
     * uses insert function to put elements of array into the minHeap
     * clears array
     * puts elements back in array one by one, using extractMin function
    */
    void heapSort() {
        MinHeap minHeap;
        for (int num : array) {
            minHeap.insert(num);
        }
        array.clear();
        while (!minHeap.isEmpty()) {
            array.push_back(minHeap.extractMin());
        }
    }

    /**
     * printArray function
     * prints the array... duh...
    */
    void printArray() {
        for (int num : array) {
            cout << num << " ";
        }
        cout << "\n";
    }
};

int main() {
    //example array
    //even though it's actually a vector...
    vector<int> arr = {1000, 0, 15, 23, 19, -222, 9918, 1, 2, 3, 5};

    HeapSort heapSort(arr);

    cout << "Original array: ";
    heapSort.printArray();

    //sort it!
    heapSort.heapSort();

    cout << "Sorted array: ";
    heapSort.printArray();

    return 0;
}
