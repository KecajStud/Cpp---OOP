//
// Created by Jacek on 20.02.2022.
//
#include "interface.h"

/////////////////////////////////////////////////////////////////////////////////////////////
///////////// Implementation

///////////// Transaction
Transaction::Transaction(int id, Buyer *toWhom, Seller *fromWhom, int cnt, int itemPrice, TransactionStatus status):
        id(id), toWhom(toWhom), fromWho(fromWhom), cnt(cnt), itemPrice(itemPrice), status(status){}
Transaction::Transaction(const Transaction &tr): Transaction(tr.id, tr.toWhom, tr.fromWho, tr.cnt, tr.itemPrice, tr.status) {}

///////////// Trader
Trader::Trader(std::string traderName, BankOfUniverse &bank, int energyCredit, int dilithiumUnits):
        traderName(std::move(traderName)), bank(bank), energyCredit(energyCredit), dilithiumUnits(dilithiumUnits) {}

///////////// Seller: public Trader
int Seller::getPrice() {return this->dilithiumPrice;}
int Seller::sell(Buyer *toWhom, int cnt){
    if(!acquire(cnt))
        return -2;
    else
        return bank.registerTransaction(this, toWhom, cnt, this->dilithiumPrice);
}

///////////// Buyer: public Trader
Buyer::Buyer(std::string traderName, BankOfUniverse &bank, int energyCredit=0, int dilithiumUnits=0): Trader(traderName, bank, energyCredit, dilithiumUnits){};

Buyer::Buyer(const Buyer &b): Buyer(b.traderName, b.bank, b.energyCredit, b.dilithiumUnits) {}





















