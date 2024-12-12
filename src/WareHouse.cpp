#include "WareHouse.h"

WareHouse::WareHouse(const string &configFilePath) : isOpen(false), actionsLog(0), volunteers(0), pendingOrders(0), inProcessOrders(0), completedOrders(0), customers(0), customerCounter(0), volunteerCounter(0), orderCounter(0), configFilePath(configFilePath), defaultVolunteer(new CollectorVolunteer(-1, "default", 0)), defaultCustomer(new SoldierCustomer(-1, "default", 0, 0)), defaultOrder(new Order(-1, -1, 0))
{
    parseFile();
}

WareHouse::WareHouse(const WareHouse& other) : isOpen(other.isOpen), actionsLog(0), volunteers(0), pendingOrders(0), inProcessOrders(0), completedOrders(0), customers(0), customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter), orderCounter(other.orderCounter), configFilePath(other.configFilePath), defaultVolunteer(other.defaultVolunteer->clone()), defaultCustomer(other.defaultCustomer->clone()), defaultOrder(new Order(*(other.defaultOrder)))
{
    for (const auto action : other.actionsLog)
    {
        actionsLog.push_back(action->clone());
    }
    for (const auto volunteer : other.volunteers)
    {
        volunteers.push_back(volunteer->clone());
    }
    for (const auto order : other.pendingOrders)
    {
        pendingOrders.push_back(new Order(*order));
    }
    for (const auto order : other.inProcessOrders)
    {
        inProcessOrders.push_back(new Order(*order));
    }
    for (const auto order : other.completedOrders)
    {
        completedOrders.push_back(new Order(*order));
    }
    for (const auto customer : other.customers)
    {
        customers.push_back(customer->clone());
    }
}

WareHouse::WareHouse(WareHouse&& other) noexcept : 
    isOpen(std::move(other.isOpen)),
    actionsLog(std::move(other.actionsLog)),
    volunteers(std::move(other.volunteers)),
    pendingOrders(std::move(other.pendingOrders)),
    inProcessOrders(std::move(other.inProcessOrders)),
    completedOrders(std::move(other.completedOrders)),
    customers(std::move(other.customers)),
    customerCounter(other.customerCounter),
    volunteerCounter(other.volunteerCounter),
    orderCounter(other.orderCounter),
    configFilePath(std::move(other.configFilePath)),
    defaultVolunteer(other.defaultVolunteer),
    defaultCustomer(other.defaultCustomer),
    defaultOrder(other.defaultOrder) 
{

    // Reset the source object's pointers to null or default values.

    other.actionsLog.clear();
    other.volunteers.clear();
    other.pendingOrders.clear();
    other.inProcessOrders.clear();
    other.completedOrders.clear();
    other.customers.clear();
    other.isOpen = false;
    other.customerCounter = 0;
    other.volunteerCounter = 0;
    other.orderCounter = 0;
    other.configFilePath = "";
    other.defaultVolunteer = nullptr;
    other.defaultCustomer = nullptr;
    other.defaultOrder = nullptr;
}

WareHouse::~WareHouse()
{
    // important remark: we only delete the object pointed by the pointers and not the pointers themselves.
    for (BaseAction* action : actionsLog) 
    {
        delete action;
    }

    for (Volunteer* volunteer : volunteers) 
    {
        delete volunteer;
    }

    for (Order* order : pendingOrders) 
    {
        delete order;
    }

    for (Order* order : inProcessOrders) 
    {
        delete order;
    }

    for (Order* order : completedOrders) 
    {
        delete order;
    }

    for (Customer* customer : customers) 
    {
        delete customer;
    }

    if (defaultVolunteer)
    {
        delete defaultVolunteer;
    }
    
    if (defaultCustomer)
    {
        delete defaultCustomer;
    }

    if (defaultOrder)
    {
        delete defaultOrder;
    }
    
}

WareHouse & WareHouse::operator=(const WareHouse& other)
{
    if(this != &other)
    {
        for (BaseAction* action : actionsLog) 
        {
            delete action;
        }

        actionsLog.clear();

        for (Volunteer* volunteer : volunteers) 
        {
            delete volunteer;
        }

        volunteers.clear();

        for (Order* order : pendingOrders) 
        {
            delete order;
        }

        pendingOrders.clear();

        for (Order* order : inProcessOrders) 
        {
            delete order;
        }

        inProcessOrders.clear();

        for (Order* order : completedOrders) 
        {
            delete order;
        }

        completedOrders.clear();

        for (Customer* customer : customers) 
        {
            delete customer;
        }

        customers.clear();

        delete defaultVolunteer;
        defaultVolunteer = other.defaultVolunteer->clone();

        delete defaultCustomer;
        defaultCustomer = other.defaultCustomer->clone();

        delete defaultOrder;
        defaultOrder = new Order(*(other.defaultOrder));

        for (const auto action : other.actionsLog)
        {
            actionsLog.push_back(action->clone());
        }
        for (const auto volunteer : other.volunteers)
        {
            volunteers.push_back(volunteer->clone());
        }
        for (const auto order : other.pendingOrders)
        {
            pendingOrders.push_back(new Order(*order));
        }
        for (const auto order : other.inProcessOrders)
        {
            inProcessOrders.push_back(new Order(*order));
        }
        for (const auto order : other.completedOrders)
        {
            completedOrders.push_back(new Order(*order));
        }
        for (const auto customer : other.customers)
        {
            customers.push_back(customer->clone());
        }

        isOpen = other.isOpen;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        orderCounter = other.orderCounter;
        configFilePath = other.configFilePath;
    }
    return *this;
}

WareHouse& WareHouse::operator=(WareHouse&& other) noexcept 
{
    if (this != &other) {
        for (BaseAction* action : actionsLog) 
        {
            delete action;
        }

        actionsLog.clear();

        for (Volunteer* volunteer : volunteers) 
        {
            delete volunteer;
        }

        volunteers.clear();

        for (Order* order : pendingOrders) 
        {
            delete order;
        }

        pendingOrders.clear();

        for (Order* order : inProcessOrders) 
        {
            delete order;
        }

        inProcessOrders.clear();

        for (Order* order : completedOrders) 
        {
            delete order;
        }

        completedOrders.clear();

        for (Customer* customer : customers) 
        {
            delete customer;
        }

        customers.clear();

        delete defaultVolunteer;
        defaultVolunteer = nullptr;

        delete defaultCustomer;
        defaultCustomer = nullptr;

        delete defaultOrder;
        defaultOrder = nullptr;
        
        // Move basic members
        isOpen = std::move(other.isOpen);
        customerCounter = std::move(other.customerCounter);
        volunteerCounter = std::move(other.volunteerCounter);
        orderCounter = std::move(other.orderCounter);
        configFilePath = std::move(other.configFilePath);

        // Move vectors and pointers
        actionsLog = std::move(other.actionsLog);
        volunteers = std::move(other.volunteers);
        pendingOrders = std::move(other.pendingOrders);
        inProcessOrders = std::move(other.inProcessOrders);
        completedOrders = std::move(other.completedOrders);
        customers = std::move(other.customers);

        // Move default objects
        defaultVolunteer = std::move(other.defaultVolunteer);
        defaultCustomer = std::move(other.defaultCustomer);
        defaultOrder = std::move(other.defaultOrder);

        // Reset source object's pointers
        other.actionsLog.clear();
        other.volunteers.clear();
        other.pendingOrders.clear();
        other.inProcessOrders.clear();
        other.completedOrders.clear();
        other.customers.clear();
        other.isOpen = false;
        other.customerCounter = 0;
        other.volunteerCounter = 0;
        other.orderCounter = 0;
        other.configFilePath = "";
        other.defaultVolunteer = nullptr;
        other.defaultCustomer = nullptr;
        other.defaultOrder = nullptr;
    }
    return *this;
}

void WareHouse::start()
{
    open();
    while(isOpen)
    {
        string action;
        std::getline(std::cin, action);
        vector<string> words = input(action);
        //choose the right action 
        if(words[0] == "step")
        {
            BaseAction* step = new SimulateStep(stoi(words[1]));
            step->act(*this);
        }
        else if(words[0] == "order")
        {
            BaseAction* order = new AddOrder(stoi(words[1]));
            order->act(*this);
        }
        else if(words[0] == "customer")
        {
            BaseAction* customer = new AddCustomer(words[1],words[2],stoi(words[3]),stoi(words[4]));
            customer->act(*this);
        }
        else if(words[0] == "orderStatus")
        {
            BaseAction* orderStatus = new PrintOrderStatus(stoi(words[1]));
            orderStatus->act(*this);
        }
        else if(words[0] == "customerStatus")
        {
            BaseAction* customerStatus = new PrintCustomerStatus(stoi(words[1]));
            customerStatus->act(*this);
        }
        else if(words[0] == "volunteerStatus")
        {
            BaseAction* volunteerStatus = new PrintVolunteerStatus(stoi(words[1]));
            volunteerStatus->act(*this);  
        }
        else if(words[0] == "log")
        {
            BaseAction* log = new PrintActionsLog();
            log->act(*this);
        }
        else if(words[0] == "close")
        {
            BaseAction* close = new Close();
            close->act(*this);
        }
        else if(words[0] == "backup")
        {
            BaseAction* backup = new BackupWareHouse();
            backup->act(*this);
        }
        else if(words[0] == "restore")
        {
            BaseAction* restore = new RestoreWareHouse();
            restore->act(*this);
        }
    }
}

void WareHouse::parseFile()
{
    std::ifstream inputFile(configFilePath);

    // Read the file content
    string line;
    while (std::getline(inputFile, line)) 
    {
        if (line.empty() || line[0] == '#'|| line[0] == '/') 
        {
            continue;
        }
        // Process each letter as needed
        std::istringstream iss(line);
        string substring;
        vector<string> substrings;

        // Read each substring separated by spaces or tabs
        while (iss >> substring) 
        {
            substrings.push_back(substring);
        }
        if(substrings[0] == "customer")
        {
            if(substrings[2] == "soldier")
            {
                Customer* soldier = new SoldierCustomer(assignCustomerID(), substrings[1], stoi(substrings[3]), stoi(substrings[4]));
                customers.push_back(soldier);
            }
            else
            {
                Customer* civilian = new CivilianCustomer(assignCustomerID(), substrings[1], stoi(substrings[3]), stoi(substrings[4]));
                customers.push_back(civilian);
            }
        }
        else if(substrings[0] == "volunteer")
        {
            if(substrings[2] == "collector")
            {
                Volunteer* collector = new CollectorVolunteer(assignVolunteerID(), substrings[1], stoi(substrings[3]));
                volunteers.push_back(collector);
            }
            else if (substrings[2] == "limited_collector")
            {
                Volunteer* limitedCollector = new LimitedCollectorVolunteer(assignVolunteerID(), substrings[1], stoi(substrings[3]), stoi(substrings[4]));
                volunteers.push_back(limitedCollector);
            }
            else if(substrings[2] == "driver")
            {
                Volunteer* driver = new DriverVolunteer(assignVolunteerID(), substrings[1], stoi(substrings[3]),stoi(substrings[4]));
                volunteers.push_back(driver);
            }
            else if (substrings[2] == "limited_driver")
            {
                Volunteer* limitedDriver = new LimitedDriverVolunteer(assignVolunteerID(), substrings[1], stoi(substrings[3]), stoi(substrings[4]),stoi(substrings[5]));
                volunteers.push_back(limitedDriver);
            }
        }
    }
    inputFile.close();
}

void WareHouse::addOrder(Order* order)
{
    pendingOrders.push_back(order);
    (getCustomer(order->getCustomerId())).addOrder(order->getId()); // also adds orderId to the customer
}

void WareHouse::addAction(BaseAction* action)
{
    actionsLog.push_back(action);
}

void WareHouse::addCustomer(Customer* customer)
{
    customers.push_back(customer);
}

Customer& WareHouse::getCustomer(int customerId) const
{
    for(size_t i = 0; i < customers.size(); ++i)
    {
        if(customers[i]->getId() == customerId)
        {
            return *customers[i];
        }
    }
    return *defaultCustomer;
}

Volunteer& WareHouse::getVolunteer(int volunteerId) const
{
    for(size_t i = 0; i < volunteers.size(); ++i)
    {
        if(volunteers[i]->getId() == volunteerId)
        {
            return *volunteers[i];
        }
    }
    return *defaultVolunteer;
}

Order& WareHouse::getOrder(int orderId) const
{
    for(size_t i = 0; i < pendingOrders.size(); ++i)
    {
        if(pendingOrders[i]->getId() == orderId)
        {
            return *pendingOrders[i];
        }
    }
    for(size_t i = 0; i < inProcessOrders.size(); ++i)
    {
        if(inProcessOrders[i]->getId() == orderId)
        {
            return *inProcessOrders[i];
        }
    }
    for(size_t i = 0; i < completedOrders.size(); ++i)
    {
        if(completedOrders[i]->getId() == orderId)
        {
            return *completedOrders[i];
        }
    }
    return *defaultOrder;
}

const vector<BaseAction*> &WareHouse::getActions() const
{
    return actionsLog;
}

vector<string> WareHouse::input(const string &action)
{
    vector<string> words;
    string currentWord;

    for (size_t i = 0; i < action.length(); ++i) 
    {
        char c = action[i];
        if (c != ' ')  //If the character is not a space, add it to the current word
        {
            currentWord += c;
        } 
        else // If the character is a space, add the current word to the vector
        {
            if(!currentWord.empty()) {
                words.push_back(currentWord);
                currentWord.clear();  
            }
        }
    }
    if(!currentWord.empty()) 
    {
        words.push_back(currentWord);
    }
    return words;
}

int WareHouse::assignOrderID()
{
    int orderId = orderCounter;
    orderCounter++;
    return orderId;
}

int WareHouse::assignCustomerID()
{
    int customerId = customerCounter;
    customerCounter++;
    return customerId;

}

int WareHouse::assignVolunteerID()
{
    int volunteerId = volunteerCounter;
    volunteerCounter++;
    return volunteerId;
}

void WareHouse::close()
{
    isOpen = false;
}

void WareHouse::open()
{
    isOpen = true;
    std::cout << "Warehouse is open!\n\n";
}

string WareHouse::toPrint() const
{
    string print = "";
    for (const auto order : pendingOrders)
    {
        print += order->closeString();
    }
    for (const auto order : inProcessOrders)
    {
        print += order->closeString();
    }
    for (const auto order : completedOrders)
    {
        print += order->closeString();
    }
    return print;
}

//goes through all the orders in pending orders and assigns them to the relevant volunteer
void WareHouse::assignOrders()
{
    for (auto order = pendingOrders.begin(); order != pendingOrders.end();)
    {
        int status = (int)((**order).getStatus());
        int control = status;
        for (auto volunteer : volunteers)
        {
            if (volunteer->canTakeOrder(**order))
            {
                volunteer->acceptOrder(**order);
                if (status)
                {
                    (**order).setDriverId(volunteer->getId());
                }
                else
                {
                    (**order).setCollectorId(volunteer->getId());
                }
                (**order).setStatus((OrderStatus) (++status));
                inProcessOrders.push_back(*order);
                order = pendingOrders.erase(order);
                break;
            }
        }
        if (status == control)
        {
            ++order;
        }
    }
}

//performs a step for each volunteer
void WareHouse::step()
{
    for (auto volunteer : volunteers)
    {
        volunteer->step();
    }
}

//checks all volunteers and relocates their orders to the relevant list upon comletion
void WareHouse::examineOrders()
{
    for (auto volunteer : volunteers)
    {
        if (!(volunteer->isBusy()) and (volunteer->getCompletedOrderId() != NO_ORDER))
        {
            for (auto order = inProcessOrders.begin(); order != inProcessOrders.end();)
            {
                if ((**order).getId() == volunteer->getCompletedOrderId())
                {
                    if ((**order).getStatus() == OrderStatus::COLLECTING)
                    {
                        pendingOrders.push_back(*order);
                        inProcessOrders.erase(order);
                    }
                    else
                    {
                        (**order).setStatus(OrderStatus::COMPLETED);
                        completedOrders.push_back(*order);
                        inProcessOrders.erase(order);
                    }
                    break;
                }
                ++order;
            }
        }
    }
}

//deletes used up volunteers
void WareHouse::sendHome()
{
    for (auto volunteer = volunteers.begin(); volunteer != volunteers.end();)
    {
        if (!((**volunteer).hasOrdersLeft()) and !((**volunteer).isBusy()))
        {
            delete *volunteer;
            *volunteer = nullptr;
            volunteer = volunteers.erase(volunteer);
        }
        else
        {
            ++volunteer;
        }
    }
}