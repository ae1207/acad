#ifndef BOOKING_MANAGER_HPP
#define BOOKING_MANAGER_HPP

#include <iostream>
#include <fstream>
#include <filesystem>
#include "Bus.hpp"
#include "Passenger.hpp"
#include "RefundManager.hpp"
#include "PointsManager.hpp"
using namespace std;

class BookingManager {
private:
    RefundManager refundManager;
    PointsManager pointsManager;

public:
    BookingManager();
    ~BookingManager();

    bool bookTicket(Passenger* passenger, Bus* bus, int seatNumber);
    bool cancelTicket(Passenger* passenger, Bus* bus, int ticketID, int hoursBeforeDeparture);
    bool showTickets(Passenger* passenger);
    bool searchBusByID(Bus* buses[], int busCount, int busID);
    Bus* getBusByID(Bus* buses[], int busCount, int busID);
    bool sortBusByPrice(Bus* buses[], int busCount);
    bool showBuses(Bus* buses[], int busCount);
    bool printTicket(Passenger* passenger);
};

#endif
