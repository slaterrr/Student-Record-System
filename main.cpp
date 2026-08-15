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
#include <fstream>
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

void sort(studentList &);
void display(studentList);
void mainMenu(studentList &);
void addStudent(studentList &);
void editStudent(studentList &);
void removeStudent(studentList &);
void viewStudent(studentList &);
int binarySearch(studentList, int userChoice);
void saveStudentRecord(studentList);
void readStudentRecord(studentList &);
float findAverage(studentList);
void sortGPA(studentList &);
void sortID(studentList &);
void sortName(studentList &);
int findLowestGPA(studentList &);
int findHighestGPA(studentList &);
int linearSearchName(studentList &,string);

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
        
        cout << string(60,'-') << endl << string(60,'-') << endl << string(60,'-') << endl;
        cout << "Hello and welcome to slaterrr's Student Record System!" << endl;
        cout << string (60, '-') << endl; // Prints 60 characters of '-'
        cout << "What would you like to do today?" << endl << endl;
        cout << "Add - adds a student to the record system." << endl;
        cout << "Edit - edits an existing student's record(Name, GPA, or ID)." << endl;
        cout << "Remove - removes an existing student from the record system." << endl;
        cout << "View - displays entire student record system." << endl;
        cout << "Load - loads student record from file" << endl;
        cout << "Save - saves entire student record onto a file" << endl;
        cout << "Exit - exits program" << endl;
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

        else if(userMenuChoice == "SAVE")
        {
            cout << endl << "You chose save!" << endl;
            cout << string(30,'-') << endl;
            saveStudentRecord(studentRecord);
        }

        else if(userMenuChoice == "LOAD")
        {
            cout << endl << "Loading up student record file"
            << endl;
            readStudentRecord(studentRecord);
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
        sort(studentRecord);
        display(studentRecord);
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

/*
Function: removeStudent
Params: studentList & studentRecord - vector, passed by reference
Returns: nothing
Desc: Allows user to remove a student from the studentRecord vector
*/
void removeStudent(studentList & studentRecord)
{
    Student tempStudent; // creates temporary new Student class variable
    int userChoice;
    int requestedStudentPos;
    if(studentRecord.size() >= 1)
    {
        sort(studentRecord);    
        display(studentRecord);
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

/*
Function: viewStudent
Params: studentList & studentRecord - vector, passed by reference
Returns: nothing
Desc: Allows user to view all students from the studentRecord vector
*/
void viewStudent(studentList & studentRecord)
{
    string userChoice;
    if(studentRecord.size() >= 1)
    {
        cout << "What would you like to do? Select from below" << endl << endl;

        cout << "All - view all student records" << endl
             << "Average - view average GPA in student record" << endl
             << "Lowest - view lowest GPA in student record" << endl
             << "Highest - view highest GPA in student record" << endl
             << "Search - search for student using either name, ID, or GPA" << endl;
            
            cin >> userChoice;
            for(char &c : userChoice)
            {
                c = toupper(c);
            }

            if(userChoice == "ALL")
            {
                cout << "What would you like the order sorted by?" << endl
                << endl << "GPA" << endl
                << "Name" << endl
                << "ID" << endl
                << "Enter here: ";

                cin >> userChoice;
                cout << endl;
                for(char & c : userChoice)
                {
                    c = toupper(c);
                }

                if(userChoice == "GPA")
                {
                    // must make 3 functions - sortGPA, sortID, sortName
                    cout << "All student records listed in GPA descending order below"
                    << endl << string(60,'-') << endl
                    << left << setw(10) << "ID"
                    << setw(30) << "Name"
                    << setw(5) << "GPA" << endl
                    << string(60,'-') << endl;
                    sortGPA(studentRecord);
                    display(studentRecord);
 
                }
                
                else if(userChoice == "NAME")
                {
                    cout << "All student records listed in descending alphabetical order below"
                    << endl << string(60,'-') << endl
                    << left << setw(10) << "ID"
                    << setw(30) << "Name"
                    << setw(5) << "GPA" << endl
                    << string(60,'-') << endl;
                    sortName(studentRecord);
                    display(studentRecord);
                }
                else if(userChoice == "ID")
                {
                    cout << "All student records listed in ID descending order below"
                    << endl << string(60,'-') << endl
                    << left << setw(10) << "ID"
                    << setw(30) << "Name"
                    << setw(5) << "GPA" << endl
                    << string(60,'-') << endl;
                    sortID(studentRecord);
                    display(studentRecord);
                }
                else
                {
                    cout << endl << "Invalid choice. Please try again" << endl;
                    cout << string (60, '+') << endl; // Prints 60 characters of '-'
                    cout << string (60, '*') << endl << endl; // Prints 60 characters of '-'
                }
            }

            else if(userChoice == "AVERAGE")
            { 
                // Display average GPA
                float averageGPA = findAverage(studentRecord);
                cout << endl
                << "Average GPA in student record is "
                << averageGPA << "!" << endl; 
            }    

            else if (userChoice == "LOWEST")
            {
                // Display lowest GPA
//                float lowestGPA = findLowestGPA(studentRecord);
                sortGPA(studentRecord);
                cout << "The lowest GPA belongs to "
                << studentRecord[studentRecord.size() - 1].getName()
                << ", with a GPA of "
                << studentRecord[studentRecord.size() - 1].getGPA()
                << endl;
            }
            else if(userChoice == "HIGHEST")
            {
                // Display highest GPA
                sortGPA(studentRecord);
                cout << "The highest GPA belongs to "
                << studentRecord[0].getName()
                << ", with a GPA of "
                << studentRecord[0].getGPA() << "!"
                << endl;
            }

            else if(userChoice == "SEARCH")
            {
                int targetPos;
                // Use/create linear search function
                cin.get();                
                cout << "Please type full name of student: ";
                getline(cin, userChoice);
                targetPos = linearSearchName(studentRecord,userChoice);
                if(targetPos >= 0)
                {
                    cout << left << setw(10) << "Name" << left << setw(30)
                    << "ID" << setw(5) << "GPA" << endl;
                    cout << left << setw(10) << studentRecord[targetPos].getID()
                    << setw(30) << studentRecord[targetPos].getName()
                    << setw(5) << studentRecord[targetPos].getGPA() << endl
                    << string(30,'-') << endl;
                }
            }

            else
            {
           cout << endl << "Invalid choice. Please try again" << endl;
            cout << string (60, '+') << endl; // Prints 60 characters of '-'
            cout << string (60, '*') << endl << endl; // Prints 60 characters of '-'
        }
    }


    else
    {
        cout << "No students to view, redirecting back to main menu." << endl;
        cout << string(30,'-') << endl;
    }

}

/*
Function: binarySearch
Params: studentList & studentRecord - vector, passed by reference
        int userChoice - user's decision saved onto variable
Returns: int - location of student in vector
Desc: Searches for desired student ID, returns the position of the vector corresponding
        with the ID, else returns -1
*/
int binarySearch(studentList studentRecord, int userChoice)
{
    int lowerBound = 0;
    int upperBound = studentRecord.size() - 1;
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
            upperBound = middle - 1;
            middle = (upperBound + lowerBound) / 2;
        }
        else
        {   
            lowerBound = middle + 1;
            middle = (upperBound + lowerBound) / 2;
        }
    } 
    while (lowerBound <= upperBound);
    return -1;

}

/*
Function: saveStudentRecord
Params: studentList & studentRecord - vector, passed by reference
Returns: nothing
Desc: Allows user to save entire student record from the studentRecord vector
        onto a .txt file
*/
void saveStudentRecord(studentList studentRecord)
{
    ofstream fout;
    fout.open("studentRecord.txt");
    if(!fout)
    {
        cout << "Error opening" << "studentRecord" << ".txt" << endl;
    }
    else
    {
        if(studentRecord.size() >= 1)
        {
            sort(studentRecord);
            fout << left << setw(10) << "ID"
                << setw(30) << "NAME"
                << setw(5) << "GPA" << endl;
            for (int i = 0; i < studentRecord.size(); i++)
            {
                fout << studentRecord[i].getID() << "|"
                << studentRecord[i].getName() << "|"
                << studentRecord[i].getGPA() << "|"
                << endl;
            }
            cout << "Student Record successfully saved" << endl;
        }
        else
        {
            cout << "No students to save, redirecting back to main menu." << endl;
            cout << string(30,'-') << endl;
        }  
    }
    fout.close();
}

/*
Function: sort
Params: studentList & studentRecord - vector, passed by reference
Returns: nothing
Desc: Sorts vector by descending ID order
*/
void sort(studentList & studentRecord)
{
    Student tempStudent;
    //  Sorting for studentRecord vector in ascending order based on ID
        for(int i = 0;i < studentRecord.size(); i++)
        {
            for(int j = i+1; j < studentRecord.size(); j++)
            {
                if(studentRecord[i].getID() < studentRecord[j].getID() )
                {
                    tempStudent = studentRecord[i];
                    studentRecord[i] = studentRecord[j];
                    studentRecord[j] = tempStudent;
                }
            }
        }
}

void sortGPA(studentList & studentRecord)
{
    Student tempStudent;
    //  Sorting for studentRecord vector in ascending order based on GPA
        for(int i = 0;i < studentRecord.size(); i++)
        {
            for(int j = i+1; j < studentRecord.size(); j++)
            {
                if(studentRecord[i].getGPA() < studentRecord[j].getGPA() )
                {
                    tempStudent = studentRecord[i];
                    studentRecord[i] = studentRecord[j];
                    studentRecord[j] = tempStudent;
                }
            }
        }
}

void sortID(studentList & studentRecord)
{
    Student tempStudent;
    //  Sorting for studentRecord vector in ascending order based on ID
        for(int i = 0;i < studentRecord.size(); i++)
        {
            for(int j = i+1; j < studentRecord.size(); j++)
            {
                if(studentRecord[i].getID() < studentRecord[j].getID() )
                {
                    tempStudent = studentRecord[i];
                    studentRecord[i] = studentRecord[j];
                    studentRecord[j] = tempStudent;
                }
            }
        }
}

void sortName(studentList & studentRecord)
{
    Student tempStudent;
    //  Sorting for studentRecord vector in descending order based on name
        for(int i = 0;i < studentRecord.size(); i++)
        {
            for(int j = i+1; j < studentRecord.size(); j++)
            {
                if(studentRecord[i].getName() < studentRecord[j].getName() )
                {
                    tempStudent = studentRecord[i];
                    studentRecord[i] = studentRecord[j];
                    studentRecord[j] = tempStudent;
                }
            }
        }
}


/*
Function: display
Params: studentList & studentRecord - vector, passed by reference
Returns: nothing
Desc: Displays entire student record to user on screen
*/
void display(studentList studentRecord)
{
    cout << left << setw(10) << "ID"
    << setw(30) << "NAME"
    << setw(5) << "GPA" << endl;
    for (int i = 0; i < studentRecord.size(); i++)
        {
            cout << left << setw(10) << studentRecord[i].getID()
            << setw(30) << studentRecord[i].getName()
            << setw(5) << studentRecord[i].getGPA() << endl;
        }
}

/*
Function: readStudentRecord
Params: studentList & studentRecord - vector, passed by reference
Returns: nothing
Desc: Reads and displays entire student record from .txt file onto terminal
*/
void readStudentRecord(studentList & studentRecord)
{
    ifstream fin;
    string tempReader;

    cout << string(30,'-') << endl;
    fin.open("studentRecord.txt");
    if(!fin)
    {
        cout << "Error opening \"studentRecord.txt\" " << endl;
    }
    else
    { 
        studentRecord.clear();
        string trash;
        getline(fin,trash);
        while( getline(fin,tempReader,'|') )
        {  
                Student tempStudent;
                int id;
                float gpa;
                studentRecord.push_back(tempStudent);
                id = stoi(tempReader);
                studentRecord[studentRecord.size()-1].setID(id);
                getline(fin,tempReader,'|');
                studentRecord[studentRecord.size()-1].setName(tempReader);      
                getline(fin,tempReader,'|');  
                gpa = stof(tempReader);
                studentRecord[studentRecord.size()-1].setGPA(gpa);
                fin.get();
        }
        display(studentRecord);
    }
}

float findAverage(studentList studentRecord)
{
    float average = 0;
    for(int i = 0; i < studentRecord.size(); i++)
    {
        average += studentRecord[i].getGPA();
    }
    average = average / studentRecord.size();
    return average;
}

int findLowestGPA(studentList & studentRecord)
{
    int lowest = 0; // returns lowest student GPA position in vector
    sortGPA(studentRecord); 
    // since sorted descending, will give lowest by default at the end
    lowest = studentRecord.size();
    return lowest;
}

int linearSearchName(studentList & studentRecord,string target)
{
    string upperCopy;
    for(char & c : target)
    {
        c = toupper(c);
    }
    for(int i = 0; i < studentRecord.size(); i++)
    {
        upperCopy = studentRecord[i].getName();
        for(char & c : upperCopy)
        {
            c = toupper(c);
        }
        if(target == upperCopy)
        {
            return i;
        }
    }
    return -1;
}