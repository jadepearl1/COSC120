#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>

using namespace std;

// Jade Pearl
// Project 2
// COSC 120-001
// date created: 3/10
// date last modified: 3/16
// purpose of this program is to prompt the user to pick between two math calculators: 1. Binary Converter or 2. Prime Test
// After validating user input for their choice, the program will run one of the chosen options.
// Binary Converter will read in binary numbers from an input file and convert all valid binary numbers into base 10/decimal numbers.
// The program will then take the sum and average of all decimal numbers converted from a valid binary number and output everything
// to the screen.
// Prime test will take a list of integer numbers from an input file and calculate which ones are prime and output them to the
// screen. It will also output the total count of how many prime numbers were found in the list


void decimalSum(int, int&); // prototype that is used to take the sum of all decimal numbers derived from valid binary numbers
void decimalAvg(int, int, float&); // prototype for a procedure that takes the average of all decimal numbers derived from valid binary numbers
void testPrime (int, bool&, int&); // prototype for procedure that is used to test if a number is prime
void numPrime (int&); // prototype for procedure that is used to count the number of prime numbers in the list

int main()
{
    int option; // int variable that stores the choice of the user from the math calculator menu
    cout << "Welcome to the Math Calculator. Please enter 1 to perform the Binary Converter or 2 to perform the Prime Test:" << endl;
    // statement that prompts the user to pick between the two math calculators
    cin >> option; // user inputs the desired option
    cout << endl; //new line for neater formatting purposes

    while ((option != 1) && (option != 2)) // while loop used to validate user input if they do not enter a valid option until they
    {                                      //enter a 1 or 2 from the menu
        cout << "Invalid input. Please input 1 for Binary Converter or 2 for Prime Test." << endl; // validation prompt
        cin >> option; //user must input option again
    }

    ifstream infile; // defining data input file that will later be opened and used in either scenario


    if (option == 1) // if statement that begins the run for the Binary Converter option
    {
        cout << fixed << showpoint << setprecision(2); // set precision to make the decimal average print until after two decimal places
        int numDigit, binary; // defining variables that represent the numbers to be read in from the input file: One for reading the digit
                              // representing how many digits are behind it (the binary digits) and the other variable represents the binary
                              // digits themselves

        infile.open("binary.txt"); // input file is opened for reading
        if(!infile) // statement that shows when the input file cannot be found, opened, or read
        {
            cout << "Error finding or opening file." << endl;
            return 1; // return 1 statement ends the program if there is no input file found or read
        }

        int sum = 0; //initializing a variable for finding the sum of all decimal #'s derived from valid binary #'s.
                     //Will be sent by reference to the decimalSum procedure defined earlier
        int decimalCount = 0; //initialize a variable that counts the number of decimal #'s derived from valid binary #'s.
                              // will be used to calculate the decimal average in the decimalAvg procedure
        float average; //initialize a float variable to be used for finding the average of the decimal numbers

        //add a variable that helps validate data provided
        int error = 0;

        infile >> numDigit; // prime the binary.txt read for input analysis by the program
        while (infile) //make a while loop for reading and processing data from the input file
        {
            cout << "The decimal value of the binary number ";
            int decimal = 0; //initializing a variable decimal that is used to output the binary numbers in decimal form
            for (int i = 1; i <= numDigit; i++) //make a for loop that reads in binary integers up to the value of the non-binary digit used
            {                                   //to represent how many binary digits are behind it on the same line
                infile >> binary; //start reading the binary digits from the input file
                if ((binary != 1) && (binary != 0)) //if else statement that includes data validation and skips to the next line of input if
                {                                   //the binary digit is found invalid
                    cout << binary << " is Invalid Binary number." << endl;
                    error = 1; //logic that takes note of an error in binary digits
                }

                else if (error == 0) //write the logic that will be used for valid binary numbers
                {
                    cout << binary;
                    decimal += binary * (pow(2, (numDigit - i))); //calculate decimal value of binary number using the digit times 2^current
                                                                  //power
                }
            }

            if (error == 0) //write a statement that outputs out the decimal value for each valid binary number and calls to the sum function
            {
                cout << " is " << decimal << "." << endl;
                decimalSum(decimal, sum);
                decimalCount++; //increase the count of how many decimal numbers have been made from valid binary numbers
            }
            error = 0; //reassign the value of the validation variable to 0 for the next line of data so that it can continue reading if there
                       //was an invalid binary number read
            infile >> numDigit; //begin reading the next line of data to continue the loop while there is still data in the file
            cout << endl;
        }
        cout << "The Sum of the decimal numbers is " << sum << "." << endl << endl; //output the sum of decimal #'s

        decimalAvg(decimalCount, sum, average); //call to the average function and then calculate + output the average fixed to 2 decimal places
        cout << "The average of the decimal numbers is " << average << "." << endl;
    }
    //end of code for Binary Converter



    if(option == 2) //if statement that begins the run for the Prime Test option
    {
        //String that shows that the program is about to list off the prime numbers read from the input file
        cout << "The primes in the list are:" << endl << endl;
        //introduce three integer variables, one to represent all numbers to be read from the file and one to represent which numbers
        //analyzed are prime. Make one to represent the number of prime numbers found in the input file list as well.
        int num; // variable that will be read from the input file
        bool prime; //boolean variable that is true when a number is prime and false if it is composite
        int primeCount = 0; //initialize a count variable that gets incremented when a prime number is found in the list

        infile.open("numbers.txt"); //input file opened for reading
        if(!infile) // when file cannot be found or opened
        {
            cout << "Error opening file." << endl; // error telling user file cannot be opened
            return 1; //end program if there is an error with the file
        }

        infile >> num; //primes the read and reads in first number on the list
        while(infile)
        {
            prime = true; //assume prime is true for every number. will be proved false in the test procedure if it is found to be composite
                          //this is just to acknowledge that there are numbers in the list and the program continues to run if prime starts
                          //out equal to true
            testPrime(num, prime, primeCount); //call to the testPrime procedure
            infile >> num; //read in the next number of the file and repeat the while loop until no data is left
        }
        infile.close(); //close the input file and then output how many prime numbers were found in the list
        cout << endl;
        cout << "There are " << primeCount << " primes in the list.";

    }
    return 0;
}



//**********************************************************************
//                          decimalSum
//  task: from the binary converter: takes the initialized sum value
//        from the main function and adds all decimal values from valid
//        binary numbers, accumulating their sum
//  data in: decimal (pass by value), sum (pass by reference)
//  data out: sum (passed back by reference)
//
//**********************************************************************
void decimalSum(int decimal, int& sum) //procedure heading and body for decimalSum
{
    sum += decimal; //add decimal values to the sum as they are processed from valid binary numbers
}



//**********************************************************************
//                          decimalAvg
//  task: from the binary converter: divides the sum from the main
//        function and divides it by the number of decimal numbers taken
//        from valid binary numbers to get the average.
//  data in: decimalCount (pass by value), sum (pass by value)
//           average (pass by reference)
//  data out: average (passed back by reference)
//
//**********************************************************************
void decimalAvg(int decimalCount, int sum, float& average) //
{
    average = float(sum) / decimalCount;
}



//**********************************************************************
//                    testPrime
//  task: taking numbers from input list and determining if it is prime
//  data in: num, prime (passed by reference), primeCount (passed by
//                                                         reference)
//  data output: num (passed back by reference)
//
//**********************************************************************
void testPrime(int num, bool& prime, int& primeCount)
{
    //create if else if statement that reads in a number from the list, it is made to disproves 1s, 0s, and negative numbers as prime and
    //automatically counts 2 as a prime number. The final else statement is made to analyze even further if other numbers are prime or not.
    if((num == 1) || (num <= 0))
    {
        prime = false;
    }

    else if (num == 2)
    {
        prime = true;
    }

    else
    {
        //create for loop that tests for a number being prime if it can be divided by 2 up to itself minus 1 with NO REMAINDER. Ex. if the
        //program reads the number 19, it will test if 2 up to 18 can divide 19. If none of these work, the number in question is a prime number
        for (int i = 2; i <= (num - 1); i++)
        {
            if (num %i == 0)
            {
                prime = false;
            }
        }
    }

    if (prime == true) //if a number is found as prime, print the number then call to the numPrime function to increase the count of how many
    {                  //prime numbers were found in the list
        cout << num << endl;
        numPrime(primeCount);
    }
}


//***********************************************************************
//                          numPrime
//  task: counting the number of prime numbers in the list and increments
//        the count of prime numbers every time a prime number is
//        calculated. The final value of primeCount is passed back to the
//        main function.
//  data in: primeCount (passed by reference)
//  data out: primeCount (passed back by reference)
//
//***********************************************************************
void numPrime(int& primeCount)
{
    primeCount++; //increment primeCount
}
