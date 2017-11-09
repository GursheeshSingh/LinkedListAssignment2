#include <iomanip>
#include <cstdio>
#include <fstream>
#include "StudentReportCard.h"
#include "student.h"

bool StudentReportCard::hasNext(StudentReportCard *pStudentReportCard) {
    return (pStudentReportCard->next != nullptr);
}

bool StudentReportCard::isEmpty(StudentReportCard *head) {
    return (head == nullptr);
}

void StudentReportCard::makeStudentReportCard() {

    StudentReportCard *newStudentReportCard = new StudentReportCard(); //this will be the node with marks
    newStudentReportCard->next = nullptr;
    cin.ignore();
    cout << "Enter The Roll Number : " << endl;
    char rollNo[12];
    cin.getline(rollNo, sizeof(rollNo));

    SemesterScheme *pSemesterScheme = SemesterScheme::head; //this will loop through all the Semesters

    if (Student::findRollNumber(rollNo)) {
        //now the student report card will have roll no
        strcpy(newStudentReportCard->rollNo, rollNo);

        cout << "Roll Number Exists in Records.." << endl;

        int semesterNumber; //this will have all the semester numbers we Read from the file

        while (pSemesterScheme != nullptr) {

            semesterNumber = pSemesterScheme->semesterNumber;

            if (Subject::getNumberOfSubjects(pSemesterScheme->subjectListHead) == 0) {
                cout << "No Subjects exists in semester " << semesterNumber << endl;
                continue;
            }

            cout << "###################################" << endl;
            cout << "For Semester " << semesterNumber << endl;
            cout << "###################################" << endl;

            Subject *subject = pSemesterScheme->subjectListHead;
            int subjectCount = 0;

            while (subject != nullptr) {

                cout << "Enter Marks for Subject(" << subject->name << "(" << subject->code << "))" << endl;

                cout << "Marks: ";
                cin >> newStudentReportCard->marks[semesterNumber][subjectCount];

                subject = subject->next;
                if (subject == nullptr)
                    cout << "IS NULL" << endl;
//                cout << "Subject Count: " << subjectCount << endl;

                subjectCount++;

            }
            pSemesterScheme = pSemesterScheme->next;
//            cout << "Adding" << endl;

        }
        addReportToList(newStudentReportCard);
        printStudentReportCards();
        writeReportCardToFile(newStudentReportCard);
    } else {
        cout << "Roll Number: " << rollNo << " does not exists in records.." << endl;
    }
}


void StudentReportCard::addReportToList(StudentReportCard *newStudentReportCard) {

    StudentReportCard *pStudentReportCard = head;

    if (isEmpty(head)) {
//        cout << "HeaderChandged" << endl;
        head = newStudentReportCard;
        return;
    }

    while (hasNext(pStudentReportCard)) {
        pStudentReportCard = pStudentReportCard->next;
    }

    pStudentReportCard->next = newStudentReportCard;
    cout << "Added" << endl;
}


void StudentReportCard::writeReportCardToFile(StudentReportCard *pStudentReportCard) {
    if (SemesterScheme::isEmpty(SemesterScheme::head)) {
        cout << "No Semester Record Exists.." << endl;
        cout << "First add Semester Schemes" << endl;
        return;
    }
    FILE *file;
    file = fopen(STUDENT_REPORTCARDS, "a");
    if (file == nullptr) {
        cout << "Could not open File.." << endl;
        return;
    }
    fprintf(file, "Roll Number: %s\n", pStudentReportCard->rollNo);

    SemesterScheme *pSemesterScheme = SemesterScheme::head;

    while (pSemesterScheme != nullptr) {

        int semesterNumber = pSemesterScheme->semesterNumber;

        fprintf(file, "Semester %d", pSemesterScheme->semesterNumber);

        Subject *pSubject = pSemesterScheme->subjectListHead;

        int subjectCount = 0;

        while (pSubject != nullptr) {

            int marks = pStudentReportCard->marks[semesterNumber][subjectCount];

            cout << "Marks: " << marks << endl;
            //----------error in this-----
            fprintf(file, "%s,%s,%d,%d",
                    pSubject->name, pSubject->code, 100, marks);

            pSubject = pSubject->next;
//            cout << "Subject Number: "  << subjectCount << endl;
//            cout << "Subject Marks: " << pStudentReportCard->marks[semesterNumber][subjectCount] << endl;
//            cout << "Subject Count: " << subjectCount << endl;
            subjectCount++;
        }
        fputc('\n', file);
        pSemesterScheme = pSemesterScheme->next;
    }
    fclose(file);

}

void StudentReportCard::writeReportCardsToFile() {
    fstream file;
    file.open(STUDENT_REPORTCARDS, ios::out);
    file.close();
    StudentReportCard *pStudentReportCard = head;
    while (pStudentReportCard != nullptr) {
        writeReportCardToFile(pStudentReportCard);
        pStudentReportCard = pStudentReportCard->next;
    }

    cout << "Successfully Written Report Cards to file" << endl;
}

void StudentReportCard::readReportCardsFromFile() {
    StudentReportCard studentReportCard;
    bool flag;
    FILE *file;
    file = fopen(STUDENT_REPORTCARDS, "r");
    if (file == nullptr) {
        cout << "Could not open File.." << endl;
        return;
    }


    char *sentence = new char[50];

    while(fgets(sentence,50,file)){
        cout << sentence;
    }

}

void StudentReportCard::printStudentReportCards() {
    StudentReportCard::readReportCardsFromFile();
}
//void StudentReportCard::printStudentReportCards() {
//    StudentReportCard *pStudentReportCard = StudentReportCard::head;
//    SemesterScheme *pSemesterScheme = SemesterScheme::head;
//
//    cout.setf(ios::left);
//
//    while (pStudentReportCard != nullptr) {
//
//        cout << "Roll No: " << pStudentReportCard->rollNo << endl;
//
//        while (pSemesterScheme != nullptr) {
//            cout << "Semester " << pSemesterScheme->semesterNumber << endl;
//
////            cout << endl;
//
//            cout << setw(30) << "Subject Name(Subject Code)"
//                 << setw(15) << "Max Marks"
//                 << setw(20) << "Marks Obtained" << endl;
//
//            Subject *subject = pSemesterScheme->subjectListHead;
//
//            int semesterNum = pSemesterScheme->semesterNumber;
//            int subjectCount = 0;
//            while (subject != nullptr) {
//
//                cout << setw(15) << subject->name << setw(15) << subject->code
//                     << setw(15) << "100"
//                     << setw(20) << pStudentReportCard->marks[semesterNum][subjectCount] << endl;
//
//                subject = subject->next;
//                subjectCount++;
//            }
//
//            cout << endl;
//            cout << endl;
//
//            pSemesterScheme = pSemesterScheme->next;
//
//        }
//        pStudentReportCard = pStudentReportCard->next;
//    }
//}

