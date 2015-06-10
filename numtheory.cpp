
//Jeremy Tillay
//Final Project
//RSA Decryption Scheme + other neat tools
//April 2015
//Kaiser CSC1254

#include <iostream>
#include <vector>
#include<string>
#include<iomanip>
#include<map>


using namespace std;



unsigned long inverseMod(unsigned long s, unsigned long mod)
{
	//this function returns the value inverseMod such that s*inverseMod % mod = 1 % mod
	unsigned long i = 0;
	while (s*i%mod != 1 && i<mod)
		++i;

	//brute force solution by finding if anything from 1 to mod-1 is the inverse of s

	if (i == mod)
		return 0;
	//0 can never be an inverse, this is an indication that there is an error. 
	//Never use inverse mod on values without an inverse.
	else
		return i;

}


unsigned long modExp(unsigned long b, unsigned long e, unsigned long m)
{
	//this finds b^e mod m 
	//sinds b and e might be huge, regulation exponentiation won't work
	//we square b repeatedly or multiply by b repeatedly and doing the %m operation every time
	unsigned long remainder;
	unsigned long x = 1;

	while (e != 0)
	{
		remainder = e % 2;
		e = e / 2;
		//we will square b repeatedly, reducing e in half each time and handling remainders if e can't be evenly halved

		if (remainder == 1)
		{
			x = (x * b) % m;
			
		}
		b = (b * b) % m; // New base equal b^2 % m
	}
	return x;
}

void menu()
{
	//to avoid clutter, we create a menu function we will call to prompt the user for what tool they want to use
	cout << "***************************************************" << endl;
	cout << "* Choose what you want to do by entering a number *" << endl;
	cout << "* corresponding to the options below:             *" << endl;
	cout << "* 0.) Exit program                                *" << endl;
	cout << "* 1.) RSA Encryption                              *" << endl;
	cout << "* 2.) RSA Decryption                              *" << endl;
	cout << "* 3.) Prime Factorization                         *" << endl;
	cout << "* 4.) Carmichael Number Tester                    *" << endl;
	cout << "* 5.) Miller-Rabin Primality Test                 *" << endl;
	cout << "***************************************************" << endl;
}


vector<unsigned long> RSAEncrypt(string input, unsigned long key1, unsigned long key2, unsigned long power)
{
	//this is a math function that encrypts data
	vector<unsigned long> asciistring, encryptedstring;

	for (int i = 0; i < input.size(); i++)
	{
		

		asciistring.push_back((unsigned long)(input[i]));
		//this just finds the ascii value of each char and assigns longs to it
		
	}

	for (int i = 0; i < asciistring.size(); i++)
	{
		encryptedstring.push_back(modExp(asciistring[i], power, key1*key2));
		//this is the string encrypted by some power in some mod group key1*key2
	}

	return encryptedstring;
}

vector<char> RSADecrypt(vector<unsigned long> encryptedmessage, unsigned long key1, unsigned long key2, unsigned long power)
{
	//this function decrypts our message of unsigned longs into a vector of characters, which is essentially a string
	vector<char> decrypt;
	for (int i = 0; i < encryptedmessage.size(); i++)
	{
		
			decrypt.push_back(char(modExp(encryptedmessage[i], inverseMod(power, (key1 - 1)*(key2 - 1)), key1*key2)));
			//first we perform a modular exponentation to undo the modular exponentation we did in the encryption
			//then we find the ascii value corresponding to the decrypted values and place them into a vector
	}
	return decrypt;
}

map<long, int> PrimeFactors(long n)
{
	//this generates a map of factors of a given unsigned long n and a corresponding int giving the power of each unique factor in the unsigned long n
	map<long, int> factors;

		for (int i = 2; i <= n; i++)
		{
			if (n%i == 0)
			{
				while (n%i == 0)
				{
					n = n / i;
					++factors[i];
				}
			}
		}
	return factors;
}


bool isprime(unsigned long x)
{
	//brute force method for determining if something is prime
	for (unsigned long i = 2; i < x; i++)
	{
		if (x%i == 0)
			return false;

	}
	return true;
}

bool millerrabin(unsigned long input, unsigned long tester)
{
	//probabilistic test to determine if a number is prime
	//This is called the Miller-Rabin test
	int poweroftwo = 2;
	int totalpower = 1;
	while ((input - 1) % poweroftwo == 0)
	{
		poweroftwo *= 2;
		totalpower++;
	}
	
	poweroftwo = poweroftwo / 2;
	totalpower--;

	if (modExp(tester, (input - 1) / poweroftwo, input) == 1)
	{
			
		return true;
	}

	for (int i = 0; i < totalpower; i++)
	{
		if(modExp(tester, (input - 1) / poweroftwo, input) == -1)
		{
	
			return true;
		}
		if(modExp(tester, (input - 1) / poweroftwo, input) == (input - 1))
		{

			return true;
			
		}
		poweroftwo = poweroftwo / 2;
	}
	//if none of the above equations are satisified, the miller robin test fails and returns false
	return false;
}

bool iscarmichael(long x)
{
	//using our factoring function, we can determine if a number is carmichael
	//this relies on some math theory that says a number is carmichael if and only if it is square free and for each factor p, p-1%x-1 = 0
	map<long, int> factors = PrimeFactors(x);
	for (map<long, int>::const_iterator it = factors.begin();it != factors.end(); ++it)
	{
		if ((x - 1) % (it->first -1) != 0 || (it->second) % 2 == 0)
		{
			return false;
		}
	}

	return true; 
}

vector<unsigned long> Factor(long z)
{
	//this just returns a vector of factors, does not return the power of the factors in z
	vector<unsigned long> factors;
	for (long i = 2; i <= z; i++)
		if (z%i == 0 && i <= z)
		{
			factors.push_back(i);
			while (z%i == 0)
			{

				z = z / i;
			}
		}
	return factors;
}


unsigned long gcd(unsigned long a, unsigned long b)
{
	//uses the euclidean algorithm to find the greatest common denominator of a and b
	unsigned long c;
	while (a != 0) {
		c = a; a = b%a;  b = c;
	}
	return b;
}


int main()
{

	char answer;
	
	unsigned long key1, key2, power;
	long n;
	vector<unsigned long> asciistring, encryptedstring;
	string mystring;
	int input;
	menu();
	cin >> input;
	//now I will choose what to do based on user input, using above-defined tools
	//this function will repeat as long as the user inputs valid input
	//switch statement was very finicky about calling new variables. had to localize a lot. 
	//some brackets that seem unnecessary were actually critical
	while (input != 0)
	{
		switch (input)
		{
		case 1:

			cout << "You have chosen to encrypt a message" << endl;
			cout << "First enter the message you want encrypted: " << endl;
			cin.ignore();
			getline(cin, mystring);
			cout << "you will encrpyt: " << mystring << endl;

			cout << "Now input two keys that are sufficiently large prime numbers" << endl;
			cout << "If you need some examples, the following would work: 13, 17, 79, 229, 809 ,1777, 5717" << endl;

			unsigned long key1, key2;
			cin >> key1 >> key2;

			//now I have to error check the keys are right
			//this will loop until valid keys are entered

			while (!isprime(key1) || !isprime(key2) || (key1 - 1)*(key2 - 1) < 129 || key1 < 2 || key2 < 2)
			{
				if (!isprime(key1))
				{
					cout << "key1 is not prime, please change your key1 and reenter both keys" << endl;
				}
				if (!isprime(key2))
				{
					cout << "key2 is not prime, please change your key2 and reenter both keys" << endl;
				}
				if ((key1 - 1)*(key2 - 1) < 129)
				{
					cout << "Your keys were not large enough, please enter bigger keys" << endl;
				}
				if (key1 < 2)
				{
					cout << "Your key1 was not a positive prime number, please enter two positive prime numbers";
				}
				if (key2 < 2)
				{
					cout << "Your key2 was not a positive prime number, please enter two positive prime numbers";
				}
				cin >> key1 >> key2;
			}

			//generates an appropriate power to encrypt the message
			cout << "now please enter a number to encode the message that is not a multiple of any of these things: ";
			{
				int prod = 1;
				{
					vector<unsigned long> totientfactors = Factor((key1 - 1)*(key2 - 1));

					for (int i = 0; i < totientfactors.size(); i++)
					{
						prod *= totientfactors[i];
						cout << totientfactors[i] << " ";
					}
				}

				cout << endl << "You may use, for example " << prod + 1 << endl;
			}

			unsigned long power;
			cin >> power;

			//error checks the power is appropriate. calls for input until fixed
			while (gcd(power, (key1 - 1)*(key2 - 1)) != 1)
			{
				cout << "Unfortunately your number is not coprime with the totient. Try again";
				cin >> power;
			}

			//call encryption function
			encryptedstring = RSAEncrypt(mystring, key1, key2, power);

			//cout every part of encrypted function along with the data used to encode it, but not original message
			for (int i = 0; i < mystring.size(); i++)
			{

				cout << encryptedstring[i] << " ";
			}
			cout << endl << "This is your message encoded as numbers with the following public data";
			cout << endl << "Modkey: " << key1 * key2 << endl;



			cout << "Raised to power: " << power << endl;
			cout << "Would you like to see us decrypt it? Type y if so." << endl;
			cin >> answer;
			//verify proper encoding
			if (answer == 'y')
			{
				for (int i = 0; i < encryptedstring.size(); i++)
				{
					cout << RSADecrypt(encryptedstring, key1, key2, power)[i];
				}
			}
			break;

		case 2:
			cout << "You have chosen to decrypt an encoded message. Be sure all your keys and powers are accurate." << endl;
			cout << "What are the keys to your encrypter? If you only know the mod...";
			cout << "Then you may need to use a factoring tool to find your keys...";
			cin >> key1 >> key2;
			cout << "What power was the message raised to?";
			cin >> power;
			cout << "Now enter the values corresponding to your encrypted message";
			{
			vector<unsigned long> encryptedkey;
			unsigned long x;

			while (cin >> x)
			{
				encryptedkey.push_back(x);
			}
			for (int i = 0; i < encryptedkey.size(); i++)
			{
			//call the decrypt function to get the vector of chars pre-encryption and the cout them all to piece together the string
				cout << RSADecrypt(encryptedkey, key1, key2, power)[i];
			}
			//cin.clear makes sure you can use the newline key and program won't read it as swith input.
			cin.clear();
			}
			break;
		case 3:
			cout << "You have chosen to factor a number" << endl;
			cout << "Enter the POSITIVE number greater than 1 that you want factored" << endl;
			{
				cin >> n;
				if (n < 2)
				{
					cout << "I cannot factor this"; 
					break;
				}
				//neatly prints out prime factorization with power carrots if the power of a factor is more than 1
				else
				{
					map<long, int> factors = PrimeFactors(n);
					map<long, int>::const_iterator it = factors.begin();
					cout << "The prime factorization is: " << endl;
					cout << it->first;
					if (it->second != 1)
						cout << "^" << it->second;
					++it;
					for (it; it != factors.end(); ++it)
					{

						cout << "*" << it->first;
						if (it->second != 1)
						{
							cout << "^" << it->second;
						}
					}
				}
			}
			break;
		case 4:
		{
			long input;
			cout << "You have chosen to test if a number is a carmichael number." << endl;
			cout << "A carmichael number causes problems for primality tests." << endl;
			cout << "Carmichael numbers are numbers x such that a^x-1 mod x = 1 mod x for all integers a. " << endl;
			cout << "Please enter the number you want to test:" << endl;
			cin >> input;
			//error checking for primes
			if (isprime(input))
			{
				cout << "This number is prime. Only composite numbers can be carmichael numbers.";
			}
			//call carmichael bool function
			else if (iscarmichael(input))
			{
				cout << "This number is a carmichael number";
			}
			else
				cout << "This number is not a carmichael number";
		}
		break;
		case 5:
		{
			long input, test;
			cout << "You have chosen to test if a number is prime." << endl;
			cout << "This test is best used on large numbers that are too big to test conventionally" << endl;
			cout << "This is a probablistic test. It does not guarantee primality or not." << endl;
			cout << "But it can make a very strong guess." << endl;
			cout << "A carmichael number is not prime, " << endl;
			cout << "but it will always evaluate as prime by this test" << endl;
			cout << "On with the test, choose the integer you would like to test:" << endl;
			cin >> input;
			if (input < 2)
			{
				cout << "What are you doing crazy, this test only works on positive numbers greater than 1";
				break;
			}
			cout << "Now, choose another positive integer, a smaller one, of your choosing. This will test the primality of " << input << endl;
			cin >> test;
			cout << endl;
			double prob = 100;
			//calls the miller-rabin test until the user decides to quit
			while (millerrabin(input, test)&&test !=0)
			{
				prob *= .25;
				cout << "There's about a " << 100 - prob << "% chance this number is actually prime." << endl;
				cout << "You can now enter a NEW number to test " << input << " for primality. Enter 0 to exit" << endl;
				cin >> test;
				cout << endl;
			}
			cout << "The test has failed for: " << test << ", which means " << input << " is DEFINITELY not prime.";
		}
		break;
		default:
			cout << "Error: You need to enter one of the numbers listed." << endl;
			break;
		}
		cout << endl <<"You may now enter a new command" << endl;
		menu();
		cin >> input;
		cout << endl;
	} 
	
	return 0;
	
}

