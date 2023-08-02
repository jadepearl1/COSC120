#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

//PLEASE NOTE: This program will also be using an outfile to store information the student enters and displays that
//as well as a summary of their results. The program is still interactive and displays the sample output
//on the program run screen.

int main()
{
    ofstream outfile;
    outfile.open("grades.txt");
    int option; //input object that labels the option the student picks from the menu
    cout << "Welcome to the Grade Calculator! Input '1' to calculate your"
    << " current average or '2' to find what you need on the final exam. " << endl;
    cin >> option;
    outfile << "You chose option " << option << endl; // input is summarized in outfile
    cout << endl;

    if (option == 1) // if statements that runs depending on what option the user inputs
    {                // this if statement is for finding the current class avg
        float classAvg; // input object to store the value for the average class grade
        float quizWeight = 0.25; //stores weights for average calculation
        float homeWeight = 0.1875;
        float testWeight = 0.4375;
        float projWeight = 0.125;


        // for each assignment type, prompt user to enter how many of an assignment they completed
        // these steps will be repeated for each assignment type
        int quizComplete;
        cout << "How many quizzes have you completed? ";
        cin >> quizComplete;
        outfile << "Quizzes completed: " << quizComplete << endl; // input summarized in outfile
        float quizScore; //define variables that will store each score for every assignment
        float quizTotal = 0; //define variables that accumulate the number of points the student accrued from their scores
        float quizAvg;   //define average that will be taken after loop.
        for (int i = 1; i <= quizComplete; i++) // each assignment type has a for loop that stacks the amount of total
        {                                       // points the user has accrued. this will help calculate the avg for that assignment type
            cout << "What was your score on quiz " << i << "? ";
            cin >> quizScore;
            quizTotal += quizScore;
        }
        quizAvg = quizTotal / quizComplete; //calculating average for each assignment type
        cout << endl;

        //repeat of steps above as done for the quiz assignment type
        int homeComplete;
        cout << "How many homeworks have you completed? ";
        cin >> homeComplete;
        outfile << "Homeworks completed: " << homeComplete << endl; // input summarized in outfile
        float homeScore;
        float homeTotal = 0;
        float homeAvg;
        for (int i = 1; i <= homeComplete; i++)
        {
            cout << "What was your score on homework " << i << "? ";
            cin >> homeScore;
            homeTotal += homeScore;
        }
        homeAvg = homeTotal / homeComplete;
        cout << endl;

        int testComplete;
        cout << "How many tests have you completed? ";
        cin >> testComplete;
        outfile << "Tests completed: " << testComplete << endl; // input summarized in outfile
        float testScore;
        float testTotal = 0;
        float testAvg;
        for (int i = 1; i <= testComplete; i++)
        {
            cout << "What was your score on test " << i << "? ";
            cin >> testScore;
            testTotal += testScore;
        }
        testAvg = testTotal / testComplete;
        cout << endl;

        int projComplete;
        cout << "How many projects have you completed? ";
        cin >> projComplete;
        outfile << "Projects completed: " << projComplete << endl; // input summarized in outfile
        float projScore;
        float projTotal = 0;
        float projAvg;
        for (int i = 1; i <= projComplete; i++)
        {
            cout << "What was your score on project " << i << "? ";
            cin >> projScore;
            projTotal += projScore;
        }
        projAvg = projTotal / projComplete;
        cout << endl << endl; // double line spacing for better formatting in output

        //calculate class average, keeping in mind grade weight of each assignment and how many points each assigment
        // had and making them worth out of 100, i.e. Quiz is out of 10 pts so the quiz avg has to be multiplied by 10
        // in order to be out of 100 total points

        classAvg = (quizAvg * quizWeight * 10) + (homeAvg * homeWeight * 10) + (testAvg * testWeight) + (projAvg * projWeight * 4);
        cout << fixed << showpoint << setprecision(2); // set precision to fix average two places after the decimal point

        // chain of if statements that analyze the average percent in the class and displays the students average
        // and tells them what letter grade they have in the course. Under each statement, the summary of their results
        // are copied and pasted into the outfile
        if ((classAvg >= 90) && (classAvg <= 100))
        {
            cout << "Your current average is " << classAvg << " and your grade is an A." << endl;
            outfile << "Your current average is " << classAvg << " and your grade is an A." << endl;
        }
        if ((classAvg >= 80) && (classAvg < 90))
        {
            cout << "Your current average is " << classAvg << " and your grade is a B." << endl;
            outfile << "Your current average is " << classAvg << " and your grade is a B." << endl;
        }
        if ((classAvg >=70) && (classAvg < 80))
        {
            cout << "Your current average is " << classAvg << " and your grade is a C." << endl;
            outfile << "Your current average is " << classAvg << " and your grade is a C." << endl;
        }
        if ((classAvg >= 60) && (classAvg < 70))
        {
            cout << "Your current average is " << classAvg << " and your grade is a D." << endl;
            outfile << "Your current average is " << classAvg << " and your grade is a D." << endl;
        }
        if (classAvg < 60)
        {
            cout << "Your current average is " << classAvg << " and your grade is an F." << endl;
            outfile << "Your current average is " << classAvg << " and your grade is an F." << endl;
        }
    } // end of scenario 1 if statement

    if (option == 2) // if statement for finding what is needed on the final
    {
        char desiredGrade; // char object that stores the letter grade the student wishes to obtain
        float desiredPercent; // float object that represents the minimum percent value to obtain the desired grade letter
        float quizAvg, homeAvg, testAvg, projAvg; // float objects to store averages of each assignment type
        float finalExam; // float object describing what is needed on the final exam
        float quizWeight = 0.2; // this variable and the next three are float constants that store weight of each
        float homeWeight = 0.15;// assignment type
        float testWeight = 0.35;
        float projWeight = 0.1;

        cout << "Please enter the grade you wish to earn for the class: "; // prompting the user to enter their desired grade
        cin >> desiredGrade;
        outfile << "Desired grade: " << desiredGrade << endl; // input summary in outfile
        cout << endl;

        switch (desiredGrade) // switch statement that processes the student's desired grade and assigns the percentage
        {                     // value corresponding to the letter grade to their desired grade
            case 'a':
            case 'A':
                desiredPercent = 90.0;
                break;
            case 'b':
            case 'B':
                desiredPercent = 80.0;
                break;
            case 'c':
            case 'C':
                desiredPercent = 70.0;
                break;
            case 'd':
            case 'D':
                desiredPercent = 60.0;
                break;
        } // end of switch statement

        cout << "Please enter your quiz average: "; // prompts user to enter their percent averages for each assignment type
        cin >> quizAvg;                             // and then summary of their input is put into the outfile
        outfile << "Quiz Average: " << quizAvg << endl;
        cout << endl;

        cout << "Please enter your homework average: ";
        cin >> homeAvg;
        outfile << "Homework Average: " << homeAvg << endl;
        cout << endl;

        cout << "Please enter your test average: ";
        cin >> testAvg;
        outfile << "Test Average: " << testAvg << endl;
        cout << endl;

        cout << "Please enter your project average: ";
        cin >> projAvg;
        outfile << "Project Average: " << projAvg << endl;
        cout << endl;

        // calculation of the user's average in the course + set precision to fix the decimal after 2 places
        float classAvg = (quizAvg * quizWeight) + (homeAvg * homeWeight) + (testAvg * testWeight) + (projAvg * projWeight);
        cout << fixed << showpoint << setprecision(2);
        // calculation of what is needed on the final exam
        finalExam = ((desiredPercent - classAvg) / 20.0) * 100;

        if (finalExam <= 100) // if statement that shows what the student needs on the final to
        {                     // obtain their desired grade and output is also summarized in outfile
            cout << "You need to score at least " << finalExam << " on your final exam to earn a " << desiredGrade << ".";
            outfile << "You need to score at least " << finalExam << " on your final exam to earn a " << desiredGrade << "." << endl;
            cout << endl;
        }

        if (finalExam > 100) // if statement for when the student cannot obtain their desired grade
        {                    // no matter what they get on the final exam. Summary of output is put in outfile
            cout << "You cannot earn a " << desiredGrade << " in this course.";
            outfile << "You cannot earn a " << desiredGrade << " in this course." << endl;
            cout << endl;
        }
    } // end of scenario 2 if statement

    cout << "A summary of your results is found in the grades.txt file." << endl;
    outfile << "The above is the summary of your results."; // ending statement that signifies the summary outfile is finished
    outfile.close(); // closing the outfile after it is done being modified by the program
    return 0;
}
