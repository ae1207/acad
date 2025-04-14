#include "header/QueueManager.hpp"
using namespace std;

QueueManager::QueueManager() : backPtr(nullptr), frontPtr(nullptr) {}

QueueManager::~QueueManager() {
    while (!isEmpty())
        dequeue();
}

bool QueueManager::isEmpty() const {
    if(backPtr == nullptr) {
        cout << "Passenger queue is empty!\n";
        return true;
    }
    return false;
}

bool QueueManager::enqueue(QueueItemType* newItem) {
    QueueNode* newPtr = new QueueNode;
    newPtr->item = newItem;
    newPtr-> next = nullptr;
    if(isEmpty())
        frontPtr = newPtr;
    else
        backPtr->next = newPtr;
    backPtr = newPtr;
    return true;
}

bool QueueManager::dequeue() {
    if(isEmpty())
        return false;

    QueueNode* tempPtr = frontPtr;
    if(frontPtr == backPtr)
        backPtr = nullptr;
    frontPtr = frontPtr->next;

    tempPtr->item = nullptr;
    tempPtr->next = nullptr;
    delete tempPtr;
    return true;
}

QueueItemType* QueueManager::getFront() {
    if(isEmpty())
        return nullptr;

    return frontPtr->item;
}

bool QueueManager::addPassenger() {
    cout << "Adding passenger to queue..." << endl;
    string name, phoneNumber;
    cout << "Passenger name: ";
    cin >> name;
    cout << "Passenger phone number: ";
    cin >> phoneNumber;

    Passenger* passenger = new Passenger(name, phoneNumber);

    if(!enqueue(passenger))
        return false;

    cout << "Passenger " << name << " added to queue." << endl;
    return true;
}

bool QueueManager::removePassenger() {
    char wantToRemove = 'Y';
    cout << "Are you sure to remove a passenger? (Y/n): ";
    cin >> wantToRemove;
    if(toupper(wantToRemove) == 'N')
        return false;

    cout << "Removing passenger from queue..." << endl;

    if(!dequeue())
        return false;

    cout << "The passenger has been removed from queue." << endl;
    return true;
}

bool QueueManager::showPassengers() {
    if(isEmpty())
        return false;

    cout << "Showing passengers queue..." << endl;
    for(QueueNode* curPtr = frontPtr; curPtr != NULL; curPtr = curPtr->next) {
        cout << "--------------------\n";
        curPtr->item->display();
        cout << "--------------------\n";
    }
    return true;
}

void QueueManager::displayMenu() {
    while(true) {
        cout << "\tQUEUE MANAGER:" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "\t 1. Add passenger to queue" << endl;
        cout << "\t 2. Remove passenger from queue" << endl;
        cout << "\t 3. Show passengers" << endl;
        cout << "\t 4. Exit Queue Manager" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << endl;

        int option;
        cout << "Choose an option: ";
        cin >> option;

        system("cls");

        switch (option)
        {
        case 1:
            addPassenger();
            break;

        case 2:
            removePassenger();
            break;

        case 3:
            showPassengers();
            break;

        case 4:
            cout << "Exiting Queue Manager..." << endl;
            return;

        default:
            cout << "Unsuccesful. Invalid option.\n";
            break;
        }
        cout << endl;
    }
}
