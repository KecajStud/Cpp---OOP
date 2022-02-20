#include "interface.h"

int main() {
    Bank* universe_bank = new Bank();
    auto kupujacy = new Enterprise("kupujacy", 300, 1000);
    auto sprzedajacy = new Kiligoni("sprzedajacy", 1000, 100, 2);
    kupujacy->print_statistics();
    sprzedajacy->print_statistics();
    std::cout<<std::endl<<std::endl;

    std::vector<Seller*> lista_sprzedajacych;
    lista_sprzedajacych.push_back(sprzedajacy);

    kupujacy->buy_dilithium(lista_sprzedajacych, universe_bank, 500);
    kupujacy->print_statistics();
    sprzedajacy->print_statistics();

    return 0;
}
