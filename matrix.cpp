/**
 * @file matrix.cpp
 * @brief Implementacja klasy matrix
 */

#include "matrix.h"
#include <cstdlib>
#include <ctime>

 // ==================== Konstruktory i destruktor ====================

 /**
  * @brief Konstruktor domyślny - tworzy pustą macierz o rozmiarze 0x0
  */
matrix::matrix(void) : n(0), allocated_n(0), macierz_ptr(nullptr) {}

/**
 * @brief Konstruktor parametryczny - tworzy macierz n×n wypełnioną zerami
 * @param n Rozmiar macierzy kwadratowej
 */
matrix::matrix(int n) : n(n), allocated_n(n) {
    macierz_ptr = std::make_unique<int[]>(n * n);
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] = 0;
    }
}

/**
 * @brief Konstruktor z tablicą - tworzy macierz n×n wypełnioną wartościami z tablicy
 * @param n Rozmiar macierzy kwadratowej
 * @param t Wskaźnik do tablicy z danymi (wymaga n*n elementów)
 */
matrix::matrix(int n, int* t) : n(n), allocated_n(n) {
    macierz_ptr = std::make_unique<int[]>(n * n);
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] = t[i];
    }
}

/**
 * @brief Konstruktor kopiujący - tworzy głęboką kopię macierzy
 * @param m Macierz źródłowa do skopiowania
 */
matrix::matrix(const matrix& m) : n(m.n), allocated_n(m.allocated_n) {
    macierz_ptr = std::make_unique<int[]>(n * n);
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] = m.macierz_ptr[i];
    }
}

/**
 * @brief Destruktor - zwalnia automatycznie pamięć dzięki unique_ptr
 */
matrix::~matrix(void) {}

// ==================== Metody dostępowe ====================

/**
 * @brief Zwraca referencję do elementu macierzy z walidacją
 * @param x Indeks wiersza (0-based)
 * @param y Indeks kolumny (0-based)
 * @return Referencja do elementu umożliwiająca modyfikację
 * @throw std::logic_error Jeśli współrzędne są poza zakresem
 */
int& matrix::at(int x, int y) {
    if (x >= n || y >= n || x < 0 || y < 0)
        throw std::logic_error("Zle wspolrzedne macierzy");
    return macierz_ptr[x * n + y];
}

/**
 * @brief Zwraca stałą referencję do elementu macierzy
 * @param x Indeks wiersza (0-based)
 * @param y Indeks kolumny (0-based)
 * @return Stała referencja do elementu (tylko odczyt)
 */
const int& matrix::at(int x, int y) const {
    return macierz_ptr[x * n + y];
}

// ==================== Metody losowania i wypełniania ====================

/**
 * @brief Wypełnia macierz losowymi liczbami z zakresu [0, 9]
 * @return Referencja do bieżącej macierzy (umożliwia łańcuchowanie wywołań)
 */
matrix& matrix::losuj(void) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] = dis(gen);
    }
    return *this;
}

/**
 * @brief Wypełnia macierz losowymi liczbami z zakresu [0, x]
 * @param x Górna granica zakresu losowania
 * @return Referencja do bieżącej macierzy
 */
matrix& matrix::losuj(int x) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, x);
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] = dis(gen);
    }
    return *this;
}

/**
 * @brief Wypełnia macierz wzorem szachownicy (naprzemienne 0 i 1)
 * @details Pola gdzie (i+j) jest nieparzyste otrzymują wartość 1, pozostałe 0
 * @return Referencja do bieżącej macierzy
 */
matrix& matrix::szachownica(void) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            at(i, j) = ((i + j) % 2 != 0) ? 1 : 0;
        }
    }
    return *this;
}

// ==================== Operator wyjścia ====================

/**
 * @brief Operator wyjścia - wypisuje macierz do strumienia
 * @details Każdy wiersz w osobnej linii, elementy oddzielone spacjami
 * @param o Strumień wyjściowy
 * @param m Macierz do wypisania
 * @return Referencja do strumienia (umożliwia łańcuchowanie)
 */
std::ostream& operator<<(std::ostream& o, const matrix& m) {
    for (int i = 0; i < m.n; ++i) {
        for (int j = 0; j < m.n; ++j) o << m.at(i, j) << " ";
        o << "\n";
    }
    return o;
}

// ==================== Operatory arytmetyczne ze skalarami ====================

/**
 * @brief Dodaje skalar do wszystkich elementów macierzy (operator +=)
 * @param a Wartość do dodania
 * @return Referencja do bieżącej macierzy
 */
matrix& matrix::operator+=(int a) {
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] += a;
    }
    return *this;
}

/**
 * @brief Odejmuje skalar od wszystkich elementów macierzy (operator -=)
 * @param a Wartość do odjęcia
 * @return Referencja do bieżącej macierzy
 */
matrix& matrix::operator-=(int a) {
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] -= a;
    }
    return *this;
}

/**
 * @brief Mnoży wszystkie elementy macierzy przez skalar (operator *=)
 * @param a Mnożnik
 * @return Referencja do bieżącej macierzy
 */
matrix& matrix::operator*=(int a) {
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] *= a;
    }
    return *this;
}

/**
 * @brief Postinkrementacja - zwiększa wszystkie elementy o 1
 * @return Kopia macierzy sprzed inkrementacji
 */
matrix matrix::operator++(int) {
    matrix temp(n);
    for (int i = 0; i < n * n; ++i) {
        temp.macierz_ptr[i] = macierz_ptr[i];
        macierz_ptr[i]++;
    }
    return temp;
}

/**
 * @brief Transponuje macierz (zamienia wiersze z kolumnami)
 * @details Odbija macierz względem głównej przekątnej
 * @return Referencja do bieżącej macierzy
 */
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

/**
 * @brief Ustawia wartości na głównej przekątnej macierzy
 * @param t Tablica z wartościami (wymaga n elementów)
 * @return Referencja do bieżącej macierzy
 */
matrix& matrix::diagonalna(int* t) {
    for (int i = 0; i < n; ++i) {
        at(i, i) = t[i];
    }
    return *this;
}

/**
 * @brief Ustawia wartości na k-tej przekątnej macierzy
 * @param k Numer przekątnej (0=główna, >0=nad główną, <0=pod główną)
 * @param t Tablica z wartościami
 * @return Referencja do bieżącej macierzy
 */
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

/**
 * @brief Ustawia wartości w wybranej kolumnie
 * @param x Indeks kolumny
 * @param t Tablica z wartościami (wymaga n elementów)
 * @return Referencja do bieżącej macierzy
 * @throw std::logic_error Jeśli indeks jest poza zakresem
 */
matrix& matrix::kolumna(int x, int* t) {
    if (x >= n) throw std::logic_error("Zly indeks kolumny");
    for (int i = 0; i < n; ++i) {
        at(i, x) = t[i];
    }
    return *this;
}

/**
 * @brief Ustawia wartości w wybranym wierszu
 * @param y Indeks wiersza
 * @param t Tablica z wartościami (wymaga n elementów)
 * @return Referencja do bieżącej macierzy
 * @throw std::logic_error Jeśli indeks jest poza zakresem
 */
matrix& matrix::wiersz(int y, int* t) {
    if (y >= n) throw std::logic_error("Zly indeks wiersza");
    for (int i = 0; i < n; ++i) {
        at(y, i) = t[i];
    }
    return *this;
}

/**
 * @brief Tworzy macierz jednostkową (jedynki na głównej przekątnej, reszta zera)
 * @return Referencja do bieżącej macierzy
 */
matrix& matrix::przekatna(void) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            at(i, j) = (i == j) ? 1 : 0;
        }
    }
    return *this;
}

/**
 * @brief Wypełnia jedynkami obszar pod główną przekątną, reszta zera
 * @return Referencja do bieżącej macierzy
 */
matrix& matrix::pod_przekatna(void) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            at(i, j) = (i > j) ? 1 : 0;
        }
    }
    return *this;
}

/**
 * @brief Wypełnia jedynkami obszar nad główną przekątna, reszta zera
 * @return Referencja do bieżącej macierzy
 */
matrix& matrix::nad_przekatna(void) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            at(i, j) = (i < j) ? 1 : 0;
        }
    }
    return *this;
}

/**
 * @brief Alokuje lub realokuje pamięć dla macierzy o nowym rozmiarze
 * @details Jeżeli macierz nie ma jeszcze zaalokowanej pamięci lub
 * aktualnie zaalokowana pamięć jest mniejsza niż wymagana,
 * pamięć zostaje zaalokowana ponownie w rozmiarze rozmiar × rozmiar.
 * Jeżeli zaalokowanej pamięci jest więcej niż potrzeba,
 * istniejąca alokacja zostaje zachowana bez zmian.
 * @param rozmiar Nowy rozmiar logiczny macierzy (musi być > 0)
 * @return Referencja do bieżącego obiektu macierzy
 * @throw std::logic_error Gdy rozmiar <= 0
 */
matrix& matrix::alokuj(int rozmiar) {
    if (rozmiar <= 0)
        throw std::logic_error("Rozmiar musi byc dodatni");

    // Brak pamięci lub za mało pamięci
    if (allocated_n == 0 || allocated_n < rozmiar) {
        macierz_ptr = std::make_unique<int[]>(rozmiar * rozmiar);
        allocated_n = rozmiar;

        for (int i = 0; i < rozmiar * rozmiar; ++i)
            macierz_ptr[i] = 0;
    }

    // ZAWSZE ustawiamy aktualny rozmiar logiczny
    n = rozmiar;
    return *this;
}

/**
 * @brief Postdekrementacja - zmniejsza wszystkie elementy o 1
 * @return Kopia macierzy sprzed dekrementacji
 */
matrix matrix::operator--(int) {
    matrix temp(n);
    for (int i = 0; i < n * n; ++i) {
        temp.macierz_ptr[i] = macierz_ptr[i];
        macierz_ptr[i]--;
    }
    return temp;
}

/**
 * @brief Operator wywołania - dodaje wartość całkowitą do wszystkich elementów
 * @param d Wartość zmiennoprzecinkowa (konwertowana na int)
 * @return Referencja do bieżącej macierzy
 */
matrix& matrix::operator()(double d) {
    int wartosc = static_cast<int>(d);
    for (int i = 0; i < n * n; ++i) {
        macierz_ptr[i] += wartosc;
    }
    return *this;
}

/**
 * @brief Operator równości - sprawdza czy dwie macierze są identyczne
 * @param m Macierz do porównania
 * @return true jeśli macierze mają ten sam rozmiar i wszystkie elementy są równe
 */
bool matrix::operator==(const matrix& m) const {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i) {
        if (macierz_ptr[i] != m.macierz_ptr[i]) return false;
    }
    return true;
}

/**
 * @brief Operator większości - sprawdza czy wszystkie elementy są większe
 * @param m Macierz do porównania
 * @return true jeśli każdy element tej macierzy > odpowiadający element m
 */
bool matrix::operator>(const matrix& m) const {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i) {
        if (macierz_ptr[i] <= m.macierz_ptr[i]) return false;
    }
    return true;
}

/**
 * @brief Operator mniejszości - sprawdza czy wszystkie elementy są mniejsze
 * @param m Macierz do porównania
 * @return true jeśli każdy element tej macierzy < odpowiadający element m
 */
bool matrix::operator<(const matrix& m) const {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i) {
        if (macierz_ptr[i] >= m.macierz_ptr[i]) return false;
    }
    return true;
}

/**
 * @brief Dodaje dwie macierze element po elemencie
 * @param m1 Pierwsza macierz
 * @param m2 Druga macierz
 * @return Nowa macierz będąca sumą
 * @throw std::logic_error Jeśli macierze mają różne rozmiary
 */
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

/**
 * @brief Wykonuje mnożenie macierzowe
 * @param m1 Pierwsza macierz
 * @param m2 Druga macierz
 * @return Nowa macierz będąca iloczynem macierzowym
 * @throw std::logic_error Jeśli macierze mają różne rozmiary
 */
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

/**
 * @brief Dodaje skalar do macierzy (macierz + liczba)
 * @param m Macierz
 * @param a Wartość do dodania
 * @return Nowa macierz z dodaną wartością do każdego elementu
 */
matrix operator+(const matrix& m, int a) {
    matrix wynik(m.n);
    for (int i = 0; i < m.n * m.n; ++i) {
        wynik.macierz_ptr[i] = m.macierz_ptr[i] + a;
    }
    return wynik;
}

/**
 * @brief Dodaje skalar do macierzy (liczba + macierz)
 * @param a Wartość do dodania
 * @param m Macierz
 * @return Nowa macierz z dodaną wartością do każdego elementu
 */
matrix operator+(int a, const matrix& m) {
    matrix wynik(m.n);
    for (int i = 0; i < m.n * m.n; ++i) {
        wynik.macierz_ptr[i] = a + m.macierz_ptr[i];
    }
    return wynik;
}

/**
 * @brief Mnoży macierz przez skalar (macierz * liczba)
 * @param m Macierz
 * @param a Mnożnik
 * @return Nowa macierz z pomnożonymi elementami
 */
matrix operator*(const matrix& m, int a) {
    matrix wynik(m.n);
    for (int i = 0; i < m.n * m.n; ++i) {
        wynik.macierz_ptr[i] = m.macierz_ptr[i] * a;
    }
    return wynik;
}

/**
 * @brief Mnoży skalar przez macierz (liczba * macierz)
 * @param a Mnożnik
 * @param m Macierz
 * @return Nowa macierz z pomnożonymi elementami
 */
matrix operator*(int a, const matrix& m) {
    return m * a;
}

/**
 * @brief Odejmuje skalar od macierzy (macierz - liczba)
 * @param m Macierz
 * @param a Wartość do odjęcia
 * @return Nowa macierz z odjętą wartością
 */
matrix operator-(const matrix& m, int a) {
    matrix wynik(m.n);
    for (int i = 0; i < m.n * m.n; ++i) {
        wynik.macierz_ptr[i] = m.macierz_ptr[i] - a;
    }
    return wynik;
}

/**
 * @brief Odejmuje macierz od skalara (liczba - macierz)
 * @param a Wartość bazowa
 * @param m Macierz
 * @return Nowa macierz gdzie każdy element = a - element_macierzy
 */
matrix operator-(int a, const matrix& m) {
    matrix wynik(m.n);
    for (int i = 0; i < m.n * m.n; ++i) {
        wynik.macierz_ptr[i] = a - m.macierz_ptr[i];
    }
    return wynik;
}