/*
 * HW3 - Miller Rabin + powermod
 * Author: Hao lu
 */
#include <iostream>
#include <algorithm>
using namespace std;

int powermod(int a, int b, int c)
{
    long long prod = 1, temp1 = a;
    while(b > 0)
    {
        if(b % 2 == 1)
            prod = (prod * temp1) % c;
        temp1 = (temp1 * temp1) % c;
        b /= 2;
    }
    return (int) prod;
}

bool MillerRabin(int x)
{
    if(x == 2)
        return true;
    else if(x == 1 || x % 2 ==0)
        return false;

    int s = 0, t = x - 1;
    while(t % 2 == 0)
    {
        s++;
        t /= 2;
    }
    for(int i = 0; i < 30; ++i)
    {
        int a = rand() % (x-3) +2;
        int x1 = powermod(a, t, x);
        for(int j = 1; j <= s; ++j)
        {
            long long prod2 =0, temp2 = x1;
            int sp = x1;
            while(sp)
            {
                if(sp % 2 == 1)
                    prod2 = (prod2 + temp2) % x;
                temp2 = (temp2 + temp2) % x;
                sp /= 2;
            }
            int x2 = (int) prod2;
            if(x2 == 1 && x1 != 1 && x1 != x - 1)
                return false;
            x1 = x2;
        }
        if(x1 != 1)
            return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    int x;
    x = atoi(argv[1]);

    if(MillerRabin(x) == 1)
        cout << "prime" << endl;
    else
        cout << "not prime" << endl;

    system("pause");
    return 0;
}