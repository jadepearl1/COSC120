// This program finds the average time spent programming by a student
// each day over a three day period.
// Jade Pearl

#include <iostream>
using namespace std;

int main()
{
    int numStudents;
    float proHours, proTotal, proAverage;
    float bioHours, bioTotal, bioAverage;
    int student,day = 0;     // these are the counters for the loops
    int numDay;
    cout << "This program will find the average number of hours a day"
         << " that a student spent programming and studying biology over a long weekend\n\n";
    cout << "How many students are there ?" << endl << endl;
    cin >> numStudents;

    cout << "How many days were in the long weekend?" << endl;
    cin >> numDay;

    for(student = 1; student <= numStudents; student++)
    {
        proTotal = 0;
        for(day = 1; day <= numDay; day++)
        {
            cout << "Please enter the number of programming hours worked by student "
                    << student <<" on day " << day << "." << endl;
            cin >> proHours;
            proTotal = proTotal + proHours;
        }

        bioTotal = 0;
        for(day = 1; day <= numDay; day++)
        {
            cout << "Please enter the number of biology hours studied by student "
                    << student <<" on day " << day << "." << endl;
            cin >> bioHours;
            bioTotal = bioTotal + bioHours;
        }

        proAverage = proTotal / numDay;
        cout << endl;
        cout << "The average number of hours per day spent programming by "
        << "student " << student << " is " << proAverage
        << endl << endl << endl;

        bioAverage = bioTotal / numDay;
        cout << endl;
        cout << "The average number of hours per day spent studying biology by "
        << "student " << student << " is " << bioAverage
        << endl << endl << endl;
    }
    return 0;
}
//Exercise 1: Had the inner loop iterate n times by making constant MAXDAY
//into a variable of no initialized value, numDay; replacing all uses of MAXDAY with
//int numDay; string prompts user to enter number of days in the long weekend

//Exercise 2: Created another for loop within the main loop for calculating average
//hours spent on studying biology. Changed numHours, total, and average to proHours,
//proTotal, and proAverage to represent hours spent on programming. Created similar variables
//to represent hours spent on biology studies and applied the variables to the rest of the code
//made the second nested for loop by copying and pasting the first nested loop for calculating
//programming hours and modifying the code to fit the criteria for biology using the variables made
//for bio hours. Initializing bioTotal and proTotal within the main for loop to store values for
//calculation within the nested for loops.
