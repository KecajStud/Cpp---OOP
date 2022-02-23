//
// Created by Jacek on 20.02.2022.
//

#ifndef DILITHIUM_INTERFACE_H
#define DILITHIUM_INTERFACE_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <time.h>

/////////////////////////////////////////////////////////////////////////////////////////////
///////////// Interface

///////////// Class announcements

class Buyer;
class Seller;
class BankOfUniverse;

///////////// Transaction

enum class TransactionStatus{
    registered, finalized
}
const std::string statusName[] = {"registered", "finalized"};
struct Transaction{
    int id;
    Buyer *toWhom;
    Seller *fromWho;
    int cnt;
    int itemPrice;
    TransactionStatus status;

    //constructor and copy constructor:
    Transaction(int id, Buyer *toWhom, Seller *fromWhom, int cnt, int itemPrice, int TransactionStatus status);
    Transaction(const Transaction&);
};


#endif //DILITHIUM_INTERFACE_H
