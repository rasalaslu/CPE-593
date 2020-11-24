/*
    HW2- GCD, LCM and powermod
    Author: Hao Lu
 */

#include <iostream>

using namespace std;

int gcd(int a, int b)
{
    int temp;
    if (a < b){
        temp = a;
        a = b;
        b = temp;
    }
    while (b != 0){
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}

int powermod(int a, int b, int r)
{
    int prod = 1;
    while (b > 0) {
        if (b % 2 != 0) {
            prod = (prod * a) % r;
        }
        a = (a * a) % r;
        b = b / 2;
    }
    return prod;
}

int main(int argc, char *argv[])
{
    int a, b, r;
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    r = atoi(argv[3]);

    cout << "GCD(a,b)= " << gcd(a, b) << endl;
    cout << "LCM(a,b)= " << lcm(a, b) << endl;
    cout << "powermod(a, b, r)= " << powermod(a, b, r);

    getchar();
    return 0;
}