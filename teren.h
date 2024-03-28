#ifndef TEREN_H
#define TEREN_H

#include <iostream>
#include <string>
#include <vector>
#include "templates.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Teren {
private:
    std::string nume;
    std::string program;
    double pret;
    std::vector<std::string> oreLibere;

    std::string inceputProgram;
    int inceputOra;
    int inceputMinut;
    std::string sfarsitProgram;
    int sfarsitOra;
    int sfarsitMinut;

public:
    Teren(const std::string& nume, const std::string& program, double pret)
            : nume(nume), program(program), pret(pret) {
        generareOreLibere();
    }

    ~Teren() {
        std::cout << "Destructorul pentru " << nume << " a fost apelat.\n";
    }

    void resetOreLibere() {
        oreLibere.clear();
        generareOreLibere();
    }

    void stergeOra(const std::string& s) {
        auto it = std::find(oreLibere.begin(), oreLibere.end(), s);
        if (it != oreLibere.end()) {
            oreLibere.erase(it);
        }
    }

    void generareOreLibere() {
        oreLibere.clear();
        std::string inceputProgram = getProgram().substr(0, 5); // 10:00
        setInceputProgram(inceputProgram);
        setInceputOra(std::stoi(getInceputProgram().substr(0, 2))); // 10
        setInceputMinut(std::stoi(getInceputProgram().substr(3, 2))); // 00

        std::string sfarsitProgram = getProgram().substr(6, 5); // 12:00
        setSfarsitProgram(sfarsitProgram);
        setSfarsitOra(std::stoi(getSfarsitProgram().substr(0, 2))); // 12
        setSfarsitMinut(std::stoi(getSfarsitProgram().substr(3, 2))); // 00

        while (getInceputOra() < getSfarsitOra() || (getInceputOra() == getSfarsitOra() && getInceputMinut() <= getSfarsitMinut())) {
            std::string ora = (getInceputOra() < 10 ? "0" : "") + std::to_string(getInceputOra()) + ":" +
                              (getInceputMinut() < 10 ? "0" : "") + std::to_string(getInceputMinut());
            oreLibere.push_back(ora);
            setInceputMinut(getInceputMinut() + 30);
            if (getInceputMinut() >= 60) {
                setInceputOra(getInceputOra() + 1);
                setInceputMinut(getInceputMinut() - 60);
            }
        }
    }


    /*void afisareOreLibere() const {
        std::cout << "Ore Libere pentru Terenul " << nume << ":\n";
        for (const std::string& ora : oreLibere) {
            std::cout << ora << std::endl;
        }
    }*/

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

    // Getteri și setteri pentru variabilele adăugate

    std::string getInceputProgram() const {
        return inceputProgram;
    }

    void setInceputProgram(const std::string& inceputProgram) {
        this->inceputProgram = inceputProgram;
    }

    int getInceputOra() const {
        return inceputOra;
    }

    void setInceputOra(int inceputOra) {
        this->inceputOra = inceputOra;
    }

    int getInceputMinut() const {
        return inceputMinut;
    }

    void setInceputMinut(int inceputMinut) {
        this->inceputMinut = inceputMinut;
    }

    std::string getSfarsitProgram() const {
        return sfarsitProgram;
    }

    void setSfarsitProgram(const std::string& sfarsitProgram) {
        this->sfarsitProgram = sfarsitProgram;
    }

    int getSfarsitOra() const {
        return sfarsitOra;
    }

    void setSfarsitOra(int sfarsitOra) {
        this->sfarsitOra = sfarsitOra;
    }

    int getSfarsitMinut() const {
        return sfarsitMinut;
    }

    void setSfarsitMinut(int sfarsitMinut) {
        this->sfarsitMinut = sfarsitMinut;
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
