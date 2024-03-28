#ifndef POO1_DATETEREN_H
#define POO1_DATETEREN_H
#include <iostream>
#include <string>

class dateTeren {
private:
    std::string numeTeren;
    std::string programTeren;
    double pretTeren;

public:
    // Constructor
    dateTeren(const std::string& nume, const std::string& program, double pret)
            : numeTeren(nume), programTeren(program), pretTeren(pret) {}

    // Constructor de copiere
    dateTeren(const dateTeren& other)
            : numeTeren(other.numeTeren), programTeren(other.programTeren), pretTeren(other.pretTeren) {}

    // Destructor
    ~dateTeren() {
        std::cout << "Destructorul pentru terenul " << numeTeren << " a fost apelat.\n";
    }

    // Getter și setter pentru NumeTeren

};
#endif //POO1_DATETEREN_H
