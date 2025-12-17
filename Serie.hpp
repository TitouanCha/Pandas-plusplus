#ifndef SERIE_HPP
#define SERIE_HPP
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <functional>
#include <type_traits>

template <typename T>
class Serie
{
    std::vector<T> data;
    std::string name;
   
public:
    Serie() : data(), name("unnamed") {}
    Serie(const std::string& name) : data(), name(name) {}
    Serie(const std::vector<T>& serie) : data(serie), name("pandas") {}
    Serie(const std::string& name, const std::vector<T>& serie) : data(serie), name(name) {}
    Serie(size_t size, const T& value) : data(size, value), name("pandas") {}
    Serie(const std::string& name, size_t size, const T& value) : data(size, value), name(name) {}

    // Règle des 5
    ~Serie() = default;
    Serie(const Serie& other) = default;
    Serie(Serie&& other) noexcept = default;
    Serie& operator=(const Serie& other) = default;
    Serie& operator=(Serie&& other) noexcept = default;

    // Getters et setters
    const std::vector<T>& getData() const { return data; }
    void setData(const std::vector<T>& newData) { data = newData; }
    const std::string& getName() const { return name; }
    void setName(const std::string& newName) { name = newName; }

    // Opérateurs arithmétiques
    Serie<T> operator+(const Serie<T>& other) const {
        return arithmetic(other, std::plus<T>());
    }
    Serie<T>& operator+=(const Serie<T>& other) {
        *this = arithmetic(other, std::plus<T>());
        return *this;
    }
    Serie<T> operator+(const T& value) const {
        return arithmetic(value, std::plus<T>());
    }
    Serie<T>& operator+=(const T& value) {
        *this = arithmetic(value, std::plus<T>());
        return *this;
    }
    Serie<T> operator-(const Serie<T>& other) const {
        return arithmetic(other, std::minus<T>());
    }
    Serie<T>& operator-=(const Serie<T>& other) {
        *this = arithmetic(other, std::minus<T>());
        return *this;
    }
    Serie<T> operator-(const T& value) const {
        return arithmetic(value, std::minus<T>());
    }
    Serie<T>& operator-=(const T& value) {
        *this = arithmetic(value, std::minus<T>());
        return *this;
    }
    Serie<T> operator*(const Serie<T>& other) const {
        return arithmetic(other, std::multiplies<T>());
    }
    Serie<T>& operator*=(const Serie<T>& other) {
        *this = arithmetic(other, std::multiplies<T>());
        return *this;
    }
    Serie<T> operator*(const T& value) const {
        return arithmetic(value, std::multiplies<T>());
    }
    Serie<T>& operator*=(const T& value) {
        *this = arithmetic(value, std::multiplies<T>());
        return *this;
    }
    Serie<T> operator/(const Serie<T>& other) const {
        if (data.size() != other.data.size())
            throw std::invalid_argument("Size not matching");
        std::vector<T> result;
        result.reserve(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            if (other.data[i] == T(0))
                throw std::invalid_argument("Division by zero");
            result.push_back(data[i] / other.data[i]);
        }
        return Serie<T>("result", result);
    }
    Serie<T>& operator/=(const Serie<T>& other) {
        *this = *this / other;
        return *this;
    }
    Serie<T> operator/(const T& value) const {
        if (value == T(0))
            throw std::invalid_argument("Division by zero");
        std::vector<T> result;
        result.reserve(data.size());
        for (size_t i = 0; i < data.size(); ++i)
            result.push_back(data[i] / value);
        return Serie<T>("result", result);
    }
    Serie<T>& operator/=(const T& value) {
        *this = *this / value;
        return *this;
    }

    // Indexation par masque booléen
    Serie<T> operator[](const Serie<bool>& mask) const {
        if (data.size() != mask.size()) throw std::invalid_argument("Size not matching");
        std::vector<T> result;
        result.reserve(data.size());
        for (size_t i = 0; i < data.size(); ++i)
            if (mask.get(i)) result.push_back(data[i]);
        return Serie<T>("result", result);
    }

    // Indexation par indices
    Serie<T> operator[](const Serie<int>& indices) const {
        std::vector<T> result;
        result.reserve(indices.size());
        for (size_t i = 0; i < indices.size(); ++i) {
            int idx = indices.get(i);
            if (idx < 0 || static_cast<size_t>(idx) >= data.size())
                throw std::out_of_range("Index out of range");
            result.push_back(data[static_cast<size_t>(idx)]);
        }
        return Serie<T>("result", result);
    }
    
    // Prédicat - utilise SFINAE pour n'accepter que les callables
    template<typename Predicate,
             typename = typename std::enable_if<
                 std::is_same<decltype(std::declval<Predicate>()(std::declval<T>())), bool>::value
             >::type>
    Serie<T> operator[](Predicate pred) const {
        std::vector<T> result;
        result.reserve(data.size());
        for (size_t i = 0; i < data.size(); ++i)
            if (pred(data[i])) result.push_back(data[i]);
        return Serie<T>("result", result);
    }

    // Opérateurs de comparaison
    Serie<bool> operator==(const Serie<T>& other) const {
        return compare(other, std::equal_to<T>());
    }
    Serie<bool> operator!=(const Serie<T>& other) const {
        return compare(other, std::not_equal_to<T>());
    }
    Serie<bool> operator<(const Serie<T>& other) const {
        return compare(other, std::less<T>());
    }
    Serie<bool> operator<=(const Serie<T>& other) const {
        return compare(other, std::less_equal<T>());
    }
    Serie<bool> operator>(const Serie<T>& other) const {
        return compare(other, std::greater<T>());
    }
    Serie<bool> operator>=(const Serie<T>& other) const {
        return compare(other, std::greater_equal<T>());
    }
    Serie<bool> operator==(const T& value) const {
        return compare(value, std::equal_to<T>());
    }
    Serie<bool> operator!=(const T& value) const {
        return compare(value, std::not_equal_to<T>());
    }
    Serie<bool> operator<(const T& value) const {
        return compare(value, std::less<T>());
    }
    Serie<bool> operator<=(const T& value) const {
        return compare(value, std::less_equal<T>());
    }
    Serie<bool> operator>(const T& value) const {
        return compare(value, std::greater<T>());
    }
    Serie<bool> operator>=(const T& value) const {
        return compare(value, std::greater_equal<T>());
    }

    // Affichage
    friend std::ostream& operator<<(std::ostream& os, const Serie<T>& s) {
        os << "[ ";
        for (size_t i = 0; i < s.data.size(); ++i) {
            os << s.data[i];
            if (i + 1 < s.data.size()) os << ", ";
        }
        os << " ]";
        return os;
    }

    // Accès par indice (retourne par valeur pour éviter problème avec vector<bool>)
    T get(size_t index) const {
        if (index >= data.size())
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    // Accès par indice pour modification
    T& operator[](size_t index) { 
        return data[index]; 
    }
    const T& operator[](size_t index) const { 
        return data[index]; 
    }

    T& at(size_t index) {
        if (index >= data.size())
            throw std::out_of_range("Index out of range");
        return data[index];
    }
    const T& at(size_t index) const {
        if (index >= data.size())
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    size_t size() const {
        return data.size();
    }
    bool empty() const {
        return data.empty();
    }
    void push_back(const T& value) {
        data.push_back(value);
    }
    void clear() {
        data.clear();
    }
    
    // Itérateurs
    typename std::vector<T>::iterator begin() {
        return data.begin();
    }
    typename std::vector<T>::iterator end() {
        return data.end();
    }
    typename std::vector<T>::const_iterator begin() const {
        return data.begin();
    }
    typename std::vector<T>::const_iterator end() const {
        return data.end();
    }

private:
    template<typename Operator>
    Serie<T> arithmetic(const Serie<T>& other, Operator op) const {
        size_t sz = data.size();
        if (sz != other.data.size())
            throw std::invalid_argument("Size not matching");
        std::vector<T> result;
        result.reserve(sz);
        for (size_t i = 0; i < sz; ++i)
            result.push_back(op(data[i], other.data[i]));
        return Serie<T>("result", result);
    }
    
    template<typename Operator>
    Serie<T> arithmetic(const T& value, Operator op) const {
        std::vector<T> result;
        result.reserve(data.size());
        for (size_t i = 0; i < data.size(); ++i)
            result.push_back(op(data[i], value));
        return Serie<T>("result", result);
    }

    template<typename Operator>
    Serie<bool> compare(const Serie<T>& other, Operator op) const {
        size_t sz = std::min(data.size(), other.data.size());
        std::vector<bool> result;
        result.reserve(sz);
        for (size_t i = 0; i < sz; ++i)
            result.push_back(op(data[i], other.data[i]));
        return Serie<bool>("result", result);
    }

    template<typename Operator>
    Serie<bool> compare(const T& value, Operator op) const {
        std::vector<bool> result;
        result.reserve(data.size());
        for (size_t i = 0; i < data.size(); ++i)
            result.push_back(op(data[i], value));
        return Serie<bool>("result", result);
    }
};

// Opérateurs logiques pour Serie<bool> - utilise get() pour éviter le problème vector<bool>
inline Serie<bool> operator&&(const Serie<bool>& lhs, const Serie<bool>& rhs) {
    if (lhs.size() != rhs.size())
        throw std::invalid_argument("Size not matching");
    std::vector<bool> result;
    result.reserve(lhs.size());
    for (size_t i = 0; i < lhs.size(); ++i)
        result.push_back(lhs.get(i) && rhs.get(i));
    return Serie<bool>("result", result);
}

inline Serie<bool> operator||(const Serie<bool>& lhs, const Serie<bool>& rhs) {
    if (lhs.size() != rhs.size())
        throw std::invalid_argument("Size not matching");
    std::vector<bool> result;
    result.reserve(lhs.size());
    for (size_t i = 0; i < lhs.size(); ++i)
        result.push_back(lhs.get(i) || rhs.get(i));
    return Serie<bool>("result", result);
}

inline Serie<bool> operator!(const Serie<bool>& s) {
    std::vector<bool> result;
    result.reserve(s.size());
    for (size_t i = 0; i < s.size(); ++i)
        result.push_back(!s.get(i));
    return Serie<bool>("result", result);
}

#endif