#include <iostream>
#include "StudentMethods.cpp"
#include "SemesterSchemeMethods.cpp"
#include "StudentReportCardMethods.cpp"
#include "subjectMethods.cpp"

using namespace std;

Student *Student::head = nullptr;
bool Student::updating = false;
SemesterScheme *SemesterScheme::head = nullptr;
StudentReportCard *StudentReportCard::head = nullptr;

void fileChecker();

void readFiles();

int main() {

    fileChecker();
    readFiles();

    while (true) {
        int option;

        cout << "1.Student " << endl;
        cout << "2.Semester " << endl;
        cout << "3.Student Report Card " << endl;
        cin >> option;
        switch (option) {
            case 1:
                cout << "1.Add Student Record " << endl;
                cout << "2.Delete Student Record " << endl;
                cout << "3.Update Student Record " << endl;
                cout << "4.Print Student Records " << endl;
                cin >> option;
                switch (option) {
                    case 1:
                        Student::addStudentRecord();
                        break;
                    case 2:
                        Student::deleteStudentRecord();
                        break;
                    case 3:
                        Student::updateStudentRecord();
                        break;
                    case 4:
                        Student::printStudentRecords();
                        break;
                }
            case 2:
                cout << "1.Add Semester Scheme " << endl;
                cout << "2.Delete Semester Scheme " << endl;
                cout << "3.Add Subject To Semester " << endl;
                cout << "4.Print Semester Schemes " << endl;
                cin >> option;
                switch (option) {
                    case 1:
                        SemesterScheme::addAScheme();
                        break;
                    case 2:
                        SemesterScheme::deleteAScheme();
                        break;
                    case 3:
                        SemesterScheme::addSubjectToSemester();
                        break;
                    case 4:
                        SemesterScheme::printSemesterSchemes();
                        break;
                }
            case 3:
                cout << "1.Make Student Report Card " << endl;
                cout << "2.Print Student Report Cards" << endl;
                cin >> option;
                switch (option) {
                    case 1:
                        StudentReportCard::makeStudentReportCard();
                        break;
                    case 2:
                        StudentReportCard::printStudentReportCards();
                        break;
                }
            case 4:
                exit(0);
            default:
                cout << "Invalid Option" << endl;
        }
    }

}

void readFiles() {
    Student::readStudentRecords();
    SemesterScheme::readSemesterSchemes();
}


void fileChecker() {
    {   //in this block we create a new file if none exists
        fstream file1, file2, file3;
        //opening file in input mode to tell us if file exists or not
        file1.open(STUDENT_DATAFILE, ios::in);
        if (file1 == nullptr) { //will be true if file1 does not exists
            cout << "File 1 Does Not exists" << endl;
            //closing file1 in input mode
            file1.close();
            //creating a new file1 as none exists
            file1.open(STUDENT_DATAFILE, ios::out);
            file1.close();
        }
        file2.open(SEMESTER_DATAFILE, ios::in);
        if (file2 == nullptr) { //will be true if file2 does not exists
            cout << "File 2 Does Not exists" << endl;
            //closing file2 in input mode
            file2.close();
            //creating a new file2 as none exists
            file2.open(SEMESTER_DATAFILE, ios::out);
            file2.close();
        }
        file3.open(STUDENT_REPORTCARDS, ios::in);
        if (file3 == nullptr) { //will be true if file3 does not exists
            cout << "File 3 Does Not exists" << endl;
            //closing file3 in input mode
            file3.close();
            //creating a new file3 as none exists
            file3.open(STUDENT_REPORTCARDS, ios::out);
            file3.close();
        }
    }
}