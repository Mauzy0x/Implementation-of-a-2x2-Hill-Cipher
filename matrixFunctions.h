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
        }
    }
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
invert_matrix Defintion:

Take in (int[2][2])matrix and find the inverse
Inverse = 1/(ad−bc) ​(mod 26)
*/
void invert_matrix(int matrix[2][2]) {
    // Calculate determinant
    int determinant = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26;
    if (determinant < 0) determinant += 26;

    // Check for non-invertible matrix
    if (determinant == 0) {
        cout << "Error: Matrix is not invertible" << endl;
        return;
    }

    // Find multiplicative inverse of determinant
    int det_inv = -1;
    for (int index = 0; index < 26; index++) {
        if ((index * determinant) % 26 == 1) {
            det_inv = index;
            break;
        }
    }
    if (det_inv == -1) {
        cout << "Error: Matrix is not invertible" << endl;
        return;
    }

    // Calculate inverse matrix elements
    int inverseMatrix[2][2] = {
        {((matrix[1][1] * det_inv) % 26 + 26) % 26, ((-matrix[0][1] * det_inv) % 26 + 26) % 26},
        {((-matrix[1][0] * det_inv) % 26 + 26) % 26, ((matrix[0][0] * det_inv) % 26 + 26) % 26}
    };

    // Copy inverse matrix to original matrix
    for (int row_index = 0; row_index < 2; row_index++) 
    { // Row
        for (int column_index = 0; column_index < 2; column_index++) 
        { // Column
            matrix[row_index][column_index] = inverseMatrix[row_index][column_index];
        }
    }
} // end invert_matrix




/* ======================
multiply_matrix Defintion:

Take in (int[2][2])matrix1, (int[2][2])matrix2, (int[2][2])product 
Multiply matrix1 by matrix2 and populate the product matrix 
*/
void multiply_matrix(int matrix1[2][2], int matrix2[2][2], int productMatrix[2][2]) {

    int x; 
    for (int row_index = 0; row_index < 2; row_index++) 
    { // Row
        for (int column_index = 0; column_index < 2; column_index++)
        { // Column
            productMatrix[row_index][column_index] = 0;    // Zero out index

            // Matrix Multiplication P * K 
            for (x = 0; x < 2; x++) {
                productMatrix[row_index][column_index] += matrix1[row_index][x] * matrix2[x][column_index];
            }
            productMatrix[row_index][column_index] = productMatrix[row_index][column_index] % 26;
        }
    }
} // end multiply_matrix


/* ======================
multiply_matrix Defintion:

Print given matrix[2][2]
*/
void print_matrix(int matrix[2][2]) {

    for (int row_index = 0; row_index < 2; row_index++) 
    { // Row
        for (int column_index = 0; column_index < 2; column_index++)
        { // Column
            cout << matrix[row_index][column_index] << " ";
        }
        cout << endl;
    }
} // end print_matrix

#endif
