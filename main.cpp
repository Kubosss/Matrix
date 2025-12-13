#include <iostream>
#include <stdexcept>
#include "matrix.h"

using namespace std;

void test_podstawowy() {
    cout << "\n=== TEST PODSTAWOWY ===\n";
    matrix m(5);
    m.wstaw(2, 3, 99);
    cout << m;
    cout << "pokaz(2,3) = " << m.pokaz(2, 3) << endl;
}

void test_losowanie() {
    cout << "\n=== TEST LOSOWANIA ===\n";
    matrix m(6);
    m.losuj();
    cout << m;

    m.losuj(5);
    cout << "Losowanie 0-5:\n" << m;
}

void test_wzory() {
    cout << "\n=== TEST WZOROW ===\n";
    matrix m(6);

    m.przekatna();
    cout << "Przekatna:\n" << m;

    m.pod_przekatna();
    cout << "Pod przekatna:\n" << m;

    m.nad_przekatna();
    cout << "Nad przekatna:\n" << m;

    m.szachownica();
    cout << "Szachownica:\n" << m;
}

void test_diagonalne() {
    cout << "\n=== TEST DIAGONALNY ===\n";
    int t[6] = { 1,2,3,4,5,6 };
    matrix m(6);

    m.diagonalna(t);
    cout << "Diagonalna:\n" << m;

    m.alokuj(6).diagonalna_k(1, t);
    cout << "Diagonalna k=1:\n" << m;

    m.diagonalna_k(-1, t);
    cout << "Diagonalna k=-1:\n" << m;
}

void test_wiersz_kolumna() {
    cout << "\n=== TEST WIERSZ / KOLUMNA ===\n";
    int t[5] = { 9,8,7,6,5 };
    matrix m(5);

    m.wiersz(2, t);
    cout << "Wiersz 2:\n" << m;

    m.kolumna(1, t);
    cout << "Kolumna 1:\n" << m;
}

void test_operatory_int() {
    cout << "\n=== TEST OPERATORY INT ===\n";
    matrix m(4);
    m.losuj();

    cout << "Start:\n" << m;

    cout << "m + 2:\n" << (m + 2);
    cout << "2 + m:\n" << (2 + m);
    cout << "m * 3:\n" << (m * 3);
    cout << "3 * m:\n" << (3 * m);
    cout << "m - 1:\n" << (m - 1);

    m += 2;
    m -= 1;
    m *= 2;
    cout << "Po += -= *=:\n" << m;

    m(4.7);
    cout << "Po operator()(4.7):\n" << m;

    m++;
    cout << "Po m++:\n" << m;

    m--;
    cout << "Po m--:\n" << m;
}

void test_operatory_macierzy() {
    cout << "\n=== TEST OPERATORY MACIERZY ===\n";
    matrix a(3), b(3);

    a.przekatna();
    b.szachownica();

    cout << "A:\n" << a;
    cout << "B:\n" << b;

    cout << "A + B:\n" << (a + b);
    cout << "A * B:\n" << (a * b);
}

void test_porownania() {
    cout << "\n=== TEST POROWNANIA ===\n";
    matrix a(2), b(2), c(2);

    int t1[4] = { 1,2,3,4 };
    int t2[4] = { 1,2,3,4 };
    int t3[4] = { 0,1,2,3 };

    a = matrix(2, t1);
    b = matrix(2, t2);
    c = matrix(2, t3);

    cout << "A == B ? " << (a == b) << endl;
    cout << "A > C ? " << (a > c) << endl;
    cout << "C < A ? " << (c < a) << endl;
}

void test_duza_macierz() {
    cout << "\n=== TEST DUZEJ MACIERZY (n=30) ===\n";
    matrix m(30);
    m.losuj();
    cout << "Macierz 30x30 wygenerowana poprawnie.\n";
}

void test_bledy() {
    cout << "\n=== TEST ZABEZPIECZEN ===\n";
    try {
        matrix a(3), b(4);
        a* b;
    }
    catch (exception& e) {
        cout << "Zlapano blad mnozenia: " << e.what() << endl;
    }
}

int main() {
    try {
        test_podstawowy();
        test_losowanie();
        test_wzory();
        test_diagonalne();
        test_wiersz_kolumna();
        test_operatory_int();
        test_operatory_macierzy();
        test_porownania();
        test_duza_macierz();
        test_bledy();

        cout << "\n=== WSZYSTKIE TESTY ZAKONCZONE ===\n";
    }
    catch (exception& e) {
        cout << "BLAD KRYTYCZNY: " << e.what() << endl;
    }

    return 0;
}