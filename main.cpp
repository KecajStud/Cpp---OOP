#include "interface.h"

int main() {
    Bank* universe_bank = new Bank();
    auto kupujacy = new Enterprise("kupujacy", 300, 1000);
    auto sprzedajacy = new Kiligoni("sprzedajacy zwykly", 100, 100, 2);
    auto ferengi1 = new Ferengi("Pierwszy Ferengi", 100, 100,2);
    auto ferengi2 = new Ferengi("Drugi Ferengi", 2000, 1000, 2);

    ferengi1->add_friend(ferengi2);
    ferengi2->add_friend(ferengi1);



    kupujacy->print_statistics();
//    sprzedajacy->print_statistics();
    ferengi1->print_statistics();
    ferengi2->print_statistics();
    std::cout<<std::endl<<std::endl;

    std::vector<Seller*> lista_sprzedajacych;
    lista_sprzedajacych.push_back(ferengi1);

    lista_sprzedajacych.push_back(ferengi2);
    lista_sprzedajacych.push_back(sprzedajacy);

    kupujacy->buy_dilithium(lista_sprzedajacych, universe_bank, 500);
    kupujacy->print_statistics();
    ferengi1->print_statistics();
    ferengi2->print_statistics();
//    sprzedajacy->print_statistics();

    return 0;
}
