#include "Customer.h"

//Implementation of the functions of Customer

Customer::Customer(int id, const string &name, int locationDistance, int maxOrders) : id(id), name(name), locationDistance(locationDistance), maxOrders(maxOrders), ordersId(0){}

const string & Customer::getName() const
{
    return name;
}

int Customer::getId() const
{
    return id;
}

int Customer::getCustomerDistance() const
{
    return locationDistance;
}

int Customer::getMaxOrders() const
{
    return maxOrders;
}

int Customer::getNumOrders() const
{
    return ordersId.size();
}

bool Customer::canMakeOrder() const
{
    return getMaxOrders() > getNumOrders();
}

const vector<int> & Customer::getOrdersIds() const
{
    return ordersId;
}

int Customer::addOrder(int orderId)
{
    if (canMakeOrder())
    {
        ordersId.push_back(orderId);
        return orderId;
    }
    return -1;
}

//Implementation of the functions of SoldierCustomer

SoldierCustomer::SoldierCustomer(int id, const string &name, int locationDistance, int maxOrders) : Customer(id, name, locationDistance, maxOrders){}

SoldierCustomer * SoldierCustomer::clone() const
{
    return new SoldierCustomer(*this);
}

//Implementation of the functions of CivilianCustomer

CivilianCustomer::CivilianCustomer(int id, const string &name, int locationDistance, int maxOrders) : Customer(id, name, locationDistance, maxOrders){}

CivilianCustomer * CivilianCustomer::clone() const
{
    return new CivilianCustomer(*this);
}