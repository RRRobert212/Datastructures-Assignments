//Robert Donohue
//queueUsingStacks.cpp

//Implement a queue using two stacks. 
//The queue should support the standard operations enqueue and dequeue. 
//You need to fill in the enqueue and dequeue functions.

#include <iostream>
#include <stack>
using namespace std;

class Queue {

    //this is the stack data structure for free,so we can use push and pop
    stack<int> s1, s2;

public:

    //enqueue means addLast
    // a stack is basically just an upside down(?) queue
    //just need to put the integer into an EMPTY stack, and then put everything else back on top of it
    void enqueue(int x) {
        // TODO: Implement the enqueue operation using two stacks

        //move everything from first stack to second stack, so x can go on bottom of stack

        //until s1 is empty
        while(s1.size() > 0){

            //the top of the stack
            int z = s1.top();
            s2.push(z);
            //delete the element from s2 after we add it to s1
            s1.pop();
        }

        //now s1 is empty
        s1.push(x);

        //now reverse it, put everything back
        while(s2.size() > 0){
            int z = s2.top();
            s1.push(z);

            s2.pop();

        }

        



    }


    //dequeue means removeFirst
    int dequeue() {
        // TODO: Implement the dequeue operation using two stacks

        //need error checking, can't dequeue if s1 is empty
        if(s1.size() == 0){
            return -1;
        }

        //we want to dequeue the top of the stack. (the element added the longest ago)
        int x = s1.top();
        //and remove it
        s1.pop();

        return x; // Replace this with your implementation
    }
};



int main() {
    Queue q;
    q.enqueue(1);
    q.enqueue(2);
    cout << "Dequeued: " << q.dequeue() << endl;
    q.enqueue(3);
    cout << "Dequeued: " << q.dequeue() << endl;
    return 0;
}
