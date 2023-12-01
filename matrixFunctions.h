#ifndef MATRIX_FUNCTIONS_H 
#define MATRIX_FUNCTIONS_H
 
#include <iostream>
#include <algorithm>

#define cout std::cout
#define cin std::cin
#define endl std::endl
#define string std::string


/* ======================
string_toMatrix Defintion:

Take in (string)str and (int[2][2])matrix
Transform string to lowercase, convert string[index] from ascii to a=0, b=1 ... z=25
then move string[index] into matrix and print the matrix
*/
void string_toMatrix(string str, int matrix[2][2]) {

    // Make sure the key is lower case for ascii conversion
    std::transform(str.begin(), str.end(), str.begin(),
                    [](unsigned char c){ return std::tolower(c); });
                    
    int str_index = 0;
    for (int row_index = 0; row_index < 2; row_index++) 
    { // Row 
        for (int column_index = 0; column_index < 2; column_index++) 
        { // Column
            matrix[row_index][column_index] = str[str_index] - 97;
            str_index++;
            cout << matrix[row_index][column_index] << ' ';
        }
        cout << '\n';
    }
    cout << "\n\n";
} // end string_toMatrix


/* ======================
matrix_toString Defintion:

Take in (string)str and (int[2][2])matrix
Convert to ascii then append matrix[i][j] to str
*/
void matrix_toString(string &str, int matrix[2][2]) {
    
    int str_index = 0;
    for (int row_index = 0; row_index < 2; row_index++) 
    { // Row
        for (int column_index = 0; column_index < 2; column_index++)
        {   
            str[str_index] = matrix[row_index][column_index] + 65;
            str_index++;
        }
    }
} // end matrix_toString



/* ======================
inver_matrix Defintion:

Take in (int[2][2])matrix and find the inverse
Inverse = 1/(ad−bc) ​(mod 26)
*/
void invert_matrix(int matrix[2][2]) {
    int inverse_matrix[2][2];

    // This admitedtly took longer than expected to figure out 
    inverse_matrix[0][0] = (26 + -matrix[1][1]) % 26;
    inverse_matrix[0][1] = matrix[0][1] % 26;
    inverse_matrix[1][0] = matrix[1][0] % 26;
    inverse_matrix[1][1] = (26 + -matrix[0][0]) % 26;

    // Set the given matrix to the calculated inverse 
    for (int row_index = 0; row_index < 2; row_index++) 
    { // Row
        for (int column_index = 0; column_index < 2; column_index++)
        { // Column
            matrix[row_index][column_index] = inverse_matrix[row_index][column_index];
        }
    }
} // end invert_matrix



#endif