#include <iostream>

#include "Teenus.hpp"

int main(int argc, char const *argv[]) {
    auto serv = new Teenus("test");
    auto serv2 = new Teenus("test2", 0, 23);
    auto serv3 = new Teenus("test3", "R-E", 9, 17);
    std::cout << serv->nimi() << " " << serv->tunnid() << std::endl;
    std::cout << serv2->nimi() << " " << serv2->tunnid() << std::endl;
    std::cout << serv3->nimi() << " " << serv3->tunnid() << std::endl;
    std::cout << serv3->nimi() << " " << (serv3->onavatud() ? "open" : "closed") << std::endl;
    serv3->paev('P', 23, 4);
    std::cout << serv3->nimi() << " " << serv3->tunnid() << std::endl;
    std::cout << "static cast " << static_cast<Day>('U');
    return 0;
}
