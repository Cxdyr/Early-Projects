#include "Fish.h"
#include <iostream>
using namespace std;
Fish::Fish()
{

}

Fish::~Fish()
{

}


void Fish::Display()
{
    cout << "Type: " <<Type<< endl<< "School size: "<< School <<endl<< "Latitude: " << latitude <<endl<<"Longitude: " << longitude << endl << endl;
}
