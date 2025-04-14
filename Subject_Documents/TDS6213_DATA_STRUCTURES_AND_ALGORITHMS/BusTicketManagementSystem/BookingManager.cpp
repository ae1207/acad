#include "header/BookingManager.hpp"
using namespace std;

BookingManager::BookingManager() {}

BookingManager::~BookingManager() {}

bool BookingManager::bookTicket(Passenger* passenger, Bus* bus, int seatNumber) {
    if(!bus->lockSeat(seatNumber)) {
        cerr << "Unsuccessful. The seat number is invalid or already locked.\n";
        return false;
    }

    // Can add future implementations to detect user payment
    // We assume here that the user is currently doing payment here

    if(!bus->addPassenger(passenger, seatNumber)) {
        cerr << "Unsuccessful. The seat number is invalid or already occupied.\n";
        return false;
    }
    cout << "Would you like to purchase the ticket for RM" << bus->getPrice() << "? (Y/n): ";
    char wantToBuy;
    cin >> wantToBuy;
    if(toupper(wantToBuy) == 'N')
        return false;

    float currentPrice = pointsManager.applyDiscount(passenger, bus->getPrice());

    Ticket* newTicket = new Ticket(
        passenger->getName(),
        passenger->getPhoneNumber(),
        bus->getBusID(),
        bus->getRoute(),
        bus->getOperator(),
        bus->getCompany(),
        seatNumber,
        bus->getPlatformNumber(),
        currentPrice
    );

    int points = currentPrice;
    pointsManager.givePoints(passenger, points);

    TicketList* ticketList = passenger->getTicketList();
    ticketList->addTicket(newTicket);

    cout << "Ticket booked for " << passenger->getName() << " at bus " << bus->getBusID() << " seat " << seatNumber << ".\n";
    return true;
}

bool BookingManager::cancelTicket(Passenger* passenger, Bus* bus, int ticketID, int hoursBeforeDeparture) {
    TicketList* ticketList = passenger->getTicketList();

    bool ticketFound = false;
    for(int i = 1; i <= ticketList->getCount(); i++) {
        Ticket* ticket = ticketList->getTicket(i);

        // Checks if the ticketID matches
        if(ticket->getTicketID() == ticketID) {

            // Removes passenger from the bus and release the lock on the seat
            if( !bus->removePassenger(ticket->getSeatNumber()) || !bus->releaseSeat(ticket->getSeatNumber()) ) {
                cerr << "Unsuccessful. The seat number is invalid or unoccupied.\n";
                return false;
            }

            cout << "Ticket cancelled for ticket ID " << ticketID << " for passenger "
            << passenger->getName() << ", bus " << bus->getBusID() << ".\n";

            // Handles the refunding process
            if(!refundManager.processRefund(ticket, passenger, hoursBeforeDeparture))
                return false;

            ticketFound = true;
            break;
        }
    }

    if(!ticketFound) {
        cout << "Unsuccessful. Invalid ticket ID.\n";
        return false;
    }
    return true;
}

bool BookingManager::showTickets(Passenger* passenger) {
    TicketList* ticketList = passenger->getTicketList();

    for(int i = 1; i <= ticketList->getCount(); i++) {
        Ticket* ticket = ticketList->getTicket(i);
        cout << "--------------------\n";
        ticket->display();
        cout << "--------------------\n";
    }

    return true;
}

bool BookingManager::searchBusByID(Bus* buses[], int busCount, int busID) {
    for(int i = 0; i < busCount; i++) {
        if(buses[i]->getBusID() == busID) {

            cout << "Bus is found!\n";
            cout << "--------------------\n";
            buses[i]->display();
            cout << "--------------------\n";

            return true;
        }
    }
    cout << "Bus ID " << busID << " is not found!\n";
    return false;
}

Bus* BookingManager::getBusByID(Bus* buses[], int busCount, int busID) {
    for(int i = 0; i < busCount; i++) {
        if(buses[i]->getBusID() == busID)
            return buses[i];
    }
    cout << "Bus ID " << busID << " is not found!\n";
    return nullptr;
}

// Implement Bubble Sort
bool BookingManager::sortBusByPrice(Bus* buses[], int busCount) {
    for(int size = busCount; size > 1; size--) {

        for(int i = 0; i < size-1; i++) {

            if(buses[i]->getPrice() > buses[i+1]->getPrice()) {
                Bus* temp = buses[i];
                buses[i] = buses[i+1];
                buses[i+1] = temp;
            }
        }
    }
    return true;
}

bool BookingManager::showBuses(Bus* buses[], int busCount) {
    for(int i = 0; i < busCount; i++) {
        cout << "--------------------\n";
        buses[i]->display();
        cout << "--------------------\n";
    }

    return true;
}

bool BookingManager::printTicket(Passenger* passenger) {
    TicketList* ticketList = passenger->getTicketList();
    ofstream ticketFile;

    ticketFile.open("ticket.txt");

    if(!ticketFile) {
        cerr << "Unsuccessful. File could not be opened." << endl;
        return false;
    }

    for(int i = 1; i <= ticketList->getCount(); i++) {
        Ticket* ticket = ticketList->getTicket(i);

        ticketFile << "[TICKET ID: " << ticket->getTicketID() << "]" << endl;
        ticketFile << "Passenger's Name: " << ticket->getPassengerName() << endl;
        ticketFile << "Phone Number: " << ticket->getPassengerPhone() << endl;
        ticketFile << "Bus ID: " << ticket->getBusID() << endl;
        ticketFile << "Route: " << ticket->getBusRoute() << endl;
        ticketFile << "Operator: " << ticket->getBusOperator() << endl;
        ticketFile << "Travel Company: " << ticket->getBusCompany() << endl;
        ticketFile << "Seat Number: " << ticket->getSeatNumber() << endl;
        ticketFile << "Platform Number: " << ticket->getPlatform() << endl;
        ticketFile << "Ticket Status: " << ticket->getStatus() << endl;
        ticketFile << "Ticket Price: RM" << ticket->getPrice() << endl;
        ticketFile << endl;
    }

    ticketFile.close();
    cout << "Saving file to " << filesystem::current_path() << "..." << endl;
    cout << "Passenger " << passenger->getName() << " ticket(s) has been printed.\n";
    return true;
}
