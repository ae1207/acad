#ifndef QUEUE_MANAGER_HPP
#define QUEUE_MANAGER_HPP

#include <iostream>
#include "Passenger.hpp"
using namespace std;
typedef Passenger QueueItemType;

class QueueManager {
private:
    struct QueueNode
    {
        QueueItemType* item;
        QueueNode* next;
    };

    QueueNode* backPtr;
    QueueNode* frontPtr;

    bool enqueue(QueueItemType* newItem);
    bool dequeue();
    
public:
    QueueManager();
    ~QueueManager();

    bool isEmpty() const;
    bool addPassenger();
    bool removePassenger();
    bool showPassengers();
    QueueItemType* getFront();

    void displayMenu();
};

#endif