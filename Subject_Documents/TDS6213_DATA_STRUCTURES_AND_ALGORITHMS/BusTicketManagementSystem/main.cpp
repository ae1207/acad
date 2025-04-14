#include <iostream>
#include <fstream>
#include <filesystem>
#include "Bus.cpp"
#include "Passenger.cpp"
#include "Ticket.cpp"
#include "TicketList.cpp"
#include "BookingManager.cpp"
#include "RefundManager.cpp"
#include "PointsManager.cpp"
#include "QueueManager.cpp"
using namespace std;

const int NUMBER_OF_BUSES = 5;

// NOTE: IF YOU ENCOUNTER ERROR, TRY COMMENTING system("cls") ON main.cpp at line 56 AND QueueManager.cpp at line 114

int main()
{
    BookingManager bm;
    QueueManager qm;

    Bus bus1("Melaka Sentral - TBS", "Transnasional", "Ali bin Ahmad", 8, "1200", 35);
    Bus bus2("Melaka Sentral - UMP Gambang", "Pandu Laju", "Hariz bin Mahmod", 3, "1800", 25);
    Bus bus3("Melaka Sentral - Johor Bahru - Larkin", "Starmart Express", "Dwayne Johnson", 4, "1330", 30);
    Bus bus4("Melaka Sentral - Alor Setar", "Mayang Sari", "Johan bin Ibrahim", 7, "1730", 50);
    Bus bus5("Melaka Sentral - Gua Musang", "DHL Express", "Eusoff Aminurrashid", 2, "2100", 37.5);
    Bus* buses[NUMBER_OF_BUSES] = {&bus1, &bus2, &bus3, &bus4, &bus5};

    do {

        cout << "\t=======================================" << endl;
        cout << "\tWELCOME TO BUS TICKET MANAGEMENT SYSTEM" << endl;
        cout << "\t=======================================" << endl;

        cout << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "\t 1. Virtual passenger queue" << endl;
        cout << "\t 2. Book new ticket" << endl;
        cout << "\t 3. Show passenger info" << endl;
        cout << "\t 4. Edit passenger info" << endl;
        cout << "\t 5. Cancel booking" << endl;
        cout << "\t 6. Show tickets" << endl;
        cout << "\t 7. Show buses" << endl;
        cout << "\t 8. Search for bus" << endl;
        cout << "\t 9. Sort buses" << endl;
        cout << "\t 10. Print ticket" << endl;
        cout << "\t 11. Exit system" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << endl;

        int option;
        cout << "Choose an option: ";
        cin >> option;

        system("cls");

        if(option == 1) {
            qm.displayMenu();
        }

        if(option == 2 && !qm.isEmpty()) {
            int busID, seatNumber;

            cout << "Booking ticket...\n";
            cout << "Select Bus ID: ";
            cin >> busID;
            cout << "Select seat number: ";
            cin >> seatNumber;

            if(busID >= 1 || busID <= NUMBER_OF_BUSES)
                bm.bookTicket(qm.getFront(), bm.getBusByID(buses, NUMBER_OF_BUSES, busID), seatNumber);
        }

        if(option == 3) {
            cout << "Showing passenger information...\n";
            if(!qm.isEmpty()) {
                cout << "--------------------\n";
                qm.getFront()->display();
                cout << "--------------------\n";
            }
        }

        if(option == 4) {
            Passenger* editedPassenger = qm.getFront();
            if(editedPassenger != nullptr) {
                cout << "Editing passenger information...\n";
                editedPassenger->editInfo();
            }
        }

        if(option == 5) {
            int busID, ticketID, hoursBeforeDeparture;

            if(qm.getFront() != nullptr) {
                cout << "Cancelling ticket...\n";
                cout << "Select Bus ID: ";
                cin >> busID;
                cout << "Select ticket ID: ";
                cin >> ticketID;
                cout << "Hours before departure: ";
                cin >> hoursBeforeDeparture;

                bm.cancelTicket(qm.getFront(), bm.getBusByID(buses, NUMBER_OF_BUSES, busID), ticketID, hoursBeforeDeparture);
            }
        }

        if(option == 6) {
            cout << "Showing tickets...\n";
            if(qm.getFront() != nullptr)
                bm.showTickets(qm.getFront());
        }

        if(option == 7) {
            cout << "Showing buses...\n";
            for(int i = 0; i < NUMBER_OF_BUSES; i++) {
                cout << "--------------------\n";
                buses[i]->display();
                cout << "--------------------\n";
            }
        }

        if(option == 8) {
            int busID;

            cout << "Searching for bus...\n";
            cout << "Bus ID: ";
            cin >> busID;
            bm.searchBusByID(buses, NUMBER_OF_BUSES, busID);
        }

        if(option == 9) {
            cout << "Sorting the bus by price...\n";
            bm.sortBusByPrice(buses, NUMBER_OF_BUSES);
            bm.showBuses(buses, NUMBER_OF_BUSES);
        }

        if(option == 10) {
            cout << "Printing tickets...\n";
            if(qm.getFront() != nullptr)
                bm.printTicket(qm.getFront());
        }

        if(option == 11) {
            cout << "Exiting the system...\n";
            break;
        }

        cout << endl;
    } while(true);

    return 0;
}
