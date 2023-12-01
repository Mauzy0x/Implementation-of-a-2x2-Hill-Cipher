/*
*
*
*
*
*
*
*/

#include <ctime>
#include "matrixFunctions.h"


// Function declarations   ---------------------------------
string HillCipher(string, string, unsigned short);
void encrypt(int[2][2], int[2][2], int[2][2]);
void decrypt(int[2][2], int[2][2], int[2][2]);


int main() {

    // Get the message to be encrypted
    string plain_message; 
    cout << "Enter your message: ";
    getline(cin, plain_message);

    // Get user key
    string key;
    cout << "Enter the key (length 4): ";
    cin >> key;

    // Prep plaintext
    // Remove all spaces from the string
    plain_message.erase(remove_if(plain_message.begin(), plain_message.end(), ::isspace), plain_message.end());

    // Seed the random number with the current time
    srand(static_cast<unsigned>(time(0))); 
    // Pad the message 
    while (plain_message.length() % 4 != 0) { 
        plain_message += 'a' + rand() % 26;
    }

    // Encrypt in blocks of 4 characters
    string cipher_text;
    for (int index = 0; index < plain_message.length(); index += 4) {
        string chunk = plain_message.substr(index, 4);
        cipher_text += HillCipher(chunk, key, 0); 
    }
    cout << "Encrypted Message: " << cipher_text << "\n\n";


    // Decryption
    cout << "==========================\n"
         << "Decryption:\n\n";

    string decrypted_message;
    // Decrypt in blocks of 4 characters
    for (int index = 0; index < cipher_text.length(); index += 4) {
        string chunk = cipher_text.substr(index, 4);
        decrypted_message += HillCipher(chunk, key, 1);
    }
    cout << "Decrypted Message: " << plain_message << endl;

    exit(EXIT_SUCCESS);
} // end main


// Function Definitions   ---------------------------------


// Function to implement Hill Cipher
string HillCipher(string message, string key, unsigned short crypt) {

    // Get key matrix from the key string
    int keyMatrix[2][2];
    cout << "Key Matrix: \n";
    string_toMatrix(key, keyMatrix);
    
    // Get message matrix from the message string
    int messageMatrix[2][2];
    cout << "Message Matrix: \n";
    string_toMatrix(message, messageMatrix);


    if (crypt == 0) {   // Encryption
        
        // Encrypt the message matrix
        int cipherMatrix[2][2];
        encrypt(cipherMatrix, keyMatrix, messageMatrix);
        
        // Convert matrix to string
        matrix_toString(message, cipherMatrix);
    }
    else if (crypt == 1) {  // Decryption

        int plainMatrix[2][2];
        decrypt(plainMatrix, keyMatrix, messageMatrix);

        // Convert matrix to string
        matrix_toString(message, plainMatrix);
        
    } else {
        cout << "Invalid encryption mode!\n 0(encrypt) or 1(decrypt)";
        exit(EXIT_FAILURE);
    }

    return message;
} // end HillCipher

// C = E (P, K) = P ∙ K (mod 26)
void encrypt(int cipher_matrix[2][2], int key_matrix[2][2], int message_matrix[2][2]) {

    int x; 
    for (int row_index = 0; row_index < 2; row_index++) 
    { // Row
        for (int column_index = 0; column_index < 2; column_index++)
        { // Column
            cipher_matrix[row_index][column_index] = 0;    // Zero out index

            // Matrix Multipkication P * K 
            for (x = 0; x < 2; x++) {
                int beep =cipher_matrix[row_index][column_index];
                cipher_matrix[row_index][column_index] += message_matrix[row_index][x] * key_matrix[x][column_index];
                //cout << message_matrix[row_index][x] << " * " << key_matrix[x][column_index] << " + " << beep << " = " << cipher_matrix[row_index][column_index] << endl;
            }
            cipher_matrix[row_index][column_index] = cipher_matrix[row_index][column_index] % 26;
        }
    }
} // end encrypt

//  P = D (C, K) = C∙ K−1 (mod 26) = P ∙ K ∙ K−1 (mod 26)
void decrypt(int plain_matrix[2][2], int key_matrix[2][2], int cipher_matrix[2][2]) {

    invert_matrix(key_matrix);
    cout << "Inverted Key Matrix:\n";
    cout << key_matrix[0][0] << " ";
    cout << key_matrix[0][1] << endl;
    cout << key_matrix[1][0] << " ";
    cout << key_matrix[1][1] << "\n\n";

    int x; 
    for (int row_index = 0; row_index < 2; row_index++) 
    { // Row
        for (int column_index = 0; column_index < 2; column_index++)
        { // Column
            plain_matrix[row_index][column_index] = 0;    // Zero out index

            // Matrix Multipkication P * K^-1 
            for (x = 0; x < 2; x++) {
                plain_matrix[row_index][column_index] += cipher_matrix[row_index][x] * key_matrix[x][column_index];
            }
            plain_matrix[row_index][column_index] = plain_matrix[row_index][column_index] % 26;
        }
    }
} // end decrypt