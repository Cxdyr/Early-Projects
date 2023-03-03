/*
        A COUPLE THINGS: This code reuses a bunch of functions over and over again, such as artdisplay(), newscreen(), menus for fight screens
        and a fight function that takes a lot of info and then creates a fight out of it.
        newscreen() is simply a system pause, then a system clear
        artdisplay() is simply opening the filename passed into it, then outputting all of the text from the file, closing it and ending

        Also, the way I implemented this code includes a log in system, kind of pointless but cool to have. It uses if statements for each level to allow traversing levels easy
        if needed. I also have each level within its own if statement, and create objects and other things in the main area so that you can skip to each level without having any mistakes occur.

        IMPORTANT: IF YOU HAVE ERROR -> Go to line 270 and comment it out OR go to your IDE, settings, compiler, linker settings, and add -lwnmm
        to fix. It is simply a built in function to play music and it plays a lofi music track on repeat

        Please enjoy, My sense of humor is really dumb but I did put a lot of effort into this. My skills while coding this are currently in 300 level classes at ODU,
        most of the code written here is just cout statements and the reuse of functions, but there are a few slightly higher level concepts used here... But if you are looking
        for that, go check out some other things on my github this is just a passion project for fun and I am sure I could tweak some things but its cool.
        Thanks,
        Cody Rabie, 2/14/2023

*/



#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <list>
#include <random>
#include <ctime>
#include <windows.h>
#include <mmsystem.h>
#include "item.h"
#include "Bob.h"
using namespace std;

void artdisplay(string filename)
{
    ifstream artfile;
    artfile.open(filename);
    string art;
    while(!artfile.fail()&&!artfile.eof())
    {
        getline(artfile, art);
        cout << art << endl;
    }
    artfile.close();
};

void newscreen()
{
    cout << endl;
    system("pause");
    system("cls");
};

char chooseattack()
{
    cout << endl << endl << "a) base attack " << endl;
    cout << "b) special attack " << endl;
    cout << "c) block attack" << endl;
    char in;
    cin >> in;
    return in;

};

char chooseweapon(int level)
{

    cout << "Unlocked weapons: " << endl;
    cout << "1) Knife " << endl;
    if(level>1)
    {
        cout << "2) Laser Gun " << endl;
    }
    if(level>2)
    {
        cout << "3) Fish Hook " << endl;
    }
    /// need to think of more blah blah
    int choice;
    cout << "choice: ";
    cin >> choice;
    return choice;
};

int bobattackdice(int damage, int dice)
{
    switch(dice)
    {
    case 1:
    {
        cout << "Bob missed his attack " << endl;
        damage = 0;
    }
    break;
    case 2:
    case 3:
    case 4:
    case 5:
    {
        cout << "Bob hit his attack inflicting " << damage << " damage! " << endl;
    }
    break;
    }
    return damage;
};

int villainattackdice(int vdamage, string name, int dice)
{
    switch(dice)
    {
    case 1:
    {
        cout << name << " missed his attack " << endl;
        vdamage = 0;

    }
    break;
    case 2:
    case 3:
    {
        cout << name << " hit bob with " << vdamage << " damage! " <<endl;
    }
    break;
    }
    return vdamage;
};

int fightsequence(string weaponname, int Bdamage,int Bsdamage, int Bbdamage, string villainname, int Vilhealth, int Vildamage, string Vilart)
{
    default_random_engine*gptr;
    gptr = new default_random_engine(time(NULL));

    uniform_int_distribution<int>BattackChance(1,5);
    uniform_int_distribution<int>VattackChance(1,3);

    string villainart = Vilart;
    int Bhealth = 75;

    int Vhealth = Vilhealth; // villain health
    int Vdamage=Vildamage; // villain attack
    int alive = 1; /// set to 1 while villain is alive, 0 breaks loop and kills villain

    while(alive==1)
    {
        int Vd = VattackChance(*gptr);
        int Bd = BattackChance(*gptr);
        newscreen();
        artdisplay(villainart);
        cout << "Boss Health: " << Vhealth << "   Bob Health: " << Bhealth << endl;
        cout << weaponname;///newWeapon->Getname();
        char attack = chooseattack();
        switch(attack)
        {
        case 'a':
        {
            ///Bdamage=  newWeapon->Getbaseattack();
            int damage1 =bobattackdice(Bdamage, Bd);
            Vhealth = Vhealth-damage1;

            int Vdamage1 = villainattackdice(Vdamage, villainname, Vd);
            Bhealth = Bhealth - Vdamage1;
        }
        break;
        case 'b':
        {
            ///Bsamage=  newWeapon->Getspecialattack();
            int damage1 =bobattackdice(Bsdamage, Bd);
            Vhealth = Vhealth-damage1;

            int Vdamage1 = villainattackdice(Vdamage, villainname, Vd);
            Bhealth = Bhealth - Vdamage1;
        }
        break;
        case 'c':
        {
            cout << "blocked attack and gained " << Bbdamage /*newWeapon->Getbaseblock()*/ << " health points.";
            Bhealth=Bhealth+ Bbdamage;
            Vdamage = Vdamage+1;
        }
        break;
        }
        if (Vhealth<=0 && Bhealth>0)
        {
            alive=0;
            cout << "Bob has killed " << villainname;
            newscreen();
        }
        if((Bhealth<=0 && Vhealth<=0)|| Bhealth<=0)
        {
            alive=0;
            cout << "You have died to " <<villainname << "... come on man seriously?";
            newscreen();
        }
    }
    return 1;
};

char dailymenu()
{
    cout << endl << "a) Watch TV " << endl << "b) Pet dog " << endl << "c) View items " << endl << "d) Go to the gym " << endl;
    char in;
    cin >> in;
    return in;
};

char gymmenu()
{
    cout << endl << "a) bench press " << endl << "b) do squats " << endl << "c) go to locker room " << endl;
    char in;
    cin >> in;
    return in;
};

char martialmenu()
{
    cout << endl << "a) fight with a kick or whatever " << endl << "b) use ray gun " << endl;
    char in;
    cin >> in;
    return in;
};

char martialbossmenu()
{
    cout << endl << "a) fight with a kick or whatever " << endl << "b) study kevins attack " << endl;
    char in;
    cin >> in;
    return in;
};



int main()
{
    ofstream fileupdate;
    ifstream file;
    string username, password;
    int choice, level;
    cout << "1: Register " << endl << "2: Login " << endl << "choice: ";
    cin>>choice;
    if(choice==1)
    {
        string username, password;
        cout << "select a username: ";
        cin >> username;
        cout << "select a password: ";
        cin >> password;

        ofstream file;
        file.open(username+"_.txt"); ///underscore added to files so they never get mixed up with the Art files
        file << username << endl << password << endl << 0;
        file.close();
        level =1;
    }
    else if(choice==2)
    {


        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;


        file.open(username+"_.txt");
        string un, pw;
        file >> un;
        file >> pw;
        file.close();

        if(un == username && pw == password)
        {

            cout << "Logged in! " << endl;
            cout << "Type 1 to start, type 2-9 to skip to other levels " << endl;
            cin >> level;
            newscreen();

        }
        else
        {
            cout << "False Login!";
            return 0;
        }

    }


    ///    MUSIC PLAYER
    PlaySound(TEXT("Where-The-Waves-Take-Us.wav"), NULL, SND_LOOP || SND_ASYNC); /// playing music for game
    ///    MUSIC PLAYER ^



    default_random_engine*gptr;
    gptr = new default_random_engine(time(NULL));

    uniform_int_distribution<int>BattackChance(1,5);
    uniform_int_distribution<int>VattackChance(1,3);
    uniform_int_distribution<int>GamblingChance(1,2);
    uniform_int_distribution<int>ReporterDialogue(1,5);
    uniform_int_distribution<int>MartialEnemyD(1,2);
    uniform_int_distribution<int>KevinAttackD(3,10);


    item * newWeapon;
    list <item>itemlist;
    list<item>::iterator itr;




///creation of first weapon and adding to weapon list
    newWeapon = new item(1);
    newWeapon->Setname("Knife");
    newWeapon->Setspecialattackname("Shank");
    newWeapon->Setid(1);
    newWeapon->Setbaseattack(5);
    newWeapon->Setbaseblock(5);
    newWeapon->Setspecialattack(7);
    itemlist.push_back(*newWeapon);

    if(level==1)
    {
        ///start of level 1
        cout << "START OF LEVEL 1, BOB'S JOURNEY " << endl;
        newscreen();

        artdisplay("IntroArt1.txt");
        cout << endl << endl << "type C to close diary ";
        char startgame;
        cin >> startgame;
        if(startgame!='C')
        {
            cout << "GAME OVER, YOU SUCK " << endl << " how do you not even type a character right ";
            return 0;
        }
        else
        {

            system("cls");
            artdisplay("IntroArt2.txt");
            newscreen();
            artdisplay("IntroArt3.txt");
            newscreen();
            artdisplay("IntroArt4.txt");
            cout << endl <<"Bob: But I love my dog, I have to do something... ";
            cout << "Bob set out on a journey to find any and every alien he could. " << endl << "his journey let him to a forest..." << endl;
            newscreen();

            int taskcomplete = 0;
            level =1;
            while(taskcomplete==0)
            {
                artdisplay("MapArt1.txt");
                cout << endl << "choice: ";
                char mapchoice1;
                cin >> mapchoice1;
                switch(mapchoice1)
                {
                case 'a':
                {
                    cout << "It seems you found an item... a knife hiding in the lake. " << endl << "this could be useful.";
                    newWeapon->Display();
                    newscreen();
                    taskcomplete = 1;
                }
                break;
                case 'b':
                case 'c':
                {
                    system("cls");
                    cout << "Cannot enter area without weapon ";
                    newscreen();
                }
                break;
                }
            }
            /// end of task 1/3 other tasks in new loop for level 1
            while(taskcomplete==1)
            {
                artdisplay("MapArt1.txt");
                cout << endl << "choice: ";
                char mapchoice1;
                cin >> mapchoice1;
                switch(mapchoice1)
                {
                case 'a':
                {
                    system("cls");
                    cout << "you have already completed this task ";
                    newscreen();
                }
                break;
                case 'b':
                {
                    system("cls");
                    artdisplay("Level1Art1.txt");
                    cout << "Greg: Yo its greg, the alien greg. " << endl << endl<< "Bob: What do you want with my dog, and all other" << endl << "dogs matter of fact." << endl << endl << "Greg: I'll tell you under one condition...";
                    newscreen();
                    artdisplay("Level1Art1.txt");
                    cout << "Bob: And whats that? " << endl << endl << "Greg: Guess what number i'm thinking of in my head...";
                    newscreen();
                    int numbergame;
                    int counter = 0;
                    char stab='x';
                    while(numbergame!=28)
                    {
                        artdisplay("Level1Art1.txt");
                        cout << "what number is Greg thinking of?  ";
                        cin >> numbergame;
                        if(numbergame>28 && numbergame<=58)
                        {
                            cout <<endl << endl << "Greg: Warm, ill give you this " << endl << "you're within 30 numbers of being correct.";
                            newscreen();
                        }
                        else if(numbergame<28 && numbergame>=0)
                        {
                            cout << endl << endl << "Greg: I mean, kinda warm. Its a bit more than this though";
                            newscreen();
                        }
                        else if(numbergame==28)
                        {
                            cout << "Greg: I'm a bit surprised that you guessed that" << endl << "well I'll just leave then, no need to " << endl << "even tell you, I'll just leave. ";
                            newscreen();
                            cout << "Greg left " << endl;
                        }
                        else
                        {
                            cout << endl << endl << "Greg: Not even close, seriously dude. ";
                            newscreen();
                        }
                        if(counter>10&&numbergame!=28)
                        {
                            cout << "do you want to stab greg:  a (yes)    any other char (no)   " << endl;
                            cout << "choice: ";
                            cin >> stab;
                            if(stab=='a')
                            {
                                cout << "Bob stabbed Greg with his knife and murdered the alien in hold blood, sick... very sick man. " << endl;
                                numbergame=28;
                            }
                        }

                        counter++;
                    }
                    taskcomplete=2;
                    newscreen();
                }
                break;
                case 'c':
                {
                    system("cls");
                    cout << "talk to greg first ";
                    newscreen();
                }
                break;
                }
            }

            ///end of task 2/3 new loop for the final task in level 1

            while(taskcomplete==2)
            {
                artdisplay("MapArt2.txt");
                cout << "choice: ";
                char mapchoice1;
                cin >> mapchoice1;
                if(mapchoice1=='c')
                {
                    system("cls");
                    cout << "Bob entered the Den of Dread... ";
                    newscreen();
                    artdisplay("Boss1Art.txt");
                    cout << endl << endl << "Krogg: WHO DARES TO DEFY KROGG, DIE HUMAN AND AS WELL YOUR DOG" << endl;
                    int itemnumber = chooseweapon(1);
                    while(itemnumber!=1)
                    {
                        itemnumber=chooseweapon(1);
                    }
                    newWeapon->Display();
                    int fightwon = fightsequence(newWeapon->Getname(),newWeapon->Getbaseattack(),newWeapon->Getspecialattack(), newWeapon->Getbaseblock(), "Krogg",100, 5, "Boss1Art.txt");
                    if(fightwon==1)
                    {
                        taskcomplete=3;;
                    }


                }
                else
                {
                    cout << "Come on man, you don't really have a choice here. " << endl << "do you know how much extra effort it took to code this, come on. " << endl;
                    newscreen();
                }

            }

            level = 2;

        }
        cout << "END OF LEVEL 1 " << endl;
        newscreen();


    }


    newWeapon = new item(2);
    newWeapon->Setname("Laser Gun");
    newWeapon->Setbaseattack(7);
    newWeapon->Setbaseblock(1);
    newWeapon->Setspecialattack(20);
    newWeapon->Setid(2);
    newWeapon->Setspecialattackname("Beam");
    itemlist.push_back(*newWeapon);

    if(level==2)
    {
        cout << "START OF LEVEL 2, BOB'S DOG " << endl;
        newscreen();

        cout << "YOU HAVE DEFEATED KROGG " << endl << "KROGG HAS DROPPED THE LASER GUN" << endl;

        itr=itemlist.begin();
        while(itr!=itemlist.end())
        {
            itr->Display();
            itr++;
        }
        newscreen();
        artdisplay("MapArt3.txt");
        newscreen();

        level = 2; /// start of level 2
        int counter=1;
        while(level==2)
        {
            artdisplay("Level2Art.txt");
            cout << endl << " PET DOG " << endl;
            newscreen();
            if(counter<=3)
            {
                cout << "Your dog loves it! <3"<<endl;
                newscreen();
            }
            else if(counter>2 && counter<=5)
            {
                cout << "Your dog is starting to not like it as much! <3" << endl;
                newscreen();
            }
            else if(counter>5 && counter <=6)
            {
                cout <<"Your dog dislikes it, and wants you to stop now! </3 "<<endl;
                newscreen();
            }
            else if(counter>6 && counter<8)
            {
                cout << "Your dog never dislikes it, something must be wrong..." << endl;
                newscreen();
            }
            if(counter>8)
            {
                cout << "This is an imposter! " << endl;
                level = 3;
                newscreen();
            }
            counter++;
        }


        /// end of level 2 and start of level 3, battle with the copy alien
    }
    if(level==3)
    {
        cout << "START OF LEVEL 3, BOB vs SMEEG " << endl;
        newscreen();

        artdisplay("Boss2Art.txt");
        cout << endl << "Smeeg: Yo its not actually your dog you dork, its me Smeeg" << endl << "I like transform and stuff, its pretty cool."<< endl << endl <<"Bob: Wheres my dog Smeeg you're being a real piece of shit right now. " << endl;

        while(level==3)
        {
            int fightwon = fightsequence(newWeapon->Getname(),newWeapon->Getbaseattack(),newWeapon->Getspecialattack(),newWeapon->Getbaseblock(),"Smeeg",120,7, "Boss2Art.txt");
            if(fightwon==1)
            {
                level=4;
            }

        }

    }

    newWeapon = new item(3);
    newWeapon->Setname("RAY GUN");
    newWeapon->Setid(3);
    newWeapon->Setbaseattack(50);
    newWeapon->Setbaseblock(1);
    newWeapon->Setspecialattack(5);
    newWeapon->Setspecialattackname("Who Cares, you arent gonna use it anyways");
    itemlist.push_back(*newWeapon);
    int wallet = 50;/// amount of money bob has
///start of next level
    if(level==4)
    {
        cout << "START OF LEVEL 4, BOB vs CASINO " << endl;
        newscreen();
        while(level==4)
        {
            artdisplay("Level4Art.txt");
            cout << endl << "Bob: Is this a slot machine? Why does " << endl << "Smeeg think this is a money printer? " << endl;
            newscreen();
            artdisplay("Level4Art.txt");
            cout << "*cha ching*" << endl << endl << "Bob: Whats that? " << endl;
            cout << "choice: (a) play slots    (b) kill the vibe " << endl;
            char choice;
            cin >> choice;
            if(choice!='a')
            {
                cout << "Wow, you really killed the vibe... you happy now? " <<endl;
                newscreen();
                choice='a';
            }

            int counter = 0;
            while(choice=='a')
            {
                artdisplay("Level4Art.txt");
                cout << endl << "$5 per spin "  << endl << "Money: " << wallet << endl;
                cout << "choose numbers 1 or 2: ";
                int numb;
                cin >> numb;
                int slotnumb= GamblingChance(*gptr);
                if(numb==slotnumb)
                {
                    system("cls");
                    artdisplay("Level4Art.txt");
                    cout << "JACKPOT YOU HAVE WON $100,000! " << endl;
                    wallet = wallet+100000;
                    newscreen();
                }
                else if(numb!=slotnumb)
                {
                    system("cls");
                    artdisplay("Level4Art.txt");
                    cout << "Dead spin, -$5 " << endl;
                    wallet=wallet-5;
                    newscreen();
                }
                counter++;
                if(counter>9)
                {
                    cout << "Having fun? No, no feel free to keep going. " << endl << "I don't care, but if you are bored... " << endl << "*whispers* type the number 43 into the slot machine." <<endl;
                }
                if(numb==43)
                {
                    system("cls");
                    artdisplay("Level4Art.txt");
                    cout << "SECRET MENU UNLOCKED " << endl << "receive RAY GUN " << endl;
                    newscreen();
                    itr=itemlist.begin();
                    while(itr!=itemlist.end())
                    {
                        itr->Display();
                        itr++;
                    }
                    newscreen();
                    choice='b';
                    level =5;

                }
            }
        }

    }/// end of level 4


    if(level==5)
    {
        cout << "START OF LEVEL 5, BOB'S DOG " << endl;
        newscreen();

        while(level==5)/// start of level 5, finds dog and goes back home and ends game or can play slots and pet his dog on loop
        {
            cout << "Bob: Now I have tons of money and I have weapons. " << endl << "I need to get my dog back. " << endl << endl << "Bob: Is that a note on the back of the RAY GUN? " << endl;
            newscreen();
            artdisplay("Level5Art.txt");

            artdisplay("Level5Art2.txt");
            cout << endl << "Bob: Maybe I should check this place out...";
            newscreen();

            int fightwon = fightsequence(newWeapon->Getname(), newWeapon->Getbaseattack(), newWeapon->Getspecialattack(), newWeapon->Getbaseblock(),"Godfree",550,7, "Boss3Art.txt");
            if(fightwon==1)
            {
                level=6;
            }
        }



    }

    ///adding the slot machine from earlier to Bobs collection of items
    newWeapon= new item(4);
    newWeapon->Setname("Slot Machine");
    newWeapon->Setbaseattack(1);
    newWeapon->Setspecialattack(1);
    newWeapon->Setbaseblock(7);
    newWeapon->Setid(4);
    newWeapon->Setspecialattackname("Spin Slots");
    itemlist.push_back(*newWeapon);

    if(level==6)
    {
        cout << "START OF LEVEL 6, MONOLOLUGE TYPE STUFF" << endl;
        newscreen();
        cout << "Bob: It seems I finished off the god of aliens, now where"<<endl << "is my dog? " <<endl;
        newscreen();
        artdisplay("Level6Art.txt");
        cout << endl << "Bob: MY DOG! ";
        newscreen();
        artdisplay("Level6Art.txt");
        cout << endl << "Bob: What do you say buddy, you wanna go home? " <<endl;
        newscreen();
        artdisplay("Level6Art2.txt");
        cout << endl << "Bob: Haha thats the spirit! " << endl;
        newscreen();
        artdisplay("Level2Art.txt");
        cout << endl << "Bob: Lets go inside " << endl;
        newscreen();
        artdisplay("Level7Art.txt");
        newscreen();
        level=7;
    }
    if(level==7)
    {
        cout << "START OF LEVEL 7, NORMAL LIFE " << endl;
        newscreen();
        artdisplay("Level7Art.txt");
        cout << endl << "reporter: All aliens have been scared off of Earth, no one " << endl << "realy knows why, but they're gone! " << endl;
        newscreen();

        int taskscomplte = 1;
        char startloop = 'a';
        while(startloop!='b')
        {
            artdisplay("Level7Art.txt");
            char input = dailymenu();
            switch(input)
            {
            case 'a':
            {
                system("cls");
                artdisplay("Level7Art2.txt");
                int option = ReporterDialogue(*gptr);
                if(option==1)
                {
                    cout << endl << "reporter: Just in! Dolphins are smoking weed all around town..."<<endl;
                }
                else if(option==2)
                {
                    cout << endl << "reporter: Presidential swimming contest coming up on Wolf, get ready! ";
                }
                else if(option==3)
                {
                    cout << endl << "reporter: Why are you spending so much time alone, are you ok? ";
                }
                else if(option==4)
                {
                    cout << endl << "reporter: Michael Pleps to play the rapist in Therapist the movie... " << endl << "are we allowed to say that?" <<endl;
                }
                else if(option==5)
                {
                    cout << endl << "reporter: National pepperoni shortage nation wide, and how it affects you... " <<endl;
                }
                newscreen();

            }
            break;
            case 'b':
            {
                system("cls");
                artdisplay("Level7Art.txt");
                cout << endl << "She LOVES it! <3" <<endl;
                newscreen();

            }
            break;
            case 'c':
            {
                cout << "You got some pretty cool stuff here. " << endl;
                itr=itemlist.begin();
                while(itr!=itemlist.end())
                {
                    itr->Display();
                    itr++;
                }
                newscreen();
            }
            break;
            case 'd':
            {
                newscreen();
                cout << "*after walking for 15 minutes Bob arrives at the gym*" << endl;
                artdisplay("Level7Art3.txt");
                newscreen();
                char hitlegs;
                int workoutcounter=0;
                while(workoutcounter<6)
                {
                    artdisplay("Level7Art4.txt");
                    hitlegs = gymmenu();
                    switch(hitlegs)
                    {
                    case 'a':
                    {
                        cout << "You hit chest and benched a ton of weight! Great job! " << endl;
                        cout << "There's not strength stats or anything for Bob, but if there were " << endl << "you sure would have boosted them right up! " <<endl;
                        newscreen();
                    }
                    break;
                    case 'b':
                    {
                        int chance = ReporterDialogue(*gptr);
                        if(chance==1)
                        {
                            cout << "Stop trying to hit legs you dork. Real men don't hit legs. " <<endl;
                        }
                        else if(chance==2)
                        {
                            cout << "You bench pressed and got a great pump, thank me later. " <<endl;
                        }
                        else if(chance==3)
                        {
                            cout << "This bench press machine really feels great, I love hitting chest. "<<endl;
                        }
                        else if(chance==4)
                        {
                            cout << "Really seems more like a chest day to be honest... who needs legs. " << endl;
                        }
                        else
                        {
                            cout << "How'd we end up at the bench press? Isn't it leg day? " << endl;
                        }
                        newscreen();
                    }
                    break;
                    case 'c':
                    {
                        cout << endl << "*Bob was instantly hit with a flash of naked old men* Nice." << endl;
                        newscreen();

                    }
                    break;
                    default:
                    {
                        cout << "That was not an option, are you good? Lol. " << endl;
                        newscreen();
                    }
                    break;
                    }

                    workoutcounter++;
                }
            }
            break;
            }
            taskscomplte++;
            if(taskscomplte>18)
            {
                cout << endl << "type x) to continue to next level, or any other char to continue this level: ";
                char in;
                cin >> in;
                if(in=='x')
                {
                    startloop='b';
                    level=8;
                }
                newscreen();
            }
        }

    }
    if(level==8)
    {
        cout << "START OF LEVEL 8, MARTIAL LAW " << endl;
        newscreen();
        cout << "As time went on Bob was happy his dog was safe..." << endl << "but he had grown bored, Bob missed the rush of a fight. " << endl;
        newscreen();
        cout << "One day the TV showed an Ad for a martial arts contest. " << endl << "Bob knew what he had to do. " << endl;
        newscreen();
        artdisplay("Level8Art.txt");
        cout << endl << "     Welcome to Level 8, Martial Law " << endl;
        newscreen();
        cout << "Welcome to the Tournament Arc " << endl;

        ///this is going to create a class for bob, its going to be wins to losses, health, damage, and reputation.   when in a fight he can attack normal or cheat, use ray gun and kill them, if he does
        /// a lot of the ray gun ones his reputation sinks alot
        /// class only has one instance of bob, and is only used in this section.
        Bob BobM;

        int oponentNumb = 1;
        int cheatNumb = 0;
        int oponentHealth = 50;
        int oponentDamage;


        while(oponentNumb<7) /// CODY REMEMBER TO CHANGE THIS TO LIKE 8
        {

            if((MartialEnemyD(*gptr))==1)
            {
                oponentDamage=10;
            }
            else
            {
                oponentDamage=5;
            }

            cout << endl << "Bob vs Opponent " << oponentNumb << "!"<<endl <<endl;
            artdisplay("Level8Art2.txt");
            cout << endl << "Opponent " << oponentNumb << " Health: " << oponentHealth << "     Bob Health: " << BobM.Gethealth();
            cout << endl;
            char in = martialmenu();
            switch(in)
            {
            case 'a':
            {
                oponentHealth = oponentHealth - BobM.Getdamage();
                BobM.Sethealth(BobM.Gethealth() - oponentDamage);
                cout << "Bob hit the opponent with 5 damage "   << endl;
                cout << "The opponent hit bob with " << oponentDamage << " damage "    << endl;
                newscreen();
            }
            break;
            case 'b':
            {
                system("cls");
                artdisplay("Level8Art3.txt");
                cout << "Bob fucking cheats and murders the martial artist with a RAY GUN! " << endl;
                BobM.Setreputation(BobM.Getreputation()-20);
                oponentHealth = 0;
                if(cheatNumb>3)
                {
                    cout << "You're ok with just burning these defenseless dudes alive?? Bro..." << endl;
                }
                newscreen();
                cheatNumb++;

            }
            }
            if(oponentHealth<=0)
            {
                BobM.Setwins(BobM.Getwins()+1);
                BobM.Sethealth(75);
                oponentHealth=50;
                oponentNumb++;
                cout << "Bob has won! " << BobM.Getwins() << " wins /to " << BobM.Getloses() << " losses! " <<endl;
                newscreen();
            }
            else if(BobM.Gethealth()<=0)
            {
                BobM.Setloses(BobM.Getloses()+1);
                BobM.Sethealth(75);
                oponentHealth=50;
                oponentNumb++;
                cout << "Bob lost, what a bum. " << endl;
                newscreen();
            }

        }
        if(BobM.Getreputation()>=40)
        {
            cout << "Bob proved himself in the ring and had a good reputation! " <<endl;
        }
        else if(BobM.Getreputation()<40)
        {
            cout << "Bob burned multiple people alive in a tournament where guns " << endl << "are not allowed..."<< endl;
            newscreen();
        }
        cout << "Bob has made it to the grade finals of the tournament... " << endl << "his opponent is world renown for being the greatest " << endl << "martial artist of all time..." << endl;
        newscreen();
        artdisplay("Level8Art4.txt");
        cout << endl << endl << "Kevin, THE GREATEST MARTIAL ARTIST OF ALL TIME " << endl << "wins: 2,043,  losses: 0 " << endl;
        newscreen();
        cout << "Do you really want to fight this guy? " << endl;
        cout << "Bob: a) yes     b) no   " << endl;
        char tin;
        cin >> tin;
        if(tin!='a')
        {
            cout << "You need some self belief man, this is coming from me heart to heart. " << endl;
        }
        cout << "Life isn't going to just roll over for you all the time. " << endl << "If you want something you have to leave your comfort zone and go for it. " << endl;
        cout << "Life isn't always about feeling safe, or feeling content. " << endl << "You can do it, just believe in yourself. Good luck. " <<endl;
        newscreen();
        cout << endl << endl << "PEP TALK = +200 HEALTH BOOST & +10 DAMAGE " <<endl;
        newscreen();
        BobM.Sethealth(BobM.Gethealth()+200);
        BobM.Setdamage(BobM.Getdamage()+10);

///Boss information, boss is now alive.
        int alive = 1;
        int health = 900;

        int dialoguecounter = 0;
        int deathcounter = 0;

        while(alive==1)
        {
            artdisplay("Level8Art5.txt");
            char attack = martialbossmenu();
            switch(attack)
            {
            case 'a':
            case 'b':
            default:
            {
                if(dialoguecounter==0)
                {
                    system("cls");
                    artdisplay("Level8Art6.txt");
                    cout << "Kevin dodges the attack and grabs Bob by his bald head then " << endl << "face slams him, killing him. " << endl;
                    newscreen();
                }
                else if(dialoguecounter==1)
                {
                    system("cls");
                    artdisplay("Level8Art6.txt");
                    cout << "Kevin kicks Bob in the head and it instantly kills him. " << endl;
                    newscreen();
                }
                else if(dialoguecounter>1)
                {
                    system("cls");
                    artdisplay("Level8Art6.txt");
                    cout << "Kevin blocks Bob's attack and then punches him in the head and it kills him. Wow. " << endl;
                    newscreen();
                }
            }
            break;
            }
            dialoguecounter++;
            if(dialoguecounter>=3)
            {
                cout << "Bob, I think we need to talk. " << endl;
                cout << "Bob:  any) lets talk    b) no, I must beat Kevin " << endl;
                char in;
                cin >> in;
                if(in!='b')
                {
                    cout << "I think we need to take a different approach here Bob... " << endl << "I think you need to start trusting your instincts..." << endl << endl;
                    cout << "*and so... thats what Bob did.* ";
                    alive=2;
                    newscreen();
                }
            }

        }
        while(alive==2)
        {
            int KevinD = KevinAttackD(*gptr);
            if(KevinD==3)
            {
                KevinD=40;
            }

            artdisplay("Level8Art5.txt");
            cout << endl << "Kevin Health:  " << health << "    Bob Health: " << BobM.Gethealth() << endl;
            char attack = martialbossmenu();
            switch(attack)
            {
            case 'a':
            {
                system("cls");
                artdisplay("Level8Art6.txt");
                health = health - BobM.Getdamage();
                BobM.Sethealth(BobM.Gethealth()-KevinD);
                cout << "Bob hit Kevin with a kick doing " << BobM.Getdamage() << " damage! " << endl;
                cout << "Kevin hit Bob with a crazy ass kick doing " << KevinD << " damage! " << endl;
                newscreen();

            }
            break;
            case 'b':
            {
                system("cls");
                artdisplay("Level8Art6.txt");
                cout << "Bob studies Kevins attack... Kevin hits bob for " << KevinD << endl;
                BobM.Sethealth(BobM.Gethealth()-KevinD-2);
                BobM.Setdamage(BobM.Getdamage()+5);
                newscreen();
            }
            break;
            default:
            {
                system("cls");
                cout << "That wasn't even an option bro... " << endl;
                newscreen();
            }
            break;

            }
            if (health<=0 && BobM.Gethealth()>0)
            {
                alive=0;
                cout << "Bob has killed Kevin ";
                newscreen();
                BobM.Setwins(BobM.Getwins()+1);
            }
            if((BobM.Gethealth()<=0 && health<=0) || BobM.Gethealth()<=0)
            {
                cout << "You have died to Kevin again... come on man seriously?";
                newscreen();
                BobM.Setloses(BobM.Getloses()+1);
                BobM.Sethealth(275);
                health=850; /// if you die to him we lower his health to make it easier and buff your damage a bit
                BobM.Setdamage(20);
                deathcounter++;
            }

        }

        cout << "Bob has done it, Bob has become the Greatest Martial Artist in the world! " << endl;
        artdisplay("Level8Art7.txt");
        cout << "wins: " << BobM.Getwins() << ", losses: " << BobM.Getloses() << "   and ";
        if(BobM.Getreputation()<=40)
        {
            cout << "a horrible reputation. " << endl;
        }
        else
        {
            cout << "a good reputation. " << endl;
        }
        if(deathcounter>0)
        {
            cout << endl << "You thought those deaths to Kevin wouldn't count didn't you... " << endl << "haha. we didn't count the ones we forced though. ";
            newscreen();
        }
        level=9;
    } /// adds championship trophy
    newWeapon = new item(5);
    newWeapon->Setname("Championship Belt");
    newWeapon->Setbaseattack(4);
    newWeapon->Setspecialattack(4);
    newWeapon->Setspecialattackname("Hit Person With Belt");
    newWeapon->Setbaseblock(4);
    newWeapon->Setid(5);
    itemlist.push_back(*newWeapon);

    if(level==9)
    {
        cout << "Welcome Home! " << endl;
        artdisplay("Level2Art.txt");
        newscreen();
        cout << "Wow, what a journey you've been on Bob. " << endl;
        cout << "You've got rid of all the aliens, Killed Godfree the ruler of aliens. " << endl;
        cout << "You beat Kevin, the greatest martial artist of all time and became the new one. " << endl;
        cout << "Not to mention all these cool items you've collected along the way. " << endl;
        itr=itemlist.begin();
        while(itr!=itemlist.end())
        {
            itr->Display();
            itr++;
        }
        cout << endl << "... and all the money ";
        if(wallet==50) /// if a user simply jumped into this level and doesnt have a balance from earlier slots.
        {
            wallet=102302;
        }
        cout <<  "$"<<wallet;
        newscreen();
        cout << "Bob: Lets go home to our dog " <<endl;
        artdisplay("Level8Art7.txt");
        newscreen();
        artdisplay("Level2Art.txt");
        newscreen();
        level = 10;
    }
    ///final level, essentially its own level but it allows this game to basically have a story mode, then this mode at the end.



    if(level==10)
    {
        cout << "Thank you for playing ILoveMyDog, coded and everything else by " << endl;
        cout << "Cody Rabie";
        newscreen();
        level=0;

    }


    return 0;

}










