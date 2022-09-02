// =========================================================
// File: vox.h
// Author:
// Date:
// Description:
// =========================================================

#ifndef VOXOPERATOR_H
#define VOXOPERATOR_H

#include "operator.h"

class VoxOperator : public Operator {
public:
    VoxOperator(int, double, double, double, int, OperatorType);

    VoxOperator(const VoxOperator &);

    double calculateTalkingCost(int, int) override;

    double calculateMessageCost(int, int, int) override;

    double calculateNetworkCost(double) override;
};

VoxOperator::VoxOperator(int id, double talkingCharge, double messageCost, double networkCharge, int discountRate,
                         OperatorType type) : Operator(id, talkingCharge, messageCost, networkCharge, discountRate,
                                                       type) {}

VoxOperator::VoxOperator(const VoxOperator &a) : Operator(a) {};

double VoxOperator::calculateTalkingCost(int minute, int age) {
    double amount = 0.0;
    if (minute <= 0 || age <= 0) {
        return amount;
    } else {
        amount += minute * talkingCharge;
        if (age < 18 || age > 65) {
            amount *= (100 - discountRate);
            amount = amount / 100;
        }
    }
    return amount;
}

double VoxOperator::calculateMessageCost(int quantity, int thisOpId, int otherOpId) {
    double amount = 0.0;
    if (quantity <= 0) {
        return amount;
    } else {
        amount += quantity * messageCost;
        if (thisOpId == otherOpId) {
            amount *= (100 - discountRate);
            amount = amount / 100;
        }
    }
    return amount;
}

double VoxOperator::calculateNetworkCost(double amount) {
    if (amount > 0) {
        return amount * networkCharge;
    } else {
        return 0;
    }

}

#endif
