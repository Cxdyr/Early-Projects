#ifndef TEAM_H
#define TEAM_H
#include "wrestler.h"

using namespace std;


class team
{

    public:
    team(int id, default_random_engine*ptr);

        int Getid() { return id; }
        void Setid(int val) { id = val; }
        wrestler * Gethead(int i){return teamz[i];}

void Display();

    private:
        int id;
        wrestler * teamz[14];

};

#endif // TEAM_H
