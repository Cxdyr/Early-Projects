#ifndef FARM_H
#define FARM_H
#include <iostream>
using namespace std;

class Farm
{
    public:
        Farm();
        virtual ~Farm();

        int Gettroopcount() { return troopcount; }
        void Settroopcount(int val) { troopcount = val; }
        int Getseedcount() { return seedcount; }
        void Setseedcount(int val) { seedcount = val; }
        int Getfoodcount() { return foodcount; }
        void Setfoodcount(int val) { foodcount = val; }

        void Display();



    private:
        int troopcount;
        int seedcount;
        int foodcount;
};

#endif // FARM_H
