#include <iostream>
#include "matrix.h"

using namespace std;

int main() {
    cout << "========== TESTY MACIERZY ==========" << endl << endl;
    
    try {
        // Test 1: Konstruktory
        cout << "=== TEST 1: KONSTRUKTORY ===" << endl;
        matrix m1(3);
        cout << "Macierz m1 (3x3) - inicjalizacja zerami:" << endl;
        cout << m1 << endl;
        
        // Test 2: Konstruktor z tablicą
        cout << "=== TEST 2: KONSTRUKTOR Z TABLICĄ ===" << endl;
        int tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        matrix m2(3, tab);
        cout << "Macierz m2 (3x3) - inicjalizacja tablicą:" << endl;
        cout << m2 << endl;
        
        // Test 3: Konstruktor kopiujący
        cout << "=== TEST 3: KONSTRUKTOR KOPIUJĄCY ===" << endl;
        matrix m3 = m2;
        cout << "Macierz m3 (kopia m2):" << endl;
        cout << m3 << endl;
        
        // Test 4: Metoda wstaw
        cout << "=== TEST 4: METODA WSTAW ===" << endl;
        m1.wstaw(0, 0, 10);
        m1.wstaw(1, 1, 20);
        m1.wstaw(2, 2, 30);
        cout << "Macierz po wstawieniu wartości:" << endl;
        cout << m1 << endl;
        
        // Test 5: Metoda pokaz
        cout << "=== TEST 5: METODA POKAZ ===" << endl;
        cout << "Element [1,1] = " << m1.pokaz(1, 1) << endl << endl;
        
        // Test 6: Obrócenie macierzy
        cout << "=== TEST 6: OBRÓCENIE (TRANSPOZYCJA) ===" << endl;
        matrix m_obr = m2;
        m_obr.odwroc();
        cout << "Macierz m2 po obróceniu:" << endl;
        cout << m_obr << endl;
        
        // Test 7: Losowanie
        cout << "=== TEST 7: LOSOWANIE ===" << endl;
        matrix m_los(4);
        m_los.losuj();
        cout << "Macierz 4x4 - losowe cyfry 0-9:" << endl;
        cout << m_los << endl;
        
        // Test 8: Szachownica
        cout << "=== TEST 8: WZÓR SZACHOWNICA ===" << endl;
        matrix m_szach(6);
        m_szach.szachownica();
        cout << "Szachownica 6x6:" << endl;
        cout << m_szach << endl;
        
        // Test 9: Przekątna
        cout << "=== TEST 9: PRZEKĄTNA ===" << endl;
        matrix m_diag(4);
        m_diag.przekatna();
        cout << "Macierz diagonalna (1 na przekątnej, 0 poza):" << endl;
        cout << m_diag << endl;
        
        // Test 10: Pod przekątną
        cout << "=== TEST 10: POD PRZEKĄTNĄ ===" << endl;
        matrix m_pod(4);
        m_pod.pod_przekatna();
        cout << "Macierz z jedynkami pod przekątną:" << endl;
        cout << m_pod << endl;
        
        // Test 11: Nad przekątną
        cout << "=== TEST 11: NAD PRZEKĄTNĄ ===" << endl;
        matrix m_nad(4);
        m_nad.nad_przekatna();
        cout << "Macierz z jedynkami nad przekątną:" << endl;
        cout << m_nad << endl;
        
        // Test 12: Diagonalna z danymi
        cout << "=== TEST 12: DIAGONALNA Z DANYMI ===" << endl;
        int dane[] = {1, 2, 3};
        matrix m_diag_dane(3);
        m_diag_dane.diagonalna(dane);
        cout << "Macierz z danymi na przekątnej:" << endl;
        cout << m_diag_dane << endl;
        
        // Test 13: Diagonalna przesunięta
        cout << "=== TEST 13: DIAGONALNA PRZESUNIĘTA ===" << endl;
        matrix m_diag_k(4);
        int dane4[] = {1, 2, 3};
        m_diag_k.diagonalna_k(1, dane4);
        cout << "Macierz z danymi na przekątnej przesunięte o 1 do góry:" << endl;
        cout << m_diag_k << endl;
        
        // Test 14: Kolumna
        cout << "=== TEST 14: USTAWIENIE KOLUMNY ===" << endl;
        matrix m_kol(3);
        int kolumna_dane[] = {10, 20, 30};
        m_kol.kolumna(1, kolumna_dane);
        cout << "Macierz z danymi w kolumnie 1:" << endl;
        cout << m_kol << endl;
        
        // Test 15: Wiersz
        cout << "=== TEST 15: USTAWIENIE WIERSZA ===" << endl;
        matrix m_wie(3);
        int wiersz_dane[] = {5, 10, 15};
        m_wie.wiersz(1, wiersz_dane);
        cout << "Macierz z danymi w wierszu 1:" << endl;
        cout << m_wie << endl;
        
        // Test 16: Dodawanie macierzy
        cout << "=== TEST 16: DODAWANIE MACIERZY (A+B) ===" << endl;
        matrix m4(3, tab);
        int tab2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
        matrix m5(3, tab2);
        matrix wynik_dodaw = m4 + m5;
        cout << "Macierz A:" << endl << m4 << endl;
        cout << "Macierz B:" << endl << m5 << endl;
        cout << "Wynik A + B:" << endl << wynik_dodaw << endl;
        
        // Test 17: Mnożenie macierzy
        cout << "=== TEST 17: MNOŻENIE MACIERZY (A*B) ===" << endl;
        int tab_a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int tab_b[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
        matrix ma(3, tab_a);
        matrix mb(3, tab_b);
        matrix wynik_mno = ma * mb;
        cout << "Macierz A:" << endl << ma << endl;
        cout << "Macierz B:" << endl << mb << endl;
        cout << "Wynik A * B:" << endl << wynik_mno << endl;
        
        // Test 18: Dodawanie skalara
        cout << "=== TEST 18: DODAWANIE SKALARA (A+5) ===" << endl;
        matrix m6(3, tab);
        matrix wynik_add_sk = m6 + 5;
        cout << "Macierz + 5:" << endl << wynik_add_sk << endl;
        
        // Test 19: Dodawanie skalara (odwrócone)
        cout << "=== TEST 19: DODAWANIE SKALARA (5+A) ===" << endl;
        matrix wynik_add_sk2 = 5 + m6;
        cout << "5 + Macierz:" << endl << wynik_add_sk2 << endl;
        
        // Test 20: Mnożenie skalara
        cout << "=== TEST 20: MNOŻENIE SKALARA (A*3) ===" << endl;
        matrix wynik_mult_sk = m6 * 3;
        cout << "Macierz * 3:" << endl << wynik_mult_sk << endl;
        
        // Test 21: Mnożenie skalara (odwrócone)
        cout << "=== TEST 21: MNOŻENIE SKALARA (3*A) ===" << endl;
        matrix wynik_mult_sk2 = 3 * m6;
        cout << "3 * Macierz:" << endl << wynik_mult_sk2 << endl;
        
        // Test 22: Odejmowanie skalara
        cout << "=== TEST 22: ODEJMOWANIE SKALARA (A-2) ===" << endl;
        matrix wynik_sub_sk = m6 - 2;
        cout << "Macierz - 2:" << endl << wynik_sub_sk << endl;
        
        // Test 23: Odejmowanie skalara (odwrócone)
        cout << "=== TEST 23: ODEJMOWANIE SKALARA (10-A) ===" << endl;
        matrix wynik_sub_sk2 = 10 - m6;
        cout << "10 - Macierz:" << endl << wynik_sub_sk2 << endl;
        
        // Test 24: Operator +=
        cout << "=== TEST 24: OPERATOR += ===" << endl;
        matrix m7(3, tab);
        m7 += 5;
        cout << "Macierz po += 5:" << endl << m7 << endl;
        
        // Test 25: Operator -=
        cout << "=== TEST 25: OPERATOR -= ===" << endl;
        matrix m8(3, tab);
        m8 -= 2;
        cout << "Macierz po -= 2:" << endl << m8 << endl;
        
        // Test 26: Operator *=
        cout << "=== TEST 26: OPERATOR *= ===" << endl;
        matrix m9(3, tab);
        m9 *= 2;
        cout << "Macierz po *= 2:" << endl << m9 << endl;
        
        // Test 27: Inkrementacja ++
        cout << "=== TEST 27: INKREMENTACJA ++ ===" << endl;
        matrix m10(2);
        m10.wstaw(0, 0, 5);
        m10.wstaw(0, 1, 6);
        m10.wstaw(1, 0, 7);
        m10.wstaw(1, 1, 8);
        cout << "Przed++:" << endl << m10;
        m10++;
        cout << "Po++:" << endl << m10 << endl;
        
        // Test 28: Dekrementacja --
        cout << "=== TEST 28: DEKREMENTACJA -- ===" << endl;
        matrix m11(2);
        m11.wstaw(0, 0, 5);
        m11.wstaw(0, 1, 6);
        m11.wstaw(1, 0, 7);
        m11.wstaw(1, 1, 8);
        cout << "Przed--:" << endl << m11;
        m11--;
        cout << "Po--:" << endl << m11 << endl;
        
        // Test 29: Operator () z double
        cout << "=== TEST 29: OPERATOR ()(double) ===" << endl;
        matrix m12(2);
        m12.wstaw(0, 0, 5);
        m12.wstaw(0, 1, 6);
        m12.wstaw(1, 0, 7);
        m12.wstaw(1, 1, 8);
        cout << "Przed (3.7):" << endl << m12;
        m12(3.7);
        cout << "Po (3.7) - wszystkie + 3:" << endl << m12 << endl;
        
        // Test 30: Operator ==
        cout << "=== TEST 30: OPERATOR == ===" << endl;
        matrix m13(2);
        m13.wstaw(0, 0, 1);
        m13.wstaw(0, 1, 2);
        m13.wstaw(1, 0, 3);
        m13.wstaw(1, 1, 4);
        matrix m14(2);
        m14.wstaw(0, 0, 1);
        m14.wstaw(0, 1, 2);
        m14.wstaw(1, 0, 3);
        m14.wstaw(1, 1, 4);
        cout << "m13 == m14? " << (m13 == m14 ? "TAK" : "NIE") << endl << endl;
        
        // Test 31: Operator >
        cout << "=== TEST 31: OPERATOR > ===" << endl;
        matrix m15(2);
        m15.wstaw(0, 0, 5);
        m15.wstaw(0, 1, 5);
        m15.wstaw(1, 0, 5);
        m15.wstaw(1, 1, 5);
        matrix m16(2);
        m16.wstaw(0, 0, 2);
        m16.wstaw(0, 1, 2);
        m16.wstaw(1, 0, 2);
        m16.wstaw(1, 1, 2);
        cout << "m15 > m16? " << (m15 > m16 ? "TAK" : "NIE") << endl << endl;
        
        // Test 32: Operator <
        cout << "=== TEST 32: OPERATOR < ===" << endl;
        cout << "m16 < m15? " << (m16 < m15 ? "TAK" : "NIE") << endl << endl;
        
        // Test 33: Metoda alokuj
        cout << "=== TEST 33: METODA ALOKUJ ===" << endl;
        matrix m_alloc;
        m_alloc.alokuj(3);
        m_alloc.wstaw(0, 0, 10);
        m_alloc.wstaw(1, 1, 20);
        m_alloc.wstaw(2, 2, 30);
        cout << "Macierz po alokacji i wstawieniu danych:" << endl;
        cout << m_alloc << endl;
        
        cout << "========== WSZYSTKIE TESTY ZAKONCZONE POMYSLNIE! ==========" << endl;
        
    } catch (exception& e) {
        cout << "BŁĄD: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}