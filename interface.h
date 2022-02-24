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
};
const std::string statusName[] = {"registered", "finalized"};
struct Transaction{
    int id;
    Buyer *toWhom;
    Seller *fromWho;
    int cnt;
    int itemPrice;
    TransactionStatus status;

    //constructor and copy constructor:
    Transaction(int id, Buyer *toWhom, Seller *fromWhom, int cnt, int itemPrice, TransactionStatus status);
    Transaction(const Transaction&);
};


class Trader{
private:
    std::string traderName;
    int energyCredit;
    int dilithiumUnits;
    BankOfUniverse& bank;
public:
    std::string name();
    //technical part:
    Trader(std::string traderName, BankOfUniverse &bank, int energyCredit, int dilithiumUnits);
    Trader(const Trader&) = default;
    Trader& operator=(const Trader&) = delete;
    virtual ~Trader() = default; //prawdopodobnie wywyola podstawowy destruktor dla danej klasy, a co z referencja
};










#endif //DILITHIUM_INTERFACE_H
