/*
 * Course: COEN 2220 - Programming 2
 * Name: [Your Name]
 * Lab: Lab 10 - Stacks & Queues
 * Description: Practice - a dynamic queue of tutoring requests
 * Due date: [Date]
 */

#include <iostream>
#include <string>
using namespace std;

class TutoringQueues
{
private:
    struct Node
    {
        string studentId; // Store one student waiting for tutoring.
        Node *next;       // Point to the student immediately behind this one.
    };

    Node *front; // Point to the student who must be served next.
    Node *rear;  // Point to the student most recently added.

public:
    TutoringQueue()
    {

        front = nullptr;
        rear = nullptr;
    }

    ~TutoringQueue()
    {
        while (front != nullptr)
        {
            Node *nodeToDelete = front;
            front = front->next; // Advance before releasing the current node.
            delete nodeToDelete;
        }

        rear = nullptr;
    }

    bool isEmpty() const
    {
        return front == nullptr;
    }

    // ===== Resolve these TODOs now (Part E) =====

    // TODO (Part E): Write enqueue to add newStudentId at rear.
    void enqueue(const string& newStudentId)
    {
        Node *newNode = new Node;
        newNode->studentId = newStudentId;
        newNode->next = nullptr; // The new student begins as the last node.

        if (rear == nullptr)
        {
            front = newNode; // The first node is also the front.
            rear = newNode;  // The first node is also the rear.
            return;
        }

        rear->next = newNode; // Connect the old rear to the new node.
        rear = newNode;       // The new node becomes the rear.
    }
    // TODO (Part E): Write dequeue. It returns bool and uses string& servedStudentId.
    bool dequeue(string& servedStudentId)
    {
        if (front == nullptr)
        {
            return false; // An empty queue has no student to serve.
        }

        Node *nodeToDelete = front;
        servedStudentId = front->studentId;
        front = front->next; // The next student becomes the front.

        if (front == nullptr)
        {
            rear = nullptr; // If the queue becomes empty, update rear.
        }

        delete nodeToDelete;
        return true;
    }
};

int main()
{
    cout << boolalpha;

    // TODO (Part E): Create a TutoringQueue object.
    TutoringQueue tutoringQueue;
    // TODO (Part E): Add TU-301, TU-318, and TU-327 in that arrival order.
    tutoringQueue.enqueue("TU-301");
    tutoringQueue.enqueue("TU-318");
    tutoringQueue.enqueue("TU-327");
    // TODO (Part E): Dequeue and print the first two served student IDs.
    string servedStudent;
    if (tutoringQueue.dequeue(servedStudent))
    {
        cout << "Served student: " << servedStudent << endl;
    }
    if (tutoringQueue.dequeue(servedStudent))
    {
        cout << "Served student: " << servedStudent << endl;
    }
    // TODO (Part E): Dequeue the last student, then print whether the queue is empty.
    if (tutoringQueue.dequeue(servedStudent))
    {
        cout << "Served student: " << servedStudent << endl;
    }
    // TODO (Part E): Add TU-340 after the queue becomes empty, dequeue it, and print its ID.
    tutoringQueue.enqueue("TU-340");
    if (tutoringQueue.dequeue(servedStudent))
    {
        cout << "Served student after empty queue: " << servedStudent << endl;
    }

    return 0;
}

/*
 * Analysis Answers
 *
 * E1 — First arrival
 * Why must the first call to enqueue assign newNode to both front and rear?
 * Answer: When the first student arrives, the queue is empty, so both front and rear must point to the same node representing that student. This ensures that the queue correctly reflects that there is one student waiting to be served.
 *
 * E2 — Last departure
 * After dequeue removes the only remaining node, what must happen to rear and why?
 * Answer: Rear must be set to nullptr after the last node is removed to indicate that the queue is now empty. If rear were not updated, it would still point to a deleted node, leading to undefined behavior if another enqueue operation were attempted.
 *
 * E3 — FIFO evidence
 * List the expected service order for TU-301, TU-318, and TU-327. Explain why this
 * differs from the return order of the function-call stack in Part D.
 * Answer: The service order for TU-301, TU-318, and TU-327 is the same as their arrival order: TU-301 is served first, followed by TU-318, and then TU-327. This demonstrates the First In, First Out (FIFO) principle of queues, where the first student to arrive is the first to be served. This differs from the Last In, First Out (LIFO) behavior of a stack, where the most recently added item is the first to be removed.
 *
 */