//
// Created by Jacek on 20.02.2022.
//

#ifndef DILITHIUM_INTERFACE_H
#define DILITHIUM_INTERFACE_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
//#include <pair>

class Seller;
class Buyer;
class Bank; // bedzie miec slownik WOW


///////////// Transaction
class Transaction{
protected:
    Seller* seller;
    Buyer* buyer;
    int quantity;
    int price;
    bool finalized;
public:
    //technical part:
    Transaction() = delete;
    Transaction(Seller*, Buyer*, int, int);
    Transaction (const Transaction&) = delete;
    Transaction& operator=(const Transaction&) = delete;
    ~Transaction() = default;

    void finalize() ;
    int get_quantity() const;
    int get_price() const;
    int get_total_price() const;
};

///////////// Person
class Person{
protected:
    std::string name;
    int dilithium;
    int money;
public:
    //technical part:
    Person() = delete;
    Person(std::string, int, int);
    Person& operator=(const Person&) = delete;
    virtual ~Person() = default;
    void print_statistics();
};

///////////// Buyer
class Buyer: public Person{
protected:
    // attributes
    int needed_dilithium;

    // methods
    bool need_buy(int);
    bool buy_from_seller(Seller*, Bank*);
    virtual bool accept_price(int)=0;
    bool execute_transaction(Transaction*, int, Bank*);
    void deposit_money(Transaction*, Bank*);
    void receive_dilithium(int);

public:
    //technical part:
    Buyer() = delete;
    Buyer(std::string, int, int);
    Buyer(const Buyer&) = delete;
    Buyer& operator=(const Buyer*) = delete;
    ~Buyer() override = default;

    //interface:
    void buy_dilithium(std::vector<Seller*>, Bank*, int);
};

///////////// Enterprise
class Enterprise: public Buyer{
private:
    bool accept_price(int) override;
public:
    Enterprise() = delete;
    Enterprise(std::string, int, int);
    Enterprise(const Buyer&) = delete;
    Enterprise& operator=(const Enterprise*) = delete;
    ~Enterprise() override = default;
};

///////////// Seller
class Seller: public Person{
protected:
    int price;
public:
    //technical part:
    Seller() = delete;
    Seller(std::string, int, int, int);
    Seller(const Seller&) = delete;
    Seller& operator=(const Seller&) = delete;
    ~Seller() = default;

    //methods:
    int get_price() const;
    virtual bool enough_dilithium(int) =0;
    int register_transaction(Transaction*, Bank*);
    void get_earned_money(Transaction*, Bank*);
};


///////////// Kiligoni
class Kiligoni: public Seller{
public:
    //technical part:
    Kiligoni() = delete;
    Kiligoni(std::string, int, int, int);
    Kiligoni(const Kiligoni&) = delete;
    Kiligoni& operator=(const Kiligoni&) = delete;
    ~Kiligoni() override = default;


    bool enough_dilithium(int) override;
};

///////////// Ferengi
class Ferengi: public Seller{
private:
    int price_for_friend;
    std::vector<Ferengi*> friends;
    void internal_transaction(Ferengi*, int);

public:
    //technical part:
    Ferengi() = delete;
    Ferengi(std::string, int, int, int);
    Ferengi(const Kiligoni&) = delete;
    Ferengi& operator=(const Ferengi&) = delete;
    ~Ferengi() override = default;

    void add_friend(Ferengi*);
    bool enough_dilithium(int) override;
};

///////////// Bank
class Bank{
private:
    int current_id;
    std::map<int, Transaction*> current_transactions;
    //std::vector<Transaction*> current_transactions;
    std::vector<Transaction*> archive;
    int dilithium;
    int money;
public:
    //technical part:
    Bank() = default;
    Bank(const Bank&) = delete;
    Bank& operator=(const Bank&) = delete;
    ~Bank();

    //methods:
    int register_transaction(Transaction*); /// receive money
    bool accept_transaction(Transaction*, int);

    void receive_money(Transaction*);
    void receive_dilithium(Transaction*);

    int return_money(Transaction*);
    int return_dilithium(Transaction*);
};

///////////// Universe
class Universe{
private:
    Bank bank;
    std::vector<Person*> seller_list;
    std::vector<Person*> buyer_list;
public:
    Universe() = delete;
    Universe(int, int, int);
    Universe(const Universe&) = delete;
    Universe& operator=( const Universe&) = delete;
    ~Universe();

    void update();
};

#endif //DILITHIUM_INTERFACE_H
