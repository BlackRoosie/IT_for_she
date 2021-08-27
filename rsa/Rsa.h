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
	string msg, msgDecode = "";
	bool checkP = false, checkQ = false;
	vector<long long> firstPrimes;


public:
	Rsa(string c) {
		msg = c;

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

	vector<long long> encrypt()	
	{
		long long single;
		for (int i = 0; i < msg.length(); i++)
		{
			single = (long long)msg[i];
			msgEncode.push_back( Maths::power(single, e, n));	// msg^e % n  -> (msgToCode% n)^e % n
		}
		
		return msgEncode;
	}

	string decrypt()	//do poprawy! -> braæ zakodowan¹
	{
		for (int i = 0; i < msgEncode.size(); i++)
		{
			msgDecode += (char)Maths::power(msgEncode[i], d, n);
		}
		return msgDecode;
	}

	long long getP() { return p; }
	long long getQ() { return q; }
	long long getN() { return n; }
	long long getE() { return e; }
	long long getFi() { return fi; }
	long long getD() { return d; }
	string getMsg() { return msg; }
	vector<long long> getMesgEncode() { return msgEncode; }
	string getMsgDecode() { return msgDecode; }

	~Rsa() {}

};