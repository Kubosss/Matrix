#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <iomanip>

class matrix {
private:
    int n;
    int allocated_n;
    std::unique_ptr<int[]> macierz_ptr;

public:
    matrix(void);
    matrix(int n);
    matrix(const matrix& other) = delete;
    matrix(matrix&& other) noexcept = default;
    ~matrix(void);

    int& at(int x, int y);
    const int& at(int x, int y) const;

    matrix& odwroc(void);
    matrix& losuj(void);
    matrix& losuj(int x);

    matrix& diagonalna(int* t);
    matrix& diagonalna_k(int k, int* t);
    matrix& kolumna(int x, int* t);
    matrix& wiersz(int y, int* t);

    matrix& przekatna(void);
    matrix& pod_przekatna(void);
    matrix& nad_przekatna(void);
    matrix& szachownica(void);

    matrix& operator+=(int a);
    matrix& operator-=(int a);
    matrix& operator*=(int a);
    matrix operator++(int);

    friend matrix operator+(const matrix& m1, const matrix& m2);
    friend matrix operator+(int a, const matrix& m);
    friend std::ostream& operator<<(std::ostream& o, const matrix& m);

    void wstaw(int x, int y, int val) { at(x, y) = val; }

    int getSize() const { return n; }
};
#endif