#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int total = 1;

    int favorite;
    cout << "Menu:" << endl;
    cout << "1. Coffee" << endl;
    cout << "2. Tea" << endl;
    cout << "3. Coke" << endl;
    cout << "4. Orange Juice" << endl;
    int coffee = 0, tea = 0, coke = 0, oj = 0;

    do
    {
        cout << "Please input the favorite beverage of person #" << total
            << ": Choose 1, 2, 3, or 4 from the menu or -1 to exit the program" << endl;
        cin >> favorite;
        switch (favorite)
        {
            case 1:
                coffee++;
                total++;;
                break;
            case 2:
                tea++;
                total++;
                break;
            case 3:
                coke++;
                total++;
                break;
            case 4:
                oj++;
                total++;
                break;
        }
    }
    while (favorite != -1);

    cout << "The total number of people surveyed is " << total - 1 << " The results are as follows: " << endl;
    cout << "Beverage Number of Votes" << endl;
    cout << "Coffee: " << coffee << endl;
    cout << "Tea: " << tea << endl;
    cout << "Coke: " << coke << endl;
    cout << "Orange juice: " << oj;

    return 0;
}
