#include <iostream>
#include <iomanip>

using namespace std;


// This program uses a structure to hold data about a rectangle
// It calculates the area and perimeter of a box

// Jade and Jordan
// date modified: 4/20/2022

struct dimensions
{
    float length;
    float width;
};

struct results
{
    float area;
    float perimeter;
};

struct Rectangle
{
    results ap;
    dimensions sizes;
};

void Area(Rectangle);
void Perimeter(Rectangle);

int main()
{
   Rectangle box;

   cout << "Enter the length of a rectangle: ";

   cin >> box.sizes.length; //reads and stores length

   cout << "Enter the width of a rectangle: ";

   cin >> box.sizes.width; //reads and stores width

   cout << fixed << showpoint << setprecision(2);

   //call to functions for calculating area and perimeter
   Area(box);
   Perimeter(box);

   return 0;
}



//**********************************************************************
//                              Area
//
// task: find area of the rectangle
// data in: Rectangle structure variable box
// data out: none
//
//**********************************************************************
void Area (Rectangle b)
{
    b.ap.area = b.sizes.length * b.sizes.width;
    cout << "The area of the rectangle is " << b.ap.area << endl;
}



//**********************************************************************
//                              Perimeter
//
// task: finding the perimeter of the rectangle
// data in: Rectangle structure variable box
// data out: none
//
//**********************************************************************
void Perimeter(Rectangle b)
{
    b.ap.perimeter = (b.sizes.length * 2) + (b.sizes.width * 2);
    cout << "The perimeter of the rectangle is " << b.ap.perimeter << endl;
}
