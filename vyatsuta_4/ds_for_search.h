//
// Created by voldemort on 11/29/23.
//

#ifndef F_MAZE_2_DS_FOR_SEARCH_H
#define F_MAZE_2_DS_FOR_SEARCH_H
#include "common.h"


class Node {
public:
    Loc location;  // Loc should be a structure to hold the position (row, col)
    double gCost;  // Cost from start node to this node
    double hCost;  // Heuristic cost from this node to the goal
    double fCost;  // Total cost (gCost + hCost)
    Node* parent;  // Pointer to parent node for path reconstruction

    Node(Loc loc, Node* p = nullptr, double g = 0, double h = 0)
            : location(loc), parent(p), gCost(g), hCost(h), fCost(g + h) {}

    // Heuristic function (Manhattan distance)
    static double CalculateHCost(const Loc& loc, const Loc& goal) {
        return abs(loc.r - goal.r) + abs(loc.c - goal.c);
    }
};



template<typename T>
class Stack
{
private:
    T* stack;
    int top;
    int max;
public:
    Stack(int max = 10000)
    {
        this->stack = new T[max];
        this->max   = max;
        this->top   = -1;
    }
    ~Stack()
    {
        delete[] stack;
    }
    bool IsEmpty() const
    {
        return (top == -1);
    }
    bool IsFull() const
    {
        return (top == max-1);
    }
    T& Top() const
    {
        assert(IsEmpty() == false);
        return stack[top];
    }
    void Push(const T& val)
    {
        assert(IsFull() == false);
        top++;
        stack[top] = val;
    }
    T Pop()
    {
        assert(IsEmpty() == false);
        T val = stack[top];
        top--;
        return val;

    }
};
template<typename T>


class Queue
{
private:
    int front;
    int max;
protected:
    int rear;
    T* queue;
    int count;
public:
    Queue(int max = 10000)
    {
        this->queue = new T[max];
        this->max = max;
        this->front = 0;
        this->rear = -1;
        this->count = 0;
    }

    ~Queue()
    {
        delete[] queue;
    }
    Queue<T>& operator=(const Queue<T>& other) {
        if (this != &other) {
            delete[] queue; // Release existing resources

            max = other.max;
            queue = new T[max];
            front = other.front;
            rear = other.rear;
            count = other.count;

            for (int i = 0; i < max; ++i) {
                queue[i] = other.queue[i];
            }
        }
        return *this;
    }

    void Clear() {
        front = 0;
        rear = -1;
        count = 0;
         for (int i = 0; i < max; ++i) {
             queue[i] = T(); // Requires default constructible type T
         }
    }
    bool IsEmpty() const
    {
        return count == 0;
    }

    bool IsFull() const
    {
        return count == max;
    }

    void Enqueue(const T& item)
    {
        assert(!IsFull());
        rear = (rear + 1) % max;
        queue[rear] = item;
        count++;
    }

    T Dequeue()
    {
        assert(!IsEmpty());
        T item = queue[front];
        front = (front + 1) % max;
        count--;
        return item;
    }

    T& Front() const
    {
        assert(!IsEmpty());
        return queue[front];
    }
    void Reverse() {
        if (IsEmpty()) {
            return; // No need to reverse if the queue is empty
        }

        int start = front;
        int end = (rear < front) ? (rear + max) : rear; // Adjust if the queue is wrapped around

        while (start < end) {
            T temp = queue[start % max];
            queue[start % max] = queue[end % max];
            queue[end % max] = temp;

            start++;
            end--;
        }
    }
};

template<typename T>
class PriorityQueue : public Queue<T> {
public:
    // Constructor (use base class constructor)
    using Queue<T>::Queue;

    // Method to insert with priority
    void EnqueueWithPriority(const T& item) {
        if (this->IsEmpty()) {
            this->Enqueue(item);
        } else {
            // Simple linear insertion based on priority
            int i;
            for (i = this->rear; (i >= 0 && this->queue[i]->fCost > item->fCost); i--) {
                this->queue[i + 1] = this->queue[i];
            }
            this->queue[i + 1] = item;
            this->rear++;
            this->count++;
        }
    }
};

#endif //F_MAZE_2_DS_FOR_SEARCH_H
