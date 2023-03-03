#include <iostream>
#include "wrestler.h"
#include "team.h"
#include <string>
#include <fstream>
#include <ostream>
#include <random>
#include <ctime>
#include <team.h>
using namespace std;

team::team(int i, default_random_engine*ptr)
{   id = i;
    wrestler * curr;

    for(int n=0; n<14; n++)
    {
        teamz[n]=NULL;
    }

    int teammembers;
    normal_distribution<double>numdist(25,3);
    teammembers= numdist(*ptr);

    for (int i =1; i <= teammembers; i++)
    {
        curr = new wrestler(ptr);
        curr->Setid(id+i);
        int index = curr->Getcl();
        if(index == -1){cout<<"Wrestler: " <<curr->Getid() <<", weighing "<< curr->Getweight() <<" cannot compete."<<endl;}
        else if (teamz[index]==NULL){teamz[index]=curr;}
        else if(curr->GetabilityScore()>teamz[index]->GetabilityScore())
            {
                curr->Setnext(teamz[index]);
                teamz[index]=curr;
            }
        else
            {
            curr->Setnext(teamz[index]->Getnext());
            teamz[index]->Setnext(curr);
            }
    }
}


void team::Display()
{
    cout <<"TEAM NUMBER: "<< id << endl <<endl;
    for (int i=0; i<14; i++)
    {
        if (teamz[i]!=NULL)
        {
            teamz[i]->ShowAll();
        }
        cout<<"---------------------------------------------END-OF-WEIGHT-CLASS---"<<endl;
    }
}
