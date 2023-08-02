#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
    int time, height;
    float fallDistance;
    const float gravity = (9.8 / pow(1, 2));

    cout << "Please input the time of fall in seconds: " << endl;
    cin >> time;
    cout << endl;

    cout << "Please input the height of the bridge in meters: " << endl;
    cin >> height;

    cout << endl
         << "Time falling (seconds) \t Distance Fallen (meters)" << endl
         << "**********************************************" << endl;

    cout << fixed << showpoint << setprecision(2);
    for (int i = 0; i <= time; i++)
    {
        fallDistance = (0.5 * gravity * pow(i, 2));
        cout << i << "\t\t\t " << fallDistance << endl;
    }

    cout << endl;
    if (fallDistance > height)
    {
        cout << "Warning-Bad Data: The distance fallen exceeds the height of the bridge." << endl;
    }

    return 0;
}
