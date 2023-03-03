#include <iostream>
#include "wrestler.h"
#include <string>
#include "team.h"
#include <fstream>
#include <ostream>
#include <random>
#include <ctime>
#include <team.h>

using namespace std;

int bout(wrestler*w1,wrestler*w2,default_random_engine*gptr);
void match(team * t1, team * t2, default_random_engine*gptr);
int main()
{
    default_random_engine *gptr;
    gptr = new default_random_engine(time(NULL));

    team * t1 = new team(100,gptr);
    team * t2 = new team(200,gptr);
    t1->Display();
    cout << endl;


    match(t1,t2,gptr);


    return 0;
}

int bout(wrestler*w1,wrestler*w2,default_random_engine*gptr)
{
    normal_distribution<double>w1dist(w1->GetabilityScore(),15);
    normal_distribution<double>w2dist(w2->GetabilityScore(),15);
    int score1, score2;

    score1 = (int) w1dist(*gptr);
    score2 = (int) w2dist(*gptr);

    return score1-score2;
}

void match(team * t1, team * t2, default_random_engine*gptr)
{
    int Diff = 0;
    int TScore1 =0;
    int TScore2 = 0;

    cout<<"Match between team# "<<t1->Getid()<<" and #"<<t2->Getid()<<endl;
    for(int i=0; i<14; i++)
    {
        if((t1->Gethead(i)!=NULL)&&(t2->Gethead(i)==NULL))
        {
            TScore1 = TScore1 + 6;
        }
        else if((t1->Gethead(i)!=NULL)&&(t2->Gethead(i)!=NULL))
        {
            Diff = bout(t1->Gethead(i), t2->Gethead(i), gptr);
            if (Diff>0)
            {
                if(Diff<4)
                {
                    TScore1 = TScore1+3;
                }
                else if(Diff<9)
                {
                    TScore1 = TScore1+4;
                }
                else if(Diff<13)
                {
                    TScore1=TScore1 +5;
                }
                else
                {
                    TScore1 = TScore1 + 6;
                }
            }
            else if (Diff<0)
            {
                if(Diff>-4)
                {
                    TScore2 = TScore2+3;
                }
                else if(Diff>-9)
                {
                    TScore2= TScore2 +4;
                }
                else if(Diff>-13)
                {
                    TScore2= TScore2+5;
                }
                else
                {
                    TScore2 = TScore2+6;
                }
            }

        }
        if(TScore1>TScore2)
        {
            cout<<"TEAM #"<< t1->Getid()<<" is victorious "<<TScore1<<" to "<<TScore2<<endl;
        }
        else if (TScore2>TScore1)
        {
            cout << "TEAM #: " << t2->Getid() << " is victorious "<<TScore2 << " to " << TScore1 << endl;   //maybe move outside of the loop to see what it does
        }

    }

}
