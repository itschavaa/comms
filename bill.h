// =========================================================
// File: bill.h
// Author: Salvador Rodriguez Paredes
// Date: 24/05/2022
// Description:
// =========================================================

#ifndef BILL_H
#define BILL_H

class Bill {
private:
    double limitAmount, currentDebt, totalMoneySpent;

public:
    Bill();

    Bill(double);

    Bill(const Bill &);

    double getLimitAmount() const;

    double getCurrentDebt() const;

    double getTotalMoneySpent() const;

    void add(double);

    void pay(double);

    void changeTheLimit(double);

    bool check(double) const;
};

Bill::Bill() {
    limitAmount = 0;
    currentDebt = 0;
    totalMoneySpent = 0;
}

Bill::Bill(double limitAmount) {
    if (limitAmount <= 0) {
        this->limitAmount = 0;
    } else if (limitAmount > 0) {
        this->limitAmount = limitAmount;
    }
    currentDebt = 0;
    totalMoneySpent = 0;
}

Bill::Bill(const Bill &a) {
    limitAmount = a.limitAmount;
    currentDebt = a.currentDebt;
    totalMoneySpent = a.totalMoneySpent;
}

double Bill::getLimitAmount() const {
    return limitAmount;
}

double Bill::getCurrentDebt() const {
    return currentDebt;
}

double Bill::getTotalMoneySpent() const {
    return totalMoneySpent;
}

void Bill::add(double amount) {
    if (amount > 0) {
       currentDebt += amount;
    }
}

void Bill::pay(double amount) {
    if (amount > 0) {
        if (amount <= currentDebt) {
            currentDebt -= amount;
            totalMoneySpent += amount;
        } else {
            totalMoneySpent += currentDebt;
            currentDebt = 0;

        }
    }
}


void Bill::changeTheLimit(double amount) {
    if (amount > currentDebt && amount > 0) {
        limitAmount = amount;
    }
}

bool Bill::check(double amount) const {
    return (currentDebt + amount) < limitAmount;
}

#endif
