#include <iostream>
#include <limits>
#include <iomanip>
#include <conio.h>
#include <cstring>
#include <windows.h>
#include <vector>

#define sleep(a) (Sleep(a * 1000))

using namespace std;

void printCentered(const string& text) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int consoleWidth;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1; 

    int padding = (consoleWidth - text.length()) / 2; 

    cout << string(padding, ' ') << text;
}

void handleCinError(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n\nINVALID. PLEASE TRY AGAIN...\n\n" << endl;
    sleep(1);
}

class Student {
    static float assignment_weightage, quiz_weightage, exam_weightage;

    string name;
    int reg_no;
    float assignment_marks, quiz_marks, exam_marks, final_marks;
    char grade;
    string comment;

public:
    static void setWeightage() {
        do {
            system("cls");
            cout << "\nNOTE: Weightages of Assignment, Quiz and Exam should add up to 100%\n\n";
            cout << "Enter the weightages(in %) for :- " << endl;
            cout << "\n\tAssignments(1/3) : ";
            cin >> assignment_weightage;
            if(cin.fail()){
                handleCinError();
                continue;
            }
            cout << "\n\tQuizzes(2/3) : ";
            cin >> quiz_weightage;
            if(cin.fail()){
                handleCinError();
                continue;
            }
            cout << "\n\tExams(3/3) : ";
            cin >> exam_weightage;
            if(cin.fail()){
                handleCinError();
                continue;
            }
            if (assignment_weightage + quiz_weightage + exam_weightage != 100) {
                cout << "\n\nINVALID... PLEASE ENTER AGAIN\n\n";
                sleep(1);
            }
        } while (assignment_weightage + quiz_weightage + exam_weightage != 100);
    }

    void input();
    void setAssignmentMarks();
    void setQuizMarks();
    void setExamMarks();
    void setGrade();
    void menu(vector<Student>&, int&);
    void display();
    static void goToMenu();
};

float Student::assignment_weightage = 30;           //Default Weightage
float Student::quiz_weightage = 30;
float Student::exam_weightage = 40;

void Student::input() {
    cin.ignore();
    cout << "\nEnter the name : ";
    getline(cin, name);

    bool validNum = false;
    while(!validNum){
        cout << "\nEnter the Register Number : ";
        cin >> reg_no;
        if(cin.fail()){
            handleCinError();
        }
        else
            validNum = true;
    }

    setAssignmentMarks();
    setQuizMarks();
    setExamMarks(); 
    setGrade();
}

void Student::setAssignmentMarks() {
    bool validMark;
    do{
        validMark = false;
        while(!validMark){
            cout << "\nEnter the Assignment marks(100) : ";
            cin >> assignment_marks;
            if(cin.fail()){
                handleCinError();
            }
            else
                validMark = true;
        }
        try{
            if (assignment_marks > 100 || assignment_marks < 0)
                throw(1);
        } catch (int) {
            cout << "\nINVALID MARKS... PLEASE ENTER AGAIN\n";
        }
    } while (assignment_marks > 100 || assignment_marks < 0);
}

void Student::setQuizMarks(){
    bool validMark;
    do {
        validMark = false;
        while(!validMark){
            cout << "\nEnter the Quiz marks(100) : ";
            cin >> quiz_marks;
            if(cin.fail()){
                handleCinError();
            }
            else
                validMark = true;
        }
        try{
            if (quiz_marks > 100 || quiz_marks < 0)
                throw(1);
        } catch (int) {
            cout << "\nINVALID MARKS... PLEASE ENTER AGAIN\n";
        }
    } while (quiz_marks > 100 || quiz_marks < 0);
}

void Student::setExamMarks() {
    bool validMark;
    do {
        validMark = false;
        while(!validMark){
            cout << "\nEnter the Exam marks(100) : ";
            cin >> exam_marks;
            if(cin.fail()){
                handleCinError();
            }
            else
                validMark = true;
        }
        try{
            if (exam_marks > 100 || exam_marks < 0)
            throw(1);
        } catch (int) {
            cout << "\nINVALID MARKS... PLEASE ENTER AGAIN\n";
        }
    } while (exam_marks > 100 || exam_marks < 0);
}

void Student::setGrade() {
    final_marks = (assignment_weightage * assignment_marks + quiz_weightage * quiz_marks + exam_weightage * exam_marks) / 100;
    if (final_marks > 90) {
        grade = 'A';
        comment = "Excellent";
    } else if (final_marks > 80) {
        grade = 'B';
        comment = "Very Good";
    } else if (final_marks > 70) {
        grade = 'C';
        comment = "Good";
    } else if (final_marks > 60) {
        grade = 'D';
        comment = "Satisfactory";
    } else if (final_marks > 50) {
        grade = 'E';
        comment = "Needs Improvement";
    } else {
        grade = 'F';
        comment = "Poor";
    }
}

void Student::display() {
    cout << "\n\nName : " << name << endl;
    cout << "Register Number : " << reg_no << endl;
    cout << "Marks :-" << endl;
    cout << "\tAssignment(100) : " << assignment_marks << endl;
    cout << "\tQuiz(100) : " << quiz_marks << endl;
    cout << "\tExam(100) : " << exam_marks << endl;
    cout << "\tFINAL(100) : " << final_marks << endl;
    cout << "Grade : " << grade << endl;
    cout << "Comment : " << comment << endl;
}

void Student::goToMenu() {
    char key;
    do {
        cout << "\nPress 'Y' to go to Menu :  ";
        cin >> key;
    } while (key != 'Y' && key != 'y');
}

void Student::menu(vector<Student>& stu, int& stuCount) {
    int ch;
    while (1) {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n\n";
        printCentered("MENU");
        cout << "\n\n";
        printCentered("1. Add Student");
        cout << "\n\n";
        printCentered("2. Get Details of a Student");
        cout << "\n\n";
        printCentered("3. Get Details of all Students");
        cout << "\n\n";
        printCentered("4. Delete Student");
        cout << "\n\n";
        printCentered("5. Modify Weightage");
        cout << "\n\n";
        printCentered("6. Modify marks of a student");
        cout << "\n\n";
        printCentered("7. See Details");
        cout << "\n\n";
        printCentered("8. Exit");
        cout << "\n\n";

        bool validNum;
        do {
            validNum = false;
            while(!validNum){
                cout << endl;
                cout << "\nEnter your choice : ";
                cin >> ch;
                if(cin.fail()){
                    handleCinError();
                }
                else
                    validNum = true;
            }
        } while (ch < 1 || ch > 8);

        system("cls");

        switch (ch) {
        case 1: {
            Student s;
            char choice;
            do {
                system("cls");
                cout << "\nADDING STUDENT...\n\n";
                cout << "Enter the details of the student :- " << endl;
                s.input();
                stu.push_back(s);
                stuCount++;
                cout << "\nDo you want to add another Student?(Y/N) : ";
                cin >> choice;
            } while (choice == 'Y' || choice == 'y');
            break;
        }
        case 2: {
            if (!stuCount) {
                cout << "\n\n\n\n\n\n\n\n\n";
                printCentered("NO STUDENTS FOUND");
                sleep(1);
                break;
            }

            int num, found = 0;
            cout << "DISPLAYING STUDENT...\n\n";
            bool validNum = false;
            while(!validNum){
                cout << "Enter the Register number of the Student : ";
                cin >> num;
                if(cin.fail()){
                    handleCinError();
                }
                else
                    validNum = true;
            }
            for (int i = 0; i < stuCount; i++) {
                if (num == stu[i].reg_no) {
                    stu[i].display();
                    found++;
                }
            }
            if (!found)
                cout << "\nSTUDENT NOT FOUND!\n";
            goToMenu();
            break;
        }
        case 3: {
            if (!stuCount) {
                cout << "\n\n\n\n\n\n\n\n\n";
                printCentered("NO STUDENTS FOUND");
                sleep(1);
                break;
            }
            cout << "DISPLAYING ALL STUDENTS...\n";
            for (int i = 0; i < stuCount; i++)
                stu.at(i).display();
            goToMenu();
            break;
        }
        case 4: {
            if (!stuCount) {
                cout << "\n\n\n\n\n\n\n\n\n";
                printCentered("NO STUDENTS FOUND");
                sleep(1);
                break;
            }

            int rNo, f = 0;
            cout << "DELETING STUDENT...\n\n";
            bool validNum = false;
            while(!validNum){
                cout << "Enter the Register Number of the Student you want to delete : ";
                cin >> rNo;
                if(cin.fail()){
                    handleCinError();
                }
                else
                    validNum = true;
            }
            for (int i = 0; i < stuCount; i++) {
                if (stu[i].reg_no == rNo) {
                    stu.erase(stu.begin() + i);
                    cout << "\nSTUDENT DATA DELETED!\n";
                    sleep(2);
                    stuCount--;
                    f++;
                }
            }
            if (!f) {
                cout << "\nSTUDENT NOT FOUND!\n";
            }
            sleep(1);
            break;
        }
        case 5: {
            cout << "MODIFYING WEIGHTAGE...\n\n";
            cout << "\nRe-enter the weightage :-" << endl;
            setWeightage();
            for (int i = 0; i < stuCount; i++)
                stu[i].setGrade();
            cout << "\nWEIGHTAGE MODIFIED SUCCESSFULLY!";
            sleep(1);
            break;
        }
        case 6: {
            if (!stuCount) {
                cout << "\n\n\n\n\n\n\n\n\n";
                printCentered("NO STUDENTS FOUND");
                sleep(1);
                break;
            }

            int num, f = 0;
            cout << "MODIFYING MARKS OF A STUDENT...\n\n";
            bool validNum = false;
            while(!validNum){
                cout << "Enter the Register No. of the Student : ";
                cin >> num;
                if(cin.fail()){
                    handleCinError();
                }
                else
                    validNum = true;
            }
            for (int i = 0; i < stuCount; i++) {
                if (num == stu[i].reg_no) {
                    cout << "\nRe-enter the marks :-";
                    stu[i].setAssignmentMarks();
                    stu[i].setQuizMarks();
                    stu[i].setExamMarks();
                    f++;
                }
            }
            if (!f) {
                cout << "\nSTUDENT NOT FOUND!\n";
                sleep(1);
                break;
            }
            cout << "\nSTUDENT'S MARKS MODIFIED!";
            sleep(1);
            break;
        }
        case 7: {
            cout << "\nGrade: \n";
            cout << "\t91 to 100 - 'A' \n";
            cout << "\t81 to 90 - 'B' \n";
            cout << "\t71 to 80 - 'C' \n";
            cout << "\t61 to 70 - 'D' \n";
            cout << "\t51 to 60 - 'E' \n";
            cout << "\tBelow 50 - 'F' \n";
            cout << endl;

            cout << "\nWeightage :\n";
            cout << "\tAssignment : " << assignment_weightage;
            cout << "\n\tQuiz : " << quiz_weightage;
            cout << "\n\tExam : " << exam_weightage;
            cout << endl;

            int noOfFailures = 0;
            for (int i = 0; i < stuCount; i++) {
                if (stu[i].grade == 'F')
                    noOfFailures++;
            }

            cout << "\nNumber of Students : " << stuCount << endl;
            cout << "Number of Passed Students : " << stuCount - noOfFailures << endl;
            cout << "Number of Failed Students : " << noOfFailures << endl;
            goToMenu();
            break;
        }
        case 8: {
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
            printCentered("EXITING PROGRAM...\n\n\n\n\n\n\n\n\n\n\n\n");
            sleep(2);
            return;
        }
        }
    }
}

int main() {
    int stuCount = 0;
    vector<Student> stu;

    system("cls");

    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    printCentered("Welcome");
    cout << "\n\n";
    printCentered("Student Grade Calculator");
    cout << "\n\n\n\n\n\n\n";
    printCentered("Press any key to continue...");
    getch();

    Student s;
    s.menu(stu, stuCount);

    return 0;
}