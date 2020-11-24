/*
 * HW4 - Quicksort
 * Author: Hao Lu
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>

using namespace std;

void Quicksort(int x[], int L, int R)
{
    if (R <= L)
        return;
    int i = L;
    int j = R + 1;
    int key = x[L];
    while (true)
    {
        while (x[++i] < key)
        {
            if (i == R)
                break;
        }
        while (x[--j] > key)
        {
            if (j == L)
                break;
        }
        if (i >= j)
            break;
        int temp = x[i];
        x[i] = x[j];
        x[j] = temp;
    }
    int temp = x[L];
    x[L] = x[j];
    x[j] = temp;
    Quicksort(x, L, j - 1);
    Quicksort(x, j + 1, R);
}

string Readdat(string filename, int line)
{
    ifstream filein;
    filein.open(filename, ios::in);
    string text[512];
    int i = 0;
    while (!filein.eof())
    {
        string temp;
        getline(filein, temp, '\n');
        text[i] = temp;
        i += 1;
    }
    return text[line - 1];
}

int main()
{
    int k = stoi(Readdat("hw2a.dat", 1));
    for(int j = 1; j <= k; j++)
    {
        int size = stoi(Readdat("hw2a.dat", j * 2));
        string a1 = Readdat("hw2a.dat", j * 2 + 1);
        string a2[size];
        stringstream ssin(a1);
        int i = 0;
        while(ssin.good() && i < size)
        {
            ssin >> a2[i];
            ++i;
        }
        int a3[size];
        for (int i = 0; i < size; i++)
        {
            a3[i] = stoi(a2[i]);
        }
        Quicksort(a3, 0, size - 1);
        for (int i = 0; i < size; i++)
        {
            cout<<a3[i]<<" ";
        }
        cout<<endl;
    }

    system("pause");
    return 0;
}