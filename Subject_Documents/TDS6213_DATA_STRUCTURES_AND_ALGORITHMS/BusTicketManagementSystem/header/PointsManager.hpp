#ifndef POINTS_MANAGER_HPP
#define POINTS_MANAGER_HPP

#include <iostream>
#include "Passenger.hpp"
#include "BookingManager.hpp"
#include "Ticket.hpp"
using namespace std;

class PointsManager {
private:
    static const int pointsPerRM;

public:
    PointsManager();
    ~PointsManager();

    bool givePoints(Passenger* passenger, int points);
    bool deductPoints(Passenger* passenger, int points);
    float applyDiscount(Passenger* passenger, float price);
};

#endif