#include <iostream>
#include <iomanip>
using namespace std;


// This program will input American money and convert it to foreign currency

// Jade and Jordan
// date modified: 3/3/2022
// purpose of program is to convert USD to foreign currency

// Prototypes of the functions
void  convertMulti(float dollars, float& euros, float& pesos);
void  convertMulti(float dollars, float& euros, float& pesos, float& yen);
float convertToYen(float dollars);
float convertToEuros(float dollars);
float convertToPesos(float dollars);


int main ()


{
	float dollars;
	float euros;
	float pesos;
	float yen;

	cout << fixed << showpoint << setprecision(2);

	cout << "Please input the amount of American Dollars you want converted "
         << "to euros and pesos" << endl;
	cin >> dollars;

	convertMulti(dollars, euros, pesos);
	cout << "$" << dollars << " is converted to " << euros << " euros and " << pesos << " pesos." << endl << endl;

	cout << "Please input the amount of American Dollars you want converted "
	     << "to euros, pesos and yen" << endl;
	cin >> dollars;

    convertMulti(dollars, euros, pesos, yen);
    cout << "$" << dollars << " is converted to " << euros << " euros and " << pesos << " pesos and " << yen << " yen." << endl << endl;


	cout << "Please input the amount of American Dollars you want converted "
	     << "to yen" <<endl;
	cin >> dollars;

    yen = convertToYen(dollars);
    cout << "$" << dollars << " is converted to " << yen << " yen" << endl << endl;

	cout << "Please input the amount of American Dollars you want converted"
	     << " to euros" << endl;
	cin  >> dollars;

	euros = convertToEuros(dollars);
    cout << "$" << dollars << " is converted to " << euros << " euros" << endl << endl;


	cout << "Please input the amount of American Dollars you want converted"
	     << " to pesos " << endl;
	cin >> dollars;

    pesos = convertToPesos(dollars);
    cout << "$" << dollars << " is converted to " << pesos << " pesos" << endl << endl;


	return 0;
}


// All of the functions are stubs that just serve to test the functions
// Replace with code that will cause the functions to execute properly



//  ************************************************************************
//                           convertMult
//
//   task:     This function takes a dollar value and converts it to euros
//             and pesos
//   data in:  dollars
//   data out: euros and pesos
//
//   ***********************************************************************


void  convertMulti(float dollars, float& euros, float& pesos)

{
    euros = (dollars * 0.701);
    pesos = (dollars * 12.66);
}


//  ************************************************************************
//                           convertMult
//
//   task:     This function takes a dollar value and converts it to euros
//             pesos and yen
//   data in:  dollars
//   data out: euros pesos yen
//
//   ***********************************************************************

void  convertMulti(float dollars, float& euros, float& pesos, float& yen)

{
    euros = (dollars * 0.701);
    pesos = (dollars * 12.66);
    yen = (dollars * 91.25);
}


//  ****************************************************************************
//                           convertToYen
//
//   task:          This function takes a dollar value and converts it to yen
//   data in:       dollars
//   data returned: yen
//
//   ***************************************************************************

float convertToYen(float dollars)

{
	return (dollars * 91.25);
}

//  ****************************************************************************
//                           convertToEuros
//
//   task:          This function takes a dollar value and converts it to euros
//   data in:       dollars
//   data returned: euros
//
//   ***************************************************************************


float convertToEuros(float dollars)
{
	return (dollars * 0.701);
}

//  *****************************************************************************
//                           convertToPesos
//
//   task:          This function takes a dollar value and converts it to pesos
//   data in:       dollars
//   data returned: pesos
//
//   ****************************************************************************
float convertToPesos(float dollars)

{
    return (dollars * 12.66);
}


