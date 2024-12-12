#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Order.h"
#include "Customer.h"
#include "Volunteer.h"
#include "Action.h"
class BaseAction;
class Volunteer;

// Warehouse responsible for Volunteers, Customers Actions, and Orders.


class WareHouse {

    public:
        WareHouse(const string &configFilePath);
        void start();
        void addOrder(Order* order);
        void addAction(BaseAction* action);
        Customer &getCustomer(int customerId) const;
        Volunteer &getVolunteer(int volunteerId) const;
        Order &getOrder(int orderId) const;
        const vector<BaseAction*> &getActions() const;
        void close();
        void open();

        //added manually
        int assignOrderID(); //assigns and increments
        int assignCustomerID(); //assigns and increments
        int assignVolunteerID(); //assigns and increments
        void addCustomer(Customer* customer);
        string toPrint() const; //used in closed in conjunction with order's closeString 
        void assignOrders(); //phase 1 of simulateStep
        void step(); //phase 2 of simulateStep
        void examineOrders(); //phase 3 of simulateStep
        void sendHome();// phase 4 of simulateStep
        void parseFile(); // used to process the configFile
        
        //rule of 5
        WareHouse(const WareHouse& other);
        WareHouse(WareHouse&& other) noexcept;
        WareHouse& operator=(const WareHouse& other);
        WareHouse& operator=(WareHouse&& other) noexcept;
        ~WareHouse();

    private:
        bool isOpen;
        vector<BaseAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Customer*> customers;
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
        //added manually
        vector<string> input(const string &action); // used to process user input
        int orderCounter;
        string configFilePath; 
        //default object return values if no such object exists
        Volunteer* defaultVolunteer;
        Customer* defaultCustomer;
        Order* defaultOrder;
};