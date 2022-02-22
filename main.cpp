#include "interface.h"

int main() {
    srand(time(NULL));
//    Bank* universe_bank = new Bank();
//    auto kupujacy = new Enterprise("kupujacy", 300, 1000);
//    auto sprzedajacy = new Kiligoni("sprzedajacy zwykly", 100, 100, 2);
//    auto ferengi1 = new Ferengi("Pierwszy Ferengi", 100, 100,2);
//    auto ferengi2 = new Ferengi("Drugi Ferengi", 2000, 1000, 2);
//
//    ferengi1->add_friend(ferengi2);
//    ferengi2->add_friend(ferengi1);
//
//
//
//    kupujacy->print_statistics();
////    sprzedajacy->print_statistics();
//    ferengi1->print_statistics();
//    ferengi2->print_statistics();
//    std::cout<<std::endl<<std::endl;
//
//    std::vector<Seller*> lista_sprzedajacych;
//    lista_sprzedajacych.push_back(ferengi1);
//
//    lista_sprzedajacych.push_back(ferengi2);
//    lista_sprzedajacych.push_back(sprzedajacy);
//
//    kupujacy->buy_dilithium(lista_sprzedajacych, universe_bank, 500);
//    kupujacy->print_statistics();
//    ferengi1->print_statistics();
//    ferengi2->print_statistics();
////    sprzedajacy->print_statistics();


//    int ferengi = 0;
//
//    std::vector<Ferengi*> friends;
//    std::vector<Ferengi*> seller_list;
//    for (int i=0;i<10;i++){
//        auto new_ferengi = new Ferengi("Sprzedajacy_Ferengi"+ std::to_string(ferengi++), rand()%10 * 100 + 100, rand()%10 * 100 + 100, rand()%3+1);
//        seller_list.push_back(new_ferengi);
//        friends.push_back(new_ferengi);
//
//    }
//
//    for(int i=0;i<ferengi;i++) {
//        int multiplier = i / 3;
//        for (int j = multiplier * 3; j<ferengi && j < multiplier * 3 + 3; j++){
//            if (i != j) friends[i]->add_friend(friends[j]);
//        }
//    }
//    for(auto ferengi_friends: friends) ferengi_friends->print_friends();

    Universe universe(2,8,5);
    universe.update();

    return 0;
}
