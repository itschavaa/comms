// =========================================================
// File: operator.h
// Author:
// Date:
// Description:
// =========================================================

#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

typedef enum {
    VOX, INTERNET
} OperatorType;

class Operator {
protected:
    int id, discountRate;
    double talkingCharge, messageCost, networkCharge, totalInternetUsage;
    int totalSpentTalkingTime, totalMessageSent;
    OperatorType type;

public:
    Operator(int, double, double, double, int, OperatorType);

    Operator(const Operator &);

    int getId() const;

    int getDiscountRate() const;

    double getTalkingChage() const;

    double getMessageCost() const;

    double getNetworkCharge() const;

    int getTotalSpentTalkingTime() const;

    int getTotalMessageSent() const;

    double getTotalInternetUsage() const;

    OperatorType getType() const;

    void addTalkingTime(int);

    void addTotalMessageSent(int);

    void addTotalInternetUsage(double);

    string toString() const;

    virtual double calculateTalkingCost(int, int) = 0;

    virtual double calculateMessageCost(int, int, int) = 0;

    virtual double calculateNetworkCost(double) = 0;
};

Operator::Operator(int id, double talkingCharge, double messageCost, double networkCharge, int discountRate,
                   OperatorType type) {
    this->id = id;
    this->talkingCharge = talkingCharge;
    this->messageCost = messageCost;
    this->networkCharge = networkCharge;
    this->discountRate = discountRate;
    this->type = type;
    this->totalSpentTalkingTime = 0.0;
    this->totalMessageSent = 0.0;
    this->totalInternetUsage = 0.0;
}

Operator::Operator(const Operator &a) {
    this->id = a.id;
    this->discountRate = a.discountRate;
    this->talkingCharge = a.talkingCharge;
    this->messageCost = a.messageCost;
    this->networkCharge = a.networkCharge;
    this->totalSpentTalkingTime = a.totalSpentTalkingTime;
    this->totalMessageSent = a.totalMessageSent;
    this->totalInternetUsage = a.totalInternetUsage;
    this->type = a.type;
}

int Operator::getId() const {
    return id;
}

int Operator::getDiscountRate() const {
    return discountRate;
}

double Operator::getTalkingChage() const {
    return talkingCharge;
}

double Operator::getMessageCost() const {
    return messageCost;
}

double Operator::getNetworkCharge() const {
    return networkCharge;
}

double Operator::getTotalInternetUsage() const {
    return totalInternetUsage;
}

int Operator::getTotalSpentTalkingTime() const {
    return totalSpentTalkingTime;
}

int Operator::getTotalMessageSent() const {
    return totalMessageSent;
}

OperatorType Operator::getType() const {
    return type;
}

void Operator::addTalkingTime(int minute) {
    if (minute > 0) {
        this->totalSpentTalkingTime += minute;
    }
}

void Operator::addTotalMessageSent(int quantity) {
    if (quantity > 0) {
        this->totalMessageSent += quantity;
    }
}

void Operator::addTotalInternetUsage(double amount) {
    if (amount > 0) {
        this->totalInternetUsage += amount;
    }
}

string Operator::toString() const {
    stringstream aux;
    aux << "Operator " << fixed << setprecision(2) << getId() << ": " << getTotalSpentTalkingTime() << " "
        << getTotalMessageSent() << " "<< getTotalInternetUsage();
    return aux.str();
}

#endif
