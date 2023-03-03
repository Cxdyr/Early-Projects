#include <iostream>
#include "coins.h"
#include <fstream>
#include <ostream>

using namespace std;
char menu();
int main()
{
    int yearTemp;
    string typeTemp;
    string conditionTemp;
    string materialTemp;
    double costTemp;
    double valueTemp;

    fstream fin;
    fstream fout;
    fin.open("text.txt",ios::in);
    coins * prev = NULL;
    coins * head = NULL;
    coins * curr = NULL;

fin>>yearTemp;
    while(!fin.eof())
    {
        if(head==NULL)
        {
        head= new coins;
        head->Setyear(yearTemp);
        fin.ignore();
        getline(fin,typeTemp);
            head->Settype(typeTemp);
        getline(fin,conditionTemp);
            head->Setcondition(conditionTemp);
        getline(fin,materialTemp);
            head->Setmaterial(materialTemp);
        fin>>costTemp;
            head->Setcost(costTemp);
        fin>>valueTemp;
            head->Setvalue(valueTemp);
        }
        else
        {
            curr= new coins;
            curr->Setnext(head);
            head=curr;
            head->Setyear(yearTemp);
        fin.ignore();
        getline(fin,typeTemp);
            head->Settype(typeTemp);
        getline(fin,conditionTemp);
            head->Setcondition(conditionTemp);
        getline(fin,materialTemp);
            head->Setmaterial(materialTemp);
        fin>>costTemp;
            head->Setcost(costTemp);
        fin>>valueTemp;
            head->Setvalue(valueTemp);
        }
fin>>yearTemp;
    }
fin.close();

char inputV ='%';
while(inputV!='X')
    {
    inputV =menu();
switch(inputV){


case 'D':{
    if(curr!=NULL)
    {
        curr->Display();
        curr = curr->Getnext();
    }}break;


case 'M':{if(head!=NULL){head->Showall();}
            else{cout<<"no coins"<<endl;}
}break;


case 'A':{ curr = new coins;
    int yearTemp;
    string typeTemp;
    string conditionTemp;
    string materialTemp;
    double costTemp;
    double valueTemp;
        cout << "Coin year: ";
        cin >> yearTemp;
        curr->Setyear(yearTemp);
        cout << endl <<"Coin type: ";
        cin >> typeTemp;
        curr->Settype(typeTemp);
        cout << endl << "Coin condition: ";
        cin >> conditionTemp;
        curr->Setcondition(conditionTemp);
        cout << endl << "Material type: ";
        cin >> materialTemp;
        curr->Setmaterial(materialTemp);
        cout << endl << "Cost amount: ";
        cin >> costTemp;
        curr->Setcost(costTemp);
        cout << endl << "Value amount: ";
        cin >> valueTemp;
        curr->Setvalue(valueTemp);
        curr->Setnext(head);
        head = curr;
}break;


case 'S':{
    int targetyear;
    curr = head;
    prev = head;
    cout << "What is the year of the coin you wish to remove? ";
    cin >> targetyear;
    if(head==NULL) cout << "DOESNT EXIST";
    else if(targetyear==head->Getyear())
    {
        head = head->Getnext();
        curr->Setnext(NULL);
        delete curr;
    }
    else{
        bool found = false;
        while(curr!=NULL)
        {
            if(targetyear!=curr->Getyear())
            {
                prev=curr;
                curr=curr->Getnext();
            }
            else
            {
                cout << "Coin found!"<< endl;
                found = true;
                break;
            }
        }
        if(found)
        {
            prev->Setnext(curr->Getnext());
            curr->Setnext(NULL);
            delete curr;
        }
        else {cout<< "Coin not in list" << endl;}
    }}break;


case 'T':{
    double sum=0;
    curr=head;
    while(curr!=NULL)
    {
        sum = sum+curr->Getvalue();
        curr=curr->Getnext();
    }
cout << "The total value of the list is: $" << sum << endl;
}break;


case 'U':{
    int target;
    char which;
    cout<< "Find what coin? Enter the year of the coin: " <<endl;
    cin >>target;
    cout <<"What would you like to change in this coin's data?" << endl;
    cout <<"Y, for year. C, for condition. M, for material. P, for cost amount. V, for value." << endl;
    cin >> which;

    coins * tcoins;
    bool found = false;
    curr=head;
    while(curr!=NULL)
    {
        if(target==curr->Getyear())
        {
            found = true;
            tcoins = curr;
            curr=NULL;
        }
        else{curr=curr->Getnext();}
    }
    if (which=='Y')
    {
    if(found){tcoins->Display();
        cout<< "New year?" << endl;
        cin >> yearTemp;
        tcoins->Setyear(yearTemp);

        tcoins = NULL;
        }
    else{cout <<"This coin is not in the list" << endl;}
    }
    else if(which=='C')
    {
    if(found){tcoins->Display();
        cout<< "New condition?" << endl;
        cin >> conditionTemp;
        tcoins->Setcondition(conditionTemp);

        tcoins = NULL;
        }
    else{cout <<"This coin is not in the list" << endl;}
    }
      else if(which=='M')
    {
    if(found){tcoins->Display();
        cout<< "New material?" << endl;
        cin >> materialTemp;
        tcoins->Setmaterial(materialTemp);

        tcoins = NULL;
        }
    else{cout <<"This coin is not in the list" << endl;}
    }
      else if(which=='P')
    {
    if(found){tcoins->Display();
        cout<< "New price amount?" << endl;
        cin >> costTemp;
        tcoins->Setcost(costTemp);

        tcoins = NULL;
        }
    else{cout <<"This coin is not in the list" << endl;}
    }
      else if(which=='V')
    {
    if(found){tcoins->Display();
        cout<< "New value?" << endl;
        cin >> valueTemp;
        tcoins->Setvalue(valueTemp);
        tcoins = NULL;
        }
    else{cout <<"This coin is not in the list" << endl;}
    }
}break;


case 'X':{fout.open("text.txt",ios::out);

    curr=head;
    while(curr!=NULL)
    {if(curr!=head){fout<<endl;}
        fout << curr->Getyear() << endl;
        fout << curr->Gettype() << endl;
        fout << curr->Getcondition() << endl;
        fout << curr->Getmaterial() << endl;
        fout << curr->Getcost() << endl;
        fout << curr->Getvalue();
        curr=curr->Getnext();
    }fout.close();break;}
}
}
delete head;
return 0;
}

char menu(){
     char inputV;
    cout << "Menu of Morris functions: "<< endl;
    cout << "D) Display current coin collection" << endl;
    cout << "M) Display all of the current coin collection" << endl;
    cout << "A) Add a new coin" << endl;
    cout << "S) Sell a coin and remove it from the collection"<< endl;
    cout << "T) Compute the total value of the collection" << endl;
    cout << "U) Update a current coin" << endl;
    cout << "X) Update the data file and exit" << endl;
    cin >> inputV;
    return inputV;
}

