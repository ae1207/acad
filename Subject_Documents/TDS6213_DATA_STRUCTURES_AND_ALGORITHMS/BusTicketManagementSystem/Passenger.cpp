#include "header/Passenger.hpp"
using namespace std;

Passenger::Passenger() : name(""), phoneNumber(""), busPoints(0), ticketList(nullptr) {}

Passenger::Passenger(string name, string phoneNumber) : name(name), 
phoneNumber(phoneNumber), busPoints(0) {
    ticketList = new TicketList();
}

Passenger::~Passenger() {
    ticketList = nullptr;
}

bool Passenger::redeemPoints(int points) {
    if(points <= 0 || points > busPoints)
        return false;
    
    busPoints -= points;
    return true;
}

bool Passenger::earnPoints(int points) {
    busPoints += points;
    return true;
}

string Passenger::getName() const { return name; }

string Passenger::getPhoneNumber() const { return phoneNumber; }

int Passenger::getBusPoints() const { return busPoints; }

TicketList* Passenger::getTicketList() const { return ticketList; }

bool Passenger::editInfo() {
    cout << "Edit name: ";
    cin >> name;
    cout << "Edit phone number: ";
    cin >> phoneNumber;
    
    cout << endl;
    this->name = name;
    this->phoneNumber = phoneNumber;
    cout << "Information updated for passenger " << name << ".\n";
    return true;
}

void Passenger::display() const {
    cout << "Passenger Name: " << name << endl;
    cout << "Passenger Phone Number: " << phoneNumber << endl;
    cout << "Bus Points: " << busPoints << endl;
}