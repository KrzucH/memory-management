#include <iostream>
#include "unique_ptr.hpp"
#include <memory>





int main() {
    uniq_ptr<int> a = new int(4);    
    auto c = std::make_unique<int> (5);
    auto b = a.get();

    // std::cout << b << '\n';

    std::cout << *a;

    a.reset(new int (5));
    a.reset(nullptr);
    
        
    return 0;
}