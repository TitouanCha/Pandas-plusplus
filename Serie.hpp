#ifndef SERIE_HPP
#define SERIE_HPP
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

template <typename T>
class Serie
{
        std::vector<T> data;
        std::string name;
    
public:
    Serie(std::string name) : data(), name(name) {}
    Serie(std::string name, std::vector<T> serie) : data(serie), name(name) {}
    Serie(std::string name, int size, T value) : data(size, value), name(name) {}

    const T& operator()(int index) const{ 
        return data[static_cast<size_t>(index)]; 
    }
    T& operator()(int index){ 
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


    

};



#endif