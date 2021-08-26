#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include "Rsa.h"

using namespace std;

int main()
{
	fstream data;
	data.open("D:/studia/programy_mentoringowe/IT_for_She/test.txt", ios::in);
	fstream encryptFile;
	encryptFile.open("D:/studia/programy_mentoringowe/IT_for_She/encrypt.txt", ios::in | ios::out | ios::trunc);
	fstream decryptFile;
	decryptFile.open("D:/studia/programy_mentoringowe/IT_for_She/decrypt.txt", ios::in | ios::out | ios::trunc);

	if (!data.good())
		cout << "not good 1" << endl;
	if (!encryptFile.good())
		cout << "not good 2" << endl;
	if (!decryptFile.good())
		cout << "not good 3" << endl;
	cout << "--------------------------------------------------------" << endl;

	string msg;
	getline(data, msg);
	cout << msg << endl;
	Rsa test(msg);

	cout << "p: " << test.getP() << endl;
	cout << "q: " << test.getQ() << endl;
	cout << "fi: " << test.getFi() << endl;
	cout << "n: " << test.getN() << endl;
	cout << "e: " << test.getE() << endl;
	cout << "d: " << test.getD() << endl;

	cout << "msg: " << test.getMsg() << endl;

	vector<long long> msgEncode = test.encrypt();
	for (int i = 0; i < msgEncode.size(); i++)
		cout << msgEncode[i] << '\t';
	cout << endl;
	string msgDecode = test.decrypt();

	cout <<"z funkcji decrypt: "<< msgDecode;

	//encryptFile << msgEncode;
	//decryptFile << msgDecode;


	data.close();
	encryptFile.close();
	decryptFile.close();

	return 0;
}
