#include <iostream>
#include <string>
#include <vector>
#include "utilizator.h"
#include "teren.h"
/*class Inchiriere {
private:
    Utilizator utilizator;
    Teren teren;

public:
    Inchiriere(const Utilizator& utilizator, const Teren& teren) : utilizator(utilizator), teren(teren) {}

    void afisareDetalii() const {
        std::cout << "Utilizator: " << utilizator.getNume() << std::endl;
        std::cout << "Teren: " << teren << std::endl;
    }
};*/
class Inchiriere {
private:
    Utilizator utilizator;
    Teren teren;
public:
    Inchiriere(const Utilizator& utilizator, const Teren& teren)
            : utilizator(utilizator), teren(teren) {}

    friend std::ostream& operator<<(std::ostream& os, const Inchiriere& inchiriere);
};

std::ostream& operator<<(std::ostream& os, const Inchiriere& inchiriere) {
    os << "Detalii Inchiriere: " << inchiriere.utilizator << ", " << inchiriere.teren;
    return os;
}


class Menu {
private:
    std::vector<Teren> terenuri;
    bool gasitTeren=false;
    int optiune;
    std::string numeTeren, programTeren;
    double pretTeren;
public:

    void setOptiune(){
        std::cin>>optiune;
    }
    int getOptiune() const{
        return optiune;
    }
    void setGasitTerenToFalse(){
        this->gasitTeren = false;
    }
    void setGasitTerenToTrue(){
        this->gasitTeren = true;
    }
    bool getGasitTeren() const{
        return gasitTeren;
    }
    // Adăugare teren nou
    void adaugaTeren(const Teren& teren) {
        terenuri.push_back(teren);
    }

    // Afișează toate terenurile
    void afiseazaTerenuri() const {
        std::cout << "Terenuri disponibile:\n";
        for (const auto& teren : terenuri) {
            std::cout << teren << "\n";
        }
    }
    // Metoda pentru rularea meniului
    void run() {

        while (true && getOptiune()!=4) {

            std::cout << "Introduceti o optiune (1, 2 sau 3):\n ";
            std::cout << "1.Adaugare/Editare/Stergere teren.\n ";
            std::cout << "2.Inchiriere teren.\n ";
            std::cout << "3.Verificare lista terenuri.\n ";
            /*std::cout << "4.Verificare disponibiltate ora x.\n ";*/
            std::cout << "4.Inchidere aplicatie.\n ";
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
                            Teren teren(numeTeren, programTeren, pretTeren);
                            adaugaTeren(teren);
                        }
                        case 2:{
                            setGasitTerenToFalse();
                            std::cout << "Introduceti numele vechi al terenului:\n ";
                            std::cin >> numeTeren;
                            for (auto& teren : terenuri) {
                                if (teren.getNume() == numeTeren) {
                                    setGasitTerenToTrue();
                                    std::cout << "Introduceti numele nou al terenului:\n ";
                                    std::cin >> numeTeren;
                                    std::cout << "Introduceti programul nou al terenului (hh:mm-hh:mm):\n ";
                                    std::cin >> programTeren;
                                    std::cout << "Introduceti pretul nou al terenului:\n ";
                                    std::cin >> pretTeren;
                                    teren.setNume(numeTeren);
                                    teren.setProgram(programTeren);
                                    teren.setPret(pretTeren);

                                    break;
                                }
                            }
                            if(!getGasitTeren())
                            {
                                std::cout<<"Terenul introdus nu exista\n";
                                break;
                            }
                        }
                        case 3:{
                            std::cout << "Introduceti numele terenului pe care vreti sa il stergeti:\n ";
                            std::cin >> numeTeren;
                            for (auto it = terenuri.begin(); it != terenuri.end(); ++it) {
                                if (it->getNume() == numeTeren) {
                                    it = terenuri.erase(it);
                                    std::cout << "Terenul cu numele " << numeTeren << " a fost sters.\n";
                                    break;
                                }
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
                    std::cout<<"Teren:\n";
                    user1.setTeren();
                    for (auto it = terenuri.begin(); it != terenuri.end(); ++it) {
                        if (it->getNume() == user1.getTeren()) {
                            it->stergeOra("10:00");
                            break;
                        }
                    }
                    std::cout<<"Am facut rezervarea!\n";
                    break;

                }
                case 3:
                    std::cout << "Ati ales optiunea 3.\n";
                    afiseazaTerenuri();
                    break;
                /*case 4:
                    std::cout << "Ati ales optiunea 4.\n";
                    break;*/
                case 4:
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
    Teren teren("Teren1", "10:00-12:00", 50.0);
    menu.adaugaTeren(teren);
    Teren teren1("Teren3", "08:00-12:00", 25.0);
    menu.adaugaTeren(teren1);

    Utilizator user("John", "08:00-16:00");
    std::cout << user.getNume() << std::endl;
    std::cout << user.getNume() << std::endl;
    std::cout << user.getIntervalOrar() << std::endl;
    Utilizator user2 (user);
    std::cout << user2 << std::endl;
    Inchiriere inchiriere(user, teren);
    std::cout<<inchiriere<<"\n";
    menu.run();
    return 0;
}
