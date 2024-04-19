//BST.cpp -Robert Donohue


#include <stddef.h>
#include<bits/stdc++.h>
using namespace std;
            

//defining the structure of nodes used in the tree
class BSTNode{

public:

    int value;

    // a bstnode has pointers, left and right, which point to other bstnodes
    BSTNode *left;
    BSTNode *right;


    BSTNode(int v){

        value = v;
        left = nullptr;
        right = nullptr;

    }
};

class BST {
private:

    BSTNode *root;

public:
    //set root to point to nothing when tree is first initialized
    BST() {
        root = nullptr;
    }


    //destructor
    ~BST() {
        destroyTree(root);
    }

    void destroyTree(BSTNode* n) {
        if (n != nullptr) {
            destroyTree(n->left);
            destroyTree(n->right);
            delete n;
        }
    }


    
/**
 * insert function
 * takes value to insert as input
 * inserts value into tree in correct position (if value is not already in trees)
 */  

        
    void insert(int value){
        
        root = insertHelp(root, value);

    }


/***
 * insertHelp function
 * utility for insert function
 * takes BSTNode and value as input, returns new BSTNode(value) if it finds an empty node
 * otherwise traverses tree looking for empty node appropriate for value to be inserted
*/

    BSTNode *insertHelp(BSTNode *n, int val){
        
        if(n == nullptr){
            return new BSTNode(val);
        }

        // if val is less than the value where n points
        if(val < n -> value){

            //try again, starting at the left child of n
            n -> left= insertHelp(n -> left, val);
        }
        // if val is greater than the value where n points
        else if(val > n ->value){

            //try again, starting at the right child of n
            n -> right = insertHelp(n -> right, val);

        }

        //otherwise, val must equal n-> value, so just return n, then basically nothing happens
        return n;

    }




/**
 * delete value function
 * takes value to delete as input
 * deletes value from tree, if it exists 
*/

    void deleteValue(int value){

        root = deleteValueHelper(root, value);
        

    }

    BSTNode *deleteValueHelper(BSTNode *n, int val){

        //value not in tree
        if(n == nullptr){
            return nullptr;
        }

        //search for value to the left
        if(val < n ->value){

           n->left = deleteValueHelper(n->left, val);
        }
        //search to the right
        else if( val > n -> value){

            n->right = deleteValueHelper(n->right, val);
        }

        //found it, delete it for 3 cases
        else{

            //case 1 and 2, node has no children or node has 1 child, we can delete node and replace it with child, need a temporary node

            if(n->left == nullptr){
                
                //store the child in a temp node
                BSTNode *temp = n->right;
                //delete the node
                delete n;
                //return temp, the child node that doesn't get deleted
                return temp;
            }
            else if(n->right == nullptr){

                BSTNode *temp = n->left;
                delete n;
                return temp;
            }

            //case 3, node has two children
            //needs another utility function to find the node that replaces the node to be deleted.
            //we find the leftmost child of the right child of the parent. This is a viable replacement
            else{

                //replacement is the node all the way left of the right child of n
                BSTNode *replacement = leftmostNode(n->right);

                //turn n into its replacement
                n->value = replacement->value;

                //delete the replacement
                n->right = deleteValueHelper(n->right, replacement->value);



            }

        }



        return n;


    }

    //this finds the leftmost child of a node n
    BSTNode *leftmostNode(BSTNode *n){
        while(n->left != nullptr){

            n = n->left;
        }

        return n;
    }

/**
 * inOrderTraversal function
 * prints all values of tree in ascending order
*/

    void inOrderTraversal() {

        inOrderTraversalHelp(root);


    }

    void inOrderTraversalHelp(BSTNode *n){

        //if it's null, stop, go back up the stack to the previously called function and continue from where you left off
        if (n == nullptr){
            return;
        }

        //traverse to the left
        inOrderTraversalHelp(n->left);

        //print the value
        cout << n -> value << " ";

        //traverse to the right
        inOrderTraversalHelp(n->right);


    }




/**
 * search function
 * searches for value in tree
 * returns true if it's in there, false otherwise
*/
    bool search(int value){

        return searchHelp(root, value);

    }

    bool searchHelp(BSTNode *n, int val){

        if(n == nullptr){

            return false;
        }

        //if val is smaller than n's value, search to the left
        else if(val < n ->value){

            return searchHelp(n ->left, val);
        }

        //if it's bigger, search to the right
        else if(val > n -> value){

            return searchHelp(n->right, val);
        }

        //if nothing else hit, it must have been found
        return true;
    }

};

/***
 * a function to test and display all capabilites of this binary search tree implementation
*/
void maintest(){
    BST tree;

    cout << "\n\nInserting integer values into tree... ";
    tree.insert(1);
    tree.insert(2);
    tree.insert(7);
    tree.insert(-6);
    tree.insert(0);
    tree.insert(700);
    tree.insert(19);
    
    cout << "\nPrinting values of nodes in ascending order: ";
    tree.inOrderTraversal(); cout << "\n";
    cout << "searching for 700, printing \"1\" if it's found: " << tree.search(700);
    cout << "\ndeleting 700, this value has no children\n";
    tree.deleteValue(700);
    cout << "searching for 700 again, printing \"0\" if it's not found: " << tree.search(700) <<"\n";
    tree.deleteValue(1);
    cout <<"deleting 1, this value has two children\n";
    cout << "searching for 1: " << tree.search(1) <<"\n";
    cout <<"deleting 0, this value has 1 child\n";
    tree.deleteValue(0);
    cout << "printing values in ascending order again: ";
    tree.inOrderTraversal();
    cout << "\n\n";

}



int main(){

    maintest();
            
            
            
   return 0;
            
}
