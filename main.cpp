#include <iostream>
#include "matrix.h"

using namespace std;

int main() {
    cout << "=== TESTY WZOROW I LOSOWANIA ===" << endl;

    try {
        matrix m_szach(8);
        m_szach.szachownica();

        cout << "Szachownica:" << endl;
        cout << m_szach << endl;

        m_szach.losuj();
        cout << "Po losowaniu:" << endl;
        cout << m_szach << endl;

    }
    catch (exception& e) {
        cout << "Blad: " << e.what();
    
    cout << "=== TESTY MODULU PODSTAWOWEGO ===" << endl;
    
    try {
        matrix m1(5);
        m1.wstaw(0, 0, 100);
        
        matrix m2(5);
        m2.wstaw(0, 0, 50);
        
        cout << "Wynik dodawania m1 + m2:" << endl;
        

    } catch(exception& e) {
        cout << e.what();
    }
    return 0;
}