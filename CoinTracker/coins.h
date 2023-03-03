#ifndef COINS_H
#define COINS_H
#include <string>
#include <iostream>
using namespace std;

class coins
{
    public:
        coins();
        virtual ~coins();


        int Getyear() { return year; }
        void Setyear(int val) { year = val; }
        string Gettype() { return type; }
        void Settype(string val) { type = val; }
        string Getcondition() { return condition; }
        void Setcondition(string val) { condition = val; }
        string Getmaterial() { return material; }
        void Setmaterial(string val) { material = val; }
        double Getcost() { return cost; }
        void Setcost(double val) { cost = val; }
        double Getvalue() { return value; }
        void Setvalue(double val) { value = val; }
        coins * Getnext(){return next;}
        void Setnext(coins *n){next =n;}

        void Display();
        void Showall();

    private:
        int year;
        string type;
        string condition;
        string material;
        double cost;
        double value;
        coins * next;
};

#endif // COINS_H
