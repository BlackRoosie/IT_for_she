#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include "Rsa.h"
#include "Maths.h"

using namespace std;

long long power(long long a, long long b, long long n)
{
	long long result = 1;
	for (int i = 0; i < b; i++)
	{
		result = result * a;
		result = result % n;
	}

	return result;
}

long long inverseModulo(long long e, long long fi)
{
	//odwrotność mod fi liczby e
	long long u = 1, w = e, x = 0, z = fi, temp;
	while (w != 0)
	{
		if (w < z)
		{
			temp = u;
			u = x;
			x = temp;
			temp = w;
			w = z;
			z = temp;
		}

		temp = w / z;
		u -= temp * x;
		w -= temp * z;
	}

	if (z != 1)
		return 0;

	if (x < 0)
		x += fi;

	return x;
}


long long crt(long long c, long long d, long long p, long long q)
{
	long long m, m1, m2, dp, dq, inv, h;

	dp = d % (p - 1);
	cout << "dp: " << dp << endl;
	dq = d % (q - 1);
	cout << "dq: " << dq << endl;
	inv = inverseModulo(q, p);
	cout << "inv: " << inv << endl;
	m1 = power(c, dp, p);
	cout << "m1: " << m1 << endl;
	m2 = power(c, dq, q);
	cout << "m2: " << m2 << endl;
	h = (inv * (m1 - m2)) % p;
	if (h < 0)
		h += p;
	cout << "h: " << h << endl;

	m = m2 + h * q;
	cout << "m: " << m << endl;
	return m;
}

long long GCD(long long  a, long long b)	//nwd
{
	if (b != 0)
		return GCD(b, a % b);

	return a;
}

long long LCM(long long a, long long b)		//nwww
{
	return a * b / GCD(a, b);
}

int main()
{
	//----------------------------------------------------------------------
	fstream data;
	data.open("D:/studia/programy_mentoringowe/IT_for_She/test.txt", ios::in);
	fstream encryptFile;
	encryptFile.open("D:/studia/programy_mentoringowe/IT_for_She/encrypt.txt", ios::in | ios::out | ios::trunc);
	fstream decryptFile;
	

	if (!data.good())
		cout << "not good 1" << endl;
	if (!encryptFile.good())
		cout << "not good 2" << endl;
	if (!decryptFile.good())
		cout << "not good 3" << endl;
	cout << "--------------------------------------------------------" << endl;

	Rsa test;

	cout << "p: " << test.getP() << endl;
	cout << "q: " << test.getQ() << endl;
	cout << "fi: " << test.getFi() << endl;
	cout << "n: " << test.getN() << endl;
	cout << "e: " << test.getE() << endl;
	cout << "d: " << test.getD() << endl;

	cout << "-----encrypting-------------" << endl;
	vector<long long> msgEncode = test.encrypt(data, encryptFile);
	cout << msgEncode.size() << endl;

	encryptFile.close();
	encryptFile.open("D:/studia/programy_mentoringowe/IT_for_She/encrypt.txt", ios::in);
	decryptFile.open("D:/studia/programy_mentoringowe/IT_for_She/decrypt.txt", ios::out | ios::trunc);

	cout << "-----decrypting-------------" << endl;
	string msgDecode = test.decrypt((istream&)encryptFile, (ostream&)decryptFile);
	cout << msgDecode << endl;


	data.close();
	encryptFile.close();
	decryptFile.close();

	return 0;
}
