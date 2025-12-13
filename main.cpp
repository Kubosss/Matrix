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
    }
    return 0;
}