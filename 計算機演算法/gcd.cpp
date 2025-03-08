#include <iostream>
#include <cstdlib>

using namespace std;

int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int num1, num2;

    cout << "Please input two integer: ";
    cin >> num1 >> num2;
    
    cout << "GCD = " << gcd(num1, num2) << endl;

    return 0;
}
