#include <iostream>

using namespace std;

class Course 
{
public:
    string courseName;
    double gradePoint;
    int creditHours;
};

int main() 
{
    double cumulativeTotalGradePoints = 0.0;
    int cumulativeTotalCredits = 0;
    char option;
    int semesterCount = 0;

    cout << "\n\t\t\t\t\t\t\t\t\t\t\t\033[36m************************\033[0m\n"; 
    cout << "\t\t\t\t\t\t\t\t\t\t\t\033[4m\033[36m*    CGPA CALCULATOR   *\033[0m\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\t\033[36m************************\033[0m\n\n\n";

    do 
    {
        semesterCount++;
        int numberOfCourses;
        cout << "\n\n\t\033[4m\033[35m Enter the number of courses for semester " << semesterCount << ": \033[0m";
        cin >> numberOfCourses;

        Course courses[numberOfCourses];

        // Input course details
        for (int i = 0; i < numberOfCourses; ++i) 
        {
            cout << "\n\n\n\t\033[35m Enter details for course " << i + 1 << ":\033[0m\n";
            cout << "\n\tCourse name: ";
            cin >> courses[i].courseName;
            cout << "\n\tGrade Point (0.0 - 4.0): ";
            cin >> courses[i].gradePoint;
            cout << "\n\tCredit Hours: ";
            cin >> courses[i].creditHours;
        }

        double totalGradePoints = 0.0;
        int totalCredits = 0;

        // Calculate total grade points and credits for the semester
        for (int i = 0; i < numberOfCourses; ++i) 
        {
            totalGradePoints += courses[i].gradePoint * courses[i].creditHours;   // multiplying grade point of each course with credit hour of that course = total grade point
            totalCredits += courses[i].creditHours;              // add all courses credit hours = total credits 
        }

        double GPA = totalGradePoints / totalCredits;

        // Display course grades for the semester
        cout << "\n\n\t\t\t\t\t\033[46m OVERALL SEMESTER " << semesterCount << " DETAIL:\033[0m\n";
        for (int i = 0; i < numberOfCourses; ++i) 
        {
            cout << "\n\t\033[32m Course Name:  \033[0m" << courses[i].courseName
                 << " , \033[32m  Grade Point:  \033[0m" << courses[i].gradePoint
                 << " , \033[32m  Credit Hours: \033[0m" << courses[i].creditHours << endl;
        }

        cout << "\n\n\n\t\033[31m 👉️ Total Credit Hours for semester " << semesterCount << ": \033[0m" << totalCredits << endl;
        cout << "\n\t\033[34m 👉️ Total Grade Points for semester " << semesterCount << ": \033[0m" << totalGradePoints << endl;
        
        cout << " \n\n\t\t\t\t\033[46m ----------- GRADE POINT AVERAGE (GPA) OF SEMESTER " << semesterCount << " -----------\033[0m\n\n";
        cout << "\n\t\t\t\t\t\t\033[36m  GPA for semester " << semesterCount << ": \033[0m" << GPA << endl;

        // Accumulate total grade points and credits across all semesters
        cumulativeTotalGradePoints += totalGradePoints;
        cumulativeTotalCredits += totalCredits;

        double CGPA = cumulativeTotalGradePoints / cumulativeTotalCredits;

        // Display cumulative results
        cout << "\n\n\n\033[31m 👉️ Cumulative Total Credits after semester " << semesterCount << ": \033[0m" << cumulativeTotalCredits << endl;
        cout << "\n\033[34m 👉️ Cumulative Total Grade Points after semester " << semesterCount << ": \033[0m" << cumulativeTotalGradePoints << endl;
        cout << " \n\n\t\t\t\033[46m -----------CUMULATIVE GRADE POINT AVERAGE (CGPA) AFTER SEMESTER " << semesterCount << " -----------\033[0m\n\n";
        cout << "\n\t\t\t\t\t\t\033[4m\033[36m Cumulative CGPA: \033[0m" << CGPA << endl;

        // Ask if the user wants to calculate GPA for another semester
        cout << "\n\n\t\t\t\tDo you want to calculate GPA for another semester? (y/n): ";
        cin >> option;

    } while (option == 'y' || option == 'Y');

cout<<"\n\n\n";
    return 0;
}

