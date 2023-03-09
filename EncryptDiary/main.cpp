#include <bits/stdc++.h>
#include <fstream>
#include "endecode.h"
using namespace std;


int main()
{
	endecode enc;
	char c;
	cout << endl << "Enter Your Choice : ->" << endl;
	cout << "1. fill diary " << endl;
	cout << "2. encrypt " << endl;
	cout << "3. decrypt " << endl;
	cin >> c;
	cin.ignore();

	switch (c) {
    case '1':
    {
        enc.filldiary();
        break;
    }
	case '2': {
		enc.encrypt();
		break;
	}
	case '3': {
		enc.decrypt();
		break;
	}
	}


}
