#include "header/RefundManager.hpp"
using namespace std;

const float RefundManager::refundPercent = 0.8;

RefundManager::RefundManager() {}

RefundManager::~RefundManager() {}

bool RefundManager::processRefund(Ticket* ticket, Passenger* passenger, int hoursBeforeDeparture) {
    float refundAmount = ticket->getPrice() * refundPercent;
    
    if(hoursBeforeDeparture < 15) {
        cerr << "Unsuccessful. Refunds are only accepted up to 15 hours before departure.\n";
        return false;
    }

    ticket->updateStatus(0); // Update the ticket status to Cancelled
    cout << "The ticket has been refunded with " << (1 - refundPercent) * 100 << "% cancellation fee. "; 
    cout << "RM" << refundAmount << " has been returned.\n";

    int points = ticket->getPrice();
    pointsManager.deductPoints(passenger, points);
    return true;
}