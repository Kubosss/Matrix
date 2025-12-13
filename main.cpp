#include <iostream>
#include "matrix.h"

using namespace std;

int main() {
    
    cout << "=== TESTY MODULU PODSTAWOWEGO (OSOBA 1) ===" << endl;
    
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