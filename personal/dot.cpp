#include <iostream>
using namespace std;

int main()
{
    int m = 2;
    int n = 4;
    int r = 3;
    int A[m][r] = {
        {1, 2, 3},
        {-1, 0, 2}};
    int B[r][n] = {
        {2, 1, 4, 3},
        {1, -1, 0, 2},
        {4, 5, 1, 1}};
    int C[m][n];
    /*
    16  14  7   10
    6   9  -2  -1
    */
    //For each row of A
    for (int i = 0; i < m; i++)
    {
        //For each column of B
        for (int j = 0; j < n; j++)
        {
            int dotted = 0;
            //Dot product(sum the products of corresponding indexes to get a single value for C)
            for (int k = 0; k < r; k++)
            {
                dotted += A[i][k] * B[k][j];
            }
            C[i][j] = dotted;
        }
    }
    //Print output in a legible way
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << C[i][j] << " ";
        }
        cout << "\n";
    }
}