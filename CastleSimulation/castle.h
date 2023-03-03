#ifndef CASTLE_H
#define CASTLE_H
#include "troop.h"
#include <list>
#include <iostream>
using namespace std;

class castle
{
public:
    castle();
    virtual ~castle();

    int GetfDefense()
    {
        return fDefense;
    }
    void SetfDefense(int val)
    {
        fDefense = val;
    }
    int GetwDefense()
    {
        return wDefense;
    }
    void SetwDefense(int val)
    {
        wDefense = val;
    }
    int GetfStorage()
    {
        return fStorage;
    }
    void SetfStorage(int val)
    {
        fStorage = val;
    }
    int GetcastleDamage()
    {
        return castleDamage;
    }
    void SetcastleDamage(int val)
    {
        castleDamage = val;
    }
    void AddTroop(troop *tptr)
    {
        trooplist.push_back(tptr);
    }
    int castleBattle(int massHealth, int doorW, int massDamage, int enemyCt);
    int troopBattle(int enemyHealth, int enemyAttack, int troopCt);
    void HungerStep();
    void Display();
    void FeedTroops();
    int TroopsToFarm();
    void TroopsToCastle(int val);
    int avgHunger();
    int avgHealth();



private:
    int fDefense;
    int wDefense;
    int fStorage;
    int castleDamage;
    list<troop*>trooplist;
    list<troop*>::iterator itr;
};

#endif // CASTLE_H
