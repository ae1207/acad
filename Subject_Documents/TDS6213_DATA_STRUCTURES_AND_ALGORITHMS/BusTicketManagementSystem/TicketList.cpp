#include <iostream>
#include "header/TicketList.hpp"
using namespace std;

TicketList::TicketList() : count(0), headPtr(nullptr) {}

TicketList::~TicketList() {
    while(!isEmpty())
        removeTicket(1);
}

TicketList::TicketNode* TicketList::find(int index) const {
    if(index < 1 || index > count)
        return nullptr; // If searched index does not exist
    else {
        TicketNode* curPtr = headPtr;
        for(int i = 1; i < index; i++) {
            curPtr = curPtr->next;
        }
        return curPtr;
    }
}

bool TicketList::isEmpty() const {
    return count == 0;
}

int TicketList::getCount() const {
    return count;
}

bool TicketList::addTicket(ListItemType* item) {
    TicketNode* newPtr = new TicketNode;
    newPtr->item = item;
    count++;
    newPtr->next = headPtr;
    headPtr = newPtr;
    return true;
}

bool TicketList::removeTicket(int index) {
    if(isEmpty())
        return false;
    
    if(index < 1 || index > count)
        return false;

    TicketNode* curPtr;
    count--;

    if(index == 1) {
        curPtr = headPtr;
        headPtr = headPtr->next;
    } else {
        TicketNode* prevPtr = find(index-1);
        curPtr = prevPtr->next;
        prevPtr->next = curPtr->next;
    }

    // Deletes the item pointer and assign to nullptr
    curPtr->item = nullptr;
    
    // Deletes the current pointer, pointer to next item and assign to nullptr
    curPtr->next = nullptr;
    delete curPtr;
    curPtr = nullptr;

    return true;
}

ListItemType* TicketList::getTicket(int index) {
    if(index < 1 || index > count)
        return nullptr;

    TicketNode* curPtr = find(index);
    return curPtr->item;
}