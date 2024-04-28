#include <iostream>
#include <string>
#include <vector>
#include "utilizator.hpp"
#include "teren.hpp"
#include "templates.hpp"
#include "inchiriere.hpp"
#include <memory>
#include <utility>


int Utilizator::numarUtilizatori = 0;

class Menu {
private:
    std::vector<std::unique_ptr<Teren>> terenuri;
    bool gasitTeren = false;
    int optiune;
    std::string numeTeren, programTeren;
    double pretTeren;
    std::vector<Inchiriere> inchirieri;
    std::vector<std::string> oreOcupate;
    std::string tipTeren;

    void prelucreazaOre(const std::string& interval) {
        oreOcupate.clear();
        size_t separator = interval.find('-');
        std::string start_time_str = interval.substr(0, separator);
        std::string end_time_str = interval.substr(separator + 1);
        int start_hour = std::stoi(start_time_str.substr(0, 2));
        int start_minute = std::stoi(start_time_str.substr(3, 2));
        int end_hour = std::stoi(end_time_str.substr(0, 2));
        int end_minute = std::stoi(end_time_str.substr(3, 2));
        int total_start_minutes = start_hour * 60 + start_minute;
        for (int total_minutes = total_start_minutes; total_minutes < end_hour * 60 + end_minute; total_minutes += 30) {
            oreOcupate.push_back(std::to_string(total_minutes / 60) + ":" + (total_minutes % 60 < 10 ? "0" : "") + std::to_string(total_minutes % 60));
        }
    }

    void adaugaTerenInterior() {
        std::string tipAcoperis, tipPardoseala;
        std::cout << "Introduceti tipul acoperisului: ";
        std::cin >> tipAcoperis;
        std::cout << "Introduceti tipul pardoselii: ";
        std::cin >> tipPardoseala;
        std::unique_ptr<Teren> terenInterior(new TerenTenisInterior(numeTeren, programTeren, pretTeren, tipAcoperis, tipPardoseala));
        adaugaTeren(std::move(terenInterior));
    }

    void adaugaTerenExterior() {
        std::string tipSuprafata;
        bool sistemIrigare;
        std::cout << "Introduceti tipul suprafetei: ";
        std::cin >> tipSuprafata;
        std::cout << "Are sistem de irigare? (1 pentru Da, 0 pentru Nu): ";
        std::cin >> sistemIrigare;
        std::unique_ptr<Teren> terenExterior(new TerenTenisExterior(numeTeren, programTeren, pretTeren, tipSuprafata, sistemIrigare));
        adaugaTeren(std::move(terenExterior));
    }

    void adaugaTerenCuInstructor() {
        std::string numeInstructor;
        double taxaInstruire;
        std::cout << "Introduceti numele instructorului: ";
        std::cin >> numeInstructor;
        std::cout << "Introduceti taxa de instruire: ";
        std::cin >> taxaInstruire;
        std::unique_ptr<Teren> terenCuInstructor(new TerenTenisCuInstructor(numeTeren, programTeren, pretTeren, numeInstructor, taxaInstruire));
        adaugaTeren(std::move(terenCuInstructor));
    }

public:
    int getOptiune() const{
        return optiune;
    }
    void setOptiune(){
        std::cin >>optiune;
    }
    void setTipTeren() {
        std::cin >> tipTeren;
    }

    std::string getTipTeren() const {
        return tipTeren;
    }

    void setGasitTerenToFalse() {
        this->gasitTeren = false;
    }

    void setGasitTerenToTrue() {
        this->gasitTeren = true;
    }

    bool getGasitTeren() const {
        return gasitTeren;
    }

    void adaugaTeren(std::unique_ptr<Teren> teren) {
        terenuri.push_back(std::move(teren));
    }

    void afiseazaTerenuri() const {
        std::cout << "Numar total de terenuri: " << Teren::getNumarTerenuri() << std::endl;
        std::cout << "Terenuri disponibile:\n";
        for(const auto& teren : terenuri) {
            teren->afisareDetalii(std::cout);
            std::cout << std::endl;
        }
    }

    void afiseazaInchirieri() const {
        std::cout << "Inchirieri efectuate:\n";
        for(const auto& inchiriere : inchirieri) {
            std::cout << inchiriere << std::endl;
        }
    }

    void run() {
        while (getOptiune() != 5) {
            std::cout << "\nIntroduceti o optiune (1, 2, 3, 4 sau 5):\n ";
            std::cout << "1.Adaugare/Editare/Stergere teren.\n ";
            std::cout << "2.Inchiriere teren.\n ";
            std::cout << "3.Verificare lista terenuri.\n ";
            std::cout << "4.Afiseaza rezervari.\n ";
            std::cout << "5.Inchidere meniu.\n ";
            setOptiune();

            switch (optiune) {
                case 1: {
                    std::cout << "Introduceti o optiune (1, 2 sau 3):\n ";
                    std::cout << "1.Adaugare teren.\n ";
                    std::cout << "2.Editare teren.\n ";
                    std::cout << "3.Stergere teren.\n ";
                    setOptiune();
                    switch(optiune){
                        case 1:{
                            std::cout << "Ati ales optiunea 1.\n";
                            std::cout << "Introduceti numele terenului:\n ";
                            std::cin >> numeTeren;
                            std::cout << "Introduceti programul terenului (hh:mm-hh:mm):\n ";
                            std::cin >> programTeren;
                            std::cout << "Introduceti pretul terenului:\n ";
                            std::cin >> pretTeren;
                            std::cout << "Introduceti tipul terenului (TerenInt, TerenExt, TerenInstr):\n";
                            setTipTeren();
                            if (getTipTeren() == "TerenInt") {
                                adaugaTerenInterior();
                            } else if (getTipTeren() == "TerenExt") {
                                adaugaTerenExterior();
                            } else if (getTipTeren() == "TerenInstr") {
                                adaugaTerenCuInstructor();
                            } else {
                                std::cout << "Tip de teren invalid!\n";
                            }
                            break;
                        }
                        case 2:{
                            setGasitTerenToFalse();
                            std::cout << "Introduceti numele vechi al terenului:\n ";
                            std::cin >> numeTeren;
                            for (auto it = terenuri.begin(); it != terenuri.end(); ++it) {
                                if ((*it)->getNume() == numeTeren) {
                                    setGasitTerenToTrue();
                                    std::cout << "Introduceti numele nou al terenului:\n ";
                                    std::cin >> numeTeren;
                                    std::cout << "Introduceti programul nou al terenului (hh:mm-hh:mm):\n ";
                                    std::cin >> programTeren;
                                    std::cout << "Introduceti pretul nou al terenului:\n ";
                                    std::cin >> pretTeren;
                                    (*it)->setNume(numeTeren);
                                    (*it)->setProgram(programTeren);
                                    (*it)->setPret(pretTeren);
                                    break;

                                }
                            }
                            if(!getGasitTeren())
                            {
                                std::cout<<"Terenul introdus nu exista\n";
                                break;
                            }
                            break;
                        }
                        case 3: {
                            std::cout << "Introduceti numele terenului pe care vreti sa il stergeti:\n ";
                            std::cin >> numeTeren;

                            auto it = std::find_if(terenuri.begin(), terenuri.end(), [&](const auto& teren) {
                                return teren->getNume() == numeTeren;
                            });
                            if (it != terenuri.end()) {
                                Teren* teren = it->get();
                                if (TerenTenisExterior* terenExtPtr = convertToDerived<TerenTenisExterior>(teren)) {
                                    std::cout << "Terenul de tenis exterior cu numele " << numeTeren << " a fost sters.\n";
                                    terenuri.erase(it);
                                } else if (TerenTenisInterior* terenIntPtr = convertToDerived<TerenTenisInterior>(teren)) {
                                    std::cout << "Terenul de tenis interior cu numele " << numeTeren << " a fost sters.\n";
                                    terenuri.erase(it);
                                } else if (TerenTenisCuInstructor* terenInstPtr = convertToDerived<TerenTenisCuInstructor>(teren)) {
                                    std::cout << "Terenul de tenis cu instructor cu numele " << numeTeren << " a fost sters.\n";
                                    terenuri.erase(it);
                                } else {
                                    std::cout << "Terenul cu numele " << numeTeren << " nu a fost gasit.\n";
                                }
                            } else {
                                std::cout << "Terenul cu numele " << numeTeren << " nu a fost gasit.\n";
                            }
                            break;
                        }

                    }
                    break;
                }
                case 2:
                {std::cout << "Ati ales optiunea 2.\n";
                    std::cout<<"Creeaza user:\n";
                    Utilizator user1;
                    std::cout<<"Nume:\n";
                    user1.setNume();
                    std::cout<<"Interval orar:\n";
                    user1.setIntervalOrar();
                    prelucreazaOre(user1.getIntervalOrar());
                    std::cout<<"Teren:\n";
                    user1.setTeren();
                    for(auto it = terenuri.begin(); it != terenuri.end(); ++it) {
                        if ((*it)->getNume() == user1.getTeren()) {
                            for (const auto& ora : oreOcupate) {
                                (*it)->stergeOra(ora);
                            }
                            break;
                        }
                    }
                    std::cout<<"Am facut rezervarea!\n";
                    Inchiriere inchiriere(user1);
                    inchirieri.push_back(inchiriere);
                    break;

                }
                case 3:
                    std::cout << "Ati ales optiunea 3.\n";
                    afiseazaTerenuri();
                    break;
                case 4:
                    std::cout << "Ati ales optiunea 4.\n";
                    std::cout << "Numarul total de utilizatori: " << Utilizator::getNumarUtilizatori() << std::endl;
                    afiseazaInchirieri();
                    break;
                case 5:
                    std::cout << "Ati ales sa opriti aplicatia.\n";
                    break;
                default:
                    std::cout << "Optiune invalida.\n";
                    break;
            }
        }
    }
};

int main() {
    Menu menu;
    Utilizator user1("John", "08:00-16:00", "Teren1");
    Utilizator user2("Alice", "10:00-18:00", "Teren2");

    TerenTenisExterior terenExterior("Terenext", "10:00-12:00", 50.0, "Suprafata1", true);
    menu.adaugaTeren(std::make_unique<TerenTenisExterior>(terenExterior));

    TerenTenisInterior terenInterior("Terenint", "08:00-12:00", 25.0, "Acoperis1", "Pardoseala1");
    menu.adaugaTeren(std::make_unique<TerenTenisInterior>(terenInterior));

    TerenTenisCuInstructor terenCuInstructor3("Terencuinstr6", "07:00-12:00", 30.0, "Instructor2", 10.0);
    Teren x("terena", "10:00-12:00", 23.0);
    menu.adaugaTeren(std::make_unique<Teren>(x));
    Teren y("terenb", "08:00-12:00", 29.0);
    x=y;
    menu.adaugaTeren(std::make_unique<Teren>(x));
    menu.adaugaTeren(std::make_unique<TerenTenisCuInstructor>(terenCuInstructor3));
    menu.run();
    return 0;
}

