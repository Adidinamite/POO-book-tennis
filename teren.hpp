#ifndef TEREN_HPP
#define TEREN_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Teren {
private:
    std::string nume;
    std::string program;
    double pret;
    std::vector<std::string> oreLibere;
    static int numarTerenuri;

    void generareOreLibere() {
        resetOreLibere();
        std::string inceputProgram = program.substr(0, 5);
        int inceputOra = std::stoi(inceputProgram.substr(0, 2));
        int inceputMinut = std::stoi(inceputProgram.substr(3, 2));

        std::string sfarsitProgram = program.substr(6, 5);
        int sfarsitOra = std::stoi(sfarsitProgram.substr(0, 2));
        int sfarsitMinut = std::stoi(sfarsitProgram.substr(3, 2));

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

    void resetOreLibere() {
        this->oreLibere.clear();
    }

public:
    Teren(const std::string& nume, const std::string& program, double pret)
            : nume(nume), program(program), pret(pret) {
        generareOreLibere();
        ++numarTerenuri;
    }

    ~Teren() {
        std::cout << "Destructorul pentru " << nume << " a fost apelat.\n";
        --numarTerenuri;
    }

    Teren& operator=(const Teren& other) {
        if (this != &other) {
            this->nume = other.nume;
            this->program = other.program;
            this->pret = other.pret;
            this->oreLibere = other.oreLibere;
        }
        return *this;
    }

    void stergeOra(std::string s) {
        auto it = std::find(oreLibere.begin(), oreLibere.end(), s);
        if (it != oreLibere.end()) {
            this->oreLibere.erase(it);
        }
    }

    void afisareOreLibere() const {
        std::cout << "Ore Libere pentru Terenul " << nume << ":\n";
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

    virtual void afisareDetalii(std::ostream& os) const {
        os << "Nume: " << nume << ", Program: ";
        for (const std::string& ora : oreLibere) {
            os << ora << " ";
        }
        os << ", Pret: " << pret;
    }

    static int getNumarTerenuri() {
        return numarTerenuri;
    }
};


int Teren::numarTerenuri = 0;

class TerenTenisExterior : public Teren {
private:
    std::string tipSuprafata;
    bool sistemIrigare;

public:
    TerenTenisExterior(const std::string& nume, const std::string& program, double pret, const std::string& tipSuprafata, bool sistemIrigare)
            : Teren(nume, program, pret), tipSuprafata(tipSuprafata), sistemIrigare(sistemIrigare) {
    }
    void afisareDetalii(std::ostream& os) const override {
        Teren::afisareDetalii(os);
        os << ", Tip Suprafata: " << tipSuprafata << ", Sistem Irigare: " << (sistemIrigare ? "Da" : "Nu");
    }
};

class TerenTenisInterior : public Teren {
private:
    std::string tipAcoperis;
    std::string tipPardoseala;

public:
    TerenTenisInterior(const std::string& nume, const std::string& program, double pret, const std::string& tipAcoperis, const std::string& tipPardoseala)
            : Teren(nume, program, pret), tipAcoperis(tipAcoperis), tipPardoseala(tipPardoseala) {
    }

    void afisareDetalii(std::ostream& os) const override {
        Teren::afisareDetalii(os);
        os << ", Tip Acoperis: " << tipAcoperis << ", Tip Pardoseala: " << tipPardoseala;
    }
};

class TerenTenisCuInstructor : public Teren {
private:
    std::string numeInstructor;
    double taxaInstruire;

public:
    TerenTenisCuInstructor(const std::string& nume, const std::string& program, double pret, const std::string& numeInstructor, double taxaInstruire)
            : Teren(nume, program, pret), numeInstructor(numeInstructor), taxaInstruire(taxaInstruire) {
    }

    void afisareDetalii(std::ostream& os) const override {
        Teren::afisareDetalii(os);
        os << ", Nume Instructor: " << numeInstructor << ", Taxa Instruire: " << taxaInstruire;
    }
};

#endif
