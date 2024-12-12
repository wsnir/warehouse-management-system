#include "Volunteer.h"

// Implements the functions of Volunteer

Volunteer::Volunteer(int id, const string &name) : completedOrderId(NO_ORDER), activeOrderId(NO_ORDER), id(id), name(name) {}

int Volunteer::getId() const
{
    return id;
}

const string & Volunteer::getName() const
{
    return name;
}

int Volunteer::getActiveOrderId() const
{
    return activeOrderId;
}

int Volunteer::getCompletedOrderId() const
{
    return completedOrderId;
}

bool Volunteer::isBusy() const
{
    return (getActiveOrderId() != NO_ORDER);
}

string Volunteer::shortString() const
{
    string sBusy = "False";
    string orderId = "None";
    if(isBusy())
    {
        sBusy = "True";
        orderId  = std::to_string(getActiveOrderId());
    }
    return "VolunteerID: " + std::to_string(getId()) + "\n" +
           "isBusy: " + sBusy + "\n" +
           "OrderID: " + orderId + "\n";
}

// Implements the functions of derived classes

// CollectorVolunteer:

CollectorVolunteer::CollectorVolunteer(int id, const string &name, int coolDown) : Volunteer(id, name), coolDown(coolDown), timeLeft(0){}

int CollectorVolunteer::getCoolDown() const
{
    return coolDown;
}

int CollectorVolunteer::getTimeLeft() const
{
    return timeLeft;
}

bool CollectorVolunteer::decreaseCoolDown()
{
    if (isBusy())
    {
        timeLeft--;
    }
    return (getTimeLeft() == 0) and isBusy();
}

bool CollectorVolunteer::hasOrdersLeft() const
{
    return true;
}

bool CollectorVolunteer::canTakeOrder(const Order &order) const
{
    return !isBusy() and !((int) order.getStatus()); //if the status is pending
}

void CollectorVolunteer::acceptOrder(const Order &order)
{
    activeOrderId = order.getId();
    timeLeft = getCoolDown();
}

void CollectorVolunteer::step()
{
    if (decreaseCoolDown())
    {
        completedOrderId = getActiveOrderId();
        activeOrderId = NO_ORDER;
    }
}

CollectorVolunteer * CollectorVolunteer::clone() const
{
    return new CollectorVolunteer(*this);
}

string CollectorVolunteer::timeString() const
{
    if (isBusy())
    {
        return "TimeLeft: " + std::to_string(getTimeLeft()) + "\n";
    }
    return "TimeLeft: None\n";
}

string CollectorVolunteer::toString() const
{
    return shortString() + timeString() + "OrdersLeft: No Limit\n";
}

// LimitedCollectorVolunteer:

LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, const string &name, int coolDown ,int maxOrders) : CollectorVolunteer(id, name, coolDown), maxOrders(maxOrders), ordersLeft(maxOrders){}

int LimitedCollectorVolunteer::getNumOrdersLeft() const
{
    return ordersLeft;
}

int LimitedCollectorVolunteer::getMaxOrders() const
{
    return maxOrders;
}

bool LimitedCollectorVolunteer::hasOrdersLeft() const
{
    return getNumOrdersLeft();
}

bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const
{
    return CollectorVolunteer::canTakeOrder(order) and hasOrdersLeft();
}

void LimitedCollectorVolunteer::acceptOrder(const Order &order)
{
    CollectorVolunteer::acceptOrder(order);
    ordersLeft--;
}

LimitedCollectorVolunteer * LimitedCollectorVolunteer::clone() const
{
    return new LimitedCollectorVolunteer(*this);
}

string LimitedCollectorVolunteer::toString() const
{
    return shortString() + timeString() + "OrdersLeft: " + std::to_string(getNumOrdersLeft()) + "\n";
}

// DriverVolunteer:

DriverVolunteer::DriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep) : Volunteer(id, name), maxDistance(maxDistance), distancePerStep(distancePerStep), distanceLeft(0){}

int DriverVolunteer::getDistanceLeft() const
{
    return distanceLeft;
}

int DriverVolunteer::getMaxDistance() const
{
    return maxDistance;
}

int DriverVolunteer::getDistancePerStep() const
{
    return distancePerStep;
}

bool DriverVolunteer::decreaseDistanceLeft()
{
    if (isBusy())
    {
        distanceLeft -= getDistancePerStep();
    }
    if (getDistanceLeft() < 0)
    {
        distanceLeft = 0;
    }
    return (getDistanceLeft() == 0) and isBusy();
}

bool DriverVolunteer::hasOrdersLeft() const
{
    return true;
}

bool DriverVolunteer::canTakeOrder(const Order &order) const
{
    return !isBusy() and ((int) order.getStatus()) and (getMaxDistance() >= order.getDistance()); //if the status is collecting 
}

void DriverVolunteer::acceptOrder(const Order &order)
{
    activeOrderId = order.getId();
    distanceLeft = order.getDistance();
}

void DriverVolunteer::step()
{
    if (decreaseDistanceLeft())
    {
        completedOrderId = getActiveOrderId();
        activeOrderId = NO_ORDER;
    }
}

DriverVolunteer * DriverVolunteer::clone() const
{
    return new DriverVolunteer(*this);
}

string DriverVolunteer::distanceString() const
{
    if (isBusy())
    {
        return "DistanceLeft: " + std::to_string(getDistanceLeft()) + "\n";
    }
    return "DistanceLeft: None\n";
}

string DriverVolunteer::toString() const
{
    return shortString() + distanceString() + "OrdersLeft: No Limit\n";
}

// LimitedDriverVolunteer:

LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep,int maxOrders) : DriverVolunteer(id, name, maxDistance, distancePerStep), maxOrders(maxOrders), ordersLeft(maxOrders){}

int LimitedDriverVolunteer::getMaxOrders() const
{
    return maxOrders;
}

int LimitedDriverVolunteer::getNumOrdersLeft() const
{
    return ordersLeft;
}

bool LimitedDriverVolunteer::hasOrdersLeft() const
{
    return getNumOrdersLeft();
}

bool LimitedDriverVolunteer::canTakeOrder(const Order &order) const
{
    return DriverVolunteer::canTakeOrder(order) and hasOrdersLeft();
}

void LimitedDriverVolunteer::acceptOrder(const Order &order)
{
    DriverVolunteer::acceptOrder(order);
    ordersLeft--;
}

LimitedDriverVolunteer * LimitedDriverVolunteer::clone() const
{
    return new LimitedDriverVolunteer(*this);
}

string LimitedDriverVolunteer::toString() const
{
    return shortString() + distanceString() + "OrdersLeft: " + std::to_string(getNumOrdersLeft()) + "\n";
}