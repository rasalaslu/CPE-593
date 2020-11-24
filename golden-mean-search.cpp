/*
 * HW3b - Finding the minimum K
 * Author: Hao Lu
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <time.h>

using namespace std;

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

void Insertionsort(int x[], int L, int R)
{
    for(int i = L; i <= R; i++)
    {
        int temp = x[i];
        int j = i - 1;
        while(j >= L - 1 && x[j] > temp)
        {
            x[j + 1] = x[j];
            j--;
        }
        x[j + 1] = temp;
    }
}

void PartialQuicksort(int x[], int L, int R, int k)
{
    if (R < L)
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
    if (R - L >= k) {
        PartialQuicksort(x, L, j - 1, k);
        PartialQuicksort(x, j + 1, R, k);
    }
    else
        Insertionsort(x, L, R);
}


int main() {

    int size = stoi(Readdat("data9.txt", 1));
    string a1 = Readdat("data9.txt", 2);
    string a2[size];
    stringstream ssin(a1);
    int i = 0;
    while (ssin.good() && i < size) {
        ssin >> a2[i];
        ++i;
    }
    int a3[size];
    for (int i = 0; i < size; i++) {
        a3[i] = stoi(a2[i]);
    }

    int l = 0;
    int r = size - 1;
    int lp = l + 0.382 * (r - l);
    int rp = l + 0.618 * (r - l);
    while(rp - lp >2) {
        time_t start1, end1;
        double t1;
        start1 = clock();
        PartialQuicksort(a3, 0, size - 1, rp);
        end1 = clock();
        t1 = double(end1 - start1) * 1000 / CLOCKS_PER_SEC;

        time_t start2, end2;
        double t2;
        start2 = clock();
        PartialQuicksort(a3, 0, size - 1, lp);
        end2 = clock();
        t2 = double(end2 - start2) * 1000 / CLOCKS_PER_SEC;

        if (t1 <= t2) {
            r = rp;
            rp = lp;
            lp = l + 0.382 * (r - l);
        }
        if (t1 > t2) {
            l = lp;
            lp = rp;
            rp = l + 0.618 * (r - l);
        }
        //cout << lp << " " << t2 << " " << rp << " " << t1<< endl;
    }


    int k;
    int tmin;

    time_t start3, end3;
    double t3;
    start3 = clock();
    PartialQuicksort(a3, 0, size - 1, rp);
    end3 = clock();
    t3 = double(end3 - start3) * 1000 / CLOCKS_PER_SEC;

    time_t start4, end4;
    double t4;
    start4 = clock();
    PartialQuicksort(a3, 0, size - 1, lp);
    end4 = clock();
    t4 = double(end4 - start4) * 1000 / CLOCKS_PER_SEC;

    if(t3 < t4)
    {
        tmin = t3;
        k = rp;
    }
    else
    {
        tmin = t4;
        k = lp;
    }

    cout << "The measured Optimal k is: " << k << endl;
    cout << "The benchmark time of k is: "<< tmin << "ms" << endl;


    /*
    ofstream out("result4.txt");
    for(k = 0; k < size; k++)
    {
        clock_t start, end;
        double t;
        start = clock();
        PartialQuicksort(a3, 0, size - 1, k);
        end = clock();
        t = double(end - start)*1000 / CLOCKS_PER_SEC;
        cout << t << endl;
        out << t << endl;
    }
*/

/*
    k = 100;
    time_t start, end;
    double t;
    start = clock();
    PartialQuicksort(a3, 0, size - 1, k);
    end = clock();
    t = double(end - start) / CLOCKS_PER_SEC;
    cout << t << endl;
    for (int i = 0; i < size; i++) {
        cout << a3[i] << " ";
    }
    cout << endl;
*/
    system("pause");
    return 0;
}
