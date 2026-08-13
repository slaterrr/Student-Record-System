/*
    Name: Slater Zevallos
    Project: Student Record System
    Desc: This program allows you to add, view, and remove student records.
          Uses vectors, referencing & dereferencing, and classes.
    Date created: 12 Aug 2026
*/
using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cctype>
#include <iomanip>
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

    void setName(string newName)
    {
        name = newName;
    }
    
    void setID(int newID)
    {
        ID = newID;
    }

    void setGPA(float newGPA)
    {
        GPA = newGPA;
    }

    string getName()
    {
        return name;
    }

    int getID()
    {
        return ID;
    }

    float getGPA()
    {
        return GPA;
    }

    private:
    string name;
    int ID;
    float GPA;
};

using studentList = vector<Student>; // Assigns 'studentList' name as an alias to vector<Student>

void mainMenu(studentList &); // created
void addStudent(studentList &);
void editStudent(studentList &);
void removeStudent(studentList &);
void viewStudent(studentList &);
int binarySearch(studentList, int userChoice);

int main() 
{
    studentList studentRecord; // Declares a vector of student records
    mainMenu(studentRecord);
    return 0;
}

/*
Function: mainMenu
Params: -
Returns: -
Desc: Displays main menu of the program, gives user a list of actions they can choose to perform
*/
void mainMenu(studentList & studentRecord)
{
    bool validChoice = true;
    
    do
    {
        string userMenuChoice;
        
        cout << string(60,'-') << endl;
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
            cout << string(30,'-') << endl;
            addStudent(studentRecord);            
        }

        else if(userMenuChoice == "EDIT")
        {
            cout << endl << "You chose edit!" << endl;
            cout << string(30,'-') << endl;
            editStudent(studentRecord);            
        }

        else if(userMenuChoice == "REMOVE")
        {
            cout << endl << "You chose remove!" << endl;
            cout << string(30,'-') << endl;
            removeStudent(studentRecord);            
        }

        else if(userMenuChoice == "VIEW")
        {
            cout << endl << "You chose view!" << endl;
            cout << string(30,'-') << endl;
            viewStudent(studentRecord);            
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

/*
Function: addStudent
Params: studentRecord - vector, passed by reference
Returns: nothing
Desc: initializes a new student, fills their information,
      and attaches it to the vector that's passed
*/
void addStudent(studentList &studentRecord)
{
    string tempNameHolder;
    int tempIDHolder;
    float tempGPAHolder;
    Student newStudent; // Declares newStudent class variable
    cin.get();
    cout << "Please enter the student's full name: ";
    getline(cin,tempNameHolder);
    newStudent.setName(tempNameHolder);

    cout << endl << "Please enter the student's ID: ";
    cin >> tempIDHolder;
    newStudent.setID(tempIDHolder);

    cout << endl << "Please enter the student's GPA: ";
    cin >> tempGPAHolder;
    newStudent.setGPA(tempGPAHolder);

    studentRecord.push_back(newStudent);
    cout << string(30, '-') << endl;
    cout << "Student Name: " << newStudent.getName() << endl;
    cout << "Student ID: " << newStudent.getID() << endl;
    cout << "Student GPA: "<< newStudent.getGPA() << endl;

    cout << endl << "Student successfully added!" << endl;
    cout << string(30, '-') << endl;
}

/*
Function: editStudent
Params: studentRecord - vector, passed by reference
Returns: nothing
Desc: allows user to edit student's information
*/
void editStudent(studentList & studentRecord)
{

    Student tempStudent; // creates temporary new Student class variable
    if(studentRecord.size() >= 1)
    {
//  Sorting for studentRecord vector in ascending order based on ID
        for (int i = 0; i < studentRecord.size() ; i++)
        {
            for(int j = i+1; j < studentRecord.size(); j++)
            {
               if (studentRecord[i].getID() > studentRecord[j].getID() )
                {
                    tempStudent = studentRecord[i];
                    studentRecord[i] = studentRecord[j];
                    studentRecord[j] = tempStudent;
                } 
            }
            
        }
//  Displaying all student records
        cout << "Listed in ID ascending order:" << endl;
        cout << left << setw(10) << "ID"
                        << setw(30) << "Name"
                        << setw(5) << "GPA" << endl << endl;
        for(int i = 0; i < studentRecord.size(); i++)
        {
            cout << left << setw(10) << studentRecord[i].getID()
                        << setw(30) << studentRecord[i].getName()
                        << setw(5) << studentRecord[i].getGPA() << endl;
        }

//  Asks user for ID and performs binary search
    int requestedStudentPos; // use this one to edit students, contains ID
    float requestedNewGPA;
    int requestedNewID;
    string requestedNewName;
    cout << endl << "Which student would you like to edit? Enter ID: ";
    int userChoice;
    string userTxtChoice;
    cin >> userChoice;
    requestedStudentPos = binarySearch(studentRecord, userChoice);

    if(requestedStudentPos >= 0)
    {
        cout << "What would you like to edit?" << endl;
        cout << string(30,'-') << endl;
        cout << "GPA | ID | Name" << endl;
        cout << "Enter here: ";
        cin >> userTxtChoice;

        for(char& c : userTxtChoice) // converts user input to uppercase
        {
            c = toupper(c);
        }    
        if(userTxtChoice == "GPA")
        {
            cout << endl << "Enter new GPA: ";
            cin >> requestedNewGPA;
            studentRecord[requestedStudentPos].setGPA(requestedNewGPA);
            cout << endl << "Confirmed." << endl;
        }
        else if(userTxtChoice == "ID")
        {
            cout << endl << "Enter new ID: ";
            cin >> requestedNewID;
            studentRecord[requestedStudentPos].setID(requestedNewID);
            cout << endl << "Confirmed." << endl;
        }
        else if(userTxtChoice == "NAME")
        {
            cout << endl << "Enter new name: ";
            cin >> requestedNewName;
            studentRecord[requestedStudentPos].setName(requestedNewName);
            cout << endl << "Confirmed." << endl;
        }
    }
    else if(requestedStudentPos == -1)
    {
        cout << "Invalid ID. redirecting to main menu" << endl;
    }

    }
    else
    {
        cout << "No students to edit, redirecting back to main menu." << endl;
        cout << string(30,'-') << endl;
    }


}

void removeStudent(studentList & studentRecord)
{
    Student tempStudent; // creates temporary new Student class variable
    int userChoice;
    int requestedStudentPos;
    if(studentRecord.size() >= 1)
    {
//  Sorting for studentRecord vector in ascending order based on ID
        for (int i = 0; i < studentRecord.size() ; i++)
        {
            for(int j = i+1; j < studentRecord.size(); j++)
            {
               if (studentRecord[i].getID() > studentRecord[j].getID() )
                {
                    tempStudent = studentRecord[i];
                    studentRecord[i] = studentRecord[j];
                    studentRecord[j] = tempStudent;
                } 
            }
        }
//  Displaying all student records
        cout << "Listed in ID ascending order:" << endl;
        cout << left << setw(10) << "ID"
                        << setw(30) << "Name"
                        << setw(5) << "GPA" << endl << endl;
        for(int i = 0; i < studentRecord.size(); i++)
        {
            cout << left << setw(10) << studentRecord[i].getID()
                        << setw(30) << studentRecord[i].getName()
                        << setw(5) << studentRecord[i].getGPA() << endl;
        }   
        
        cout << "Which student would you like to remove?" << endl
        << "Please enter ID: ";
        cin >> userChoice;
        requestedStudentPos = binarySearch(studentRecord, userChoice);

        if(requestedStudentPos >= 0)
    {
        studentRecord.erase(studentRecord.begin() + requestedStudentPos);
        cout << "Student successfully removed." << endl;
    }
    else if(requestedStudentPos == -1)
    {
        cout << "Invalid ID. redirecting to main menu" << endl;
    }

    }
    else
    {
        cout << "No students to remove, redirecting back to main menu." << endl;
        cout << string(30,'-') << endl;
    }
}

void viewStudent(studentList & studentRecord)
{

}

int binarySearch(studentList studentRecord, int userChoice)
{
    int lowerBound = 0;
    int upperBound = studentRecord.size();
    int target = userChoice;
    int middle = studentRecord.size() / 2;
    do
    {
        if(target == studentRecord[middle].getID() )
        {
            cout << "ID found." << endl;
            return middle;
        }
        else if (target > studentRecord[middle].getID())
        {
            lowerBound = middle + 1;
            middle = (upperBound + lowerBound) / 2;
        }
        else
        {
            upperBound = middle - 1;
            middle = (upperBound + lowerBound) / 2;
        }
    } 
    while (lowerBound <= upperBound);
    return -1;

}