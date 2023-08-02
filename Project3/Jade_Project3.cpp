//Jade Pearl
//Project 3
//COSC 120-001
//date started: 3/28/2022
//date modified: 4/13/2022 at 11:30am

//This program runs three different versions of the 2 player dice game, 27 which teaches about the concept of division with
//remainders. With each roll, you divide by the amount of coins in the pool and you get the remainder of what couldn't be divided.
//You continue this process until there is no coins left. Whomever has the biggest pocket wins at the end.

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>


using namespace std;

void optOne();//procedure that is used when the user selects option one
void optTwo();//procedure used when the user selects option 2
void optThree();//procedure used when the user selects option 3
int Roll(int); //value returning function that returns the dice roll
int Pockets (int, int); //value returning function that returns the pocket sizes of the user and CPU
int Pile (int, int); //value returning function that takes calculates how many coins are left in the pile at the end of each roll
float UserPercent (int, int);//calculates and returns the percentage of games won by the user
float CpuPercent (int, int);//calculates and returns the percentage of games won by the computer

int main()
{   //giving the user a menu of options and prompting them to choose from one which will then go to the procedure matching their choice
    cout << "Hello! Welcome to the game of 27! There are three different versions in this "
         << "program. "<< endl << endl;
    cout << "The first allows the user to play at least one game against the computer "
         << "and keeps score of how many wins and losses each player has and also keeps track of "
         << "the pocket of each player and how many coins are left." << endl << endl;
    cout << "The second is the same as the first option, except it also outputs a table that keeps "
         << "track of how many times each game has numbers between 1 and 27 serving as the starting number "
         << "of coins (also called 'hit count')." << endl << endl;
    cout << "The third simulates games where the computer does all rolls for as many games as the "
         << "user wishes to simulate and gives the percentage of wins of the user and computer as "
         << "well as how many games were played." << endl << endl;
    cout << "Please enter a 1, 2, or 3 for which version you will like to play." << endl;

    string sim; //variable for the option chosen by the user. sim is the name in this case because it is an option between three simulations of the game 27
    cin >> sim;
    cout << endl << endl;
    while ((sim != "1") && (sim != "2") && (sim != "3")) // data validation for menu selection
    {
        cout << "Invalid choice. Please enter a 1, 2, or 3" << endl;
        cin >> sim;
        cout << endl << endl;
    }

    unsigned seed = time(0); //causes the results to change every time for a truly random dice roll each round/game
    srand(seed); //These two lines will be used for all three scenarios

    if (sim == "1") //if statements leading to the functions from the user choice
        optOne();
    if (sim == "2")
        optTwo();
    if (sim == "3")
        optThree();
}



//**********************************************************************
//                              optOne
//
// task: carrying out option one for the 27 game and outputting the
//       results to the screen
// data in: none
// data out: outputs the prompts for the user and the results of each
//           round and game to the screen
//
//**********************************************************************
void optOne()
{
    char rematch = 'Y'; //initialized at Y so that the game runs at least once
    int gold; //coins in the pile

    char chooseRoll; //character input if the user decides to roll
    int diceRoll; //roll of the dice
    int die = 0; //represents the die. Initialized to zero before passing to function and reinitializing to clear
                 //warnings about no initialization

    int pocket; //pocket found for user OR CPU PER roll
    int userPocket; //pocket of the user
    int cpuPocket; //pocket of the CPU

    int userWins = 0; //number of games won by user and computer
    int cpuWins = 0;
    string winner; //states who wins the game
    int games = 0; //total # of games played
    float userPerc;//represents percent of games won by user
    float compPerc;//represents percent of games won by computer

    while ((rematch != 'n') && (rematch != 'N')) //When the user inputs an N or n, the game stops
    {
        gold = 27; //games ALWAYS start with 27 gold coins in the pile
        games++;
        userPocket = 0;
        cpuPocket = 0;
        while (gold > 0) //there must be gold coins left in the pile for the game to continue
        {
            cout << "If the user would like to roll now please input y." << endl;
            cin >> chooseRoll;
            while ((chooseRoll != 'y') && (chooseRoll != 'Y'))
            {
                cout << "Invalid character. Please input a y or Y to roll." << endl;
                cin >> chooseRoll;
            }
            //roll for the user and calculate their pocket
            diceRoll = Roll(die); //rolls die
            pocket = Pockets(diceRoll, gold); //calculates pocket
            userPocket += pocket; //adds the current pocket to the total pocket that will be displayed when the game is over
            gold = Pile(gold, pocket); //subtracts pocket from pile to find new amount of gold remaining in pile
            cout << "The user rolled a " << diceRoll << ". The user pocket is " << pocket << ". There are " << gold
                 << " coins remaining." << endl << endl;

            //roll for the computer and calculate their pocket. Above process is repeated for the CPU
            diceRoll = Roll(die);
            pocket = Pockets(diceRoll, gold);
            cpuPocket += pocket;
            gold = Pile(gold, pocket);
            cout << "The computer rolled a " << diceRoll << ". The computer pocket is " << pocket << ". There are " << gold
                 << " coins remaining." << endl << endl;
        }
        if (userPocket > cpuPocket) //if user wins a game
        {
            winner = "user";
            userWins ++;
        }
        else //for computer winning a game
        {
            winner = "computer";
            cpuWins ++;
        }

        //results listed and asks user if they wish to play another game
        cout << "The game is over. The user pocketed " << userPocket << " coins and the computer pocketed " << cpuPocket
             << " coins. The " << winner << " wins! Would you like to play another game? (Y or N)" << endl;
        cin >> rematch;
        while ((rematch != 'y') && (rematch != 'Y') && (rematch !='n') && (rematch != 'N'))
        {
            cout << "Invalid character. Please input a Y or N." << endl;
            cin >> rematch;
        }
        cout << endl << endl;
    }

    cout << fixed << showpoint << setprecision(2);
    userPerc = UserPercent(userWins, games); //finding percentage of games by calling to the function where percentage of wins are found
    compPerc = CpuPercent(cpuWins, games);

    cout << "There was " << games << " game(s) played. The user won " << userWins << " game(s) and the computer won "
         << cpuWins << " game(s). The user won " << userPerc << "% of the games and the computer won " << compPerc
         << "% of the games." << endl << endl;

}



//**********************************************************************
//                              optTwo
//
// task: carries out option two. Instead of outputting the wins and
//       percentages, outputs a table of the hit count for each
//       time a number of coins between 1-27 starts a round other
//       than the first round where it always starts with 27 coins
// data in: none
// data out: outputting prompts for the user, game progress and hit
//           count table to the screen
//
//**********************************************************************
void optTwo() //a lot of variables from option one are reused in option two
{
    int hits[27]; //array size of 27 whose indexes represent the amount of coins left in the pile
    int gold = 27; //game always starts with 27 gold

    int diceRoll, pocket;
    int die = 0; //represents the die. Like earlier, will be changed in the function for rolls
    char chooseRoll;
    int userPocket = 0;
    int cpuPocket = 0;


    for (int i = 0; i < 27; i++)
    {
        hits[i] = 0; //setting the first index to 1 because the game always starts
                     //with 27 coins at least once
    }

    hits[gold - 1] = 1;

    //repeat process from option one; percentages of wins and # of wins are not calculated for this option
    while (gold > 0)
    {
        cout << "If the user would like to roll now please input y." << endl;
        cin >> chooseRoll;
        while (chooseRoll != 'Y' && chooseRoll != 'y')
        {
            cout << "Invalid character. Please input a y or Y to roll." << endl;
            cin >> chooseRoll;
        }

        //user rolls as seen in option one
        diceRoll = Roll(die);
        pocket = Pockets(diceRoll, gold);
        userPocket += pocket;
        gold = Pile(gold, pocket);
        cout << "The user rolled a " << diceRoll << ". The user pocket is " << pocket << ". There are " << gold
             << " coins remaining." << endl << endl;
        hits[gold - 1]++; //adds to the number of hits in that index after result of roll is calculated

        //repeat for computer as seen in opt one
        diceRoll = Roll(die);
        pocket = Pockets(diceRoll, gold);
        cpuPocket += pocket;
        gold = Pile(gold, pocket);
        cout << "The computer rolled a " << diceRoll << ". The computer pocket is " << pocket << ". There are " << gold
             << " coins remaining." << endl << endl;
        hits[gold - 1]++; //incremented hits like what was done with user
    }

    cout << "The game is over. See the hit count table below." << endl << endl;

    cout << left << setw(25) << "Number of Coins" << setw(30) << "Hit count" << endl << endl; //formatting and printing the table
    for (int coins = 26; coins > 0; coins--)
    {
        if (hits[coins] != 0) //numbers that are not hit in the game at least once cannot show up on the table
        {
            cout << left << setw(25) << (coins + 1) << setw(30) << hits[coins] << endl;
        }
    }
}




//**********************************************************************
//                             optThree
//
// task: carries out option three; simulates multiple games and
//       sends the results to an output file. Combines the results
//       from option one and two: calculating and showing the
//       number of games played, # of games won by each player,
//       percent of wins from each player, and the hit count table
// data in: none
// data out: output file holds all the information stated in the task
//
//**********************************************************************
void optThree() //option three implements all variables from options one and two and calculates & outputs the same data from the first two
{               //options but instead, sends all of it into an output file. Review options 1 & 2 for variable objectives/purposes
    ofstream outfile; //create an output file in the code

    int hits[27];
    int gold = 27;
    int diceRoll; //diceRoll and die appear as normal for the rolls in the game
    int die = 0;

    int pocket; //pockets defined the same as in options one and two
    int userPocket;
    int cpuPocket;

    int userWins = 0; //wins are initialized at zero as done before
    int cpuWins = 0;
    string winner;
    int games; //represents # of games played. Not initialized to 0 since the user will be providing the # of games to be played
    float userPerc;
    float compPerc;

    outfile.open("27_Game");

    for (int i = 0; i < 27; i++) //initializing all elements of the array to zero in order for increment to work when specific indexes are hit
    {
        hits[i] = 0;
    }

    hits[gold - 1] = 1;

    cout << "How many games would you like to simulate? Enter a positive non-zero number:" << endl; //prompt user input and validate their input
    cin >> games;
    while (games <= 0)
    {
        cout << "Invalid number of games! Please enter a positive non-zero integer:" << endl;
        cin >> games;
    }

    for (int total = 1; total <= games; total++) //for loop representing each game played. loops in option one will be in this loop
    {
        while (gold > 0) //there must be gold coins left in the pile for the game to continue
        {
            diceRoll = Roll(die);
            pocket = Pockets(diceRoll, gold); //calculates pocket
            userPocket += pocket; //adds the current pocket to the total pocket that will be displayed when the game is over
            gold = Pile(gold, pocket); //subtracts pocket from pile to find new amount of gold remaining in pile
            hits[gold - 1]++;

            //roll for the computer and calculate their pocket. Above process is repeated for the CPU
            diceRoll = Roll(die);
            pocket = Pockets(diceRoll, gold);
            cpuPocket += pocket;
            gold = Pile(gold, pocket);
            hits[gold - 1]++;
        }

        if (userPocket > cpuPocket)
        {
            winner = "user";
            userWins ++;
        }
        else
        {
            winner = "computer";
            cpuWins ++;
        }
        gold = 27; //after game ends, gold resets to 27 coins in the pile for next game
        userPocket = 0;
        cpuPocket = 0;
    }

    outfile << fixed << showpoint << setprecision(2); //calculating user percentage as done in option one
    userPerc = UserPercent(userWins, games);
    compPerc = CpuPercent(cpuWins, games);

    outfile << "There was " << games << " game(s) played. The user won " << userWins << " game(s) and the computer won "
            << cpuWins << " game(s). The user won " << userPerc << "% of the games and the computer won " << compPerc
            << "% of the games." << endl << endl;

    outfile << "See the hit count table below." << endl << endl;
    outfile << left << setw(25) << "Number of Coins" << setw(30) << "Hit count" << endl << endl;

    for (int coins = 26; coins > 0; coins--) //calculating and displaying hits as done in option 2
    {
        if (hits[coins] != 0)
        {
            outfile << left << setw(25) << (coins + 1) << setw(30) << hits[coins] << endl;
        }
    }
    //notify the user the existence of the file and its name and prompt them to look for their results in the file
    cout << "Look for the results in the output file labeled '27_Game'." << endl << endl;
    outfile.close();
}



//**********************************************************************
//                           Roll
//
// task: rolls the dice by generating a random number between 1 and
//       6 before passing it back to the main function
// data in: garbage data from the die variable from main
// data out: the newly initialized dice roll in the die variable
//
//**********************************************************************
int Roll(int die)
{
    die = rand() % 6 + 1;
    return die;
}



//**********************************************************************
//                         Pockets
//
// task: calculates the pockets of the user and the CPU after each
//       roll
// data in: the dice roll and the amount of gold coins currently in the
//          pile
// data out: gold coins claimed in the pocket of the user or CPU
//
//**********************************************************************
int Pockets(int diceRoll, int gold)
{
    return (gold % diceRoll); //calculates pocket by taking the remainder of gold divided by diceRoll (modulus)
}



//**********************************************************************
//                           Pile
//
// task: calculates the amount of gold left in the pile
// data in: number of gold coins and the pocket that was just taken from
//          the pile if any
// data out: amount of gold coins remaining
//
//**********************************************************************
int Pile(int gold, int pocket)
{
    return (gold - pocket); //returns pile minus pocket
}



//**********************************************************************
//                          UserPercent
//
// task: calculate percentage of wins made by the user
// data in: user wins and total # of games played
// data out: percentage of wins made by the user
//
//**********************************************************************
float UserPercent(int uwins, int games)
{
    return (float(uwins)/float(games)) * 100;
}



//**********************************************************************
//                          CpuPercent
//
// task: calculate percentage of wins made by the computer
// data in: computer wins and total # of games played
// data out: percentage of wins made by the computer
//
//**********************************************************************
float CpuPercent(int cwins, int games)
{
    return (float(cwins)/float(games)) * 100;
}
