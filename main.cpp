#include <iostream>
#include <string>
#include "Serie.hpp" 


int main() {
    Serie<int> testSerie("MyIntSerie", 5, 9);
    std::cout << testSerie.operator()(2) << std::endl; 
    return 0;
}
