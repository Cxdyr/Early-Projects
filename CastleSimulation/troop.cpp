#include "troop.h"
#include <iostream>
using namespace std;
troop::troop()
{
    health = 100;
    hunger = 90;
    status = 1; //alive 1, on farm 2, dead 0
    damage = 5;
}

troop::~troop()
{
    //dtor
}

void troop::Display()
{
    if(status==1)
    {
        cout << "Troop #" << id << ", health: " << health << ", hunger: " << hunger << ", damage: " << damage<< ", in Castle" << endl;
    }
    else if(status==2)
    {
        cout << "Troop #" << id << ", health: " << health << ", hunger: " << hunger << ", damage: " << damage<< ", on Farm" << endl;
    }
    else if(status==3)
    {
        cout << "Troop #" << id <<  ", health: " << health << ", hunger: " << hunger << ", damage: " << damage<< ", Dead" << endl;
    }


}

