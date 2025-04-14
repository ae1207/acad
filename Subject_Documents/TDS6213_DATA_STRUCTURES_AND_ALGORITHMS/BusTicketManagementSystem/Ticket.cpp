#include "header/Ticket.hpp"
using namespace std;

const string Ticket::statusType[2] = {"Cancelled", "Booked"}; // 0 is Cancelled, 1 is Booked
int Ticket::ticketCount = 0;

Ticket::Ticket() : passengerName(""), 
passengerPhone(""), busID(0),
busRoute(""), busOperator(""),
busCompany(""),
seatNumber(0), platformNumber(0), 
price(0), statusIndex(1)
{
    ticketCount++;
    ticketID = ticketCount;
}

Ticket::Ticket(
    string passengerName, 
    string passengerPhone, 
    int busID,
    string busRoute,
    string busOperator,
    string busCompany,
    int seatNumber, 
    int platformNumber, 
    float price) : 
    passengerName(passengerName), 
    passengerPhone(passengerPhone), 
    busID(busID),
    busRoute(busRoute),
    busOperator(busOperator),
    busCompany(busCompany), 
    seatNumber(seatNumber), 
    platformNumber(platformNumber), 
    price(price), 
    statusIndex(1)
{
    ticketCount++;
    ticketID = ticketCount;
}

Ticket::~Ticket() {}

bool Ticket::updateStatus(int status) {
    if(status < 0 || status > 1)
        return false;
    
    statusIndex = status;
    return true;
}

int Ticket::getTicketID() const { return ticketID; }

string Ticket::getPassengerName() const { return passengerName; }

string Ticket::getPassengerPhone() const { return passengerPhone; }

int Ticket::getBusID() const { return busID; }

string Ticket::getBusRoute() const { return busRoute; }

string Ticket::getBusOperator() const { return busOperator; }

string Ticket::getBusCompany() const { return busCompany; }

int Ticket::getSeatNumber() const { return seatNumber; }

int Ticket::getPlatform() const { return platformNumber; }

float Ticket::getPrice() const { return price; }

string Ticket::getStatus() const { return statusType[statusIndex]; }

void Ticket::display() const {
    cout << "[TICKET ID: " << ticketID << "]" << endl;
    cout << "Passenger's Name: " << passengerName << endl;
    cout << "Phone Number: " << passengerPhone << endl;
    cout << "Bus ID: " << busID << endl;
    cout << "Route: " << busRoute << endl;
    cout << "Operator: " << busOperator << endl;
    cout << "Travel Company: " << busCompany << endl;
    cout << "Seat Number: " << seatNumber << endl;
    cout << "Platform Number: " << platformNumber << endl;
    cout << "Ticket Status: " << statusType[statusIndex] << endl;
    cout << "Ticket Price: RM" << price << endl;
}