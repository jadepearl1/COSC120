#include <iostream>
#include <iomanip>

using namespace std;

//this program reads and stores information from a local airport for each
//month including number of planes landed, departed, greatest number of
//planes landed on a given day in the month, and least number of planes
//landed in a given day in the month

struct AirportYear
{
   int landed;
   int departed;
   int maxLandDay;
   int minLandDay;
};


int main()
{
    AirportYear monthData[12]; //reads and stores data for each month

    for (int i = 0; i < 12; i++)
    {
        cout << "Enter the total # of planes landed in month " << i+1
             << ": " << endl;
        cin >> monthData[i].landed;

        cout << "Enter the total # of planes departed in month " << i+1
             << ": " << endl;
        cin >> monthData[i].departed;

        cout << "Enter the greatest # of planes landed in a given day in month "
             << i+1 << ": " << endl;
        cin >> monthData[i].maxLandDay;

        cout << "Enter the least # of planes landed in a given day in month "
             << i+1 << ": " << endl;
        cin >> monthData[i].minLandDay;
    }

    float totalLand = 0;
    float totalDep = 0;
    int maxLandMonth = 0;
    int minLandMonth = 0;

    for (int i = 0; i < 12; i++)
    {
        totalLand += monthData[i].landed;
        totalDep += monthData[i].departed;

        if ((i != 0) && (monthData[i].maxLandDay > monthData[maxLandMonth].maxLandDay))
            maxLandMonth = i;

        if ((i != 0) && (monthData[i].minLandDay < monthData[minLandMonth].minLandDay))
            minLandMonth = i;
    }

    cout << fixed << showpoint << setprecision(2);
    cout << "The average # of planes landed per month is: "
         << (totalLand / 12) << endl << endl;
    cout << "The average # of planes departed per month is: "
         << (totalDep / 12) << endl << endl;
    cout << "The total # of planes landed this year is: "
         << totalLand << endl << endl;
    cout << "The total # of planes departed this year is: "
         << totalDep << endl << endl;
    cout << "The greatest # of planes landed in one day is: "
         << monthData[maxLandMonth].maxLandDay << " in month " << maxLandMonth + 1
         << endl << endl;
    cout << "The least # of planes landed in one day is: "
         << monthData[minLandMonth].minLandDay << " in month " << minLandMonth + 1 << endl;

    return 0;
}
