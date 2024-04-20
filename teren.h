#ifndef TEREN_H
#define TEREN_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Teren {
private:
    std::string nume;
    std::string program;
    double pret;
    std::vector<std::string> oreLibere; /// pentru generareOrelibere

public:
    /// Constructor
    Teren(const std::string& nume, const std::string& program, double pret)
            : nume(nume), program(program), pret(pret) {
        generareOreLibere();
    }
    ~Teren() {
        std::cout << "Destructorul pentru " << nume << " a fost apelat.\n";
    }
    void resetOreLibere() {
        this->oreLibere.clear();
    }
    void stergeOra(std::string s) {
        auto it = std::find(oreLibere.begin(), oreLibere.end(), s);
        if (it != oreLibere.end()) {
            this->oreLibere.erase(it);
        }
    }
    ///oreLibere
    void generareOreLibere() {
        resetOreLibere();
        std::string inceputProgram = program.substr(0, 5); /// 10:00
        int inceputOra = std::stoi(inceputProgram.substr(0, 2)); ///10
        int inceputMinut = std::stoi(inceputProgram.substr(3, 2)); /// 00

        std::string sfarsitProgram = program.substr(6, 5); ///12:00
        int sfarsitOra = std::stoi(sfarsitProgram.substr(0, 2)); ///12
        int sfarsitMinut = std::stoi(sfarsitProgram.substr(3, 2)); ///00

        while (inceputOra < sfarsitOra || (inceputOra == sfarsitOra && inceputMinut <= sfarsitMinut)) {
            std::string ora = (inceputOra < 10 ? "0" : "") + std::to_string(inceputOra) + ":" + (inceputMinut < 10 ? "0" : "") + std::to_string(inceputMinut);
            oreLibere.push_back(ora);
            inceputMinut += 30;
            if (inceputMinut >= 60) {
                inceputOra++;
                inceputMinut -= 60;
            }
        }
    }
    void afisareOreLibere() const {
        std::cout << "Ore Libere pentru Terenul " << nume << ":" << std::endl;
        for (const std::string& ora : oreLibere) {
            std::cout << ora << std::endl;
        }
    }
    std::string getNume() const {
        return nume;
    }
    std::string getProgram() const {
        return program;
    }
    double getPret() const {
        return pret;
    }
    std::vector<std::string> getOreLibere() const {
        return oreLibere;
    }

    void setNume(const std::string& nume) {
        this->nume = nume;
    }
    void setProgram(const std::string& program) {
        this->program = program;
        generareOreLibere();
    }
    void setPret(double pret) {
        this->pret = pret;
    }
    friend std::ostream& operator<<(std::ostream& os, const Teren& teren) {
        os << "Nume: " << teren.nume << ", Program: ";
        for (const std::string& ora : teren.oreLibere) {
            os << ora << " ";
        }
        os << ", Pret: " << teren.pret;
        return os;
    }
};

#endif
