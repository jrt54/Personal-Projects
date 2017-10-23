First run make numtheory to generate the code

Then run ./numtheory

A menu will appear prompting you for more action, allowing you choose from various actions motivated by number theory

You can choose the following commands 
0.) Exit program                               
Return to terminal and cease the ./numtheory program


1.) RSA Encryption                              
You will type a simple sentence and choose a set of private keys (prime numbers) to encode the sentence. The two private keys can be used to create one of two public keys. You will also choose a second public key, the public key exponent. In general, a message can be encrypted by knowing the two public keys. So a message can be encrypted by a friend and sent to you without an intercepter being able to decrypt it unless they can reverse-engineer the private keys. 

However, the user, knowing the private keys, is quickly able to decrypt the message. Unfortunately, the option to encrypt without knowing the private keys is not currently available. This is a beta program used to demonstrate RSA's encrpytion technique.  

You will type a sentence, choose the private and public keys, and then have the option to immediately decrypt it. You must choose appropriate numbers or will receive an error (e.g. do not give a value of 15 if asked for a prime number). If you do not know appropriate numbers, several viable options will be given to you. 


2.) RSA Decryption                              
Given two private keys and the public exponent, one can decrypt the encrypted message. The hard part is factoring numbers to get the private keys that generated the first of two public keys. You must do this before decrypting

3.) Prime Factorization                         
This is a brute-force method to factor a number. It is very slow. 

4.) Carmichael Number Tester                    
Carmichael numbers have powerful properties in number theory. This is a test to determine if a number is classified as carmichael.

5.) Miller-Rabin Primality Test                 
This is a probabalistic test for whether a number is prime or not.
