
#ifndef STUDENTEXAMINATIONRECORDS_STUDENTREPORTCARD_H
#define STUDENTEXAMINATIONRECORDS_STUDENTREPORTCARD_H

#define STUDENT_REPORTCARDS "C:\\Users\\admin\\CLionProjects\\LinkedListAssignment\\ReportCards.txt"

#include "SemesterScheme.h"

struct StudentReportCard {

    char rollNo[12] = {};
    SemesterScheme *semesterSchemes = SemesterScheme::head;
    int marks[MAX_SEMESTERS][MAX_SUBJECTS];
    StudentReportCard *next;

    static StudentReportCard *head;
public:
    StudentReportCard() {

        for (int i = 0; i < MAX_SEMESTERS; ++i) {
            for (int j = 0; j < MAX_SUBJECTS; ++j) {
                marks[i][j] = -1;
            }
        }
        next = nullptr;
    }

    static bool hasNext(StudentReportCard *pStudentReportCard);

    static bool isEmpty(StudentReportCard *head);

    static void addReportToList(StudentReportCard *pStudentReportCard);

    static void makeStudentReportCard();

    static void printStudentReportCards();

    static void writeReportCardToFile(StudentReportCard* pStudentReportCard);

    static void writeReportCardsToFile();

    static void readReportCardsFromFile();

};

#endif //STUDENTEXAMINATIONRECORDS_STUDENTREPORTCARD_H
