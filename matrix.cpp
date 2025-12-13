#include "matrix.h"



matrix::matrix(void) : data(nullptr), n(0), allocated_n(0) {}

matrix::matrix(int size) : n(size), allocated_n(size) {
    if (size > 0) {
        data = std::make_unique<int[]>(size * size);
        std::fill(data.get(), data.get() + size * size, 0);
    }
}

matrix::~matrix(void) {}


int& matrix::at(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n) 
        throw std::out_of_range("Osoba 1: Indeks poza zakresem!");
    return data[x * n + y];
}

const int& matrix::at(int x, int y) const {
    return data[x * n + y];
}

matrix& matrix::alokuj(int new_n) {
    
    n = new_n;
    data = std::make_unique<int[]>(n * n);
    return *this;
}

matrix& matrix::wstaw(int x, int y, int wartosc) {
    at(x, y) = wartosc;
    return *this;
}

matrix matrix::operator+(const matrix& m) const {
    matrix result(n);
    for (int i = 0; i < n * n; ++i) result.data[i] = data[i] + m.data[i];
    return result; 
}