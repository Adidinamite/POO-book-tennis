#ifndef UTILIZATOR_HPP
#define UTILIZATOR_HPP

#include <iostream>
#include <string>

class Utilizator {
private:
    static int numarUtilizatori;
    std::string nume;
    std::string interval_orar;
    std::string teren;

public:
    // Constructori
    Utilizator() = default;
    Utilizator(const std::string& nume, const std::string& interval_orar, const std::string& teren)
            : nume(nume), interval_orar(interval_orar), teren(teren) {
        ++numarUtilizatori;
        std::cout << "Constructorul pentru " << nume << " a fost apelat.\n";
    }

    Utilizator(const Utilizator& other)
            : nume(other.nume), interval_orar(other.interval_orar), teren(other.teren) {
        ++numarUtilizatori;
        std::cout << "Constructorul de copiere pentru " << nume << " a fost apelat.\n";
    }

    ~Utilizator() {
        --numarUtilizatori;
        std::cout << "Destructorul pentru " << nume << " a fost apelat.\n";
    }


    Utilizator& operator=(const Utilizator& other) {
        if (this != &other) {
            nume = other.nume;
            interval_orar = other.interval_orar;
            teren = other.teren;
        }
        return *this;
    }

    std::string getNume() const {
        return nume;
    }

    void setNume() {
        std::cin >> nume;
    }

    std::string getTeren() const {
        return teren;
    }

    void setTeren() {
        std::cin >> teren;
    }

    std::string getIntervalOrar() const {
        return interval_orar;
    }

    void setIntervalOrar() {
        std::cin >> interval_orar;
    }

    static int getNumarUtilizatori() {
        return numarUtilizatori;
    }

    friend std::ostream& operator<<(std::ostream& os, const Utilizator& utilizator) {
        os << "Nume: " << utilizator.nume << ", Interval orar: " << utilizator.interval_orar << ", Teren: " << utilizator.teren;
        return os;
    }
};

#endif
