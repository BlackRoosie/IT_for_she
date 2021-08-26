#include <vector>

using namespace std;

class Maths
{

public:
	static long long inverseModulo(long long e, long long fi)
	{
		//odwrotnoœæ mod fi liczby e
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

	static long long NWD(long long  a, long long b)
	{
		if (b != 0)
			return NWD(b, a % b);

		return a;
	}

	static vector<long long> generateFirstPrimes(long long counter)
	{
		if (counter < 3)
			throw exception("Counter should be 3 or higher!");

		vector<long long> firstPrimes;
		firstPrimes.push_back(2);
		bool help = true;

		for (long long i = 3; i <= counter; i += 2)
		{
			for (long long j = 2; j * j <= i; j++)
			{
				if (i % j == 0)
					help = false;
			}

			if (help)
				firstPrimes.push_back(i);
			help = true;
		}

		return firstPrimes;
	}

	static long long randomNumber() {
		long long a = (static_cast<long long>(rand()) / RAND_MAX) * 32766 + 1;	//16bitowa    < 2^(n-1) + 1; 2^n - 1> 
		if (a % 2 == 0)
			a--;
		return a;
	}

	static bool checkingDivisionByFirstPrimes(long long n, vector<long long>& firstPrimes)
	{
		bool help = false;
		for (int i = 0; i < firstPrimes.size(); i++)
		{
			if (n % firstPrimes[i] == 0)
			{
				help = true;
				break;
			}
		}

		return help;
	}

	static bool MillerRabinTest(long long n)
	{
		long long s = 0, d = n - 1, a, x, j;
		while (d % 2 == 0)
		{
			s += 1;
			d = d / 2;
		}
		for (int i = 0; i < 20; i++)
		{
			a = rand() % (n - 2) + 2;	//<2; n-2>
			x = power(a, d, n);

			if (x == 1 || x == n - 1)
				continue;

			j = 1;
			while (j < s && x != n - 1)
			{
				x = (x * x) % n;
				if (x == 1)
					return false;
				j += 1;
			}

			if (x != n - 1)
				return false;
		}

		return true;
	}

	static long long power(long long a, long long b, long long n)
	{
		long long result = 1;
		for (int i = 0; i < b; i++)
		{
			result = result * a;
			result = result % n;
		}

		return result;
	}
};

