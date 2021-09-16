#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include "Rsa.h"

using namespace std;

vector<long long> encrypt(fstream& input, fstream& output)
{
	vector<long long> msgEncode;
	long long single;
	char buf[100];

	while (!input.eof())
	{
		input.read(buf, 100);
		cout << buf << endl;
		for (int i = 0; i < 100; i++)
		{
			single = (long long)buf[i];
			msgEncode.push_back(Maths::power(single, 7, 13));	// msg^e % n  -> (msgToCode% n)^e % n
			output << msgEncode[i] << " ";			//THINK ABOUT IT -> if everything will be as 1 string
		}
	}

	return msgEncode;
}

string decrypt(vector<long long>& msgEncode, fstream& output)
{
	string msgDecode = "";
	for (int i = 0; i < msgEncode.size(); i++)
	{
		msgDecode += (char)Maths::power(msgEncode[i], 7, 13);
	}

	output << msgDecode;
	return msgDecode;
}

int main()
{
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

	//vector<long long> test = encrypt(data, encryptFile);
	//for (int i = 0; i < test.size(); i++)
	//{
	//	cout << test[i] << " ";
	//}

	//cout << "--------------------------------------------------------" << endl;

	//string testDecrypt = decrypt(test, decryptFile);

	//string msg;
	//getline(data, msg);
	//cout << msg << endl;

	Rsa test;

	cout << "p: " << test.getP() << endl;
	cout << "q: " << test.getQ() << endl;
	cout << "fi: " << test.getFi() << endl;
	cout << "n: " << test.getN() << endl;
	cout << "e: " << test.getE() << endl;
	cout << "d: " << test.getD() << endl;

	cout << "-----encrypting-------------" << endl;
	vector<long long> msgEncode = test.encrypt(data, encryptFile);

	encryptFile.close();
	encryptFile.open("D:/studia/programy_mentoringowe/IT_for_She/encrypt.txt", ios::in);
	decryptFile.open("D:/studia/programy_mentoringowe/IT_for_She/decrypt.txt", ios::out | ios::trunc);

	cout << "-----decrypting-------------" << endl;
	string msgDecode = test.decrypt((istream&)encryptFile, (ostream&)decryptFile);

	//cout <<"z funkcji decrypt: "<< msgDecode;

	//encryptFile << msgEncode;
	//decryptFile << msgDecode;


	data.close();
	encryptFile.close();
	decryptFile.close();

	return 0;
}
