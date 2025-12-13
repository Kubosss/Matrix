#include "matrix.h"
#include <cstdlib>
#include <ctime>

matrix::matrix(void) : n(0), allocated_n(0), macierz_ptr(nullptr) {}

matrix::matrix(int n) : n(n), allocated_n(n) {
    macierz_ptr = std::make_unique<int[]>(n * n);
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] = 0;
    }
}

matrix::matrix(int n, int* t) : n(n), allocated_n(n) {
    macierz_ptr = std::make_unique<int[]>(n * n);
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] = t[i];
    }
}

matrix::matrix(const matrix& m) : n(m.n), allocated_n(m.allocated_n) {
    macierz_ptr = std::make_unique<int[]>(n * n);
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] = m.macierz_ptr[i];
    }
}

matrix::~matrix(void) {}

int& matrix::at(int x, int y) {
    if (x >= n || y >= n || x < 0 || y < 0)
        throw std::logic_error("Zle wspolrzedne macierzy");
    return macierz_ptr[x * n + y];
}

const int& matrix::at(int x, int y) const {
    return macierz_ptr[x * n + y];
}

matrix& matrix::losuj(void) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] = dis(gen);
    }
    return *this;
}

matrix& matrix::losuj(int x) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, x);
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] = dis(gen);
    }
    return *this;
}

matrix& matrix::szachownica(void) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            at(i, j) = ((i + j) % 2 != 0) ? 1 : 0;
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& o, const matrix& m) {
    for (int i = 0; i < m.n; ++i) {
        for (int j = 0; j < m.n; ++j) o << m.at(i, j) << " ";
        o << "\n";
    }
    return o;
}

matrix& matrix::operator+=(int a) {
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] += a;
    }
    return *this;
}

matrix& matrix::operator-=(int a) {
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] -= a;
    }
    return *this;
}

matrix& matrix::operator*=(int a) {
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] *= a;
    }
    return *this;
}

matrix matrix::operator++(int) {
    matrix temp(n);
    for (int i = 0; i < n * n; ++i) {
        temp.macierz_ptr[i] = macierz_ptr[i];
        macierz_ptr[i]++;
    }
    return temp;
}

matrix& matrix::odwroc(void) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int temp = at(i, j);
            at(i, j) = at(j, i);
            at(j, i) = temp;
        }
    }
    return *this;
}

matrix& matrix::diagonalna(int* t) {
    for (int i = 0; i < n; ++i) {
        at(i, i) = t[i];
    }
    return *this;
}

matrix& matrix::diagonalna_k(int k, int* t) {
    if (k == 0) return diagonalna(t);
    int offset = abs(k);
    int limit = (k > 0) ? (n - k) : (n + k);
    for (int i = 0; i < limit; ++i) {
        int row = (k > 0) ? i : (i + offset);
        int col = (k > 0) ? (i + offset) : i;
        at(row, col) = t[i];
    }
    return *this;
}

matrix& matrix::kolumna(int x, int* t) {
    if (x >= n) throw std::logic_error("Zly indeks kolumny");
    for (int i = 0; i < n; ++i) {
        at(i, x) = t[i];
    }
    return *this;
}

matrix& matrix::wiersz(int y, int* t) {
    if (y >= n) throw std::logic_error("Zly indeks wiersza");
    for (int i = 0; i < n; ++i) {
        at(y, i) = t[i];
    }
    return *this;
}

matrix& matrix::przekatna(void) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            at(i, j) = (i == j) ? 1 : 0;
        }
    }
    return *this;
}

matrix& matrix::pod_przekatna(void) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            at(i, j) = (i > j) ? 1 : 0;
        }
    }
    return *this;
}

matrix& matrix::nad_przekatna(void) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            at(i, j) = (i < j) ? 1 : 0;
        }
    }
    return *this;
}

matrix& matrix::alokuj(int rozmiar) {
    if (rozmiar <= 0) {
        throw std::logic_error("Rozmiar musi byc dodatni");
    }
    
    if (allocated_n == 0) {
        allocated_n = rozmiar;
        n = rozmiar;
        macierz_ptr = std::make_unique<int[]>(rozmiar * rozmiar);
        for (int i = 0; i < rozmiar * rozmiar; ++i) {
            macierz_ptr[i] = 0;
        }
    } else if (allocated_n < rozmiar) {
        allocated_n = rozmiar;
        n = rozmiar;
        macierz_ptr = std::make_unique<int[]>(rozmiar * rozmiar);
        for (int i = 0; i < rozmiar * rozmiar; ++i) {
            macierz_ptr[i] = 0;
        }
    }
    
    return *this;
}

matrix matrix::operator--(int) {
    matrix temp(n);
    for (int i = 0; i < n * n; ++i) {
        temp.macierz_ptr[i] = macierz_ptr[i];
        macierz_ptr[i]--;
    }
    return temp;
}

matrix& matrix::operator()(double d) {
    int wartosc = static_cast<int>(d);
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] += wartosc;
    }
    return *this;
}

bool matrix::operator==(const matrix& m) const {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i) {
        if (macierz_ptr[i] != m.macierz_ptr[i]) return false;
    }
    return true;
}

bool matrix::operator>(const matrix& m) const {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i) {
        if (macierz_ptr[i] <= m.macierz_ptr[i]) return false;
    }
    return true;
}

bool matrix::operator<(const matrix& m) const {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i) {
        if (macierz_ptr[i] >= m.macierz_ptr[i]) return false;
    }
    return true;
}

matrix operator+(const matrix& m1, const matrix& m2) {
    if (m1.n != m2.n) {
        throw std::logic_error("Macierze muszą mieć ten sam rozmiar do dodawania");
    }
    matrix wynik(m1.n);
    for (int i = 0; i < m1.n * m1.n; ++i) {
        wynik.macierz_ptr[i] = m1.macierz_ptr[i] + m2.macierz_ptr[i];
    }
    return wynik;
}

matrix operator*(const matrix& m1, const matrix& m2) {
    if (m1.n != m2.n) {
        throw std::logic_error("Macierze muszą mieć ten sam rozmiar do mnożenia");
    }
    matrix wynik(m1.n);
    for (int i = 0; i < m1.n; ++i) {
        for (int j = 0; j < m1.n; ++j) {
            int suma = 0;
            for (int k = 0; k < m1.n; ++k) {
                suma += m1.at(i, k) * m2.at(k, j);
            }
            wynik.at(i, j) = suma;
        }
    }
    return wynik;
}

matrix operator+(const matrix& m, int a) {
    matrix wynik(m.n);
    for (int i = 0; i < m.n * m.n; ++i) {
        wynik.macierz_ptr[i] = m.macierz_ptr[i] + a;
    }
    return wynik;
}

matrix operator+(int a, const matrix& m) {
    matrix wynik(m.n);
    for (int i = 0; i < m.n * m.n; ++i) {
        wynik.macierz_ptr[i] = a + m.macierz_ptr[i];
    }
    return wynik;
}

matrix operator*(const matrix& m, int a) {
    matrix wynik(m.n);
    for (int i = 0; i < m.n * m.n; ++i) {
        wynik.macierz_ptr[i] = m.macierz_ptr[i] * a;
    }
    return wynik;
}

matrix operator*(int a, const matrix& m) {
    return m * a;
}

matrix operator-(const matrix& m, int a) {
    matrix wynik(m.n);
    for (int i = 0; i < m.n * m.n; ++i) {
        wynik.macierz_ptr[i] = m.macierz_ptr[i] - a;
    }
    return wynik;
}

matrix operator-(int a, const matrix& m) {
    matrix wynik(m.n);
    for (int i = 0; i < m.n * m.n; ++i) {
        wynik.macierz_ptr[i] = a - m.macierz_ptr[i];
    }
    return wynik;
}