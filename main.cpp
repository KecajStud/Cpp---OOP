#include <iostream>
#include <string>
#include <vector>

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
    int get_quntity() const;
    int get_price() const;
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
    void deposit_money(int, Bank*);
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
private:
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

Seller::Seller(std::string _name, int _dilithium, int _money, int _price):
        Person(_name, _dilithium, _money), price(_price){};

int Seller::get_price() const {
    return price;
}









///////////// Kiligoni
class Kiligoni: public Seller{
    bool enough_dilithium(int ) override;
};

///////////// Ferengi
class Ferengi: public Seller{
private:
    int price_for_friend;
    std::vector<Ferengi*> friends;
    void internal_transaction(Ferengi*, int, int);
public:
    bool enough_dilithium() override;
};

///////////// Bank
class Bank{
private:
    std::vector<Transaction> current_transactions;
    std::vector<Transaction> archive;
    int dilithium;
    int money;
public:
    //technical part:
    Bank() = default;
    Bank(const Bank&) = delete;
    Bank& operator=(const Bank&) = delete;
    ~Bank();

    //methods:
    int register_transaction(Transaction*);
    bool accept_transaction(Transaction*, int id);

    void receive_money(int);
    void receive_dilithium(int);

    void return_money(int);
    void return_dilithium(int);
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


/////////////////////////////////////////////////////////////////////////////////////////////
///////////// Implementation

///////////// Transaction
Transaction::Transaction(Seller *_seller, Buyer *_buyer, int _quantity, int _price):
        seller(_seller), buyer(_buyer), quantity(_quantity), price(_price), finalized(false) {}

void Transaction::finalize() {finalized = true;}

int Transaction::get_quntity() const {return quantity;}

int Transaction::get_price() const {return price;}

///////////// Person
Person::Person(std::string _name, int _dilithium, int _money):
        name(_name), dilithium(_dilithium), money(_money){}

///////////// Buyer
Buyer::Buyer(std::string _name, int _dilithium, int _money):
        Person(_name, _dilithium, _money){};

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
    this->deposit_money(this->needed_dilithium * price, bank);

    if(!this->execute_transaction(transaction, id, bank))
        return false;

    //seller->get_earned_money(transaction, bank);  //tutaj w banku jeszcze bede musial zmienic;
    return true;
}

void Buyer::deposit_money(int cost, Bank *bank) {
    this->money -= cost;
    bank->receive_money(cost);
}

void Buyer::receive_dilithium(int quantity) {
    this->dilithium += quantity;
}

bool Buyer::execute_transaction(Transaction* transaction, int id, Bank* bank){
    if(!bank->accept_transaction(transaction, id))
        return false;
    int quantity = transaction->get_quntity();
    this->dilithium += quantity;
    bank->return_dilithium(quantity);
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

bool Enterprise::accept_price(int price) {return this->needed_dilithium * price < this->money;};






int main() {
//    Bank bank_of_universe();


    return 0;
}
