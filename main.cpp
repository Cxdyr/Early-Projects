#include <iostream>
#include "troop.h"
#include "castle.h"
#include "Farm.h"
#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <random>
#include <ctime>


using namespace std;

void artdisplay(string filename)
{
    fstream file;
    string art;
    file.open(filename);
    while(!file.eof())
    {
        getline(file, art);
        cout << art << endl;
    }
    file.close();

}

void newscreen()
{
    system("PAUSE");
    system("cls");
}

char menu()
{
    cout << "Castle Master Menu: " << endl;
    cout << "a) Fortify Gates " << endl;
    cout << "b) Fortify Walls" << endl;
    cout << "c) Send Troops to Farm " << endl;
    cout << "d) Check Farm status " << endl;
    cout << "e) Return Troops from Farm " << endl;
    cout << "f) Send Troops on Hunt " << endl;
    cout << "g) Feed Troops " << endl;
    char in;
    cin >> in;
    return in;
}

int main()
{

    castle userCastle; /// our castle
    Farm userFarm; /// our farm, seed ct, food ct, troop ct
    troop * newTroop;
    list<troop*>trooplist;
    list<troop*>::iterator itr;

    default_random_engine * gptr;
    gptr = new default_random_engine(time(NULL));
    uniform_int_distribution<int> Gdefense(15,60);
    uniform_int_distribution<int> FoodHunt(10,100);

    uniform_int_distribution<int> AttackD(1,13);
    uniform_int_distribution<int> TroopAm(5,15);
    uniform_int_distribution<int> DoorWall(1,2);
    uniform_int_distribution<int> DmgPerTroop(4,10);
    int attack, enemy, enemyattc, masshealth, DoorW, massDamage; /// attack = dice roll for base attack, enemy = dice roll for amount of enemies,, etc , doorw = door or wall under attack


    cout << "How many troops? ";
    int troopNum, seedice, troopstofarm;
    cin >> troopNum;

    cout << "Welcome to Castle, by Cody Rabie " << endl;
    artdisplay("IntroArt.txt");


    for(int i=1; i<=troopNum; i++) ///creates troops adds them to the castle list and our trooplist in main
    {
        newTroop = new troop;
        newTroop->Setid(i);
        userCastle.AddTroop(newTroop);
        trooplist.push_back(newTroop);
    }


    newscreen();
    bool onfarm = false;
    int farmtimer = 0;
    char input = 'd';
    while(input!='X')
    {
        userCastle.HungerStep();
        int alivectr = 0; /// ensuring that the castle has living troops on it
        itr=trooplist.begin();
        while(itr!=trooplist.end())
        {
            if((*itr)->Getstatus()==1 || (*itr)->Getstatus()==2 )
            {
                alivectr++;
            }
            itr++;
        }
        if(alivectr==0)
        {
            cout << "No living troops to defend the castle..." << endl;
            return 0;
        }


        attack = AttackD(*gptr); ///dice roll to randomly attack our castle
        if(attack==1)
        {
            enemy = TroopAm(*gptr); ///amount of enemy troops to attack
            masshealth = enemy*90; ///the mass amount of health the enemy troops have going into the fight, 90 base health x troop count
            DoorW = DoorWall(*gptr); /// the section of the castle to be attacked, 1

            enemyattc = DmgPerTroop(*gptr); /// damage each attacking troop does
            massDamage = enemyattc*enemy; /// the total damage (troop# * dmgpertroop) to be inflicted on castle
            if(DoorW==1)
            {
                cout << "The wall is under attack by " << enemy << " attacking troops, with level " << enemyattc << " damage! " << endl;
            }
            else if(DoorW==2)
            {
                cout << "The door is under attack by " << enemy << " attacking troops, with level " << enemyattc << " damage! " << endl;
            }
            ///function from castle.cpp that starts battle between the castle and attacking troops
            // function takes the-> masshealth, doorW, massDamage
            int newmasshealth = userCastle.castleBattle(masshealth,DoorW,massDamage, enemy);
            if(newmasshealth>0) /// if troops have defeated the castle defenses our troops suit up
            {
                int val = userCastle.troopBattle(newmasshealth,enemyattc,enemy);
                if(val==0)
                {
                    return 0;
                }
            }
            else if(newmasshealth<=0)
            {
                cout << "Castle defenses defeated the attacking enemies... " << endl;
                newscreen();
            }

        }

        int avgH = userCastle.avgHunger(); /// for the menu screen both of these
        int avgHealth = userCastle.avgHealth();


        cout << "Door Defense: "<< userCastle.GetfDefense() << ",  Wall Defense: " << userCastle.GetwDefense() << ",  Food Storage: " << userCastle.GetfStorage() << ", Avg Health: " << avgHealth << ", Avg Hunger: " << avgH << endl; /// add function to get avg hunger
        artdisplay("IntroArt.txt");


        if(onfarm==true) /// if troops on farm timer starts
        {
            farmtimer = farmtimer+1;
        }
        if(farmtimer==5)
        {
            userFarm.Setfoodcount(userFarm.Getseedcount());
            userFarm.Setseedcount(0); ///if 5 days on farm seeds are gone and we have food now.
        }

        input = menu();
        switch(input)
        {
        case 'a':
        {
            system("cls");
            int defense = Gdefense(*gptr);
            int bDefense = userCastle.GetfDefense();
            userCastle.SetfDefense(bDefense+defense);
            cout << "Castle Door Defense increased by " << defense << ", Door Defense: " << userCastle.GetfDefense() << endl;
        }
        break;/// finish other menu options then add the what happens if we get atatcked stuff then the farm stuff
        case 'b':
        {
            system("cls");
            int defense = Gdefense(*gptr);
            userCastle.SetwDefense(userCastle.GetwDefense()+defense);
            cout << "Castle Wall Defense increased by: " << defense << ", Wall Defense: " << userCastle.GetwDefense() << endl;
        }
        break;
        case 'c':
        {
            troopstofarm = userCastle.TroopsToFarm();
            if(onfarm!=true && troopstofarm>0) ///testing to see if troops are already on farm, if not we send troops to farm, then get seed ct and begin
            {
                userFarm.Settroopcount(troopstofarm);
                uniform_int_distribution<int> SeedCount(75,150);
                seedice = SeedCount(*gptr);
                int trueseed = seedice*troopstofarm;
                userFarm.Setseedcount(trueseed);
            }
            onfarm = true; ///troops are now on farm with seeds in place etc
            userFarm.Display();


            /// send troops to farm
        }
        break;
        case 'd':
        {
            system("cls");
            userFarm.Display();
            ///check farm status
        }
        break;
        case 'e':
        {
            system("cls");
            userFarm.Display(); /// showing full farm
            userFarm.Settroopcount(0); /// farm is empty now
            userCastle.TroopsToCastle(troopstofarm); /// troops are back to castle
            userCastle.SetfStorage(userCastle.GetfStorage()+userFarm.Getfoodcount()); /// castle has food from farm
            cout << endl << "Troops have returned home with the food farmed, food farmed  : " << userFarm.Getfoodcount() << ", Castle Food: " << userCastle.GetfStorage() << endl;
            userFarm.Setfoodcount(0); /// farm is out of food now
            onfarm = false; /// on farm bool is false now
            farmtimer = 0; /// farm timer set to 0 again
            userFarm.Display(); /// showing new empty farm again

            ///return troops from farm
        }
        break;
        case 'f':
        {
            system("cls");
            int foodcaught = FoodHunt(*gptr);
            userCastle.SetfStorage(userCastle.GetfStorage()+foodcaught);
            cout << "Hunt Resulted in: " << foodcaught << ", Food storage: " << userCastle.GetfStorage() << endl;
        }
        break;
        case 'g':
        {
            ///feed troops
            system("cls");
            userCastle.FeedTroops();
            userCastle.Display();
        }
        break;
        }

        newscreen();
    }



    return 0;


}
