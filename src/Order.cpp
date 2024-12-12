#include "Order.h"

Order::Order(int id, int customerId, int distance) : id(id), customerId(customerId), distance(distance), status(OrderStatus::PENDING), collectorId(NO_VOLUNTEER), driverId(NO_VOLUNTEER){}

int Order::getId() const
{
    return id;
}

int Order::getCustomerId() const
{
    return customerId;
}

int Order::getDistance() const
{
    return distance;
}

void Order::setStatus(OrderStatus status)
{
    this->status = status;
}

void Order::setCollectorId(int collectorId)
{
    this->collectorId = collectorId;
}

void Order::setDriverId(int driverId)
{
    this->driverId = driverId;
}

int Order::getCollectorId() const
{
    return collectorId;
}

int Order::getDriverId() const
{
    return driverId;
}

OrderStatus Order::getStatus() const
{
    return status;
}

string Order::statusString() const
{
    string options[] = {"Pending", "Collecting", "Delivering", "Completed"};

    return options[(int) getStatus()];
}

string Order::shortString() const
{
    return "OrderID: " + std::to_string(getId()) + "\n" +
           "OrderStatus: " + statusString() + "\n";
}

string Order::closeString() const
{
    return "OrderID: " + std::to_string(getId()) + ", CustomerID: " + std::to_string(getCustomerId()) + ", Status: " + statusString() + "\n";
}

const string Order::toString() const
{
    string cId = std::to_string(getCollectorId());
    if (getCollectorId() == NO_VOLUNTEER)
    {
        cId = "None";
    }

    string dId = std::to_string(getDriverId());
    if (getDriverId() == NO_VOLUNTEER)
    {
        dId = "None";
    }

    return shortString() +
           "CustomerID: " + std::to_string(getCustomerId()) + "\n" +
           "Collector: " + cId + "\n" +
           "Driver: " + dId + "\n";
}