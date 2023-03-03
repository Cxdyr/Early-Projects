#include "Farm.h"

Farm::Farm()
{
    troopcount = 0;
    seedcount = 0;
    foodcount = 0;
}

Farm::~Farm()
{
    //dtor
}

void Farm::Display()
{
    cout << "Troops: " << troopcount << ", Seeds: " << seedcount << ",  Food: " << foodcount << endl;
}
