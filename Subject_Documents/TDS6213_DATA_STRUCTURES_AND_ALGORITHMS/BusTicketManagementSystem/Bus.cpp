#include "header/Bus.hpp"
using namespace std;

int Bus::busCount = 0;

Bus::Bus() : route(""), busCompany(""), operatorName(""), platformNumber(0), departureTime(""), price(0), passengerCount(0){
    busCount++;
    busID = busCount;

    // Initialize the array seats and passengers
    for(int i = 0; i < numberOfSeats; i++) {
        seats[i] = false; // False means the seat is available
        passengers[i] = nullptr; // Initialie to nullptr
    }
}

Bus::Bus(
    string route, 
    string busCompany, 
    string operatorName, 
    int platformNumber, 
    string departureTime,
    float price) : 
route(route), operatorName(operatorName), platformNumber(platformNumber), 
departureTime(departureTime), price(price), passengerCount(0) {
    busCount++;
    busID = busCount;

    // Initialize the array seats and passengers
    for(int i = 0; i < numberOfSeats; i++) {
        seats[i] = false; // False means the seat is available
        passengers[i] = nullptr; // Initialie to nullptr
    }
}

Bus::~Bus() {
    for(int i = 0; i < numberOfSeats; i++) {
        passengers[i] = nullptr;
    }
}

// Value for seatNumber will be start from 1 to numberOfSeats
bool Bus::lockSeat(int seatNumber) {
    if(seatNumber < 1 || seatNumber > numberOfSeats)
        return false;

    if(seats[seatNumber-1])
        return false;
    
    seats[seatNumber-1] = true; // Marks the seat as locked
    return true;
}

bool Bus::releaseSeat(int seatNumber) {
    if(seatNumber < 1 || seatNumber > numberOfSeats)
        return false;

    if(!seats[seatNumber-1])
        return false;

    seats[seatNumber-1] = false; // Release the lock from seat
    return true;
}

bool Bus::isAvailable() const {
    return passengerCount != numberOfSeats;
}

bool Bus::addPassenger(Passenger* passenger, int seatNumber) {
    if(passengerCount >= numberOfSeats)
        return false;
    
    if(seatNumber < 1 || seatNumber > numberOfSeats)
        return false;

    if(!passenger)
        return false;

    if(passengers[seatNumber-1])
        return false;

    passengers[seatNumber-1] = passenger;
    passengerCount++;
    return true;
}

bool Bus::removePassenger(int seatNumber) {
    if(passengerCount <= 0)
        return false;

    if(seatNumber < 1 || seatNumber > numberOfSeats)
        return false;
    
    if(!passengers[seatNumber-1])
        return false;

    passengers[seatNumber-1] = nullptr;
    passengerCount--;
    return true;
}

int Bus::getBusID() const { return busID; }

string Bus::getRoute() const { return route; }

string Bus::getCompany() const { return busCompany; }

string Bus::getOperator() const { return operatorName; }

int Bus::getPlatformNumber() const { return platformNumber; }

string Bus::getDepartureTime() const { return departureTime; }

float Bus::getPrice() const { return price; }

int Bus::getEmptySeats() const { return numberOfSeats - passengerCount; }

int Bus::getPassengerCount() const { return passengerCount; }

Passenger* Bus::getPassenger(int seatNumber) { 
    if(seatNumber < 1 || seatNumber > numberOfSeats)
        return nullptr;
    
    return passengers[seatNumber-1]; 
} 

void Bus::display() const {
    cout << "[BUS ID: " << busID << "]" << endl;
    cout << "Route: " << route << endl;
    cout << "Bus Operator: " << operatorName << endl;
    cout << "Platform Number: " << platformNumber << endl;
    cout << "Departure Time: " << departureTime << endl;
    cout << "Price: " << price << endl;
    cout << "Number of Empty Buses: " << getEmptySeats() << endl;
    cout << "Passenger Count: " << passengerCount << endl;
}