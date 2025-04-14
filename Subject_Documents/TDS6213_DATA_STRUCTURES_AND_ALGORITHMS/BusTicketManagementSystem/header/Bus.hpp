#ifndef BUS_HPP
#define BUS_HPP

#include <iostream>
#include "Passenger.hpp"
using namespace std;

class Bus {
private:
    static int busCount; // Keep track of the number of buses
    static const int numberOfSeats = 40; // The number of seats in the bus
    int busID; // Unique bus ID
    string route; // The route of the bus eg. "Melaka Sentral - TBS"
    string busCompany; // The travel company of the bus
    string operatorName; // The name of the bus operator
    int platformNumber;
    string departureTime;
    float price;
    bool seats[numberOfSeats]; // Bool array to check if the seats are occupied
    Passenger* passengers[numberOfSeats]; // The bus has passengers based on the number of seats
    int passengerCount;

public:
    Bus();
    Bus(string route, string busCompany, string operatorName, int platformNumber, string departureTime, float price);
    ~Bus();

    bool lockSeat(int seatNumber); // Lock a seat to prevent other passenger from booking
    bool releaseSeat(int seatNumber); // Release lock from a seat
    bool isAvailable() const; // Checks if the bus is available

    // Adding and removing passengers from bus
    bool addPassenger(Passenger* passenger, int seatNumber);
    bool removePassenger(int seatNumber);

    // Methods for retrieving bus data
    int getBusID() const;
    string getRoute() const;
    string getCompany() const;
    string getOperator() const;
    int getPlatformNumber() const;
    string getDepartureTime() const;
    float getPrice() const;
    int getEmptySeats() const; // Retrieves the number of empty seats in the bus
    int getPassengerCount() const;
    Passenger* getPassenger(int seatNumber);

    // Display bus information
    void display() const;
};

#endif