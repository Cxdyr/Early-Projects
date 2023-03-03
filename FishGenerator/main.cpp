#include <iostream>
#include <random>
#include <ctime>
#include "Fish.h"
using namespace std;

char menu();
int main()
{
    default_random_engine * gptr;
    gptr = new default_random_engine(time(NULL));
    uniform_int_distribution<int> Ndist(-100,100); // Uniform distribution generator for latitude and longitude for schools of fish
    uniform_int_distribution<int> TypeDist(-2,1); // Uniform distribution generator for setting the type of the fishes randomly, uses inside of loop with conditionals to set char
    uniform_int_distribution<int> SchoolSize(-2,1); // Uniform distribution generator for setting the size of the schools of fish randomly using conditional inside loop
    uniform_int_distribution<int> SchoolNumber(5,10); // uniform distribution generator for setting the base amount of schools of fish to have data generated later
    uniform_int_distribution<int> TidstLong(-10,10); // to be used in T display
    uniform_int_distribution<int> TdistLat(-10,10); // to be used in T display
    uniform_int_distribution<int> Chance(-10,10);
    int  x = SchoolNumber(*gptr);
    // amount of schools of fish


  Fish school[x]; // creating multiple schools of fish each having their own data with this array
    for(int i=0; i<x; i++) // looping through each school of fish and creating random data and setting it to the schools of fish
    {
    char tempType;
    char tempSize;
    int longitude = Ndist(*gptr);
    int latitude = Ndist(*gptr);
    int randNforType = TypeDist(*gptr);
    int randNforSize = SchoolSize(*gptr);
    if(randNforType==-2)
    {
         tempType = 'A';
    }
    else if(randNforType==-1)
    {
         tempType = 'B';
    }
    else if(randNforType== 0)
    {
         tempType = 'C';
    }
    else if(randNforType==1)
    {
         tempType = 'D';
    }

    if(randNforSize==-2)
    {
        tempSize= 'S';
    }
    else if(randNforSize==-1)
    {
        tempSize = 'M';
    }
    else if(randNforSize==0)
    {
        tempSize='L';
    }
    else if(tempSize==1)
    {
        tempSize='X';
    }
    school[i].Setlongitude(longitude);
    school[i].Setlatitude(latitude);
    school[i].SetType(tempType);
    school[i].SetSchool(tempSize);

    }

    //Fish Managment Menu
    cout << "Fish Management Menu" << endl;
    cout << "type any character other than E to continue" << endl << endl;
    char option = menu();
    while(option!='E')
    {
           option=menu();
           switch(option)
           {
               case'D':
               {
                   for(int j=0; j<x; j++)
                   {
                       cout << "School "<<j <<" location: " << endl;
                       cout << "Latitude: " <<school[j].Getlatitude() << endl;
                       cout << "Longitude: " << school[j].Getlongitude() << endl << endl;
                   }

               } break;
               case'T':
                {
                    for(int i=0; i<x; i++)
                    {
                        int tempChance = Chance(*gptr);

                        int tempLongDiff = TidstLong(*gptr);
                        int tempLatDif = TdistLat(*gptr);
                        int CurrLongit=school[i].Getlongitude();
                        int CurrLatit=school[i].Getlatitude();
                        school[i].Setlongitude(CurrLongit+tempLongDiff);
                        school[i].Setlatitude(CurrLatit+tempLatDif);

                        if(tempChance==5)
                        {
                            char tempSize = school[i].GetSchool();
                            if(tempSize=='M')
                            {
                                school[i].SetSchool('S');
                            }
                            else if(tempSize=='L')
                            {
                                school[i].SetSchool('M');
                            }
                            else if(tempSize=='X')
                            {
                                school[i].SetSchool('L');
                            }

                        }
                             school[i].Display();


                    }

                }break;
               case'S':
                {
                    cout <<"type the type of fish you would like to search for, A, B, C, D: ";
                    char tempT;
                    cin >> tempT;
                    char tempC;
                    if(tempT=='A')
                    {
                        for(int i=0; i<x; i++)
                        {
                            tempC= school[i].GetType();
                            if(tempC=='A')
                            {
                                school[i].Display();
                            }
                        }
                    }
                    else if(tempT=='B')
                    {
                         for(int i=0; i<x; i++)
                        {
                            tempC= school[i].GetType();
                            if(tempC=='B')
                            {
                                school[i].Display();
                            }
                        }
                    }
                    else if(tempT=='C')
                    {
                         for(int i=0; i<x; i++)
                        {
                            tempC= school[i].GetType();
                            if(tempC=='C')
                            {
                                school[i].Display();
                            }
                        }
                    }
                    else if(tempT=='D')
                    {
                        for(int i=0; i<x; i++)
                        {
                            tempC=school[i].GetType();
                            if(tempC=='C')
                            {
                                school[i].Display();
                            }
                        }
                    }

                }break;
            }
    }
return 0;
}


char menu()
{
        cout << "D      Display location of All current Fish" << endl;
        cout << "T       Advance one Time Step" << endl;
        cout << "S       Search for a particular type of fish, display all the information for that type" << endl;
        cout << "E       Exit" << endl;
        char input;
        cin >> input;
        return input;
}
