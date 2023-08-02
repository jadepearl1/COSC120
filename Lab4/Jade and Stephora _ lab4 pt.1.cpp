// Lab 4: Jade and Stephora

#include <iostream>
#include <iomanip>

using namespace std;

int wins(); // parameterless value returning function prototypes
int losses();
float percent(int, int); // float function with two int parameters for pass by value


int main()
{
    int win = wins(); // function calls assigning values to the funcion that returns it
    int loss = losses();
    float percentWin = percent(win, loss); // call to function that computes and returns value of percentWin
    cout << fixed << setprecision(2);
    cout << "The percentage of wins is " << percentWin * 100 << "%";

    return 0;
}

int wins () // function that defines and returns win value
{
    int win;
    cout << "Please input the number of wins: ";
    cin >> win;
    cout << endl;
    return win;
}

int losses () // function that defines and returns loss value
{
    int loss;
    cout << "Please input the number of losses: ";
    cin >> loss;
    cout << endl;
    return loss;
}

float percent(int w, int l) // function that is passed wins and losses and calculates total
{                           // returns value of wins/total to percentWin in main function
    int total = w + l;
    return float(w) / total;
}
