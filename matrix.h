#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <memory>
#include <algorithm>
#include <stdexcept>


class matrix {
private:
   
    std::unique_ptr<int[]> data; 
    int n;
    int allocated_n;

    
    int& at(int x, int y);
    const int& at(int x, int y) const;

public:
    
    matrix(void);
    matrix(int n);
    matrix(int n, int* t);
    matrix(const matrix& m);
    ~matrix(void);

   
    matrix& alokuj(int n);

   
    matrix& wstaw(int x, int y, int wartosc);
    int pokaz(int x, int y) const;
    int getSize() const { return n; }

    
    matrix operator+(const matrix& m) const;
    matrix operator*(const matrix& m) const;
    matrix operator+(int a) const;
    matrix operator-(int a) const;
    
    
    matrix& odwroc(void);
    matrix& losuj(void);
    matrix& losuj(int x);
    matrix& szachownica(void);
    
    friend std::ostream& operator<<(std::ostream& o, const matrix& m);
};
#endif