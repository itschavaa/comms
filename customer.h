// =========================================================
// File: customer.h
// Author:
// Date:
// Description:
// =========================================================
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <sstream>
#include <iomanip>
#include <utility>
#include "bill.h"
#include "operator.h"

using namespace std;

class Customer {
private:
    int id, age, totalSpentTalkingTime, totalMessageSent, totalInternetUsage;
    string name;
    Operator *op;
    Bill *bill;

public:
    Customer(int, string, int, Operator *, double);

    Customer(const Customer &);

    ~Customer();

    int getId() const;

    int getAge() const;

    int getTotalSpentTalkingTime() const;

    int getTotalMessageSent() const;

    int getTotalInternetUsage() const;

    string getName() const;

    Operator *getOperator() const;

    Bill *getBill() const;

    void setOperator(Operator *);

    string toString() const;

    void talk(int, Customer &);

    void message(int, const Customer &);

    void connection(double);

    void pay(double);

};

Customer::Customer(int id, string name, int age, Operator *op, double lim) {
    this->id = id;
    this->name = name;
    this->age = age;
    this->op = op;
    totalSpentTalkingTime = 0;
    totalInternetUsage = 0;
    totalMessageSent = 0;
    bill = new Bill(lim);
}

Customer::Customer(const Customer &copy) {
    id = copy.id;
    name = copy.name;
    age = copy.age;
    totalSpentTalkingTime = copy.totalSpentTalkingTime;
    totalMessageSent = copy.totalMessageSent;
    totalInternetUsage = copy.totalInternetUsage;
    op = copy.op;
    bill = copy.bill;
}

Customer::~Customer() {
    delete bill;
    op = nullptr;
    bill = nullptr;
}

int Customer::getId() const {
    return id;
}

int Customer::getAge() const {
    return age;
}

string Customer::getName() const {
    return name;
}

int Customer::getTotalSpentTalkingTime() const {
    return totalSpentTalkingTime;
}

int Customer::getTotalMessageSent() const {
    return totalMessageSent;
}

int Customer::getTotalInternetUsage() const {
    return totalInternetUsage;
}

Operator *Customer::getOperator() const {
    return op;
}

Bill *Customer::getBill() const {
    return bill;
}

void Customer::setOperator(Operator *op) {
    this->op = op;
}

string Customer::toString() const {
    stringstream aux;
    aux << "Customer " << getId() << ": " << fixed << setprecision(2) << bill->getTotalMoneySpent() << " "
        << bill->getCurrentDebt();
    return aux.str();
}

void Customer::talk(int minutes, Customer &other) {
    if (minutes > 0 && other.id != this->id) {
        double cost = op->calculateTalkingCost(minutes, age);
        if (bill->check(cost)) {
            bill->add(cost);
            totalSpentTalkingTime += minutes;
            op->addTalkingTime(minutes);
            if (op->getId() != other.op->getId()){
                other.op->addTalkingTime(minutes);
            }
        }
    }
}


void Customer::message(int quantity, const Customer &other) {
    if (quantity > 0 && other.id != this->id) {
        double cost = op->calculateMessageCost(quantity, op->getId(), other.op->getId());
        if (bill->check(cost)) {
            bill->add(cost);
            op->addTotalMessageSent(quantity);
            this->totalMessageSent += quantity;
        }
    }
}

void Customer::connection(double amount) {
    if (amount > 0) {
        if (bill->check(op->calculateNetworkCost(amount))) {
            bill->add(op->calculateNetworkCost(amount));
            this->totalInternetUsage += amount;
            op->addTotalInternetUsage(amount);
        }
    }
}

void Customer::pay(double amount) {
            this->bill->pay(amount);
}

#endif
