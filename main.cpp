#include <iostream>
#include <string>
#include <vector>
#include <map>

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
    ~Seller() override = default;

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
Bank::~Bank() {
    for(auto current: current_transactions) delete current.second;
    for(auto archived: archive) delete archived;
}

int Bank::register_transaction(Transaction * transaction) {
    this->current_transactions[++current_id] = transaction;
    this->dilithium += transaction->get_quantity();
    return this->current_id;
}

bool Bank::accept_transaction(Transaction * transaction, int id) {
    Transaction* transaction_to_accept = current_transactions[id];
    if(transaction_to_accept != transaction) return false;
    current_transactions.erase(id);
    archive.push_back(transaction);
    return true;
}

void Bank::receive_money(Transaction * transaction) {
    this->money += transaction->get_total_price();
}

void Bank::receive_dilithium(Transaction * transaction) {
    this->dilithium += transaction->get_quantity();
}

int Bank::return_money(Transaction * transaction) {
    int total_price = transaction->get_total_price();
    this->money -= total_price;
    return total_price;
}

int Bank::return_dilithium(Transaction *transaction) {
    int dilithium_to_return = transaction->get_quantity();
    this->dilithium -= dilithium_to_return;
    return dilithium_to_return;
}


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



/////////////////////////////////////////////////////////////////////////////////////////////
///////////// Implementation

///////////// Transaction
Transaction::Transaction(Seller *_seller, Buyer *_buyer, int _quantity, int _price):
        seller(_seller), buyer(_buyer), quantity(_quantity), price(_price), finalized(false) {}

void Transaction::finalize() {finalized = true;}

int Transaction::get_quantity() const {return quantity;}

int Transaction::get_price() const {return price;}

int Transaction::get_total_price() const {
    return quantity*price;
}

///////////// Person
Person::Person(std::string _name, int _dilithium, int _money):
        name(_name), dilithium(_dilithium), money(_money){}

///////////// Buyer
Buyer::Buyer(std::string _name, int _dilithium, int _money):
        Person(_name, _dilithium, _money), needed_dilithium(0){};

bool Buyer::need_buy(int limit) {
    if(this->dilithium < limit) {
        this->needed_dilithium = limit - this->dilithium;
        return true;
    }
    else return false;
}

bool Buyer::buy_from_seller(Seller *seller, Bank *bank) {
    int price = seller->get_price();
    if(!this->accept_price(price) || !seller->enough_dilithium(this->needed_dilithium))
        return false;

    auto transaction = new Transaction(seller, this, this->needed_dilithium, price);
    int id = seller->register_transaction(transaction, bank); //sprzedawca zostawia dilithium w banku
    this->deposit_money(transaction, bank);

    if(!this->execute_transaction(transaction, id, bank))
        return false;

    //seller->get_earned_money(transaction, bank);  //tutaj w banku jeszcze bede musial zmienic;
    return true;
}
//this->needed_dilithium * price
void Buyer::deposit_money(Transaction* transaction, Bank *bank) {
    this->money -= transaction->get_total_price();
    bank->receive_money(transaction);
}

void Buyer::receive_dilithium(int quantity) {
    this->dilithium += quantity;
}

bool Buyer::execute_transaction(Transaction* transaction, int id, Bank* bank){
    if(!bank->accept_transaction(transaction, id))
        return false;
    this->dilithium += transaction->get_quantity();
    bank->return_dilithium(transaction);
    return true;
}

void Buyer::buy_dilithium(std::vector<Seller *> sellers, Bank* bank, int limit ) {
    if(!this->need_buy(limit))
        return;
    bool success = false;
    for(int i=0; i<sellers.size() && !success;i++)
        success = this->buy_from_seller(sellers[i],  bank);

    if (success)
        std::cout<<this->name<<" zakupil: "<<this->needed_dilithium<<" dilithium."<<std::endl;

}

///////////// Enterprise
Enterprise::Enterprise(std::string _name, int _dilithium, int _money):
        Buyer(_name, _dilithium, _money){};

bool Enterprise::accept_price(int price) {
    return this->needed_dilithium * price < this->money;};

///////////// Seller
int Seller::register_transaction(Transaction *transaction, Bank *bank) {
    this->dilithium -= transaction->get_quantity();

    return bank->register_transaction(transaction);
}

void Seller::get_earned_money(Transaction *transaction, Bank *bank) {
    int earning = bank->return_money(transaction);
    this->money += money;
}

Seller::Seller(std::string _name, int _dilithium, int _money, int _price):
        Person(_name, _dilithium, _money), price(_price){};

int Seller::get_price() const {
    return price;
}

///////////// Kiligoni
Kiligoni::Kiligoni(std::string _name, int _dilithium, int _money, int _price):
        Seller(_name, _dilithium, _money, _price){};

bool Kiligoni::enough_dilithium(int quntity) {
    return quntity <= this->dilithium;
}

///////////// Ferengi
Ferengi::Ferengi(std::string _name, int _dilithium, int _money, int _price):
        Seller(_name, _dilithium, _money, _price), friends(), price_for_friend(0){};

void Ferengi::add_friend(Ferengi *firend) {
    friends.push_back(firend);};

void Ferengi::internal_transaction(Ferengi * friend_seller, int quantity) {
    if(quantity > friend_seller->dilithium) quantity = friend_seller->dilithium;
    if(quantity * friend_seller->price_for_friend > this->money) quantity = this->money / friend_seller->price_for_friend;

    int total_price = quantity * friend_seller->price_for_friend;
    this->dilithium += quantity;
    friend_seller->dilithium -= quantity;
    this->money -= total_price;
    friend_seller->money = total_price;
}

bool Ferengi::enough_dilithium(int quantity){
    for(int i=0;this->dilithium<quantity && i<friends.size();){
        this->internal_transaction(friends[i],quantity);
    }
    return quantity < this->dilithium;
}

///////////// Bank


int main() {
//    Bank bank_of_universe();


    return 0;
}
