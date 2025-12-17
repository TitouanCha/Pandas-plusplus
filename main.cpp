#include <iostream>
#include <string>
#include "Serie.hpp"

using namespace std;

int main() {
    cout << "Séries" << endl;
    Serie<int> s1(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    Serie<int> s2(5, 100);
    Serie<int> s3;
    Serie<double> s4("doubles", vector<double>{1.1, 2.2, 3.3});
    
    cout << "s1: " << s1 << endl;
    cout << "s2 (5x100): " << s2 << endl;
    cout << "s3 (vide): " << s3 << endl;
    cout << "s4 (doubles): " << s4 << endl;

    cout << "\nGetters/Setters" << endl;
    cout << "Nom de s4: " << s4.getName() << endl;
    s4.setName("modified");
    cout << "Nouveau nom: " << s4.getName() << endl;

    cout << "\nMéthodes d'accès" << endl;
    cout << "s1[0]: " << s1[0] << endl;
    cout << "s1.at(5): " << s1.at(5) << endl;
    cout << "s1.size(): " << s1.size() << endl;
    cout << "s3.empty(): " << (s3.empty() ? "true" : "false") << endl;
    
    s3.push_back(42);
    cout << "s3 après push_back(42): " << s3 << endl;

    cout << "\nItérateurs" << endl;
    cout << "Parcours de s1: ";
    for (const auto& val : s1)
        cout << val << " ";
    cout << endl;

    cout << "\nOpérateurs de comparaison" << endl;
    Serie<int> a(vector<int>{1, 2, 3, 4, 5});
    Serie<int> b(vector<int>{5, 4, 3, 2, 1});
    
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "a > 3: " << (a > 3) << endl;
    cout << "a == b: " << (a == b) << endl;
    cout << "a <= 3: " << (a <= 3) << endl;

    cout << "\nFiltrage simple" << endl;
    Serie<int> greater_than_5 = s1[s1 > 5];
    cout << "s1 > 5: " << greater_than_5 << endl;

    cout << "\nFiltrage combiné" << endl;
    Serie<int> range = s1[(s1 > 3) && (s1 <= 7)];
    cout << "3 < s1 <= 7: " << range << endl;
    
    Serie<int> extremes = s1[(s1 <= 2) || (s1 >= 9)];
    cout << "s1 <= 2 || s1 >= 9: " << extremes << endl;

    cout << "\nNégation logique" << endl;
    Serie<int> not_equal_5 = s1[!(s1 == 5)];
    cout << "s1 != 5: " << not_equal_5 << endl;

    cout << "\nPrédicat" << endl;
    auto is_even = [](int x) { return x % 2 == 0; };
    Serie<int> evens = s1[is_even];
    cout << "Nombres pairs: " << evens << endl;
    
    auto is_prime = [](int x) {
        if (x < 2) return false;
        for (int i = 2; i * i <= x; ++i)
            if (x % i == 0) return false;
        return true;
    };
    Serie<int> primes = s1[is_prime];
    cout << "Nombres premiers: " << primes << endl;

    cout << "\nIndexation par positions" << endl;
    Serie<int> indices(vector<int>{0, 2, 4, 6, 8});
    Serie<int> selected = s1[indices];
    cout << "Indices " << indices << ": " << selected << endl;

    cout << "\nOpérateurs arithmétiques" << endl;
    Serie<int> x(vector<int>{10, 20, 30, 40, 50});
    Serie<int> y(vector<int>{1, 2, 3, 4, 5});
    
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "x + y: " << (x + y) << endl;
    cout << "x - y: " << (x - y) << endl;
    cout << "x * y: " << (x * y) << endl;
    cout << "x / y: " << (x / y) << endl;
    cout << "x + 5: " << (x + 5) << endl;
    cout << "x * 2: " << (x * 2) << endl;
    
    x += 100;
    cout << "x après x += 100: " << x << endl;
    x -= 50;
    cout << "x après x -= 50: " << x << endl;

    cout << "\nGestion des erreurs" << endl;
    try {
        s1.at(100);
    } catch (const out_of_range& e) {
        cout << "Exception at(): " << e.what() << endl;
    }
    
    try {
        Serie<int> bad_indices(vector<int>{0, 100});
        s1[bad_indices];
    } catch (const out_of_range& e) {
        cout << "Exception indices: " << e.what() << endl;
    }

    cout << "\nTypes variés" << endl;
    Serie<string> strings(vector<string>{"hello", "world", "test"});
    cout << "Strings: " << strings << endl;
    
    Serie<double> doubles(vector<double>{1.5, 2.5, 3.5, 4.5});
    cout << "Doubles: " << doubles << endl;
    cout << "Doubles > 2.0: " << doubles[doubles > 2.0] << endl;

    return 0;
}