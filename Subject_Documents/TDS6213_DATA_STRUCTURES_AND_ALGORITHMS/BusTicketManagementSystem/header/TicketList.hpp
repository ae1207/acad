#ifndef TICKET_LIST_HPP
#define TICKET_LIST_HPP

#include "Ticket.hpp"
typedef Ticket ListItemType;
using namespace std;

class TicketList {
private:
    struct TicketNode{
        ListItemType* item;
        TicketNode* next;
    };
    int count;
    TicketNode* headPtr;
    TicketNode* find(int index) const; // Returns a pointer to the Node at an index

public:
    TicketList();
    ~TicketList();

    bool isEmpty() const; // Checks if the list is empty
    int getCount() const; // Get the number of tickets booked
    bool addTicket(ListItemType* item); // Adds a pointer to Ticket to the list
    bool removeTicket(int index); // Removes a pointer to Ticket from the linked list
    ListItemType* getTicket(int index); // Retrieves the pointer to Ticket from the list
};

#endif