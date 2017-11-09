
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include "getterAndSettersStudent.cpp"

using namespace std;

bool Student::isEmpty(Student *head) {
    return (head == nullptr);
}

bool Student::hasNext(Student *pStudent) {
    return (pStudent->getNext() != nullptr);
}

int *Student::dateToIntArray(char *dateChar) {

    int date, month, year;
    string str[3];  //array containing date ,month,year as string
    int count = 0;

    //seperating date month and year based on '/'
    for (int i = 0; i < strlen(dateChar); ++i) {
        str[count] += dateChar[i];
        if (dateChar[i + 1] == '/') {
            count++;
            i++;
        }
    }

    //converting string values in array str into integer ad filling them in
    // date month year
    date = atoi(str[0].c_str());
    month = atoi(str[1].c_str());
    year = atoi(str[2].c_str());

    int dates[3];
    dates[0] = date;
    dates[1] = month;
    dates[2] = year;
    return (dates); //returning array containg value of date,month and year in integer
};


bool Student::checkNameValidity(char *studentName) {
    for (int i = 0; i < strlen(studentName); ++i) {
        if (!((studentName[i] >= 'A' && studentName[i] <= 'Z') || (studentName[i] >= 'a' && studentName[i] <= 'z') ||
              (studentName[i] == ' '))) {
//            cout << "Name is Invalid.." << endl;
            cout << "Name should not include any special characters" << endl;
            return false;
        }
    }
    return true;
}

bool Student::checkDateValidity(char *date) {

    int *datesIntArr;
    datesIntArr = dateToIntArray(date);

    int dateInt, month, year;

    dateInt = datesIntArr[0];
    month = datesIntArr[1];
    year = datesIntArr[2];

    //checks if the date or month or year entered is valid
    if (dateInt > 31 || dateInt <= 0) {
        cout << "Invaid Date: " << date << " " << endl;
        return false;
    }
    if (month > 12 || month <= 0) {
        cout << "Invaid Month: " << month << " " << endl;
        return false;
    }
    if (year < 0) {
        cout << "Invaid year: " << year << " " << endl;
        return false;
    }

    return true;    //date is valid
}

Student *Student::getStudent() {
    char rollNo[12] = {0}, name[30] = {0}, fatherName[30] = {0}, dateOfBirth[12] = {0};
    int semester = 0, yearOfAddmission = 0;
    Student *next;
    cout << "##################" << endl;
    cin.ignore();
    if (!updating) {
        do {
            cout << "Enter Roll No: ";
            cin.getline(rollNo, sizeof(rollNo));
        } while (findRollNumber(rollNo));
    }
    do {
        cout << "Enter Name: ";
        cin.getline(name, sizeof(name));
    } while (!checkNameValidity(name));

    do {
        cout << "Enter Father's Name: ";
        cin.getline(fatherName, sizeof(fatherName));
    } while (!checkNameValidity(fatherName));

    do {
        cout << "Enter Date of Birth(DD/MM/YYYY): ";
        cin.getline(dateOfBirth, sizeof(dateOfBirth));
    } while (!checkDateValidity(dateOfBirth));

    do {
        cout << "Enter Semester: ";
        cin >> semester;
    } while (semester > 8 || semester < 1);


    cout << "Enter year of Admission: " << endl;
    cin >> yearOfAddmission;

    Student *pStudent = new Student(rollNo, name, fatherName, dateOfBirth, semester, yearOfAddmission);
    return pStudent;

}

void Student::writeToFile(Student *pStudent) {
    cout << "Opening File.." << endl;
    fstream file;
    file.open(STUDENT_DATAFILE, ios::app);
    file.write((char *) pStudent, sizeof(*pStudent));
    file.close();
    cout << "Closing File.." << endl;
}

//this function will get all the records from the file into the linked list from starting
void Student::readStudentRecords() {
    Student student;
    bool flag = true;
    fstream file;

    file.open(STUDENT_DATAFILE, ios::in);
    cout << "Reading Student Records From File" << endl;
    while (file.read((char *) &student, sizeof(student)) != nullptr) {
//        cout << "Counting......" << endl;
//        cout << "Readed Next Location: " << student.getNext() << endl;

        student.next = nullptr;

        Student *newStudent = new Student(student);

        if (flag) {
            head = newStudent;
            flag = false;
        } else {
            Student *pStudent = head;
            while (hasNext(pStudent)) {
                pStudent = pStudent->next;
            }
            pStudent->setNext(newStudent);
        }
    }
    Student::printStudentRecords();
}

void Student::addStudentRecord() {
    Student *newStudentRecord = getStudent();

    if (isEmpty(head)) {
        cout << "List Is Empty" << endl;
        Student::head = newStudentRecord;
        cout << "Record Added as First node" << endl;
    } else {
        Student *pStudent = head;
        cout << "List is Not Empty" << endl;
        while (hasNext(pStudent)) {
            pStudent = pStudent->next;
        }
        pStudent->setNext(newStudentRecord);
        cout << "Record added at end of the list" << endl;
    }

    Student::writeToFile(newStudentRecord);
    cout << "Student Record Successfully added to File" << endl;
}

void Student::printStudentRecords() {

    Student *pStudent = head;

    int count = 0;

    cout.setf(ios::left);//making left justified

    cout << setw(22) << "Student Name"
         << setw(13) << "Roll Number"
         << setw(20) << "Father's Name"
         << setw(15) << "Date of birth"
         << setw(13) << "Semester"
         << setw(20) << "Addmission Year" << endl;

    while (pStudent != nullptr) {
        cout << setw(22) << pStudent->name
             << setw(13) << pStudent->rollNo
             << setw(20) << pStudent->fatherName
             << setw(15) << pStudent->dateOfBirth
             << setw(13) << pStudent->semester
             << setw(20) << pStudent->yearOfAddmission
             << endl;
        ++count;
        pStudent = pStudent->next;
    }

    cout << "Total Number Of Records: " << count << endl;

}

void Student::updateStudentRecord() {

    if (isEmpty(head)) {
        cout << "List is Empty" << endl;
        return;
    }

    Student::updating = true;

    cout << "Enter Roll Number of the record you want to update: " << endl;

    bool flag = false; // will remain false if record is not found
    char rollNumber[12];
    cin >> rollNumber;

    Student *pStudent = head;

    while (pStudent != nullptr) {

        if (strcmp(pStudent->rollNo, rollNumber) == 0) {
            Student *tempNextStudent = pStudent->next;
            cout << "Founded.." << endl;
            pStudent = getStudent();
            strcpy(pStudent->rollNo, rollNumber);
            pStudent->next = tempNextStudent;

            if (strcmp(rollNumber, head->rollNo) == 0) {
                //will be true if the founded node is head
                Student::head = pStudent;
                cout << "Was Head" << endl;
            } else {
                Student *tempPtr = Student::head;
                while (strcmp((tempPtr->next)->rollNo, rollNumber) != 0) {
                    tempPtr = tempPtr->next;
                }
                tempPtr->next = pStudent;
                cout << "Was not Head" << endl;
            }


            cout << "Record updated Successfully" << endl;
            flag = true;
            break;
        }

        pStudent = pStudent->next;
        cout << "Finding.." << endl;
    }

    if (!flag) {
        cout << "Record Not Found,Roll Number: " << rollNumber << " does not exists in records" << endl;
    }

    Student::updating = false;

    Student::writeLinkedListToFile();
}

void Student::writeLinkedListToFile() {

    fstream file;
    file.open(STUDENT_DATAFILE, ios::out);

    Student *pStudent = head;
    while (pStudent != nullptr) {
        file.write((char *) pStudent, sizeof(*pStudent));
        pStudent = pStudent->next;
    }

    cout << "Sucessfully Written Linked List to file" << endl;

    file.close();
}

void Student::deleteStudentRecord() {

    if (isEmpty(Student::head)) {
        cout << "List is Empty" << endl;
        return;
    }

    cout << "Enter Roll Number of the record you want to delete: " << endl;

    bool flag = false;
    char rollNumber[12];
    cin >> rollNumber;

    Student *pStudent = head;
    while (pStudent != nullptr) {
        if (strcmp(pStudent->rollNo, rollNumber) == 0) {
            Student *tempNextStudent = pStudent->next;
            if (strcmp(head->rollNo, rollNumber) == 0) {
                head = tempNextStudent;
                cout << "Was head" << endl;
            } else {
                Student *tempPtr = head;
                while (strcmp((tempPtr->next)->rollNo, rollNumber) != 0) {
                    tempPtr = tempPtr->next;
                }
                tempPtr->next = tempNextStudent;
                cout << "Was not Head" << endl;
            }
            flag = true;
            break;
        }
        pStudent = pStudent->next;
    }
    if (!flag) {
        cout << "Record Not Found,Roll Number: " << rollNumber << " does not exists in records" << endl;
    }
    Student::writeLinkedListToFile();
}

void Student::getRollNumbers(string *rollNumbers) {
    Student student;
    ifstream file;
    int i = 0;
    file.open(STUDENT_DATAFILE, ios::in);
    while (file.read((char *) &student, sizeof(student)) != nullptr) {
        rollNumbers[i] = student.rollNo;
        ++i;
    }
    file.close();
}

bool Student::findRollNumber(string rollNumber) {
    string rollNumbers[MAX_STUDENTS];
    getRollNumbers(rollNumbers);
    for (int i = 0; i < rollNumbers->length(); ++i) {
        if (rollNumber == rollNumbers[i]) {
//            cout << "Roll Number: " << rollNumber << " already exists" << endl;
            return true;
        }
    }
    return false;
}


