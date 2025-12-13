#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>

class matrix {
private:
    int n;
    int allocated_n;
    std::unique_ptr<int[]> macierz_ptr;

    int idx(int x, int y) const { return x * n + y; }

public:
    /* ================== KONSTRUKTORY ================== */
    matrix(void);
    matrix(int n);
    matrix(int n, int* t);
    matrix(const matrix& m);           // konstruktor kopiujący
    matrix(matrix&& m) noexcept = default; // konstruktor przenoszący
    ~matrix(void);

    /* ================== OPERATOR PRZYPISANIA ================== */
    matrix& operator=(const matrix& m); // operator przypisania kopiującego
    matrix& operator=(matrix&& m) noexcept = default; // operator przypisania przenoszącego

    /* ================== ALOKACJA ================== */
    matrix& alokuj(int n);

    /* ================== DOSTĘP ================== */
    int& at(int x, int y);
    const int& at(int x, int y) const;
    int pokaz(int x, int y);
    matrix& wstaw(int x, int y, int v);

    /* ================== WZORY ================== */
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

    /* ================== OPERATORY MACIERZY ================== */
    matrix operator+(matrix& m);
    matrix operator*(matrix& m);

    /* ================== OPERATORY INT ================== */
    matrix operator+(int a);
    matrix operator*(int a);
    matrix operator-(int a);

    matrix& operator+=(int a);
    matrix& operator-=(int a);
    matrix& operator*=(int a);

    matrix operator++(int);
    matrix operator--(int);

    matrix& operator()(double d);

    /* ================== PORÓWNANIA ================== */
    bool operator==(const matrix& m);
    bool operator<(const matrix& m);
    bool operator>(const matrix& m);

    /* ================== FRIEND ================== */
    friend matrix operator+(int a, matrix& m);
    friend matrix operator*(int a, matrix& m);
    friend matrix operator-(int a, matrix& m);

    friend std::ostream& operator<<(std::ostream& o, const matrix& m);
};

#endif