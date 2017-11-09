#ifndef STUDENTEXAMINATIONRECORDS_STUDENT_H
#define STUDENTEXAMINATIONRECORDS_STUDENT_H
#define STUDENT_DATAFILE "C:\\Users\\admin\\CLionProjects\\LinkedListAssignment\\Student.txt"
#define MAX_STUDENTS 60
#include <iostream>
#include <cstring>
using namespace std;
struct Student {

private:
    char rollNo[12] = {0};
    char name[30] = {0};
    char fatherName[30] = {0};
    char dateOfBirth[12] = {0};
    int semester = 0;
    int yearOfAddmission = 0;
    Student *next;

public:
    static Student* head;
    static bool updating;
    Student() {
        next = nullptr;
    }

    Student(char *rollNo, char *name, char *fatherName, char *dateOfBirth, int semester, int yearOfAddmission) {

        strcpy(this->name,name);
        strcpy(this->fatherName,fatherName);
        strcpy(this->rollNo,rollNo);
        strcpy(this->dateOfBirth,dateOfBirth);
        this->semester=semester;
        this->yearOfAddmission=yearOfAddmission;
        next = nullptr;

    }



    Student *getNext();
    void setNext(Student *next);

    static void getRollNumbers(string*);
    static bool findRollNumber(string rollNumber);

    static int* dateToIntArray(char* dateChar);

    static bool checkNameValidity(char* studentName);
    static bool checkDateValidity(char* date);

    static bool isEmpty(Student* head);
    static bool hasNext(Student* pStudent);

    static Student* getStudent();
    static void writeToFile(Student* pStudent);

    static void readStudentRecords();
    static void addStudentRecord();
    static void printStudentRecords();
    static void updateStudentRecord();
    static void deleteStudentRecord();
    static void writeLinkedListToFile();
};

#endif //STUDENTEXAMINATIONRECORDS_STUDENT_H
