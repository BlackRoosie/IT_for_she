#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include "Maths.h"

using namespace std;

class Rsa {


	long long p, q, n, e, fi, d = 0;
	vector<long long> msgEncode;
	string msgDecode = "";
	bool checkP = false, checkQ = false;
	vector<long long> firstPrimes;


public:
	Rsa() {		//string c
		//msg = c;

		srand(time(0));
		firstPrimes = Maths::generateFirstPrimes(1000);

		while (!checkP)
		{
			p = Maths::randomNumber();
			if (Maths::checkingDivisionByFirstPrimes(p, firstPrimes) == false)
			{
				checkP = Maths::MillerRabinTest(p);
			}
		}

		while (!checkQ)
		{
			q = Maths::randomNumber();
			if (Maths::checkingDivisionByFirstPrimes(q, firstPrimes) == false)
			{
				checkQ = Maths::MillerRabinTest(q);
			}
		}

		//p = 8069;
		//q = 9929;

		n = p * q;
		fi = (p - 1) * (q - 1);

		//eNumber();
		e = 7;
		while (d == 0)
		{
			d = Maths::inverseModulo(e, fi);
		}
	}

	vector<long long> encrypt(istream& input, ostream& output)		//there is a problem with const istream
	{
		long long single;
		char buf[3];
		long long temp;

		while (!input.eof())
		{
			input.read(buf, 3);
			//cout << buf << endl;
			for (int i = 0; i < 3; i++)
			{
				if (buf[i] > 0)
				{
					single = (long long)buf[i];
					temp = Maths::power(single, e, n);
					output.write((const char *) &temp, sizeof(long long));
					//msgEncode.push_back(Maths::power(single, e, n));	// msg^e % n  -> (msgToCode% n)^e % n
					//output << msgEncode[i] << " ";			//THINK ABOUT IT -> if everything will be as 1 string

				}
				
			}
		}

		return msgEncode;
	}

	string decrypt(istream& input, ostream& output)
	{
		long long temp;
		while (!input.eof())
		{
			input.read((char *) &temp, sizeof(long long));
			msgDecode += (char)Maths::power(temp, d, n);
		}

		output << msgDecode;
		return msgDecode;
	}

	long long getP() { return p; }
	long long getQ() { return q; }
	long long getN() { return n; }
	long long getE() { return e; }
	long long getFi() { return fi; }
	long long getD() { return d; }
	//string getMsg() { return msg; }
	vector<long long> getMesgEncode() { return msgEncode; }
	string getMsgDecode() { return msgDecode; }

	~Rsa() {}

};