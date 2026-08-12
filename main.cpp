/*
    Name: Slater Zevallos
    Project: Student Record System
    Desc: This program allows you to add, view, and remove student records.
          Uses vectors, arrays, pointers, referencing & dereferencing, and classes/structs.
    Date created: 12 Aug 2026
*/
using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cctype>

/*
Intialization of a class named Student, that contains a constructor with default parameters
    string Name - Student name
    int ID - Student ID
    float GPA - Student GPA
*/
class Student
{
    public:
    Student()
    {
        name = "null";
        ID = 0;
        GPA = 0.0;
    }
    private:
    string name;
    int ID;
    float GPA;
};

void mainMenu(); // created


void addStudent();
void editStudent();
void removeStudent();
void viewStudent();


int main() 
{
    vector <Student> studentRecord;
    mainMenu();
    return 0;
}

/*
Function: mainMenu
Params: -
Returns: -
Desc: Displays main menu of the program, gives user a list of actions they can choose to perform
*/
void mainMenu()
{
    bool validChoice = true;
    
    do
    {
        string userMenuChoice;
        
        cout << "Hello and welcome to slaterrr's Student Record System!" << endl;
        cout << string (60, '-') << endl; // Prints 60 characters of '-'
        cout << "What would you like to do today?" << endl << endl;
        cout << "Add - adds a student to the record system." << endl;
        cout << "Edit - edits an existing student's record(Name, GPA, or ID)." << endl;
        cout << "Remove - removes an existing student from the record system." << endl;
        cout << "View - displays entire student record system." << endl;
        cout << string (60, '-') << endl; // Prints 60 characters of '-'    
        cout << "Enter here: ";
        cin >> userMenuChoice;
        cout << endl;
        

        for(char& c : userMenuChoice) // converts user input to uppercase
        {
            c = toupper(c);
        }    

        if(userMenuChoice == "ADD")
        {
            cout << endl << "You chose add!" << endl;
            addStudent();            
        }

        else if(userMenuChoice == "EDIT")
        {
            cout << endl << "You chose edit!" << endl;
            editStudent();            
        }

        else if(userMenuChoice == "REMOVE")
        {
            cout << endl << "You chose remove!" << endl;
            removeStudent();            
        }

        else if(userMenuChoice == "VIEW")
        {
            cout << endl << "You chose view!" << endl;
            viewStudent();            
        }
   
        else if(userMenuChoice == "EXIT")
        {
            cout << endl << "Thank you for using slaterrr's Student Record System!" << endl;
            validChoice = false; 
        }
            
        else
        {
            cout << endl << "Invalid choice. Please try again" << endl;
            cout << string (60, '+') << endl; // Prints 60 characters of '-'
            cout << string (60, '*') << endl << endl; // Prints 60 characters of '-'
        }
            
    }
    while(validChoice == true);
    
}


void addStudent()
{

}

void editStudent()
{

}

void removeStudent()
{

}

void viewStudent()
{

}
