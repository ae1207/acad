#ifndef TICKET_HPP
#define TICKET_HPP

#include <iostream>
using namespace std;

class Ticket {
private:
    static int ticketCount; // Keep track of the number of tickets made
    int ticketID; // Ticket ID
    string passengerName; // The passenger's name
    string passengerPhone; // The passenger's phone number
    int busID; // Bus ID
    string busRoute; // the route
    string busOperator; // the name of the operator
    string busCompany; // the name of the bus company
    int seatNumber; // The seat number booked
    int platformNumber; // The platform the bus will be at
    float price; // The price of the ticket
    static const string statusType[]; // Either "Cancelled" or "Booked"
    int statusIndex; // Either 0 or 1

public:
    Ticket();
    Ticket(
        string passengerName, 
        string passengerPhone, 
        int busID, 
        string busRoute,
        string busOperator,
        string busCompany,
        int seatNumber, 
        int platformNumber, 
        float price
        );
    ~Ticket();

    bool updateStatus(int status); // Updates the status of the ticket
    
    // Methods for retrieving ticket data
    int getTicketID() const;
    string getPassengerName() const;
    string getPassengerPhone() const;
    int getBusID() const;
    string getBusRoute() const;
    string getBusOperator() const;
    string getBusCompany() const;
    int getSeatNumber() const;
    int getPlatform() const;
    float getPrice() const;
    string getStatus() const;

    // Displaying the ticket information
    void display() const;
};

#endif