/*
	 HW1 - LCS
	 Author: Hao Lu

	 CITE: I got the method of creating the LCS "chart" and defining the LCS route with the sign by following web site:
	       https://www.cnblogs.com/zlm-jessie/p/5664562.html
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//get the route to find LCS
void LCSroute(string l1, string l2, vector< vector<int>> &dp, vector< vector<char>> &sign)
{
    int m = l1.size();
    int n = l2.size();
    //set up the DP chart and the route sign in DP chart
    dp.resize(m + 1);
    sign.resize(m + 1);
    for (int i = 0; i < dp.size(); ++i)
        dp[i].resize(n + 1);
    for (int i = 0; i < sign.size(); ++i)
        sign[i].resize(n + 1);
    //calculate the route and fill the sign
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (l1[i - 1] == l2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                sign[i][j] = 'd';                      //route is toward the diagonal
            }
            else if (dp[i - 1][j] >= dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j];
                sign[i][j] = 'u';                      //route is upward
            }
            else {
                dp[i][j] = dp[i][j - 1];
                sign[i][j] = 'l';                      //route is toward the left
            }
        }
    }
}

//get the sequence on the route defined above
void LCSget(vector< vector<char>> &sign, string l1, int i, int j)
{
    if (i == 0 || j == 0)
        return;
    if (sign[i][j] == 'd') {
        LCSget(sign, l1, i - 1, j - 1);
        cout << l1[i - 1];                              //get the element in LCS
    }
    else if (sign[i][j] == 'u')
        LCSget(sign, l1, i - 1, j);
    else
        LCSget(sign, l1, i, j - 1);
}

//get the length of the LCS
void LCSlength(vector< vector<int>> &dp, string l1, string l2)
{
    int m = l1.size();
    int n = l2.size();
    cout << dp[m][n];                                   //every element occupies 1 byte
}

int main()
{
    //read file 1 into string s1
    string s1;
    ifstream readfile1("file1.txt");
    getline(readfile1, s1);
    /*
    cout << "The sequence of file 1 is: ";
    cout << s1 << endl;
     */
    readfile1.close();

    //read file 2 into string s2
    string s2;
    ifstream readfile2("file2.txt");
    getline(readfile2, s2);
    /*
    cout << "The sequence of file 2 is: ";
    cout << s2 << endl;
    */
    readfile2.close();

    string l1 = s1;
    string l2 = s2;
    vector< vector<int>> dp;
    vector< vector<char>> sign;

    LCSroute(l1, l2, dp, sign);
    cout << "The LCS of the two file is: ";
    LCSget(sign, l1, l1.size(), l2.size());
    cout << endl;
    cout << "The number of common bytes is: ";
    LCSlength(dp, l1, l2);

    getchar();
    return 0;
}