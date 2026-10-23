/*
 * Course: COEN 2220 - Programming 2
 * Name: [Your Name]
 * Lab: Lab 10 - Stacks & Queues
 * Description: Practice - a dynamic stack of active function calls
 * Due date: [Date]
 */

#include <iostream>
#include <string>
using namespace std;

class FunctionCallStack
{
private:
    // ===== Resolve these TODOs now (Part C) =====

    // TODO (Part C): Define Node with string functionName and Node *next.
    struct Node
    {
        string functionName; // Store one function name.
        Node *next;          // Point to the function call immediately below this one.
    };
    // TODO (Part C): Declare Node *top for the node that must leave next.
    Node *top; // Point to the function call that must leave next.

public:
    // TODO (Part C): Write a constructor that creates an empty stack.
FunctionCallStack()
    {
        top = nullptr; // The stack begins empty with no top node.
    }
    // ===== Resolve these TODOs later (Part D) =====

    // TODO (Part D): Write isEmpty as a const member function.
    ~FunctionCallStack()
    {
        while (top != nullptr)
        {
            Node *nodeToDelete = top;
            top = top->next; // Save the next function call through top before delete.
            delete nodeToDelete;
        }
    }
    // TODO (Part D): Write push to add a function name at top.
bool push(const string& newFunctionName)
    {
        Node *newNode = new Node;
        newNode->functionName = newFunctionName;
        newNode->next = top; // The new function call goes above the old top.
        top = newNode;       // The new function call becomes the top.
        return true;
    }
    // TODO (Part D): Write pop. It returns bool and uses string& removedFunctionName.
    bool pop(string& removedFunctionName)
    {
        if (top == nullptr)
        {
            return false; // An empty stack has no function to remove.
        }

        Node *nodeToDelete = top;
        removedFunctionName = top->functionName;
        top = top->next; // The next function call becomes the top.

        delete nodeToDelete;
        return true;
    }
    // TODO (Part D): Write peek. It returns bool and uses string& topFunctionName.
    bool peek(string& topFunctionName) const
    {
        if (top == nullptr)
        {
            return false; // An empty stack has no function to peek.
        }

        topFunctionName = top->functionName;
        return true;
    }
    // TODO (Part D): Write a destructor that releases every dynamic node.
    bool isEmpty() const
    {
        return top == nullptr; // An empty stack has no top node.
    }
};

int main()
{
    cout << boolalpha;

    // ===== Resolve these TODOs later (Part D) =====

    // TODO (Part D): Create a FunctionCallStack object.
    FunctionCallStack callStack;
    // TODO (Part D): Push main, loadSchedule, and formatSchedule in that order.
    callStack.push("main");
    callStack.push("loadSchedule");
    callStack.push("formatSchedule");
    // TODO (Part D): Use peek and pop to demonstrate LIFO with descriptive output.
    string currentFunction;
    if (callStack.peek(currentFunction))
    {
        cout << "Current function at the top of the stack: " << currentFunction << endl;
    }
    // TODO (Part D): Pop remaining calls, then demonstrate an unsuccessful pop on an empty stack.
    string poppedFunction;
    while (callStack.pop(poppedFunction))
    {
        cout << "Popped function: " << poppedFunction << endl;
    }
    cout << "Attempting to pop from an empty stack: " << callStack.pop(poppedFunction) << endl;

    return 0;
}

/*
 * Analysis Answers
 *
 * D1 — Adding formatSchedule
 * When push("formatSchedule") executes, what must newNode->next receive before top
 * changes? Explain why reversing those two assignments would lose the previous top.
 * Answer: newNode->next must receive the current top pointer before top is updated to point to newNode. If we reversed the assignments, we would lose the reference to the previous top node, making it impossible to access the rest of the stack and effectively breaking the linked list structure.
 *
 * D2 — Returning from a function
 * After main, loadSchedule, and formatSchedule are pushed in that order, list the
 * order in which three successful pop calls must return their names. Explain LIFO.
 * Answer: The order of successful pop calls will return "formatSchedule" first, followed by "loadSchedule", and finally "main". This demonstrates the Last In, First Out (LIFO) principle, where the most recently added item (the last one pushed onto the stack) is the first one to be removed (popped off the stack).
 *
 * D3 — Destructor order
 * Why must the destructor save a next-node address before deleting the current node?
 * Answer: The destructor must save the next-node address before deleting the current node to ensure that it can continue traversing the stack. If we delete the current node without saving the next pointer, we would lose access to the rest of the stack, leading to memory leaks and undefined behavior. By saving the next-node address, we can safely delete the current node and move on to the next one in the stack.
 *
 */