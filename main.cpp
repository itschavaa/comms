// =========================================================
// File: main.cpp
// Author:
// Date:
// Description:
// To compile: g++ -std=c++11 main.cpp -o app
// To execute: ./app input_file output_file
// =========================================================
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "bill.h"
#include "operator.h"
#include "vox.h"
#include "internet.h"
#include "customer.h"

using namespace std;

int main(int argc, char *argv[]) {
    ifstream inputFile;
    ofstream outputFile;
    int C, O, N, query, age, operatorId, type, discountRate, idCustomer1, idCustomer2, time, quantity, idCustomer, idOperator;
    double limitingAmount, talkingCharge, messageCost, networkCharge, amount;
    int  idOp = 0, idCus = 0;;
    Customer *mayorTalk, *mayorMessage, *mayorInternet;
    string name;
    vector<Customer *> customers;
    vector<Operator *> operators;
    if (argc != 3) {
        cout << "usage: " << argv[0] << " input_file output_file" << endl;
        return -1;
    }
    inputFile.open(argv[1]);
    if (!inputFile.is_open()) {
        cout << argv[0] << " : File\"" << argv[1] << "\" not found" << endl;
        return -1;
    }
    outputFile.open(argv[2]);
    inputFile >> C >> O >> N;
    customers.resize(C);
    operators.resize(O);
    for (int i = 1; i <= N; i++) {
        inputFile >> query;
        switch (query) {
            case 1:
                inputFile >> name >> age >> operatorId >> limitingAmount;
                customers[idCus] = new Customer(idCus, name, age, operators[operatorId], limitingAmount);
                idCus++;
                break;
            case 2:
                inputFile >> type >> talkingCharge >> messageCost >> networkCharge >> discountRate;
                if (type == 1) {
                    operators[idOp] = new VoxOperator(idOp, talkingCharge, messageCost, networkCharge, discountRate,
                                                      VOX);
                    idOp++;
                } else if (type == 2) {
                    operators[idOp] = new InternetOperator(idOp, talkingCharge, messageCost, networkCharge,
                                                           discountRate, INTERNET);
                    idOp++;
                }
                break;
            case 3:
                inputFile >> idCustomer1 >> idCustomer2 >> time;
                customers[idCustomer1]->talk(time, *customers[idCustomer2]);
                break;
            case 4:
                inputFile >> idCustomer1 >> idCustomer2 >> quantity;
                customers[idCustomer1]->message(quantity, *customers[idCustomer2]);
                break;
            case 5:
                inputFile >> idCustomer >> amount;
                customers[idCustomer]->connection(amount);
                break;
            case 6:
                inputFile >> idCustomer >> amount;
                customers[idCustomer]->pay(amount);
                break;
            case 7:
                inputFile >> idCustomer >> idOperator;
                customers[idCustomer]->setOperator(operators[idOperator]);
                break;
            case 8:
                inputFile >> idCustomer >> amount;
                customers[idCustomer]->getBill()->changeTheLimit(amount);
                break;
        }
    }

    for (Operator *optr: operators) {
        outputFile << optr->toString() << endl;
    }
    for (Customer *cstmr: customers) {
        outputFile << cstmr->toString() << endl;
    }
    mayorTalk = customers[0];
    mayorInternet = customers[0];
    mayorMessage = customers[0];
    for (Customer *cstmr: customers) {
        if (cstmr->getTotalSpentTalkingTime() > mayorTalk->getTotalSpentTalkingTime()) {
            mayorTalk = cstmr;
        }
        if (cstmr->getTotalSpentTalkingTime() == mayorTalk->getTotalSpentTalkingTime()) {
            if (cstmr->getId() < mayorTalk->getId()) {
                mayorTalk = cstmr;
            }
        }
    }
    for (Customer *cstmr0: customers) {
        if (cstmr0->getTotalMessageSent() > mayorMessage->getTotalMessageSent()) {
            mayorMessage = cstmr0;
        }
        if (cstmr0->getTotalMessageSent() == mayorMessage->getTotalMessageSent()) {
            if (cstmr0->getId() < mayorMessage->getId()) {
                mayorMessage = cstmr0;
            }
        }
    }
    for (Customer *cstmr: customers) {
        if (cstmr->getTotalInternetUsage() > mayorInternet->getTotalInternetUsage()) {
            mayorInternet = cstmr;
        }
        if (cstmr->getTotalInternetUsage() == mayorInternet->getTotalInternetUsage()) {
            if (cstmr->getId() < mayorInternet->getId()) {
                mayorInternet = cstmr;
            }
        }
    }
    outputFile << mayorTalk->getName() << ": " << mayorTalk->getTotalSpentTalkingTime() << endl;
    outputFile << mayorMessage->getName() << ": " << mayorMessage->getTotalMessageSent() << endl;
    outputFile << fixed << setprecision(2) << mayorInternet->getName() << ": " << mayorInternet->getTotalInternetUsage()
               << endl;

    inputFile.close();
    outputFile.close();
    return 0;
}
