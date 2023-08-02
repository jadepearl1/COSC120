#include <iostream>
#include <iomanip>
#include <istream>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <cmath>

using namespace std;

//Jade Pearl
//COSC 120-001
//Project 4: Hurricane statistics
//date created: 4/20/2022
//date modified: 4/27/2022

//The purpose of this program is to simulate a log of hurricane statistics
//that would typically be done by a weather bureau. The program will read in
//two input files (tropical.txt to hold a list of ID #s for tropical storms
//and storms.txt that stores a list of hurricanes with their names, ID#,
//lifetime in days, the four digit year of the hurricane's life, 5 recordings
//of wind speeds, two recordings of rainfall measurements, and # of tornadoes
//spawned from the storm).

//Outputs will go into an output file for the user
//to access after the program finishes running.

//The program's job once it reads in the storms.txt file is to echo print that
//information to the output file with appropriate spacing and a storm level of
//the hurricane (based off average wind speeds) or indication of a tropical storm
//and a summary line that indicates the total # of records for both hurricanes and
//tropical storms (FIRST PAGE)

//There will be separate sections of levels of hurricanes which will contain an
//alphabetized list of hurricanes per category. each category (1-5) will have
//its own list. At the end of each list will be a summary line of # of hurricanes
//in that level and the average life in days, average rain, and average # of tornadoes
//spawned and average wind speed in that level. category lists will be in order
//of category 1-5. (LEVEL PAGES)

//There will be a SUMMARY PAGE that lists the statistics of hurricane records
//including avg speed of all hurricanes, highest avg wind speed, lowest avg wind
//speed, standard deviation of the wind speed, and list # of hurricanes in each
//category

//Lastly, the program will output into the file a list of EXCEPTION REPORTS where
//the ID's of the tropical storms (CATEGORY 0) found in the storms.txt file are
//compared to the ID #s in the list of tropical storms in the file tropical.txt.
//those that matched IDs in the tropical.txt file are listed with their names in
//alphabetical order with their ID # (This is exception report 1). Those that
//are not listed in tropical.txt are listed in the same way except being labeled
//as unlisted in the tropical storm data list (This is exception report 2)


const int MAXNAME = 10; //a character array will be used for the names of each
                        //storm cannot exceed 10 characters (includes spaces)

struct Hurricane //structure variable that holds the information for each storm
{
    char name[MAXNAME]; //stores the name of a storm
    int ID; //holds the identification number of a storm
    int lifespan; //holds # of days a storm lasted
    int year; //four number year that the storm took place
    float avgWind; //float that stores wind speeds
    float avgRain; //rain fall recordings
    int numTornado; //how many tornadoes are spawned
    int level; //the category of a storm
};

void Read (Hurricane[]); //function that reads in the input file
//int findLevel (float); //function that finds the level of the storms


int main()
{
    ifstream infile; //will be to open the input file: storms.txt
    ifstream dataIn; //will be to open the input file: tropical.txt
    ofstream outfile; //applying an output file

    infile.open("storms.txt");

    Hurricane stats[200]; //An array of structures that will hold the information
                          //from the input file

    Read(stats);

    return 0;
}



//**********************************************************************
//                          Read
//
// task: Read in the input file and then output it to the screen to
//       check its functionality
// data in: the array of structures: stats
// data out: All information from the input file
//
//**********************************************************************
void Read (struct Hurricane stats[])
{
    cout << fixed << showpoint << setprecision(2);
    ifstream infile;
    infile.open("storms.txt");

    if (!infile)
    {
        cout << "Error reading file";
    }

    do
    {
        int numList = 0; //a counter variable which increases as long as there are
                         //lines in the file to be read
        infile.get(stats[numList].name, 11);
        infile >> stats[numList].ID;
        infile >> stats[numList].lifespan;
        infile >> stats[numList].year;

        float wind = 0; //make windspeed variable to take total of all windspeed measurements
        for (int i = 1; i <= 5; i++) //for loop to find the average windspeed
        {
            infile >> stats[numList].avgWind;
            wind += stats[numList].avgWind;
        }

        stats[numList].avgWind = (wind / 5);

        //stats[numList].level = findLevel(stats[numList].avgWind);

        float rain = 0;
        for (int i = 1; i <= 2; i++)
        {
            infile >> stats[numList].avgRain;
            rain += stats[numList].avgRain;
        }
        stats[numList].avgRain = (rain / 2);

        infile >> stats[numList].numTornado;
        cout << stats[numList].name << " " << stats[numList].ID << "  " << stats[numList].lifespan
             << "  " << stats[numList].year << "  " << stats[numList].avgWind << "  "
             << stats[numList].avgRain << "  " << stats[numList].numTornado;

       // cout << endl << "The level of " << stats[numList].name << " is " << stats[numList].level << endl;

        infile.ignore(200, '\n');

        cout << endl;
        numList++;
    }
    while (infile);

    infile.close();
}
