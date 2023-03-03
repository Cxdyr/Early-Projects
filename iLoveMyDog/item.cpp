#include "item.h"
#
item::item(int id)
{
    //ctor

    ///weapon IDs
    // 1 - base knife, basic 5 damage 5 blocking power, and 7 special attack, and unlimited max use
    // 2 - smashgun,
}

item::~item()
{
    //dtor
}

void item::Display()
{
    cout <<endl << name << ", stats->   Attack: " << baseattack << "  Blocking: " << baseblock << "    " << specialattackname << ": " << specialattack << endl;


}
