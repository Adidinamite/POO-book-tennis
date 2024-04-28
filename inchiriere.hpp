#ifndef INCHIRIERE_HPP
#define INCHIRIERE_HPP

#include <iostream>
#include <vector>
#include "utilizator.hpp"
class Inchiriere {
private:
    Utilizator utilizator;
public:
    Inchiriere(const Utilizator& utilizator)
            : utilizator(utilizator) {}
    friend std::ostream& operator<<(std::ostream& os, const Inchiriere& inchiriere);
};

std::ostream& operator<<(std::ostream& os, const Inchiriere& inchiriere) {
    os << "Detalii Inchiriere: " << inchiriere.utilizator;
    return os;
}
#endif