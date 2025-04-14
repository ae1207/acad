#ifndef PASSENGER_HPP
#define PASSENGER_HPP

#include <iostream>
#include "TicketList.hpp"
using namespace std;

class Passenger {
private:
    string name;
    string phoneNumber;
    int busPoints; // Bus points to be used to give discounts
    TicketList* ticketList; // Linked list to ticket history

public:
    Passenger();
    Passenger(string name, string phoneNumber);
    ~Passenger();
    
    bool redeemPoints(int points); // Subtract points
    bool earnPoints(int points); // Add points

    // Methods for retrieving passenger data
    string getName() const;
    string getPhoneNumber() const;
    int getBusPoints() const;
    TicketList* getTicketList() const;

    // Methods to edit passenger data
    bool editInfo();

    // Display information
    void display() const;
};

#endif