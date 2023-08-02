#include <iostream>
#include <iomanip>
//#include <istream>
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

//Outputs will go into an output file for the user to access after the program
//finishes running.

//The program's job once it reads in the storms.txt file is to echo print that
//information to the output file with appropriate spacing and a storm level of
//the hurricane (based off average wind speeds) or indication of a tropical storm
//and a summary line that indicates the total # of records for both hurricanes and
//tropical storms (FIRST PAGE)

//There will be separate sections of levels of hurricanes which will contain an
//alphabetized list of hurricanes per category. each category (1-5) will have
//its own list. At the end of each list will be a summary line of the # of hurricanes
//in that level and the average life in days, average rainfall, average # of tornadoes
//spawned, and average wind speed . category lists will be in order of categories
//1-5. (LEVEL PAGES)

//There will be a SUMMARY PAGE that lists the statistics of hurricane records
//including avg speed of all hurricanes, highest avg wind speed, lowest avg wind
//speed, standard deviation of wind speeds, and list the # of hurricanes in each
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
const int MAXCOUNT = 200; //maximum number of storms allowed to be listed in the
                          //input file

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

void firstPage(ifstream&, ofstream&, Hurricane[], int&); //function that reads in the input file

int findLevel(ifstream&, float); //function that finds the level of the storms

void alpha(Hurricane[], int); //procedure that is used to alphabetize each list

void levelPages(ifstream&, ofstream&, Hurricane[], int); //procedure that lists all of the level (1-5)
                                     //hurricanes + stats in their own lists
void Exceptions(ifstream&, ofstream&, Hurricane[], int);//a procedure that lists Exception
    //report 1 (all level 0 storms listed in tropical.txt) and Exception report 2
    //(all level 0 storms not listed in tropical.txt). Each report is listed
    //separately
bool Search(int[], int, int); //a procedure that will search through the
    //tropical.txt file for numbers that match the IDs found in the storms.txt file.
void Summary(ofstream&, Hurricane[], int, int[]);//procedure that lists
    //the the summary statistics of all hurricanes combined including wind speed, highest
    //wind average, lowest wind average, standard deviation, and the number of hurricanes
    //found in each level
float stdDev(Hurricane[], int, int, float); //function that finds the standard deviation
    //of all wind speeds of hurricanes from the storms.txt list

int main()
{
    ifstream infile; //will be to open the input file: storms.txt
    ifstream dataIn; //will be to open the input file: tropical.txt
    ofstream outfile; //applying an output file

    outfile << fixed << showpoint << setprecision(2);

    infile.open("storms.txt");
    dataIn.open("tropical.txt");
    outfile.open("results.txt");

    Hurricane stats[MAXCOUNT]; //An array of structures that will hold the information
                          //from the input file

    int numStorms; //variable that represents the total number of storms listed
                   //in the storms.txt file. Passed to functions by reference to
                   //keep its newfound value after the list is read in

    firstPage(infile, outfile, stats, numStorms); //call to the function that will read in
        //the input file and echo print the required information to the output file as the
        //first page

    alpha(stats, numStorms); //after list is initially read in and the first page is printed,
        //call to a function for alphabetizing said list

    levelPages(dataIn, outfile, stats, numStorms); //call to a function that will create the level pages


    cout << "Find the resulting lists in the output file: results.txt."; //inform the user of the output file


    //ALWAYS CLOSE FILES WHEN PROGRAM IS DONE RUNNING
    infile.close();
    dataIn.close();
    outfile.close();

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
void firstPage (ifstream &infile, ofstream &outfile, Hurricane stats[], int &numStorms)
{
    if (!infile) //validation for input file
    {
        outfile << "Error reading file";
    }

    outfile << setw(50) << "STORM SUMMARY SHEET" << endl << endl;
    outfile << "Name" << setw(10) << "ID" << setw(8) << "Life" << setw(8) << "Date"
            << setw(10) << "Average" << setw(12) << "Average" << setw(12) << "Tornadoes"
            << setw(10) << "Storm" << endl;
    outfile << setw(24) << "in days" << setw(18) << "wind speed" << setw(11) << "rain fall"
            << setw(10) << "spawned" << setw(11) << "level" << endl << endl;

    numStorms = 0; //initialize numStorms to zero and it will later be tied to how many storms are read in
    int numList = 0; //a counter variable which increases as long as there are
                     //lines in the file to be read
    int numHurricanes = 0; //represents the number of hurricanes to be found in the list
    int numTropical = 0; //represents the number of tropical storms to be found in the list

    do //do while loop that will read in the data from storms.txt
    {
        infile.get(stats[numList].name, 11); //read in name, ID, lifespan, and year
        infile >> stats[numList].ID;
        infile >> stats[numList].lifespan;
        infile >> stats[numList].year;

        float wind = 0; //make windspeed variable to take total of all windspeed measurements
        for (int i = 1; i <= 5; i++) //for loop to find the average windspeed
        {
            infile >> stats[numList].avgWind;
            wind += stats[numList].avgWind;
        }
        stats[numList].avgWind = (wind / 5); //initialize the average wind speed

        if (stats[numList].avgWind >= 75) //increase the number of hurricanes or tropical
            numHurricanes++;              //storms based on average wind speed of current
        else                              //storm
            numTropical++;

        stats[numList].level = findLevel(infile, stats[numList].avgWind);

        float rain = 0; //do the same for rain as was with wind measurements
        for (int i = 1; i <= 2; i++)
        {
            infile >> stats[numList].avgRain;
            rain += stats[numList].avgRain;
        }
        stats[numList].avgRain = (rain / 2);

        infile >> stats[numList].numTornado; //read in number of tornadoes spawned

        //send to the output file all of the information retrieved in the storms.txt list
        outfile << stats[numList].name << "  " << stats[numList].ID << setw(5)
                << stats[numList].lifespan << setw(10) << stats[numList].year
                << setw(10) << stats[numList].avgWind << setw(10) << stats[numList].avgRain
                << setw(10) << stats[numList].numTornado << setw(10) << stats[numList].level;

        infile.ignore(200, '\n'); //jump to a new line in the file
        outfile << endl;
        numList++; //index will increase as long as there is still data in the input file
    }
    while (infile);

    numStorms = numList; //numStorms will equal the final number of numList since it is done
        //reading in the file

    outfile << endl;
    outfile << "Total number of records=" << numStorms << endl;
    outfile << "Total number of hurricanes=" << numHurricanes << endl;
    outfile << "Total number of tropical storms=" << numTropical << endl;
    //print a summary of the information in # of records, total hurricanes, and total tropical
    //storms

    outfile << "\n\n\n\n\n\n\n\n\n\n";
}



//**********************************************************************
//                              findLevel
//
// task: finds the category or level of each storm in the storms.txt
//       file
// data in: the structure array: stats and all values stored within it
// data out: the newly found levels of the storms
//
//**********************************************************************
int findLevel(ifstream &infile, float avgWind)
{
    //find the level of a storm based on average wind speed found in firstPage
    //create a variable to represent the level of a storm that will be returned to the calling
    //function
    int level;
    if (avgWind < 75.00)
        level = 0;
    if ((avgWind >= 75) && (avgWind <= 95))
        level = 1;
    if ((avgWind >= 96) && (avgWind <= 110))
        level = 2;
    if ((avgWind >= 111) && (avgWind <= 130))
        level = 3;
    if ((avgWind >= 131) && (avgWind <= 155))
        level = 4;
    if (avgWind > 155)
        level = 5;

    return level;
}



//**********************************************************************
//                            alpha
//
// task: alphabetize the list of storms based on the comparison between
//       two names in the list
// data in: information from the storms.txt input file, stats, numStorms
// data out: an alphabetized version of the storms.txt list
//
//**********************************************************************
void alpha (Hurricane stats[], int numStorms)
{
    int temp, i, j; //define temporary variable, i for the first name and j for the second name to be compared

    for(i = 0; i < numStorms - 1; i++) //follow procedures of a bubble sort that compares strings from char arrays
    {
        temp = i; //initialize temp to the value of i

        for(j = i + 1; j < numStorms; j++)
        {
            if (strcmp(stats[temp].name, stats[j].name) > 0)
            {
                temp = j; //if the second string is earlier in alphabetization, set temp to j
            }
        }
        if(temp != i) //swap the lines if temp was set to j in the previous if statement within the nested for loop
        {
            Hurricane j = stats[temp]; //creating a new structure variable j helps assign j as its own structure
            stats[temp] = stats[i];    //to help set up the switch
            stats[i] = j;
        }
    }
}



//**********************************************************************
//                                 levelPages
//
// task: lists the level one storms in alphabetical order and their
//       stats as well as the total # hurricanes in that level, average
//       life span in days, average rain fall, average wind and avg
//       tornadoes spawned
// data in: input file object, output file object, Hurricane array of
//          structures: stats
// data out: all information from the level one hurricanes in the level
//           one category
//**********************************************************************
void levelPages(ifstream& dataIn, ofstream &outfile, Hurricane stats[], int numStorms)
{
    int totalLevel[5] = {0, 0, 0, 0, 0}; //integer array that holds numbers of each level hurricane

    //for loop that goes through the levels of storms
    for(int lvl = 1; lvl <= 5; lvl++)
    {
        //output the level number at the top of each list
        outfile << setw(50) << "Hurricane Level " << lvl << endl << endl << endl;
        outfile << "Name" << setw(10) << "Id" << setw(8) << "Life" << setw(12) << "Average"
                << setw(12) << "Average" << setw(15) << "Tornadoes" << setw(8) << "Date" << endl;
        outfile << setw(24) << "in days" << setw(12) << "wind speed" << setw(12) << "rain fall"
                << setw(12) << "spawned" << endl << endl << endl;

        float windTotal = 0; //stores the sum of all wind averages in a level
        float rainTotal = 0; //sum of all rainfall avgs in a lvl
        float tornTotal = 0; //sum of all tornadoes spawned in a lvl
        float lifeTotal = 0; //sum of all lifetime days in a lvl

        //nested for loop that goes through the information from storm.txt and outputs
        //the corresponding information depending on level
        for(int i = 0; i < numStorms; i++)
        {
            if (stats[i].level == lvl)
            {

                outfile << stats[i].name << "  " << stats[i].ID << setw(5)
                    << stats[i].lifespan << setw(12) << stats[i].avgWind
                    << setw(12) << stats[i].avgRain << setw(12) << stats[i].numTornado
                    << setw(13) << stats[i].year;
                outfile << endl;

                windTotal += stats[i].avgWind; //increase total wind, rain, tornadoes, and life
                rainTotal += stats[i].avgRain;
                tornTotal += stats[i].numTornado;
                lifeTotal += stats[i].lifespan;
                totalLevel[lvl - 1]++; //increments the number of storms in a given level
            }
        }


        //takes averages of wind, rain, tornadoes, and life in a given level
        windTotal = (windTotal / totalLevel[lvl - 1]);
        rainTotal = (rainTotal / totalLevel[lvl - 1]);
        tornTotal = (tornTotal / totalLevel[lvl - 1]);
        lifeTotal = (lifeTotal / totalLevel[lvl - 1]);

        outfile << endl << endl;

        outfile << "Total number of Level " << lvl << " hurricanes is " << totalLevel[lvl - 1] << "." << endl;
        outfile << "Average Life span in days of Level " << lvl << " hurricanes is " << lifeTotal << endl;
        outfile << "Average rain fall for Level " << lvl << " hurricanes is " << rainTotal << endl;
        outfile << "Average tornadoes spawned for Level " << lvl << " hurricanes is " << tornTotal << endl;
        outfile << "Average wind speed for Level " << lvl << " hurricanes is " << windTotal << endl << endl;
        outfile << "\n\n\n\n\n\n\n\n\n\n";
    }

    Exceptions(dataIn, outfile, stats, numStorms);//call to a function that will create
        //the exception reports for tropical storms under the storms.txt list

    Summary(outfile, stats, numStorms, totalLevel); //calls to a function that makes the summary page
}



//**********************************************************************
//                             Exceptions
//
// task: compare the ID's of the storms in the storms.txt file and the
//       list of tropical storm ID #'s in the tropical.txt to find what
//       ID's match those listed in the tropical.txt file and those that
//       do not match
// data in: the information read in from the storms.txt file, the output
//          file, the tropical.txt file, numStorms
// data out: names and ID numbers of storms listed in tropical.txt and
//           those that are not. TWO SEPARATE LISTS!!!!
//
//**********************************************************************
void Exceptions(ifstream &dataIn, ofstream &outfile, Hurricane stats[], int numStorms)
{
    if(!dataIn)
    {
        outfile << "Error reading/finding tropical.txt file!!" << endl;
    }

    int tropID[150]; //represents an ID number listed in tropical.txt. Size of
                     //150 since there cannot be more than 150 storms in a given level
    int counter = 0; //a counter that will be used as the index of the array that will
                     //be read in
    int numID; //keeps track of the number of ID numbers in tropical.txt

    do
    {
        dataIn >> tropID[counter];
        counter++;
    }
    while(dataIn);

    numID = counter; //numID is assigned to counter once there is no more lines of data in the list
        //just as what was done with numStorms in firstPage procedure

    int value; //variable used to store an ID number found in storms.txt (search value)
    bool match; //marks true if there is matching ID numbers

    outfile << setw(50) << "EXCEPTION REPORT 1" << endl << endl;
    outfile << "      " << "The Following Hurricanes were listed in the Tropical Storm data list." << endl << endl;
    outfile << "NAME" << setw(11) << "ID" << endl;
    for(int i = 0; i < numStorms; i++)
    {
        match = false; //assume that there is not a match to begin with, that way the boolean variable
            //will have a default and not stay true for all level 0 storms if it switches to true
        if(stats[i].level == 0)
        {
            value = stats[i].ID;
            match = Search(tropID, value, numID);
            if (match == true) //if statement that outputs storm names and ID's if there is a match
                outfile << stats[i].name << "   " << stats[i].ID << endl;
        }
    }

    outfile << "\n\n\n\n\n\n\n\n\n\n";

    outfile << setw(50) << "EXCEPTION REPORT 2" << endl << endl;
    outfile << "      " << "The Following Tropical Storms were not listed in the Tropical Storm data list." << endl << endl;
    outfile << "Name" << setw(11) << "ID" << endl;
    for (int i = 0; i < numStorms; i++)
    {
        //boolean expression does not need to initialize to false for exception report 2 because
        //it takes into account if there is not a match
        if (stats[i].level == 0)
        {
            value = stats[i].ID;
            match = Search(tropID, value, numID);
            if (match != true)
                outfile << stats[i].name << "   " << stats[i].ID << endl;
        }
    }

    outfile << "\n\n\n\n\n\n\n\n\n\n";
}



//**********************************************************************
//                              Search
//
// task: conduct a linear search on tropical.txt to see if any of its ID
//       numbers match that in storms.txt and then returns a boolean
//       variable
// data in: tropID array holding the IDs from tropical.txt, value -->
//          (stats.ID), numID (number of ID's in tropical.txt)
// data out: boolean value of variable pres (true/false)
//
//**********************************************************************
bool Search(int tropID[], int value, int numID)
{
    bool pres = false; //switches to true if the linear search finds matching IDs

    for(int i = 0; i < numID; i++)
    {
        if (tropID[i] == value) //variable becomes true if there is a match
            pres = true;
    }

    return pres;
}




//**********************************************************************
//                              Summary
//
// task: calculate for all hurricanes the average wind speed, the
//       highest wind speed (the one storm with the highest wind speed)
//       found out of all levels (1-5), the lowest wind speed average,
//       the standard deviation of all wind speeds,
// data in: outfile, stats, numStorms, num1, num2, num3, num4, and num5
//          from the levelPages procedure
// dataOut: average wind speed of all hurricanes, highest average wind
//          speed found, lowest avg wind speed found, standard deviation
//          off wind speeds, and the number of hurricanes per level
//
//**********************************************************************
void Summary(ofstream &outfile, Hurricane stats[], int numStorms, int totalLevel[])
{
    float windAvg; //variable used to store the overall average wind speed of all storms
    float windAvgTotal = 0; //adds on the sum of all wind averages. used to find the value for
        //windAvg variable
    //make variables representing the maximum and minimum wind speed averages in hurricanes
    //of level 1-5
    float maxWind = stats[0].avgWind;
    float minWind = stats[0].avgWind;

    int totalHurr = totalLevel[0] + totalLevel[1] + totalLevel[2] + totalLevel[3] + totalLevel[4];
    //take the total number of hurricanes in each level in order to find wind average for all
    //hurricanes

    for (int i = 0; i < numStorms; i++)
    {
        if (stats[i].level != 0) //only counts if the storm is not level 0
        {
            windAvgTotal += stats[i].avgWind;

            if (maxWind < stats[i].avgWind) //sets maximum avg found from all hurricane lvls
            {
                maxWind = stats[i].avgWind;
            }

            if (minWind > stats[i].avgWind) //sets minimum avg found from all hurricane lvls
            {
                minWind = stats[i].avgWind;
            }
        }
    }

    windAvg = windAvgTotal / totalHurr; //find windAvg of all storms

    outfile << "Summary Statistics" << endl << endl << endl;
    outfile << "Wind average of all hurricanes  " << setw(10) << windAvg << endl;
    outfile << "Highest wind average  " << setw(20) << maxWind << endl;
    outfile << "Lowest wind average  " << setw(20) << minWind << endl;
    //find the standard deviation of wind speeds by calling to a function that does the calculation
    outfile << "Standard deviation  " << setw(21) << stdDev(stats, numStorms, totalHurr, windAvg)
            << endl << endl;
    outfile << "Number of Hurricanes in each level" << endl << endl;
    outfile << "Level 1  " << setw(20) << totalLevel[0] << endl;
    outfile << "Level 2  " << setw(20) << totalLevel[1] << endl;
    outfile << "Level 3  " << setw(20) << totalLevel[2] << endl;
    outfile << "Level 4  " << setw(20) << totalLevel[3] << endl;
    outfile << "Level 5  " << setw(20) << totalLevel[4] << endl;

    outfile << "\n\n\n\n\n\n\n\n\n\n";
}




//**********************************************************************
//                                stdDev
//
// task: find the standard deviation of all hurricane (lvl 1-5) wind
//       speeds
// data in: stats, numStorms, totalHurr from the calling function
//          (Summary), windAvg from the calling function (Summary)
// data out: standard deviation
//
//**********************************************************************
float stdDev(Hurricane stats[], int numStorms, int totalHurr, float windAvg)
{
    float differences[totalHurr]; //used to find the difference of a particular
                       //storm's wind speed minus the overall average
                       //wind speed
    float totalDiff2; //variable that takes the total squared differences
                     //of all hurricanes
    float variance; //variable representing the variance of wind speeds
                    //which is needed to find the standardDeviation
    float standardDeviation; //square root of the variance is the standard deviation


    for(int i = 0; i < numStorms; i++)
    {
        if (stats[i].level != 0) //find the differences, take their sum and square them
        {
            differences[i] = stats[i].avgWind - windAvg;
            totalDiff2 += pow(differences[i], 2); //adding up the sum of the differences squared
        }
    }

    variance = totalDiff2 / totalHurr; //take the total of the differences squared divided
        //by the total number of all storms levels 1-5

    standardDeviation = sqrt(variance);

    return standardDeviation;
}
