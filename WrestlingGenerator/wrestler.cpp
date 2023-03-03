#include "wrestler.h"
#include <iostream>
#include <random>
#include <ctime>
using namespace std;

wrestler::wrestler(default_random_engine*ptr)
{
    id = 0;
    wins = 0;
    losses = 0;
    weight = 0;
    next = NULL;

    normal_distribution<double>WeightDist13(100,25); // weight dist 13, min weight = 97, max weight = 283
    normal_distribution<double>WeightDist14(114,25); // weight dist 14
    normal_distribution<double>WeightDist15(123,25); // weight dist 15
    normal_distribution<double>WeightDist16(135,25); // weight dist 16
    normal_distribution<double>WeightDist17(148,25); // weight dist 17
    uniform_int_distribution<int>AgeDist(13,17); // age dist
    normal_distribution<double> Ndist(100, 15); // ability dist
    normal_distribution<double>WrestlersDist(25,3); // array of wrestlers size

    int w;
    age = AgeDist(*ptr);
    abilityScore = (int) Ndist(*ptr);   w =(int) WeightDist13(*ptr);

    switch(age)
    {
    case 13:{
        w=-1;
        w =(int) WeightDist13(*ptr);
        weight = w; }
        break;
    case 14:{   w=-1;
       w =(int) WeightDist14(*ptr);

        weight = w; }
        break;
    case 15:{   w=-1;
        w =(int) WeightDist15(*ptr);

        weight = w; }
        break;
    case 16:{
       w = (int) WeightDist16(*ptr);
        weight = w; }
        break;
    case 17:{
         w = (int) WeightDist17(*ptr);

        weight = w; }
        break;
    }

    if(weight>96 && weight <106){cl = 0;}
    else if(weight >=106 && weight <113){cl =1;}
    else if(weight >= 113 && weight < 120){cl =2;}
    else if(weight >=120 && weight < 126){cl = 3;}
    else if(weight >=126 && weight <132){cl = 4;}
    else if(weight >=132 && weight <138){cl = 5;}
    else if(weight >= 138 && weight <145){cl = 6;}
    else if(weight >=146 && weight<152){cl =7;}
    else if(weight >=152 && weight <160){cl = 8;}
    else if(weight >=160 && weight < 170){cl = 9;}
    else if(weight >=170 && weight <182){cl = 10;}
    else if(weight >=182 && weight<195){cl =11;}
    else if(weight >=195 && weight <220){cl =12;}
    else if(weight >=220 && weight<285){cl =13;}
    else{cout<<"Wrestler is too small or too heavy. "; cl=-1;}

}

void wrestler::Display()
{
    cout <<" wrestlers id: "<<id<<", weight is = " << weight << ", ability score is: " << abilityScore << ", age is: " << age << endl;

}

void wrestler::ShowAll()
{
    Display();
    if(next!=NULL)
    {
        next->ShowAll();
    }
}
