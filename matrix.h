#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <iomanip>

/**
 * @file matrix.h
 * @brief Deklaracja klasy matrix reprezentującej macierz kwadratową liczb całkowitych
 */

 /**
  * @class matrix
  * @brief Klasa reprezentująca kwadratową macierz liczb całkowitych
  *
  * Klasa zapewnia pełną funkcjonalność operacji na macierzach kwadratowych,
  * w tym operacje arytmetyczne, porównania, transformacje i wypełnianie wzorami.
  * Pamięć jest zarządzana automatycznie przez std::unique_ptr.
  */
class matrix {
private:
    int n;                              ///< Aktualny rozmiar macierzy (n×n)
    int allocated_n;                    ///< Rozmiar zaalokowanej pamięci
    std::unique_ptr<int[]> macierz_ptr; ///< Wskaźnik do danych macierzy (przechowywane wierszami)

public:
    // ==================== Konstruktory i destruktor ====================

    /**
     * @brief Konstruktor domyślny tworzący pustą macierz 0×0
     */
    matrix(void);

    /**
     * @brief Konstruktor tworzący macierz n×n wypełnioną zerami
     * @param n Rozmiar macierzy kwadratowej
     */
    matrix(int n);

    /**
     * @brief Konstruktor tworzący macierz n×n z danymi z tablicy
     * @param n Rozmiar macierzy kwadratowej
     * @param t Wskaźnik do tablicy zawierającej n*n elementów
     */
    matrix(int n, int* t);

    /**
     * @brief Konstruktor kopiujący - tworzy głęboką kopię macierzy
     * @param m Macierz źródłowa do skopiowania
     */
    matrix(const matrix& m);

    /**
     * @brief Konstruktor przenoszący (domyślny)
     * @param other Macierz do przeniesienia
     */
    matrix(matrix&& other) noexcept = default;

    /**
     * @brief Destruktor
     */
    ~matrix(void);

    // ==================== Metody dostępowe ====================

    /**
     * @brief Zwraca referencję do elementu macierzy z walidacją
     * @param x Indeks wiersza (0-based)
     * @param y Indeks kolumny (0-based)
     * @return Referencja do elementu umożliwiająca modyfikację
     * @throw std::logic_error Jeśli współrzędne są poza zakresem
     */
    int& at(int x, int y);

    /**
     * @brief Zwraca stałą referencję do elementu macierzy
     * @param x Indeks wiersza (0-based)
     * @param y Indeks kolumny (0-based)
     * @return Stała referencja do elementu (tylko odczyt)
     */
    const int& at(int x, int y) const;

    /**
     * @brief Zwraca wartość elementu macierzy (alias dla at)
     * @param x Indeks wiersza
     * @param y Indeks kolumny
     * @return Wartość elementu
     */
    int pokaz(int x, int y) const { return at(x, y); }

    // ==================== Alokacja ====================

    /**
     * @brief Alokuje lub realokuje pamięć dla macierzy o nowym rozmiarze
     * @param n Nowy rozmiar macierzy (musi być > 0)
     * @return Referencja do bieżącej macierzy (umożliwia łańcuchowanie)
     * @throw std::logic_error Jeśli rozmiar <= 0
     */
    matrix& alokuj(int n);

    // ==================== Metody transformacji macierzy ====================

    /**
     * @brief Transponuje macierz (zamienia wiersze z kolumnami)
     * @return Referencja do bieżącej macierzy
     */
    matrix& odwroc(void);

    /**
     * @brief Wypełnia macierz losowymi liczbami z zakresu [0, 9]
     * @return Referencja do bieżącej macierzy
     */
    matrix& losuj(void);

    /**
     * @brief Wypełnia macierz losowymi liczbami z zakresu [0, x]
     * @param x Górna granica zakresu losowania
     * @return Referencja do bieżącej macierzy
     */
    matrix& losuj(int x);

    /**
     * @brief Ustawia wartości na głównej przekątnej macierzy
     * @param t Tablica zawierająca n wartości dla przekątnej
     * @return Referencja do bieżącej macierzy
     */
    matrix& diagonalna(int* t);

    /**
     * @brief Ustawia wartości na k-tej przekątnej macierzy
     * @param k Numer przekątnej (0=główna, >0=nad główną, <0=pod główną)
     * @param t Tablica z wartościami dla przekątnej
     * @return Referencja do bieżącej macierzy
     */
    matrix& diagonalna_k(int k, int* t);

    /**
     * @brief Ustawia wartości w wybranej kolumnie
     * @param x Indeks kolumny
     * @param t Tablica zawierająca n wartości dla kolumny
     * @return Referencja do bieżącej macierzy
     * @throw std::logic_error Jeśli indeks kolumny jest poza zakresem
     */
    matrix& kolumna(int x, int* t);

    /**
     * @brief Ustawia wartości w wybranym wierszu
     * @param y Indeks wiersza
     * @param t Tablica zawierająca n wartości dla wiersza
     * @return Referencja do bieżącej macierzy
     * @throw std::logic_error Jeśli indeks wiersza jest poza zakresem
     */
    matrix& wiersz(int y, int* t);

    /**
     * @brief Tworzy macierz jednostkową (1 na przekątnej, 0 poza)
     * @return Referencja do bieżącej macierzy
     */
    matrix& przekatna(void);

    /**
     * @brief Wypełnia jedynkami obszar pod główną przekątną
     * @return Referencja do bieżącej macierzy
     */
    matrix& pod_przekatna(void);

    /**
     * @brief Wypełnia jedynkami obszar nad główną przekątną
     * @return Referencja do bieżącej macierzy
     */
    matrix& nad_przekatna(void);

    /**
     * @brief Wypełnia macierz wzorem szachownicy (naprzemienne 0 i 1)
     * @return Referencja do bieżącej macierzy
     */
    matrix& szachownica(void);

    // ==================== Operatory arytmetyczne ze skalarami ====================

    /**
     * @brief Dodaje skalar do wszystkich elementów macierzy
     * @param a Wartość do dodania
     * @return Referencja do bieżącej macierzy
     */
    matrix& operator+=(int a);

    /**
     * @brief Odejmuje skalar od wszystkich elementów macierzy
     * @param a Wartość do odjęcia
     * @return Referencja do bieżącej macierzy
     */
    matrix& operator-=(int a);

    /**
     * @brief Mnoży wszystkie elementy macierzy przez skalar
     * @param a Mnożnik
     * @return Referencja do bieżącej macierzy
     */
    matrix& operator*=(int a);

    /**
     * @brief Postinkrementacja - zwiększa wszystkie elementy o 1
     * @return Kopia macierzy sprzed inkrementacji
     */
    matrix operator++(int);

    /**
     * @brief Postdekrementacja - zmniejsza wszystkie elementy o 1
     * @return Kopia macierzy sprzed dekrementacji
     */
    matrix operator--(int);

    /**
     * @brief Operator wywołania - dodaje wartość do wszystkich elementów
     * @param d Wartość zmiennoprzecinkowa (konwertowana na int)
     * @return Referencja do bieżącej macierzy
     */
    matrix& operator()(double d);

    // ==================== Operatory porównania ====================

    /**
     * @brief Sprawdza równość dwóch macierzy
     * @param m Macierz do porównania
     * @return true jeśli macierze mają ten sam rozmiar i identyczne elementy
     */
    bool operator==(const matrix& m) const;

    /**
     * @brief Sprawdza czy wszystkie elementy są większe
     * @param m Macierz do porównania
     * @return true jeśli każdy element tej macierzy > odpowiadający element m
     */
    bool operator>(const matrix& m) const;

    /**
     * @brief Sprawdza czy wszystkie elementy są mniejsze
     * @param m Macierz do porównania
     * @return true jeśli każdy element tej macierzy < odpowiadający element m
     */
    bool operator<(const matrix& m) const;

    // ==================== Friend operatory ====================

    /**
     * @brief Dodaje dwie macierze element po elemencie
     * @param m1 Pierwsza macierz
     * @param m2 Druga macierz
     * @return Nowa macierz będąca sumą
     * @throw std::logic_error Jeśli macierze mają różne rozmiary
     */
    friend matrix operator+(const matrix& m1, const matrix& m2);

    /**
     * @brief Wykonuje mnożenie macierzowe
     * @param m1 Pierwsza macierz
     * @param m2 Druga macierz
     * @return Nowa macierz będąca iloczynem macierzowym
     * @throw std::logic_error Jeśli macierze mają różne rozmiary
     */
    friend matrix operator*(const matrix& m1, const matrix& m2);

    /**
     * @brief Dodaje skalar do macierzy (macierz + liczba)
     * @param m Macierz
     * @param a Wartość do dodania
     * @return Nowa macierz z dodaną wartością do każdego elementu
     */
    friend matrix operator+(const matrix& m, int a);

    /**
     * @brief Dodaje skalar do macierzy (liczba + macierz)
     * @param a Wartość do dodania
     * @param m Macierz
     * @return Nowa macierz z dodaną wartością do każdego elementu
     */
    friend matrix operator+(int a, const matrix& m);

    /**
     * @brief Mnoży macierz przez skalar (macierz * liczba)
     * @param m Macierz
     * @param a Mnożnik
     * @return Nowa macierz z pomnożonymi elementami
     */
    friend matrix operator*(const matrix& m, int a);

    /**
     * @brief Mnoży skalar przez macierz (liczba * macierz)
     * @param a Mnożnik
     * @param m Macierz
     * @return Nowa macierz z pomnożonymi elementami
     */
    friend matrix operator*(int a, const matrix& m);

    /**
     * @brief Odejmuje skalar od macierzy (macierz - liczba)
     * @param m Macierz
     * @param a Wartość do odjęcia
     * @return Nowa macierz z odjętą wartością
     */
    friend matrix operator-(const matrix& m, int a);

    /**
     * @brief Odejmuje macierz od skalara (liczba - macierz)
     * @param a Wartość bazowa
     * @param m Macierz
     * @return Nowa macierz gdzie każdy element = a - element_macierzy
     */
    friend matrix operator-(int a, const matrix& m);

    /**
     * @brief Operator wyjścia - wypisuje macierz do strumienia
     * @param o Strumień wyjściowy
     * @param m Macierz do wypisania
     * @return Referencja do strumienia (umożliwia łańcuchowanie)
     */
    friend std::ostream& operator<<(std::ostream& o, const matrix& m);

    // ==================== Metody pomocnicze ====================

    /**
     * @brief Wstawia wartość do określonej pozycji w macierzy
     * @param x Indeks wiersza
     * @param y Indeks kolumny
     * @param val Wartość do wstawienia
     */
    void wstaw(int x, int y, int val) { at(x, y) = val; }

    /**
     * @brief Zwraca rozmiar macierzy
     * @return Rozmiar n (dla macierzy n×n)
     */
    int getSize() const { return n; }
};
#endif