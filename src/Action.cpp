#include "Action.h"
extern WareHouse* backup;

//static function that converts string to CustomerType
CustomerType cType(string customerType)
{
    if(customerType == "soldier")
    {
        return CustomerType::Soldier;
    }
    return CustomerType::Civilian;
}

//implementation of BaseAction

BaseAction::BaseAction() : errorMsg(""), status(ActionStatus::ERROR){}

ActionStatus BaseAction::getStatus() const
{
    return status;
}

string BaseAction::getErrorMsg() const
{
    return errorMsg;
}

void BaseAction::complete()
{
    status = ActionStatus::COMPLETED;
}

void BaseAction::error(string errorMsg)
{
    this->errorMsg = errorMsg;
    status = ActionStatus::ERROR;
    string msg = "Error: " + errorMsg;
    std::cout<< msg << "\n" << std::endl;
}

string BaseAction::statusString() const
{
    string options[] = {"COMPLETED", "ERROR"};

    return " " + options[(int) getStatus()] + "\n";
}

//implementation of SimulateStep

SimulateStep::SimulateStep(int numOfSteps) : BaseAction(), numOfSteps(numOfSteps){}

void SimulateStep::act(WareHouse &wareHouse)
{
    for (int i = 0; i < numOfSteps; ++i)
    {
        wareHouse.assignOrders();
        wareHouse.step();
        wareHouse.examineOrders();
        wareHouse.sendHome();
    }
    complete();
    wareHouse.addAction(this);
}

SimulateStep *SimulateStep::clone() const 
{
    return new SimulateStep(*this);
}

string SimulateStep::toString() const
{
    return "simulateStep " + std::to_string(numOfSteps) + statusString();
}

//implementation of AddOrder

AddOrder::AddOrder(int id) : BaseAction(), customerId(id){}

void AddOrder::act(WareHouse &wareHouse)
{
    Customer &temp = wareHouse.getCustomer(customerId);
    if(temp.getId() != customerId or !temp.canMakeOrder())
    {
        error("Cannot place this order");
    }
    else
    {
        wareHouse.addOrder(new Order(wareHouse.assignOrderID(), customerId, temp.getCustomerDistance()));
        complete();
    }
    wareHouse.addAction(this);
}

AddOrder *AddOrder::clone() const
{
    return new AddOrder(*this);
}

string AddOrder::toString() const
{
    return "order " + std::to_string(customerId) + statusString();
}

//implementation of AddCustomer

AddCustomer::AddCustomer(const string &customerName, const string &customerType, int distance, int maxOrders) : BaseAction(), customerName(customerName), customerType(cType(customerType)), distance(distance), maxOrders(maxOrders), sType(customerType){}

void AddCustomer::act(WareHouse &wareHouse)
{
    if (int(customerType)) //if civilian
    {
        wareHouse.addCustomer(new CivilianCustomer(wareHouse.assignCustomerID(), customerName, distance, maxOrders));
    }
    else
    {
        wareHouse.addCustomer(new SoldierCustomer(wareHouse.assignCustomerID(), customerName, distance, maxOrders));
    }
    complete();
    wareHouse.addAction(this);
}

AddCustomer *AddCustomer::clone() const
{
    return new AddCustomer(*this);
}

string AddCustomer::toString() const
{
    return "customer " + customerName + " " + sType + " " + std::to_string(distance) + " " + std::to_string(maxOrders) + statusString();
}

//implementation of PrintOrderStatus

PrintOrderStatus::PrintOrderStatus(int id) : BaseAction(), orderId(id){}

void PrintOrderStatus::act(WareHouse &wareHouse)
{
    Order &temp = wareHouse.getOrder(orderId);
    if(temp.getId() != orderId)
    {
        error("Order doesn't exist");
    }
    else
    {
        std::cout << temp.toString() << "\n";
        complete();
    }
    wareHouse.addAction(this);
}

PrintOrderStatus *PrintOrderStatus::clone() const
{
    return new PrintOrderStatus(*this);
}

string PrintOrderStatus::toString() const
{
    return "orderStatus " + std::to_string(orderId) + statusString();
}

//implementation of PrintCustomerStatus

PrintCustomerStatus::PrintCustomerStatus(int customerId) : BaseAction(), customerId(customerId){}

void PrintCustomerStatus::act(WareHouse &wareHouse)
{
    Customer &temp = wareHouse.getCustomer(customerId);
    if(temp.getId() != customerId)
    {
        error("Customer doesn't exist");
    }
    else
    {
        std::cout << "CustomerID: " << temp.getId() << "\n";
        vector<int> orderIds = temp.getOrdersIds();
        for (size_t i = 0; i < orderIds.size(); ++i)
        {
            std::cout << wareHouse.getOrder(orderIds[i]).shortString();
        }
        int numOrdersLeft = temp.getMaxOrders() - temp.getNumOrders();
        std::cout << "numOrdersLeft: " << numOrdersLeft << "\n\n";
        complete();
    }
    wareHouse.addAction(this);
}

PrintCustomerStatus *PrintCustomerStatus::clone() const
{
    return new PrintCustomerStatus(*this);
}

string PrintCustomerStatus::toString() const
{
    return "customerStatus " + std::to_string(customerId) + statusString();
}

//implementation of PrintVolunteerStatus

PrintVolunteerStatus::PrintVolunteerStatus(int id) : BaseAction(), volunteerId(id){}

void PrintVolunteerStatus::act(WareHouse &wareHouse)
{
    Volunteer &temp = wareHouse.getVolunteer(volunteerId);
    if(temp.getId() != volunteerId)
    {
        error("Volunteer doesn't exist");
    }
    else
    {
        std::cout << temp.toString() << "\n";
        complete();
    }
    wareHouse.addAction(this);
}

PrintVolunteerStatus *PrintVolunteerStatus::clone() const
{
    return new PrintVolunteerStatus(*this);
}

string PrintVolunteerStatus::toString() const
{
    return "volunteerStatus " + std::to_string(volunteerId) + statusString();
}

//implementation of PrintActionsLog

PrintActionsLog::PrintActionsLog() : BaseAction(){}

void PrintActionsLog::act(WareHouse &wareHouse)
{
    vector<BaseAction*> temp = wareHouse.getActions();
    for (size_t i = 0; i < temp.size(); ++i)
    {
        std::cout << temp[i]->toString();
    }
    std::cout << "\n";
    complete();
    wareHouse.addAction(this);
}

PrintActionsLog *PrintActionsLog::clone() const
{
    return new PrintActionsLog(*this);
}

string PrintActionsLog::toString() const
{
    return "log" + statusString();
}

//implementation of Close

Close::Close() : BaseAction(){}

void Close::act(WareHouse &wareHouse)
{
    std::cout << wareHouse.toPrint();
    complete();
    wareHouse.addAction(this);
    wareHouse.close();
}

Close *Close::clone() const
{
    return new Close(*this);
}

string Close::toString() const
{
    return "close" + statusString();
}

//implementation of BackupWareHouse

BackupWareHouse::BackupWareHouse() : BaseAction(){}

void BackupWareHouse::act(WareHouse &wareHouse)
{
    complete();
    wareHouse.addAction(this);
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
    backup = new WareHouse(wareHouse);   
}

BackupWareHouse *BackupWareHouse::clone() const
{
    return new BackupWareHouse(*this);
} 

string BackupWareHouse::toString() const
{
    return "backup" + statusString();
}

//implementation of RestoreWareHouse

RestoreWareHouse::RestoreWareHouse() : BaseAction(){}

void RestoreWareHouse::act(WareHouse &wareHouse)
{
    if (backup!=nullptr)
    {
        wareHouse = *backup;
        complete();
    }
    else
    {
        error("No backup available");
    }
    wareHouse.addAction(this);
}

RestoreWareHouse *RestoreWareHouse::clone() const
{
    return new RestoreWareHouse(*this);
}

string RestoreWareHouse::toString() const
{
    return "restore" + statusString();
}