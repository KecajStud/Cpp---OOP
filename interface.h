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
protected:
    std::string traderName;
    int energyCredit;
    int dilithiumUnits;
    BankOfUniverse& bank;
public:
    std::string name();
    //technical part:
    Trader(std::string traderName, BankOfUniverse &bank, int energyCredit=0, int dilithiumUnits=0);
    Trader(const Trader&) = default;
    Trader& operator=(const Trader&) = delete;
    virtual ~Trader() = default; //prawdopodobnie wywyola podstawowy destruktor dla danej klasy, a co z referencja
};

class Seller: public Trader{
protected:
    int dilithiumPrice;
    virtual int giveDilithium(int cnt);
public:
    virtual int getPrice();
    virtual bool acquire(int cnt)=0;
    virtual int sell(Buyer* toWhom, int cnt);
    virtual void takeCredit(int amount);
    //technical part:
    Seller(std::string traderName, BankOfUniverse &bank, int energyCredit, int dilithiumUnits=0, int dilithiumPrice=0):
            Trader(traderName, bank, energyCredit, dilithiumUnits), dilithiumPrice (dilithiumPrice){};
    Seller(const Seller&) = default;
    Seller& operator=(const Seller&) = delete;
    ~Seller() = default;
    friend BankOfUniverse; //oho mamy przyjaciela -> bank moze korzystac z metod sprzedawcy?? ocb
};







#endif //DILITHIUM_INTERFACE_H
