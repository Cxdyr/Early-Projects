#include "ship.h"
#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
#include <string>


using namespace std;

char menu()
{
    cout << "a) repair ship " << endl;
    cout << "b) synthesize fuel " << endl;
    cout << "c) analyze gravitational web " << endl;
    char val;
    cin >> val;
    return val;
}

void artdisplay(string filename)
{
    string artval;
    fstream file;
    file.open(filename);
    while(!file.eof())
    {
        getline(file, artval);
        cout << artval << endl;
    }
    file.close();
}

int main()
{
    default_random_engine * gptr;
    gptr = new default_random_engine(time(NULL));
    uniform_int_distribution<int>asteroidX(1,3);
    uniform_int_distribution<int>asteroidY(3,7);
    uniform_int_distribution<int>asteroidColllision(100,400);


    uniform_int_distribution<int>shipFuelL(10,26);
    uniform_int_distribution<int>shipFuelW(20,36);
    uniform_int_distribution<int>shipRepair(40,76);


    uniform_int_distribution<int>gravXgen(1,3); /// x coordinate of graviton
    uniform_int_distribution<int>gravYgen(1,7); /// y distance of graviton from ship
    ///gravitons can spawn anywhere even on asteroids


    ///solar wind chance
    uniform_int_distribution<int>solargen(1,4);
    uniform_int_distribution<int>solarWindsX(1,3);
    uniform_int_distribution<int>solarWindsdmg(20,100);





    ship ourShip;
    /// ship has a position we will keep track of through x, and y. It starts at 2, 0
    int x =2, y = 0;
    ///asteroids will be spawned randomly in the path of the ship 1-3 dice roll for x spawn and 2-5 for y spawn
    int asX = 0, asY = 0;
    ///graviton locations
    int gravX =0, gravY = 0;
    bool gravitonfound = false;
    int gravctr = 0;

    char pilotChoice;
    int fuelval;

    char userChoice = '$';
    while(userChoice!='x')
    {


        y++; ///increment spaceship Y coordinate
        asY--; ///decrement asteroid Y coordinate
        gravY--;

        int solarval = solargen(*gptr);
        if(solarval==4)
        {
            int dmg = solarWindsdmg(*gptr);
            ourShip.Sethealth(ourShip.Gethealth()-dmg);
            cout << "solar winds have been found, " << dmg << " damage has been inflicted on the ship " << endl;
            int xcoord = solarWindsX(*gptr);
            if(xcoord==x)
            {
                cout << "the winds have not affected our trajectory " << endl << endl;
            }
            else
            {
                cout << "the solar winds have shifted our trajectory..." << endl << endl;
                x = xcoord;
            }
        }



        ///checking for graviton collision
        if(gravY==0 && gravX==x)
        {
            cout << "gravity seems to be running differently here... " << endl << endl;
            gravitonfound = true;

        }
        ///graviton dice roll

        if(gravY<=0)
        {
            gravX = gravXgen(*gptr);
            gravY = gravYgen(*gptr);
        }



        ///checking for asteroid collision
        if(asY==0 && asX==x)
        {
            cout << "collision has occurred " <<endl;
            int tempdamage = asteroidColllision(*gptr);
            ourShip.Sethealth(ourShip.Gethealth()-tempdamage);
            cout << "asteroid has inflicted " << tempdamage << " damage to our ship. " << endl << endl;
        }
        ///asteroid creation, 1-3 dice x, 3-7 dice y, if y = 0 we create new asteroid
        if(asY<=0)
        {
            asX = asteroidX(*gptr);
            asY = asteroidY(*gptr);
        }



        cout << "ship health: " << ourShip.Gethealth() << "    ship fuel: " << ourShip.Getfuel() << "    coordinates: " << x << ", " << y << endl << endl;


        if(asX==1)
        {
            cout << " *          " ;
        }
        else if(asX==2)
        {
            cout << "      *     ";
        }
        else if(asX==3)
        {
            cout << "              * ";
        }
        for(int y = 0; y<asY; y++)
        {
            cout << endl;
        }
        if(x==1)
        {
            cout << " ^            " << endl;
        }
        else if(x==2)
        {
            cout << "      ^     " << endl;
        }
        else if(x==3)
        {
            cout << "              ^ " << endl;
        }
        artdisplay("shipart.txt");

        cout << endl << " piloting log " << endl << "a) stay on course     b) shift position " << endl;
        cin >> pilotChoice;
        switch(pilotChoice)
        {
        case 'a':
        {
            cout << "ship has not altered course at all " << endl;
        }
        break;
        case 'b':
        {
            cout << "what coordinate would you like to shift our position to?    (1-3) ";
            int tempval;
            cin >>tempval;
            if(tempval==1 || tempval==2 || tempval==3)
            {
                x = tempval;
                cout << endl << "ship course has been shifted to coordinates: " << x << ", " << y << endl;
            }
            else
            {
                cout << "error: not a valid coordinate, auto pilot has taken control. " <<endl;
            }
        }
        break;
        default:
        {
            cout << "error: invalid option, auto pilot has taken control. " << endl;
        }
        break;
        }
        cout << endl << endl;


        userChoice = menu();
        switch(userChoice)
        {
        case 'a':
        {
            if(ourShip.Gethealth()<550)
            {
                int temphealth = shipRepair(*gptr);
                ourShip.Sethealth(ourShip.Gethealth()+temphealth);
                cout << "ship has been repaired by " << temphealth << endl;
            }
            else
            {
                cout << "ship cannot be further repaired " << endl;
            }
        }
        break;
        case 'b':
        {
            if(ourShip.Getfuel()<350)
            {
                fuelval = shipFuelW(*gptr);
                ourShip.Setfuel(ourShip.Getfuel()+fuelval);
                cout << "ship has synthesized " << fuelval << " fuel " << endl;
            }
            else
            {
                cout << "ship cannot synthesize further fuel " << endl;
            }
        }
        break;
        case 'c':
        {
            if(gravitonfound)
            {
                gravctr++;
                cout << "graviton found and collected, graviton count: " << gravctr << endl;
            }
            else
            {
                cout << "gravity seems to be running normally here..." << endl;
            }

            if(gravctr>12)
            {
                cout << "enough gravitons have been found to successfully solve gravity..." << endl;
                cout << "congratulations..." << endl;
                userChoice='x';
            }
        }
        break;
        }




        ///ship fuel usage & ensuring ship is still healthy
        fuelval =shipFuelL(*gptr);
        ourShip.Setfuel(ourShip.Getfuel()-fuelval);
        if(ourShip.Gethealth()<=0 || ourShip.Getfuel()<=0)
        {
            cout << "ship is beyond repair, mission has ended. " << endl;
            userChoice = 'x';
        }



        system("pause");
        system("cls");

        gravitonfound = false;


    }




    return 0;
}
