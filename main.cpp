#include <iostream>
#include <string>
#include "Serie.hpp"


int main() {
    Serie<std::string> serieString(std::vector<std::string>{"a", "b", "c", "d", "e"});
    std::cout << "Série string: " << serieString << std::endl;
    Serie<int> serieInt(std::vector<int>{1, 2, 3, 4, 5});
    std::cout << "Série int : " << serieInt << std::endl;
    Serie<float> serieFloat(std::vector<float>{1.5f, 2.0f, 3.25f, 4.75f, 5.0f});
    std::cout << "Série float : " << serieFloat << std::endl;
    Serie<std::string> serieString2("Test", 5, "Test");
    std::cout << "Série de string remplie: " << serieString2 << std::endl;
    Serie<int> serieInt2("Nombres", 5, 42);
    std::cout << "Série de int remplie: " << serieInt2 << std::endl;
    Serie<double> serieDouble2("Nombres à virgule");
    std::cout << "Série vide: " << serieDouble2 << std::endl;

    std::cout << "\nOpérateurs de comparaison" << std::endl;
    Serie<int> s1(std::vector<int>{1, 2, 3, 4, 5});
    std::cout << "s1 : " << s1 << std::endl;
    Serie<int> s2(std::vector<int>{5, 4, 3, 2, 1});
    std::cout << "s2 : " << s2 << std::endl;

    Serie<bool> mask1 = s1 > 3; // {false, false, false, true, true}
    std::cout << "Mask1 (s1>3) : " << mask1 << std::endl;
    Serie<bool> mask2 = s1 == s2; // {false, false, true, false, false}
    std::cout << "Mask2 (s1==s2) : " << mask2 << std::endl;
    Serie<bool> mask3 = s1 <= 3; // {true, true, true, false, false}
    std::cout << "Mask3 (s1<=3) : " << mask3 << std::endl;
    Serie<bool> mask5 = s1 < 3; // {true, true, false, false, false}
    std::cout << "Mask5 (s1<3) : " << mask5 << std::endl;
    Serie<bool> mask6 = s1 >= 3; // {false, false, true, true, true}
    std::cout << "Mask6 (s1>=3) : " << mask6 << std::endl;
    Serie<bool> mask7 = s1 == 3; // {false, false, true, false, false}
    std::cout << "Mask7 (s1==3) : " << mask7 << std::endl;
    Serie<bool> mask8 = s1 != 3; // {true, true, false, true, true}
    std::cout << "Mask8 (s1!=3) : " << mask8 << std::endl;
    Serie<bool> mask9 = s1 != s2; // {true, true, false, true, true}
    std::cout << "Mask9 (s1!=s2) : " << mask9 << std::endl;
    Serie<bool> mask10 = s1 < s2; // {true, true, false, false, false}
    std::cout << "Mask10 (s1<s2) : " << mask10 << std::endl;
    Serie<bool> mask11 = s1 <= s2; // {true, true, true, false, false}
    std::cout << "Mask11 (s1<=s2): " << mask11 << std::endl;
    Serie<bool> mask12 = s1 > s2; // {false, false, false, true, true}
    std::cout << "Mask12 (s1>s2) : " << mask12 << std::endl;
    Serie<bool> mask13 = s1 >= s2; // {false, false, true, true, true}
    std::cout << "Mask13 (s1>=s2): " << mask13 << std::endl;

    std::cout << "\nIndexation avancée" << std::endl;
    Serie<int> s(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    std::cout << "s : " << s << std::endl;
    Serie<int> filtered1 = s[s > 5]; // {6, 7, 8, 9, 10}
    std::cout << "Filtered (s > 5) : " << filtered1 << std::endl;
    Serie<int> indices(std::vector<int>{0, 2, 4, 6});
    Serie<int> selected = s[indices]; // {1, 3, 5, 7}
    std::cout << "Selected (0, 2, 4, 6): " << selected << std::endl;

    std::cout << "\nOpérateurs logiques" << std::endl;
    Serie<int> sl(std::vector<int>{1, 2, 3, 4, 5});
    std::cout << "sl : " << sl << std::endl;
    Serie<int> result1 = sl[(sl > 2) && (sl < 5)];
    std::cout << "result1 ((sl > 2) && (sl < 5)) : " << result1 << std::endl;
    Serie<int> result2 = sl[!(sl == 3)];
    std::cout << "result2 (!(sl == 3)) : " << result2 << std::endl;
    Serie<int> result3 = sl[(sl < 2) || (sl > 4)];
    std::cout << "result3 ((sl < 2) || (sl > 4)) : " << result3 << std::endl;

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
    std::cout << "Sub (a-b): " << sub << std::endl;
    Serie<int> decremented = a -= 10; // {0, 10, 20, 30, 40}
    std::cout << "Decremented (c-10): " << decremented << std::endl;

    return 0;
}
