#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

const double BaseFee = 0.05; // base fee of site
const char ROCK = 'r';
const char PAPER = 'p';
const char SCISSORS = 's';

const char HEADS = 'h';
const char TAILS = 't';

struct userData
{
    string username;
    string fullLegalName;
    double depositAm; // before fee
    double playingAm; // available currency to play with after fees

} data;
double PlayerBalance ()
{
    double PlayerBal;
    cout<<"Enter the desired deposit amount: $";
    cin>>PlayerBal;
    return PlayerBal;
}



char chooseGame()
{
    char choice;
    cout << endl;
    cout << "Which game would you like to play today? " << endl;
    cout << "Enter A for Rock, Paper, Scissors." << endl;
    cout << "Enter B for Coin Flip. " << endl;
    cin >> choice;
    if(choice!='A' && choice!='B')
    {
        cout << "Please enter a valid value. If you enter an invalid value again the program will terminate." << endl;
        cout << "Enter A for Rock, Paper, Scissors." << endl;
        cout << "Enter B for Coin Flip. " << endl;
        cin >> choice;
    }
    return choice;
}





// Coin flip game functions
int coin() //cChoice Coin Flip
{
    int flip;
    flip = rand()% 2+1;
    return flip;
}

int uChoiceCoin()
{
    char coinChoice;
    int userCoinChoice;
    cout << "Would you like to select heads or tails?"<< endl;
    cout << "Enter 'h' for Heads, and enter 't' for tails: ";
    cin >> coinChoice;
    while (coinChoice!='h'&& coinChoice!='t')
    {
        cout << "Please enter a valid character " << endl;
        cout << "Would you like to select heads or tails?";
        cout << endl;
        cout << "Enter 'h' for Heads, and enter 't' for tails: ";
        cin >> coinChoice;
        cout << endl;
    }
    if (coinChoice == 'h')
    {
        userCoinChoice = 1;
    }
    if (coinChoice == 't')
    {
        userCoinChoice = 2;
    }
    return userCoinChoice;
}


//RockPaperScissorsGamesFucntions
char getComputerOption()
{
    srand(time(0));
    int num = rand() % 3+1;

    if (num==1) return 'r';
    if (num==2) return 'p';
    if (num==3) return 's';
}
char getUserOption()
{

    char userOption;
    cout << endl;
    cout << endl;
    cout << "Choose one of the following options" << endl;
    cout << "(r) for rock " << endl << "(p) for paper " << endl << "(s) for scissors" << endl;
    cin >> userOption;
    cout << endl;
    cout << endl;

    while (userOption!='r' && userOption!='p' && userOption!= 's')
    {
        cout << "Please only enter a valid option. " << endl;
        cout << "(r) for rock " << endl << "(p) for paper " << endl << "(s) for scissors" << endl;
        cin >> userOption;
    }
    return userOption;

}
void showSelectedOption(char option)
{
    if (option == 'r') cout << "Rock" << endl;
    if (option == 'p') cout << "Paper" << endl;
    if (option == 's') cout << "Scissors" << endl;
}
char chooseWinner(char uChoice, char cChoice)
{

    int w;
    if (uChoice == ROCK && cChoice == PAPER)
    {
        cout << "Computer Wins! Paper wraps Rock."<< endl << endl;
        w = 1;
        return w;
    }
    else if (uChoice == PAPER && cChoice == SCISSORS)
    {
        cout << "Computer Wins! Scissors cut Paper."<< endl << endl;
        w = 1;
        return w;

    }
    else if (uChoice == SCISSORS && cChoice == ROCK)
    {
        cout << "Computer Wins! Rock smashes Scissors."<< endl << endl;
        w = 1;
        return w;

    }
    else if (uChoice == ROCK && cChoice == SCISSORS)
    {
        cout << "You Win! Paper wraps Rock."<< endl << endl;
        w = 2;
        return w;

    }
    else if (uChoice == PAPER && cChoice == ROCK)
    {
        cout << "You Win! Paper wraps Rock."<< endl << endl;
        w = 2;
        return w;

    }
    else if (uChoice == SCISSORS && cChoice == PAPER)
    {
        cout << "You Win! Scissors cut Paper."<< endl << endl;
        w = 2;
        return w;
    }
    else
    {
        cout << "Tie." << endl << endl;
        w = 3;
        return w;
    }
}


int main()
{
    ofstream outfile;
    outfile.open("UserData.txt");

    cout<<"Welcome to Skilled Gambling Casino Prototype!" << endl;
    cout<< "Please enter your username: ";
    getline(cin, data.username);
    cout<< "Please enter your full legal name: ";
    getline(cin, data.fullLegalName);


    outfile << "Username: " << data.username << endl;
    outfile << "Full Legal Name: " << data.fullLegalName << endl << endl;


    double siteCut; // Currency from fees sent to the siteBankBalance
    double siteBankBalance = 500000; // SiteBankBalance of the funds for the site

    double wagerAmount; // amount wagered by player
    char gameChoice;

    data.depositAm = PlayerBalance(); // finds the deposit amount
    while(data.depositAm > 20000)
    {
        cout << "The max deposit amount of the website is $20000, please enter an amount under this." << endl;
        data.depositAm = PlayerBalance(); // finds the deposit amount
    }
    siteCut = data.depositAm*BaseFee; // calculates the sites cut
    data.playingAm = data.depositAm - siteCut; // calculates the players active bal

    siteBankBalance = siteBankBalance + siteCut; // sends the sites cut to the sitesBankBalance
    cout << "Your active playing balance after fees is: $" << data.playingAm << endl;

    gameChoice = chooseGame();




    switch(gameChoice)
    {
    case 'A':
        while (data.playingAm > 0 && siteBankBalance > 0)
        {
            cout << "How much would you like to wager on this match: $";
            cin >> wagerAmount;

            while (wagerAmount > data.playingAm)
            {
                cout << "Please enter an amount that you have deposited. " << endl;
                cout << "How much would you like to wager on this match: $";
                cin >> wagerAmount;
            }


            char uChoice;
            char cChoice;

            uChoice = getUserOption();
            cout << "Your choice is; " << endl;
            showSelectedOption(uChoice);

            cout << "Computer's choice is: " << endl;
            cChoice = getComputerOption();
            showSelectedOption(cChoice);

            int WinOrLose =chooseWinner(uChoice, cChoice);

            if (WinOrLose == 1)
            {
                data.playingAm = data.playingAm - wagerAmount;
                siteBankBalance = siteBankBalance + wagerAmount;
                cout << "Your new active playing balance is: $" << data.playingAm << endl;
            }
            if (WinOrLose ==2)
            {
                data.playingAm = data.playingAm + wagerAmount;
                siteBankBalance = siteBankBalance - (wagerAmount);
                cout << "Congrats! Your new active playing balance is: $" << data.playingAm << endl;
            }
            if (WinOrLose == 3)
            {
                cout << "Your active playing balance has not been affected and is still: $" << data.playingAm << endl;
            }


            outfile << "Wager amount: $" << wagerAmount << endl;
            outfile << "Playing balance: $" << data.playingAm << endl;
        }
    case 'B':
        while (data.playingAm > 0 && siteBankBalance > 0)
        {
            cout << "How much would you like to wager on this match: $";
            cin >> wagerAmount;

            while (wagerAmount > data.playingAm)
            {

                cout << "Please enter an amount that you have deposited. " << endl;
                cout << "How much would you like to wager on this match: $";
                cin >> wagerAmount;
            }
            int computerCoinFlip = coin();
            int userCoinFlip = uChoiceCoin();

            if(userCoinFlip ==1 && computerCoinFlip == 1)
            {
                data.playingAm = data.playingAm + wagerAmount;
                siteBankBalance = siteBankBalance - (wagerAmount);
                cout << "You selected heads and the coin landed on heads! Congrats, your new active balance is: $" << data.playingAm << endl;
            }
            if (userCoinFlip ==2 && computerCoinFlip==2)
            {
                data.playingAm = data.playingAm + wagerAmount;
                siteBankBalance = siteBankBalance - (wagerAmount);
                cout << "You selected tails and the coin landed on tails! Congrats, your new active balance is: $" << data.playingAm << endl;
            }
            if (userCoinFlip == 1 && computerCoinFlip == 2)
            {
                data.playingAm = data.playingAm - wagerAmount;
                siteBankBalance = siteBankBalance + wagerAmount;
                cout << "You selected heads and the coin landed on tails. Sorry, your new active balance is: $" << data.playingAm << endl;
            }
            if (userCoinFlip == 2 && computerCoinFlip == 1)
            {
                data.playingAm
                    = data.playingAm - wagerAmount;
                siteBankBalance = siteBankBalance + wagerAmount;
                cout << "You selected tails and the coin landed on heads. Sorry, your new active balance is: $" << data.playingAm << endl;
            }


            outfile << "Wager amount: $" << wagerAmount << endl;
            outfile << "Playing balance: $" << data.playingAm << endl;

        }





    }
}
