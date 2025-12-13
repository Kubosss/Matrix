#include "matrix.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <stdexcept>

/* ================== KONSTRUKTORY ================== */

matrix::matrix(void)
    : n(0), allocated_n(0), macierz_ptr(nullptr) {}

matrix::matrix(int n)
    : n(n), allocated_n(n) {
    macierz_ptr = std::make_unique<int[]>(n * n);
    for (int i = 0; i < n * n; i++)
        macierz_ptr[i] = 0;
}

matrix::matrix(int n, int* t)
    : n(n), allocated_n(n) {
    macierz_ptr = std::make_unique<int[]>(n * n);
    for (int i = 0; i < n * n; i++)
        macierz_ptr[i] = t[i];
}

matrix::matrix(const matrix& m)  // <-- konstruktor kopiujący
    : n(m.n), allocated_n(m.n) {
    macierz_ptr = std::make_unique<int[]>(n * n);
    for (int i = 0; i < n * n; i++)
        macierz_ptr[i] = m.macierz_ptr[i];
}

/* ================== OPERATOR PRZYPISANIA KOPIUJĄCEGO ================== */

matrix& matrix::operator=(const matrix& other) {
    if (this != &other) {
        n = other.n;
        allocated_n = other.allocated_n;
        macierz_ptr = std::make_unique<int[]>(n * n);
        for (int i = 0; i < n * n; ++i)
            macierz_ptr[i] = other.macierz_ptr[i];
    }
    return *this;
}

/* ================== DESTRUKTOR ================== */

matrix::~matrix(void) {}

/* ================== ALOKACJA ================== */

matrix& matrix::alokuj(int size) {
    if (!macierz_ptr || allocated_n < size) {
        macierz_ptr.reset();
        macierz_ptr = std::make_unique<int[]>(size * size);
        allocated_n = size;
    }
    n = size;
    return *this;
}

/* ================== DOSTĘP ================== */

int& matrix::at(int x, int y) {
    if (x < 0 || y < 0 || x >= n || y >= n)
        throw std::logic_error("Niepoprawny indeks macierzy");
    return macierz_ptr[x * n + y];
}

const int& matrix::at(int x, int y) const {
    if (x < 0 || y < 0 || x >= n || y >= n)
        throw std::logic_error("Niepoprawny indeks macierzy");
    return macierz_ptr[x * n + y];
}

int matrix::pokaz(int x, int y) {
    return at(x, y);
}

matrix& matrix::wstaw(int x, int y, int v) {
    at(x, y) = v;
    return *this;
}

/* ================== LOSOWANIE ================== */

matrix& matrix::losuj(void) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(0, 9);

    for (int i = 0; i < n * n; i++)
        macierz_ptr[i] = dist(gen);

    return *this;
}

matrix& matrix::losuj(int x) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(0, 9);

    for (int i = 0; i < x && i < n * n; i++) {
        int pos = gen() % (n * n);
        macierz_ptr[pos] = dist(gen);
    }
    return *this;
}

/* ================== WZORY ================== */

matrix& matrix::odwroc(void) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            std::swap(at(i, j), at(j, i));
    return *this;
}

matrix& matrix::diagonalna(int* t) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            at(i, j) = (i == j) ? t[i] : 0;
    return *this;
}

matrix& matrix::diagonalna_k(int k, int* t) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            at(i, j) = 0;

    for (int i = 0; i < n; i++) {
        int r = i;
        int c = i + k;
        if (c >= 0 && c < n)
            at(r, c) = t[i];
    }
    return *this;
}

matrix& matrix::kolumna(int x, int* t) {
    if (x < 0 || x >= n)
        throw std::logic_error("Zly indeks kolumny");
    for (int i = 0; i < n; i++)
        at(i, x) = t[i];
    return *this;
}

matrix& matrix::wiersz(int y, int* t) {
    if (y < 0 || y >= n)
        throw std::logic_error("Zly indeks wiersza");
    for (int i = 0; i < n; i++)
        at(y, i) = t[i];
    return *this;
}

matrix& matrix::przekatna(void) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            at(i, j) = (i == j) ? 1 : 0;
    return *this;
}

matrix& matrix::pod_przekatna(void) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            at(i, j) = (i > j) ? 1 : 0;
    return *this;
}

matrix& matrix::nad_przekatna(void) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            at(i, j) = (i < j) ? 1 : 0;
    return *this;
}

matrix& matrix::szachownica(void) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            at(i, j) = (i + j) % 2;
    return *this;
}

/* ================== OPERATORY MACIERZY ================== */

matrix matrix::operator+(matrix& m) {
    if (n != m.n)
        throw std::logic_error("Rozne rozmiary macierzy");
    matrix r(n);
    for (int i = 0; i < n * n; i++)
        r.macierz_ptr[i] = macierz_ptr[i] + m.macierz_ptr[i];
    return r;
}

matrix matrix::operator*(matrix& m) {
    if (n != m.n)
        throw std::logic_error("Nie mozna mnozyc macierzy o roznych rozmiarach");

    matrix r(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            r.at(i, j) = 0;
            for (int k = 0; k < n; k++)
                r.at(i, j) += at(i, k) * m.at(k, j);
        }
    return r;
}

/* ================== OPERATORY INT ================== */

matrix matrix::operator+(int a) {
    matrix r(n);
    for (int i = 0; i < n * n; i++)
        r.macierz_ptr[i] = macierz_ptr[i] + a;
    return r;
}

matrix matrix::operator-(int a) {
    matrix r(n);
    for (int i = 0; i < n * n; i++)
        r.macierz_ptr[i] = macierz_ptr[i] - a;
    return r;
}

matrix matrix::operator*(int a) {
    matrix r(n);
    for (int i = 0; i < n * n; i++)
        r.macierz_ptr[i] = macierz_ptr[i] * a;
    return r;
}

/* ================== OPERATORY PRZYPISANIA INT ================== */

matrix& matrix::operator+=(int a) {
    for (int i = 0; i < n * n; i++)
        macierz_ptr[i] += a;
    return *this;
}

matrix& matrix::operator-=(int a) {
    for (int i = 0; i < n * n; i++)
        macierz_ptr[i] -= a;
    return *this;
}

matrix& matrix::operator*=(int a) {
    for (int i = 0; i < n * n; i++)
        macierz_ptr[i] *= a;
    return *this;
}

/* ================== OPERATORY GLOBALNE ================== */

matrix operator+(int a, matrix& m) { return m + a; }
matrix operator-(int a, matrix& m) {
    matrix r(m.n);
    for (int i = 0; i < m.n * m.n; i++)
        r.macierz_ptr[i] = a - m.macierz_ptr[i];
    return r;
}
matrix operator*(int a, matrix& m) { return m * a; }
/* ================== INKREMENTACJA ================== */

matrix matrix::operator++(int) {
    matrix tmp(*this);
    for (int i = 0; i < n * n; i++)
        macierz_ptr[i]++;
    return tmp;
}

matrix matrix::operator--(int) {
    matrix tmp(*this);
    for (int i = 0; i < n * n; i++)
        macierz_ptr[i]--;
    return tmp;
}

/* ================== FUNKTOR ================== */

matrix& matrix::operator()(double d) {
    int x = static_cast<int>(d);
    for (int i = 0; i < n * n; i++)
        macierz_ptr[i] += x;
    return *this;
}

/* ================== POROWNANIA ================== */

bool matrix::operator==(const matrix& m) {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; i++)
        if (macierz_ptr[i] != m.macierz_ptr[i])
            return false;
    return true;
}

bool matrix::operator>(const matrix& m) {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; i++)
        if (macierz_ptr[i] <= m.macierz_ptr[i])
            return false;
    return true;
}

bool matrix::operator<(const matrix& m) {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; i++)
        if (macierz_ptr[i] >= m.macierz_ptr[i])
            return false;
    return true;
}

/* ================== WYJSCIE ================== */

std::ostream& operator<<(std::ostream& o, const matrix& m) {
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++)
            o << m.at(i, j) << " ";
        o << "\n";
    }
    return o;
}