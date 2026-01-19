#include <iostream>
#include "resource_manager.hpp"


int main() {

    ResourceManager rm1(20);
    ResourceManager rm2(10);

    auto rm3 = rm1;
    auto rm4{rm2};

    std::cout << "rm1 size: " << rm1.show_size() << "\n";
    std::cout << "rm2 size: " << rm2.show_size() << "\n";
    std::cout << "rm3 size: " << rm3.show_size() << "\n";
    std::cout << "rm4 size: " << rm4.show_size() << "\n";

    auto is_equal = rm1 == rm3 ? "true" : "false";
    std::cout << "rm1 == rm3 " << is_equal << "\n";

    return 0;
}