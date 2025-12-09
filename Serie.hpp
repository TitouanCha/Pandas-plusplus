#ifndef SERIE_HPP
#define SERIE_HPP
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <functional>

template <typename T>
class Serie
{
        std::vector<T> data;
        std::string name;
   
public:
    Serie(const std::string& name) : data(), name(name) {}
    Serie(const std::vector<T>& serie) : data(serie), name("pandas") {}
    Serie(const std::string& name, const std::vector<T>& serie) : data(serie), name(name) {}
    Serie(const std::string& name, int size, const T& value) : data(size, value), name(name) {}


    // Opérateurs arithmétiques //
    Serie<T> operator+(const Serie<T>& other) const {
        return arithmetic(other, std::plus<T>());
    }
    Serie<T> operator+=(const T value) const {
        return arithmetic(value, std::plus<T>());
    }
    Serie<T> operator-(const Serie<T>& other) const {
        return arithmetic(other, std::minus<T>());
    }
    Serie<T> operator-=(const T value) const {
        return arithmetic(value, std::minus<T>());
    }
    Serie<T> operator*(const Serie<T>& other) const {
        return arithmetic(other, std::multiplies<T>());
    }
    Serie<T> operator*=(const T value) const {
        return arithmetic(value, std::multiplies<T>());
    }
    Serie<T> operator/(const Serie<T>& other) const {
        if (data.size() != other.data.size())
            throw std::invalid_argument("Size not matching");
        std::vector<T> result;
        result.reserve(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            if (other.data[i] == T(0))
                throw std::invalid_argument("Division by zero, t'es fous ou quoi");
            result.push_back(data[i] / other.data[i]);
        }
        return Serie<T>("result", result);
    }
    Serie<T> operator/=(const T value) const {
        if (value == T(0))
            throw std::invalid_argument("Division by zero, t'es fous ou quoi");
        std::vector<T> result;
        result.reserve(data.size());
        for (size_t i = 0; i < data.size(); ++i)
            result.push_back(data[i] / value);
        return Serie<T>("result", result);
    }

    // Indexation avancée //
    Serie<T> operator[](const Serie<bool>& mask) const {
        if (data.size() != mask.size()) throw std::invalid_argument("Size not matching");
        std::vector<T> result;
        result.reserve(data.size());
        for (size_t i = 0; i < data.size(); ++i)
            if (mask[i]) result.push_back(data[i]);
        return Serie<T>("result", result);
    }
    Serie<T> operator[](const Serie<int>& indices) const {
        std::vector<T> result;
        result.reserve(indices.size());
        for (size_t i = 0; i < indices.size(); ++i) {
            int idx = indices[i];
            if (idx < 0 || static_cast<size_t>(idx) >= data.size())
                throw std::out_of_range("Index out of range");
            result.push_back(data[static_cast<size_t>(idx)]);
        }
        return Serie<T>("result", result);
    }

    // Opérateurs de comparaison //
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

    // Opérateurs d'affichage //
    friend std::ostream& operator<<(std::ostream& os, const Serie<T>& s) {
        size_t dataSize= s.data.size();
        os << "[ ";
        for (int i = 0; i < dataSize; ++i) {
            os << s.data[i];
            if (i + 1 < dataSize) os << ", ";
        }
        os << " ]";
        return os;
    }

    // Méthodes d'accès //
    T operator[](int index) { 
        return data[static_cast<size_t>(index)]; 
    }
    const T operator[](int index) const { 
        return data[static_cast<size_t>(index)]; 
    }
    T at(int index){
        if(index < 0 || index >= static_cast<int>(data.size()))
            throw std::out_of_range("Index out of range");
        return data[static_cast<size_t>(index)];
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
    T begin() const {
        return data.front();
    }
    T end() const {
        return data.back();
    }

private:
    template<typename Operator>
    Serie<T> arithmetic(const Serie<T>& other, Operator op) const {
        size_t size = data.size();
        if (size != other.data.size())
            throw std::invalid_argument("Size not matching");

        std::vector<T> result;
        result.reserve(size);
        for (int i = 0; i < size; ++i) {
            T value = op(data[i], other.data[i]);
            result.push_back(value);
        }
        return Serie<T>("result", result);
    }
    template<typename Operator>
    Serie<T> arithmetic(const T& value, Operator op) const {
        size_t size = data.size();
        std::vector<T> result;
        result.reserve(size);
        for (int i = 0; i < size; ++i) {
            T v = op(data[i], value);
            result.push_back(v);
        }
        return Serie<T>("result", result);
    }

    template<typename Operator>
    Serie<bool> compare(const Serie<T>& other, Operator op) const {
        size_t size = data.size();
        if (size != other.data.size())
            throw std::invalid_argument("Size not matching");

        std::vector<bool> result;
        result.reserve(size);
        for (int i = 0; i < size; ++i) {
            bool b = static_cast<bool>(op(data[i], other.data[i]));
            result.push_back(b);
        }
        return Serie<bool>("result", result);
    }

    template<typename Operator>
    Serie<bool> compare(const T& value, Operator op) const {
        size_t size = data.size();
        std::vector<bool> result;
        result.reserve(size);
        for (int i = 0; i < size; ++i) {
            bool b = static_cast<bool>(op(data[i], value));
            result.push_back(op(data[i], value));
        }
        return Serie<bool>("result", result);
    }
};

#endif
