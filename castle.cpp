#include "castle.h"
#include <random>
#include <ctime>

castle::castle()
{
    fDefense = 250;
    wDefense = 250;
    fStorage = 400;
    castleDamage = 200;
}

castle::~castle()
{
    //dtor
}

void castle::Display()
{
    itr = trooplist.begin();
    while(itr!=trooplist.end())
    {
        (*itr)->Display();
        itr++;
    }
    /// cout castle troops status
}




void castle::HungerStep()
{
    default_random_engine * gptr;
    gptr = new default_random_engine(time(NULL));

    uniform_int_distribution<int>HungerLossDice(7,13);
    uniform_int_distribution<int>HealthGainDice(3,8);
    uniform_int_distribution<int>DyingHungerDice(20,30);



    itr=trooplist.begin();
    while(itr!=trooplist.end())
    {
        int hunger = HungerLossDice(*gptr);
        int healthdamage = DyingHungerDice(*gptr);
        int healthboost = HealthGainDice(*gptr);
        if((*itr)->Getstatus()==1 || (*itr)->Getstatus()==2) /// if troop is in castle,or on farm they become hungry
        {
            (*itr)->Sethunger((*itr)->Gethunger()-hunger);
        }
        if((*itr)->Gethunger()<=0)
        {
            /// if troop is hunger they lose health and hunger goes back to zero
            (*itr)->Sethealth((*itr)->Gethealth()-healthdamage);
            (*itr)->Sethunger(0);
        }
        if((*itr)->Gethealth()<=0)
        {
            /// if health is low they die
            (*itr)->Setstatus(0);
        }
        if((*itr)->Getstatus()!=0 && (*itr)->Gethunger()>=95)
        {
            ///If troop is well fed and alive their health gets boosted
            (*itr)->Sethealth((*itr)->Gethealth()+healthboost);
        }

        itr++;

    }

}

void castle::FeedTroops()
{
    cout << "How much food do you want to feed the troops?" ;
    int foodam;
    cin >> foodam; /// net am of food to be fed
    int troopam = trooplist.size(); /// am of troops
    int foodpertroop = foodam/troopam; ///food per troop
    if(fStorage<foodam)
    {
        cout << "you do not have enough food to feed this to your troops... " << endl;
    }
    else
    {
        itr = trooplist.begin();
        while(itr!=trooplist.end())
        {
            (*itr)->Sethunger((*itr)->Gethunger()+foodpertroop); ///feeding each troop the am per toop
            itr++;
        }
        fStorage =fStorage -foodam; ///update food storage
    }


}

int castle::castleBattle(int massHealth, int doorW, int massDamage, int enemyCt)
{
    int battleBegin = 1;
    while(battleBegin==1)
    {
        if(doorW==1)
        {
            cout << endl << "Wall under attack " << endl << " attacking troop health: " << massHealth << endl << "castle wall health: " << wDefense << endl << endl;
            cout << "attacking troops inflicted: " << massDamage << " damage " << endl << endl;
            cout << "castle defense inflicted: " << castleDamage << " damage to the enemies" << endl;
            massHealth = massHealth -castleDamage;
            wDefense = wDefense-massDamage;
            system("PAUSE");
            system("cls");

        }
        else if(doorW==2)
        {
            cout << endl<< "Door under attack " << endl << " attacking troop health: " << massHealth << endl;
            cout << "attacking troops inflicted: " << massDamage << " damage " << endl << endl;
            cout << "castle defense inflicted: " << castleDamage << " damage to the enemies " << endl;
            massHealth = massHealth -castleDamage;
            fDefense = fDefense-massDamage;
            system("PAUSE");
            system("cls");
        }
        if(massHealth<0)
        {
            cout << "Attacking Troops have been defeated, castle defenses boosted by +50 " << endl;
            fDefense = fDefense+50;
            wDefense = wDefense+50;
            battleBegin = 0; /// battle over
            massHealth = 0;
            system("PAUSE");
            system("cls");

        }
        else if(fDefense<=0 || wDefense<=0)
        {
            /// castle defense has fallen, now the troops need to fight with the remainder of the attacking enemies
            massHealth = massHealth/enemyCt; ///we take the total health, divide it by the amount of enemies and find the health per enemy
            cout << "Castle defenses have fallen... our troops suit up for battle with the remainder of enemies " << endl;
            battleBegin = 0; ///battle between castle and troops over
            system("PAUSE");
            system("cls");
        }
    }
    return massHealth;
}

int castle::troopBattle(int enemyHealth, int enemyAttack, int troopCt)
{

    default_random_engine * gptr;
    gptr = new default_random_engine(time(NULL));
    uniform_int_distribution<int>FatigueFactor(1,3);
    int troopHealth, troopDamage, baseEnemyHealth, fatigueFactor, listSize, ctr;
    listSize = trooplist.size();
    ctr=0;
    int battle = 1;
    baseEnemyHealth = enemyHealth; /// need this because enemy health will act as each enemies health and we will lose track of the others
    itr = trooplist.begin();
    int i = 0;
    while(i<troopCt)
    {
        while((*itr)->Getstatus()!=1)
        {
            cout << "This troop cannot fight " << endl;
            (*itr)->Display();
            ctr++;
            if(ctr==listSize)
            {
                cout << "You have no available troops to fight, your castle has fallen. " << endl;
                return 0;
            }
            itr++;
        }
        troopDamage = (*itr)->Getdamage();
        enemyHealth = baseEnemyHealth; ///reseting the next enemy health to this
        /// battle between a troop and enemy starts
        battle = 1;
        while(battle==1)
        {
            fatigueFactor = FatigueFactor(*gptr);
            troopHealth = (*itr)->Gethealth(); /// getting our troops current health
            enemyHealth = enemyHealth-troopDamage; ///damaging the first enemy
            (*itr)->Sethealth(troopHealth-enemyAttack+fatigueFactor); ///setting our new troop health (fatigueFactor is basically damage taken away from the enemy from being tired)

            if(enemyHealth<=0) /// if the enemy dies
            {

                (*itr)->Display();
                i++; ///on to the next troop
                cout << "has defeated attacking enemy # " << i << endl;
                battle = 0;
            }
            else if((*itr)->Gethealth()<=0)
            {
                (*itr)->Setstatus(0); /// our troop dies
                int val = (*itr)->Getid();
                cout << "Troop " << val << " has been defeated by enemy troop. " << endl;
                ctr++; ///counting the amount of troops defeated
                itr++; /// on to our next troop
                battle = 0; ///battle ends

            }
            if(listSize==ctr)
            {
                cout << "All available troops have been defeated, the castle is undefended and has fallen. " << endl;
                return 0;
            }
        }

    }
    system("PAUSE");
    system("cls");
    return 1;

}






int castle::TroopsToFarm()
{

    cout << "How many troops would you like to send to the farm: #";
    int troopsgone, tgctr, availabletroops;
    availabletroops = trooplist.size();
    cin >> troopsgone;
    if(availabletroops<troopsgone)
    {
        cout << "you do not have that many troops available to leave " << endl;
        troopsgone = 0;
        return troopsgone;
    }
    tgctr =0;


    itr = trooplist.begin();
    for(int i=0; i<troopsgone; i++)
    {
        if((*itr)->Getstatus()==1)
        {
            tgctr++;
            (*itr)->Setstatus(2);
        }


        itr++;
    }
    if(troopsgone==tgctr)
    {
        cout << troopsgone << " troops have been sent to the farm! " << endl;
    }
    else if(troopsgone!=tgctr)
    {
        cout << troopsgone << " troops could not be sent to the farm, your " << tgctr << " available troops have been sent. " << endl;
    }
    return troopsgone;
}

void castle::TroopsToCastle(int troopsback)
{
    itr = trooplist.begin();
    for(int i=0; i<troopsback; i++)
    {
        (*itr)->Setstatus(1);
        itr++;
    }


}

int castle::avgHunger()
{
    int hunger;
    int troopctr = 0;
    int avgHungr = 0;
    itr = trooplist.begin();
    while(itr!=trooplist.end())
    {
        hunger = (*itr)->Gethunger();
        avgHungr = avgHungr+hunger;
        troopctr++;
        itr++;
    }
    avgHungr = avgHungr/troopctr;
    return avgHungr;
}

int castle::avgHealth()
{
    int health;
    int troopctr = 0;
    int avgHealth = 0;
    itr = trooplist.begin();
    while(itr!=trooplist.end())
    {
        health = (*itr)->Gethealth();
        avgHealth = avgHealth+health;
        troopctr++;
        itr++;
    }
    avgHealth = avgHealth/troopctr;
    return avgHealth;
}

