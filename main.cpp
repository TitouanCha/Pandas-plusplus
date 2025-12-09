#include <iostream>
#include <string>
#include "Serie.hpp"


int main() {
    Serie<std::string> serieTest(std::vector<std::string>{"a", "b", "c", "d", "e"});
    std::cout << "Série initiale: " << serieTest << std::endl;

    std::cout << "\nOpérateurs de comparaison" << std::endl;
    Serie<int> s1(std::vector<int>{1, 2, 3, 4, 5});
    std::cout << "s1 : " << s1 << std::endl;
    Serie<int> s2(std::vector<int>{5, 4, 3, 2, 1});
    std::cout << "s2 : " << s2 << std::endl;
    Serie<bool> mask1 = s1 > 3; // {false, false, false, true, true}
    std::cout << "Mask1 (s1>3) : " << mask1 << std::endl;
    Serie<bool> mask2 = s1 == s2; // {false, false, true, false, false}
    std::cout << "Mask2 (s1==s2): " << mask2 << std::endl;
    Serie<bool> mask3 = s1 <= 3; // {true, true, true, false, false}
    std::cout << "Mask3 (s1<=3) : " << mask3 << std::endl;

    
    std::cout << "\nIndexation avancée" << std::endl;
    Serie<int> s(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    std::cout << "s : " << s << std::endl;
    Serie<int> filtered1 = s[s > 5]; // {6, 7, 8, 9, 10}
    std::cout << "Filtered1 (s > 5) : " << filtered1 << std::endl;
    Serie<int> indices(std::vector<int>{0, 2, 4, 6});
    Serie<int> selected = s[indices]; // {1, 3, 5, 7}
    std::cout << "Selected (0, 2, 4, 6): " << selected << std::endl;


    std::cout << "\nOpérateurs arithmétiques" << std::endl;
    Serie<int> a(std::vector<int>{10, 20, 30, 40, 50});
    std::cout << "Série a: " << a << std::endl;
    Serie<int> b(std::vector<int>{1, 2, 3, 4, 5});
    std::cout << "Série b: " << b << std::endl;
    Serie<int> sum = a + b; // {11, 22, 33, 44, 55}
    std::cout << "Sum (a+b): " << sum << std::endl;
    Serie<int> incremented = a += 5; // {15, 25, 35, 45, 55}
    std::cout << "Incremented (a+5): " << incremented << std::endl;
    Serie<int> sub = a - b; // {9, 18, 27, 36, 45}
    std::cout << "Subtraction (a-b): " << sub << std::endl;
    Serie<int> decremented = a -= 10; // {0, 10, 20, 30, 40}
    std::cout << "Decremented (c-10): " << decremented << std::endl;

    return 0;
}
