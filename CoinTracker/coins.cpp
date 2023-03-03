#include "coins.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
coins::coins()
{
    year = 0;
    type = "";
    condition = "";
    material = "";
    cost = 0;
    value = 0;
    next = NULL;

}

coins::~coins()
{
    if(next!=NULL){

    delete next;
    }
    else
    cout << "This is the end of the list "<< endl;
    }


void coins::Display()
{
    if(year!=0){
    cout << "Year: " << year << ", type: " <<type << ", condition: "<< condition<< endl;
    cout << "material: "<< material<<", cost: $"<< cost<<", and value: $"<<value<< "."<< endl <<endl;
    }
}

void coins::Showall()
{
    Display();
    if(next!=NULL){next->Showall();}
}


