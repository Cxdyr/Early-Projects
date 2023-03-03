#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>
using namespace std;
class item
{
    public:
        item(int id);
        virtual ~item();

        int Getid(){return id;}
        void Setid(int val){id = val;}
        string Getname(){return name;}
        void Setname(string val){name = val;}
        string Getspecialattackname(){return specialattackname;}
        void Setspecialattackname(string val){specialattackname=val;}
        int Getbaseattack() { return baseattack; }
        void Setbaseattack(int val) { baseattack = val; }
        int Getbaseblock() { return baseblock; }
        void Setbaseblock(int val) { baseblock = val; }
        int Getspecialattack() { return specialattack; }
        void Setspecialattack(int val) { specialattack = val; }


        void Display();

    protected:

    private:
        int id;
        string name;
        string specialattackname;
        int baseattack;
        int baseblock;
        int specialattack;
};

#endif // ITEM_H
