#include <ctime>
#include <chrono>
#include "matrixFunctions.h"


// Function declarations   ---------------------------------
string HillCipher(string, string, unsigned short);
void encrypt(int[2][2], int[2][2], int[2][2]);
void decrypt(int[2][2], int[2][2], int[2][2]);
void attack_key(string, string);


int main() {

    // Get the message to be encrypted
    string plain_message; 
    cout << "Enter your message: ";
    getline(cin, plain_message);

    // Get user key
    string key;
    cout << "Enter the key (length 4): ";
    cin >> key;

// Encryption
    cout << "______________________________\n"
         << "Encryption:\n\n";

    // Get the start time
    auto encryption_start = std::chrono::high_resolution_clock::now();

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
    cout << "Encrypted Message: " << cipher_text << "\n";

    // Get the end time
    auto encryption_end = std::chrono::high_resolution_clock::now();

    // Calculate and print the elapsed time
    auto encryption_duration = std::chrono::duration_cast<std::chrono::microseconds>(encryption_end - encryption_start);
    cout << "Encryption time: " << encryption_duration.count() << " microseconds" << endl;

// Decryption
    cout << "==========================\n"
         << "Decryption:\n\n";

    // Get the start time
    auto decryption_start = std::chrono::high_resolution_clock::now();

    string decrypted_message;
    // Decrypt in blocks of 4 characters
    for (int index = 0; index < cipher_text.length(); index += 4) {
        string chunk = cipher_text.substr(index, 4);
        decrypted_message += HillCipher(chunk, key, 1);
    }
    cout << "Decrypted Message: " << decrypted_message << endl;

    // Get the end time
    auto decryption_end = std::chrono::high_resolution_clock::now();
    // Calculate and print the elapsed time
    auto decryption_duration = std::chrono::duration_cast<std::chrono::microseconds>(decryption_end - decryption_start);
    cout << "Decryption time: " << decryption_duration.count() << " microseconds" << endl;

// Known plaintext attack
    cout << "==========================\n"
         << "Known Plaintext Attack:\n\n";

    // Get the start time
    auto attack_start = std::chrono::high_resolution_clock::now();

    // Capture the first 4 characters of the plain message 
    string captured_text = plain_message.substr(0, 4);
    string cipher_block = cipher_text.substr(0, 4);
    attack_key(captured_text, cipher_block);

    // Get the end time
    auto attack_end = std::chrono::high_resolution_clock::now();
    // Calculate and print the elapsed time
    auto attack_duration = std::chrono::duration_cast<std::chrono::microseconds>(attack_end - attack_start);
    cout << "Attack time: " << attack_duration.count() << " microseconds" << endl;

    exit(EXIT_SUCCESS);
} // end main


// Function Definitions   ---------------------------------


// Function to implement Hill Cipher
string HillCipher(string message, string key, unsigned short crypt) {

    // Get key matrix from the key string
    int keyMatrix[2][2];
    string_toMatrix(key, keyMatrix);

    cout << "\nKey Matrix: \n";
    print_matrix(keyMatrix);

    

    // Get message matrix from the message string
    int messageMatrix[2][2];
    string_toMatrix(message, messageMatrix);

    cout << "Message Matrix: \n";
    print_matrix(messageMatrix);


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
void encrypt(int cipherMatrix[2][2], int keyMatrix[2][2], int messageMatrix[2][2]) {

    multiply_matrix(messageMatrix, keyMatrix, cipherMatrix);

} // end encrypt

//  P = D (C, K) = C∙ K−1 (mod 26) = P ∙ K ∙ K−1 (mod 26)
void decrypt(int plainMatrix[2][2], int keyMatrix[2][2], int cipherMatrix[2][2]) {

    invert_matrix(keyMatrix);

    cout << "Inverted Key Matrix:\n";
    print_matrix(keyMatrix);
    cout << "\n\n";

    multiply_matrix(cipherMatrix, keyMatrix, plainMatrix);

} // end decrypt


void attack_key(string captured_text, string ciphertext_block) {
    
    // Convert strings to a matrix
    cout << "\nCaptured text Matrix:\n";
    int capturedMatrix[2][2];
    string_toMatrix(captured_text, capturedMatrix);
    print_matrix(capturedMatrix);


    cout << "\nCipher Block Matrix:\n";
    int cipherBlockMatrix[2][2];
    string_toMatrix(ciphertext_block, cipherBlockMatrix);
    print_matrix(cipherBlockMatrix);

    // Invert the plaintext
    cout << "Inverted Plaintext Matrix:\n";
    invert_matrix(capturedMatrix);
    print_matrix(capturedMatrix);

    // P^-1 * C
    int keyMatrix[2][2];
    multiply_matrix(capturedMatrix, cipherBlockMatrix, keyMatrix);

    cout << "\n\nKey matrix:\n";
    print_matrix(keyMatrix);

} // end attack_keycaptured_matrix 
