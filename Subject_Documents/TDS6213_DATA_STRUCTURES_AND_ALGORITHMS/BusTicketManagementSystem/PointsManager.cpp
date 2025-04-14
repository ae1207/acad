#include "header/PointsManager.hpp"
using namespace std;

const int PointsManager::pointsPerRM = 100;

PointsManager::PointsManager() {}

PointsManager::~PointsManager() {}

bool PointsManager::givePoints(Passenger* passenger, int points) {
    if(!passenger->earnPoints(points)) {
        cerr << "Unsuccessful. Invalid or insufficient bus points.\n";
        return false;
    }
    
    cout << "Passenger " << passenger->getName() << " received " << points << " bus points.\n"; 
    cout << "Total Bus Points: " << passenger->getBusPoints() << endl;
    return true;
}

bool PointsManager::deductPoints(Passenger* passenger, int points) {
    if(!passenger->redeemPoints(points)) {
        cerr << "Unsuccessful. Invalid or insufficient bus points.\n";
        return false;
    }
    
    cout << "Passenger " << passenger->getName() << " is deducted " << points << " bus points.\n";
    cout << "Total Bus Points: " << passenger->getBusPoints() << endl;
    return true;
}

float PointsManager::applyDiscount(Passenger* passenger, float price) {
    float usePoints;
    char wantToApply = 'Y';

    cout << "Would you like to apply a discount using your bus points? (" << pointsPerRM << " points per RM1 discount) (Y/n): ";
    cin >> wantToApply;
    if(toupper(wantToApply) == 'N')
        return price;

    cout << "How many points to use? (At least 100 points): ";
    cin >> usePoints;

    if(usePoints < 100) {
        cerr << "Unsuccessful. Insufficient points used.\n";
        return price;
    }

    if(!deductPoints(passenger, usePoints))
        return price;
     
    float discount = usePoints/pointsPerRM; // Calculate the discount

    price = price - discount;
    cout << usePoints << " bus points have been used! Ticket price is now RM" << price << ".\n";
    return price;
}