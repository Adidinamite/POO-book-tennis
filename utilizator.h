#ifndef UTILIZATOR_H
#define UTILIZATOR_H

#include <iostream>
#include <string>

class Utilizator {
private:
    std::string nume;
    std::string interval_orar;
    std::string teren;
public:
    // Constructor
    Utilizator() = default;
    Utilizator(const std::string& nume, const std::string& interval_orar, const std::string& teren)
            : nume(nume), interval_orar(interval_orar), teren(teren) {
        std::cout << "Constructorul pentru " << nume << " a fost apelat.\n";
    }


    Utilizator(const Utilizator& other)
            : nume(other.nume), interval_orar(other.interval_orar), teren(other.teren) {
        std::cout << "Constructorul de copiere pentru " << nume << " a fost apelat.\n";
    }


    ~Utilizator() {
        std::cout << "Destructorul pentru " << nume << " a fost apelat.\n";
    }


    std::string getNume() const {
        return nume;
    }


    void setNume() {
        std::cin>>nume;
    }
    std::string getTeren() const {
        return teren;
    }


    void setTeren() {
        std::cin>>teren;
    }

    std::string getIntervalOrar() const {
        return interval_orar;
    }


    void setIntervalOrar( ) {
        std::cin>>interval_orar;
    }


    friend std::ostream& operator<<(std::ostream& os, const Utilizator& utilizator) {
        os << "Nume: " << utilizator.nume << ", Interval orar: " << utilizator.interval_orar << ", Teren: " << utilizator.teren;
        return os;
    }
};

#endif
