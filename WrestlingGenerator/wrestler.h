#ifndef WRESTLER_H
#define WRESTLER_H
#include <string>
#include <random>
#include <ctime>

using namespace std;
class wrestler
{
    public:
        wrestler(){}
        wrestler(default_random_engine*ptr);

        int Getid() { return id; }
        void Setid(int val) { id = val; }
        int Getage() { return age; }
        void Setage(int val) { age = val; }
        double Getweight() { return weight; }
        void Setweight(double val) { weight = val; }
        double GetabilityScore() { return abilityScore; }
        void SetabilityScore(double val) { abilityScore = val; }
        int Getwins() { return wins; }
        void Setwins(int val) { wins = val; }
        int Getlosses() { return losses; }
        void Setlosses(int val) { losses = val; }
        int Getcl() { return cl; }
        void Setcl(int val) { cl = val; }

        wrestler * Getnext(){return next;}
        void Setnext(wrestler * n){next = n;}

    void Display();
    void ShowAll();


    private:
        int id;
        int age;
        double weight;
        double abilityScore;
        int wins;
        int losses;
        int cl;
        wrestler * next;
};

#endif // WRESTLER_H
