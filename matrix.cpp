#include "matrix.h"

int& matrix::at(int x, int y) {
    if (x >= n || y >= n)
        throw std::logic_error("Zle wspolrzedne macierzy");
    return macierz_ptr[x * n + y];
}

const int& matrix::at(int x, int y) const {
    return macierz_ptr[x * n + y];
}

matrix& matrix::losuj(void) {
    std::srand(time(NULL));
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] = std::rand() % 10;
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