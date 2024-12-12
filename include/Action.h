#pragma once
#include <string>
#include <vector>
#include "WareHouse.h"
using std::string;
using std::vector;
//added manually
#include <iostream>
class WareHouse;


enum class ActionStatus{
    COMPLETED, ERROR
};

enum class CustomerType{
    Soldier, Civilian
};


class BaseAction{
    public:
        BaseAction();
        ActionStatus getStatus() const;
        virtual void act(WareHouse& wareHouse)=0;
        virtual string toString() const=0;
        virtual BaseAction* clone() const=0;
        //added manually
        virtual ~BaseAction() = default;

    protected:
        void complete();
        void error(string errorMsg);
        string getErrorMsg() const;
        //added manually
        string statusString() const; //modular string used in toString 

    private:
        string errorMsg;
        ActionStatus status;
};

class SimulateStep : public BaseAction {

    public:
        SimulateStep(int numOfSteps);
        void act(WareHouse &wareHouse) override;
        string toString() const override;
        SimulateStep *clone() const override;
        //added manually
        ~SimulateStep() = default;

    private:
        const int numOfSteps;
};

class AddOrder : public BaseAction {
    public:
        AddOrder(int id);
        void act(WareHouse &wareHouse) override;
        string toString() const override;
        AddOrder *clone() const override;
        //added manually
        ~AddOrder() = default;

    private:
        const int customerId;
};


class AddCustomer : public BaseAction {
    public:
        AddCustomer(const string &customerName, const string &customerType, int distance, int maxOrders);
        void act(WareHouse &wareHouse) override;
        AddCustomer *clone() const override;
        string toString() const override;
        //added manually
        ~AddCustomer() = default;

    private:
        const string customerName;
        const CustomerType customerType;
        const int distance;
        const int maxOrders;
        //added manually
        const string sType;
};

class PrintOrderStatus : public BaseAction {
    public:
        PrintOrderStatus(int id);
        void act(WareHouse &wareHouse) override;
        PrintOrderStatus *clone() const override;
        string toString() const override;
        //added manually
        ~PrintOrderStatus() = default;

    private:
        const int orderId;
};

class PrintCustomerStatus: public BaseAction {
    public:
        PrintCustomerStatus(int customerId);
        void act(WareHouse &wareHouse) override;
        PrintCustomerStatus *clone() const override;
        string toString() const override;
        //added manually
        ~PrintCustomerStatus() = default;

    private:
        const int customerId;
};


class PrintVolunteerStatus : public BaseAction {
    public:
        PrintVolunteerStatus(int id);
        void act(WareHouse &wareHouse) override;
        PrintVolunteerStatus *clone() const override;
        string toString() const override;
        //added manually
        ~PrintVolunteerStatus() = default;

    private:
        const int volunteerId;
};


class PrintActionsLog : public BaseAction {
    public:
        PrintActionsLog();
        void act(WareHouse &wareHouse) override;
        PrintActionsLog *clone() const override;
        string toString() const override;
        //added manually
        ~PrintActionsLog() = default;

    private:
};

class Close : public BaseAction {
    public:
        Close();
        void act(WareHouse &wareHouse) override;
        Close *clone() const override;
        string toString() const override;
        //added manually
        ~Close() = default;

    private:
};

class BackupWareHouse : public BaseAction {
    public:
        BackupWareHouse();
        void act(WareHouse &wareHouse) override;
        BackupWareHouse *clone() const override;
        string toString() const override;
        //added manually
        ~BackupWareHouse() = default;

    private:
};


class RestoreWareHouse : public BaseAction {
    public:
        RestoreWareHouse();
        void act(WareHouse &wareHouse) override;
        RestoreWareHouse *clone() const override;
        string toString() const override;
        //added manually
        ~RestoreWareHouse() = default;

    private:
};

