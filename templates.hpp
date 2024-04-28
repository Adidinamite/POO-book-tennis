#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <iostream>
#include <vector>
#include "teren.hpp"

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        os <<"[" << *elem << "]\n";
    }
    return os;
}

template <typename T>
T* convertToDerived(Teren* teren) {
    return dynamic_cast<T*>(teren);
}
#endif
