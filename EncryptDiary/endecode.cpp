#include "endecode.h"

endecode::endecode()
{
    //dtor
}

endecode::~endecode()
{
    //dtor
}

void endecode::encrypt()
{
	cout << "filename: " << endl;
	cin >> file;
	cout << "key: ";
	cin >> key;

	// Input stream
	fstream fin, fout;


	fin.open(file, fstream::in);
	fout.open("encrypt.txt", fstream::out);

	while (fin >> noskipws >> c) {
		int temp = (c + key);

		// Write temp as char in
		fout << (char)temp;
	}

	fin.close();
	fout.close();
}


void endecode::decrypt()
{
	cout << "key: ";
	cin >> key;
	fstream fin;
	fstream fout;
	fin.open("encrypt.txt", fstream::in);
	fout.open("decrypt.txt", fstream::out);

	while (fin >> noskipws >> c) {

		// Remove the key from the char
		int temp = (c - key);
		fout << (char)temp;
	}

	fin.close();
	fout.close();
}

void endecode::filldiary()
{
    cout << "filename: " << endl;
    string file, text;
    cin >> file;

    fstream fout;
    fout.open(file, fstream::out);
    char loop = '#';
    while(loop!='x')
    {
        cout << "type:   (enter = end line)  " << endl;
        cin.ignore();
        getline(cin, text);
        fout << text << endl;
        cout << "type x to end, other to continue " << endl;
        cin >> loop;
    }
    fout.close();
}
