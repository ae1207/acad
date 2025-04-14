#ifndef REFUND_MANAGER_HPP
#define REFUND_MANAGER_HPP

#include <iostream>
#include "Ticket.hpp"
#include "BookingManager.hpp"
#include "PointsManager.hpp"
using namespace std;

class RefundManager {
private:
    static const float refundPercent;
    PointsManager pointsManager;

public:
    RefundManager();
    ~RefundManager();

    bool processRefund(Ticket* ticket, Passenger* passenger, int hoursBeforeDeparture);
};

#endif