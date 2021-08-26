#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>

class Rsa {
	long long p, q, n, e, fi, d, msg;

public:
	Rsa(long long a, long long b, long long c) {
		p = a;
		q = b;
		msg = c;

		n = p * q;
		fi = (p - 1) * (q - 1);

		e = eNumber();
		while (d == 0)
		{
			d = inverseModulo();
		}
	}

	long long inverseModulo()	//long long e, long long fi
	{
		//odwrotnoœæ mod e liczby fi
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

	long long NWD(long long  a, long long b)
	{
		if (b != 0)
			return NWD(b, a % b);

		return a;
	}

	long long eNumber()		
	{
		long long e = 3;
		srand(time(0));
		long long random = rand() % fi + 3;
		if (random % 2 == 0)
			random -= 1;

		for (long long i = random; i < fi; i += 2)
		{
			if (NWD(i, n) == 1)
			{
				e = i;
				break;
			}
		}

		return e;
	}

	long long power(long long a, long long b)
	{
		if (b == 0)
			return 1;
		if (b == 1)
			return a;

		return a * power(a, b - 1);
	}

	long long encrypt()	//long long msg, long long e, long long n
	{
		return power(msg, e) % n;
	}

	long long decrypt()	//long long msg, long long d, long long n
	{
		return power(msg, d) % n;
	}

	long long getP() { return p; }
	long long getQ() { return q; }
	long long getN() { return n; }
	long long getE() { return e; }
	long long getFi() { return fi; }
	long long getD() { return d; }
	long long getMsg() { return msg; }

	~Rsa() {}

};