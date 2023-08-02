#include <iostream>
#include <iomanip>

using namespace std;

void winLoss (int&, int&); // procedure (void function) prototype that uses two pass by reference variables with "&"
float percent(int, int);   // same as exercise 1; float function that is passed two int variables and
                           // returns a value to the main function

int main()
{
    int wins; // define wins and losses (initially garbage data untill passed by reference to procedure)
    int losses;
    winLoss(wins, losses); //call to void function w/ parameters

    float percentWin = percent(wins, losses); // call to value-returning function that will return percentWin value
    cout << fixed << setprecision(2);
    cout << "The percentage of wins is " << percentWin * 100 << "%";

    return 0;
}

void winLoss(int& win, int& loss) // heading for void function with variables passed by reference. NO return statement.
{
    cout << "Please input the number of wins: ";
    cin >> win;
    cout << endl;

    cout << "Please input the number of losses: ";
    cin >> loss;
    cout << endl;
}

float percent(int w, int l) // same as exercise 1; calculates total and returns value of win/total for percentWin value
{
    int total = w + l;
    return float(w) / total;
}
