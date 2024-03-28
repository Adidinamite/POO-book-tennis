#ifndef TEMPLATES
#define TEMPLATES

#include <iostream>
#include <vector>
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        os <<"[" <<elem << "]\n";
    }
    return os;
}
#endif
