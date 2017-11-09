
#ifndef STUDENTEXAMINATIONRECORDS_SEMESTERSCHEME_H
#define STUDENTEXAMINATIONRECORDS_SEMESTERSCHEME_H
#define MAX_SEMESTERS 6

#define SEMESTER_DATAFILE "C:\\Users\\admin\\CLionProjects\\LinkedListAssignment\\SemestersInfo.txt"

#include <iostream>
#include "subjectMethods.cpp"

using namespace std;

struct SemesterScheme {

    int semesterNumber;
    int year;
    Subject *subjectListHead = nullptr;
    double maxMarksTheory;
    double maxMarksSessional;
    SemesterScheme *next = nullptr;
public:
    static SemesterScheme *head;
    SemesterScheme() {

    }

    SemesterScheme(int semesterNumber, int year, Subject *subjectListHead,
                   double maxMarksTheory = 100, double maxMarksSessional = 30) {
        this->semesterNumber = semesterNumber;
        this->year = year;
        this->subjectListHead = subjectListHead;
        this->maxMarksTheory = maxMarksTheory;
        this->maxMarksSessional = maxMarksSessional;
        this->next = nullptr;
    }

    void setNext(SemesterScheme *next);

    bool addSubject();

    static bool isEmpty(SemesterScheme *head);
    static bool hasNext(SemesterScheme *pSemesterScheme);

    SemesterScheme *getSemesterSceheme();
    static bool writeSchemeToFile(SemesterScheme* semesterScheme);
    static void writeLinkedListToFile();

    static bool addAScheme();
    static bool deleteAScheme();
    static void printSemesterSchemes();
    static void readSemesterSchemes();
    static void addSubjectToSemester();
    static bool findSemesterNumbers(int semesterNumber);

    int numberOfSubjects();
    int getYear() const;
};


#endif //STUDENTEXAMINATIONRECORDS_SEMESTERSCHEME_H
