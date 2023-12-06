# Basic implementation of a 2x2 Hill Cipher in C++
## Example output:
```
Enter your message: Hill Cipher
Enter the key (length 4): dcif
______________________________
Encryption:


Key Matrix: 
3 2 
8 5 
Message Matrix: 
7 8 
11 11 

Key Matrix: 
3 2 
8 5 
Message Matrix: 
2 8 
15 7 

Key Matrix: 
3 2 
8 5 
Message Matrix: 
4 17 
24 10 
Encrypted Message: HCRZSSXNSPWU
Encryption time: 118 microseconds
==========================
Decryption:


Key Matrix: 
3 2 
8 5 
Message Matrix: 
7 2 
17 25 
Inverted Key Matrix:
21 2 
8 23 



Key Matrix: 
3 2 
8 5 
Message Matrix: 
18 18 
23 13 
Inverted Key Matrix:
21 2 
8 23 



Key Matrix: 
3 2 
8 5 
Message Matrix: 
18 15 
22 20 
Inverted Key Matrix:
21 2 
8 23 


Decrypted Message: HILLCIPHERYK
Decryption time: 114 microseconds
==========================
Known Plaintext Attack:


Captured text Matrix:
7 8 
11 11 

Cipher Block Matrix:
7 2 
17 25 
Inverted Plaintext Matrix:
25 22 
1 23 


Key matrix:
3 2 
8 5 
Attack time: 37 microseconds
```
