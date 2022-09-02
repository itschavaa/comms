// =========================================================
// File: vox.h
// Author:
// Date:
// Description:
// =========================================================

#ifndef InternetOperator_H
#define InternetOperator_H

#include "operator.h"

class InternetOperator : public Operator {
private:
    const double LIMITGB = 1.0;

public:
    InternetOperator(int, double, double, double, int, OperatorType);

    InternetOperator(const InternetOperator &);

    double calculateTalkingCost(int, int);

    double calculateMessageCost(int, int, int);

    double calculateNetworkCost(double);
};

InternetOperator::InternetOperator(int id, double talkingCharge, double messageCost, double networkCharge,
                                   int discountRate, OperatorType type) : Operator(id, talkingCharge, messageCost,
                                                                                   networkCharge, discountRate, type) {}

InternetOperator::InternetOperator(const InternetOperator &copy) : Operator(copy) {}

double InternetOperator::calculateTalkingCost(int minute, int age) {
    double amount = 0.0;
    if (minute <= 0 || age <= 0) {
        return amount;
    } else {
        amount = minute * talkingCharge;
        if (minute < 2) {
            amount *= (100 - discountRate);
            amount = amount / 100;
        }
    };
    return amount;
}

double InternetOperator::calculateMessageCost(int quantity, int thisOpId, int otherOpId) {
    double amount = 0.0;
    if (quantity <= 0) {
        return amount;
    } else {
        amount = quantity * messageCost;
        if (quantity < 3) {
            amount *= (100 - discountRate);
            amount = amount / 100;
        }
    }
    return amount;
}

double InternetOperator::calculateNetworkCost(double amount) {
    double cost = 0.0;
    if (amount <= 0) {
        return cost;
    } else if (amount > LIMITGB) {
        cost = (amount - LIMITGB) * networkCharge;
        return cost;
    } else {
        return cost;
    }
}


#endif
