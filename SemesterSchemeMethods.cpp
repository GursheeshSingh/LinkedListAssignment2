
#define MAX_SEMESTERS 8

#include <cstring>
#include <fstream>
#include "SemesterScheme.h"

using namespace std;

bool SemesterScheme::isEmpty(SemesterScheme *head) {
    return (head == nullptr);
}

bool SemesterScheme::hasNext(SemesterScheme *pSemesterScheme) {
    return (pSemesterScheme->next != nullptr);
}

void SemesterScheme::addSubjectToSemester(){
    bool semesterFound = false ,subjectAdded;
    cout << "Enter Semester to add subject in- ";
    int semesterNum;
    cin >> semesterNum;

    SemesterScheme *pSemesterScheme = head;
    while (pSemesterScheme){
        if(pSemesterScheme->semesterNumber==semesterNum){
            semesterFound = true;
            break;
        }
        pSemesterScheme = pSemesterScheme->next;
    }
    if (semesterFound) {
        subjectAdded = pSemesterScheme->addSubject();
        if(subjectAdded){
            cout << "Subject Succcessfully added" << endl;
        }
        writeLinkedListToFile();
    } else{
        cout << "Semester " << semesterNum << " does not exists.." << endl;
    }


}

bool SemesterScheme::addSubject() {
    int n,numberOfSubjects = Subject::getNumberOfSubjects(subjectListHead);
    cout << "Enter The Number of Subjects You Want to Enter- " << endl;
    cin >> n;
    if ((n+ numberOfSubjects) > MAX_SUBJECTS){
        cout << "Cannot Add " << n << " Subjects " << endl
             << " as Max Number of added Subjects can be: " << MAX_SUBJECTS << endl
                << numberOfSubjects << " subjects are already added...";
        return false;
    }
    for (int i = 1; i <=n ; ++i) {
        Subject::addASubject(&(this->subjectListHead));
    }

}

bool SemesterScheme::addAScheme() {

    SemesterScheme *scheme = new SemesterScheme();

//    if (numberOfSemesters == MAX_SEMESTERS) {
//        cout << "Maximum number of Semesters already exists.." << endl;
//        return false;
//    }

    SemesterScheme *newSemesterScheme = scheme->getSemesterSceheme();

    if (isEmpty(head)) {
        cout << "List is Empty" << endl;
        head = newSemesterScheme;
        cout << "Record Added as First node" << endl;
    } else {
        SemesterScheme *pSemesterScheme = head;
        cout << "List is Not Empty" << endl;
        while (hasNext(pSemesterScheme)) {
            pSemesterScheme = pSemesterScheme->next;
        }
        pSemesterScheme->setNext(newSemesterScheme);
        cout << "Record added at end of the list" << endl;
    }
//    SemesterScheme::writeSchemeToFile(newSemesterScheme);
}

bool SemesterScheme::deleteAScheme() {
    if (isEmpty(head)) {
        cout << "Semesters List is Empty" << endl;
        return false;
    }

    cout << "Enter Semester Number of the Semester Scheme you want to Delete: ";
    int semesterNumber;
    cin >> semesterNumber;

    SemesterScheme *pSemesterSceheme = head;

    while (pSemesterSceheme != nullptr) {

        if (semesterNumber == pSemesterSceheme->semesterNumber) {
            SemesterScheme *tempNextSemester = pSemesterSceheme->next;

            if (semesterNumber == (head)->semesterNumber) {
                head = tempNextSemester;
                cout << "Was Head" << endl;
            } else {
                SemesterScheme *tempPtr = head;
                while ((tempPtr->next)->semesterNumber != semesterNumber) {
                    tempPtr = tempPtr->next;
                }
                tempPtr->next = tempNextSemester;
            }

            return true;

        }

        pSemesterSceheme = pSemesterSceheme->next;

    }


}



void SemesterScheme::printSemesterSchemes() {

    SemesterScheme *pSemesterSceheme = head;

    while (pSemesterSceheme != nullptr) {

        cout << "Semester " << pSemesterSceheme->semesterNumber << endl;
        cout << "Semester Belonging to year: " << pSemesterSceheme->year << endl;

        cout << "Subjects Belonging to Semester " <<
             pSemesterSceheme->semesterNumber << ": " << endl;

        Subject::printSubjects(pSemesterSceheme->subjectListHead);
        //this will print all the subjects in the linked list with header subjectListHead

        pSemesterSceheme = pSemesterSceheme->next;

    }
}


SemesterScheme *SemesterScheme::getSemesterSceheme() {  //non static function
    int semesterNumber, year, count;

    do {

        cout << "Enter Semester Number: ";
        cin >> semesterNumber;
//        bool find = findSemesterNumbers(semesterNumber);
    } while (findSemesterNumbers(semesterNumber)); // this will be true if Semester Number already exists

    cout << "Enter Year semester is applied in: " << endl;
    cin >> year;

    do {

        cout << "Enter The Number of Subjects to be included in Semester " << semesterNumber << endl;
        cin >> count;

        if (!(count >= 0 && count <= 6)) {      //will be true if count is out of range[0,6]
            cout << "Invalid number of Subjects..";
        }

    } while (count < 0 || count > 6);

    for (int i = 0; i < count; ++i) {

        Subject::addASubject(&subjectListHead);

    }

    SemesterScheme *semesterScheme = new SemesterScheme(semesterNumber, year, subjectListHead);

    return semesterScheme;

}

bool SemesterScheme::writeSchemeToFile(SemesterScheme *semesterScheme) {
    int numberOfSubjects = Subject::getNumberOfSubjects
            (semesterScheme->subjectListHead);
    Subject *subject = semesterScheme->subjectListHead;
    FILE *file;
    file = fopen(SEMESTER_DATAFILE, "a");
    fprintf(file, "%d \t %d \t %d\n",
            semesterScheme->semesterNumber,
            semesterScheme->year,
            numberOfSubjects);
    for (int i = 0; i < numberOfSubjects; ++i) {
        fprintf(file, "%s,%s\n", subject->name, subject->code);
        subject = subject->next;
    }
    fclose(file);
}

void SemesterScheme::writeLinkedListToFile() {
    fstream file;
    file.open(SEMESTER_DATAFILE,ios::out);
    file.close();
    SemesterScheme *pSemesterScheme = head;
    while (pSemesterScheme!= nullptr){
        writeSchemeToFile(pSemesterScheme);
        pSemesterScheme = pSemesterScheme->next;
    }

    cout << "Successfully Written Semester Scheme Linked List To File.." << endl;
}


void SemesterScheme::readSemesterSchemes(){
    SemesterScheme semesterScheme;
    int numberOfSubjects;
    bool flag1 = true;  // flags tell us that the headers are empty

    FILE* file;
    file = fopen(SEMESTER_DATAFILE,"r");

    cout << "Reading Semester Schemes From File" << endl;

    while (fscanf(file, "%d \t %d \t %d",
                  &semesterScheme.semesterNumber,
                  &semesterScheme.year , 
                  &numberOfSubjects)==3) {
//        cout << "In" << endl;
        Subject subject;
        int flag2 = true;
        for (int j = 0; j < numberOfSubjects; ++j) {
            
            fscanf(file, "%[^,],%[^\n]",subject.name,subject.code);
//            cout << subject.code << subject.name << endl;
            Subject* newSubject = new Subject(subject);
            
            if (flag2){ //will be true for only 1 time 
            
                semesterScheme.subjectListHead = newSubject;
                flag2 = false;
            
            } else{
            
                Subject *pSubject = semesterScheme.subjectListHead;
            
                while (Subject::hasNext(pSubject)){
                    pSubject = pSubject->next;
                }
                pSubject->next = newSubject;
            }
        }
        
        SemesterScheme* newSemesterScheme = new SemesterScheme(semesterScheme);
        
        if (flag1){
            head = newSemesterScheme;
            flag1 = false;
        } else{

            SemesterScheme *pSemesterScheme = head;
            while (SemesterScheme::hasNext(pSemesterScheme)){
                pSemesterScheme = pSemesterScheme->next;
            }
            pSemesterScheme->next = newSemesterScheme;
        }
        
    }
    fclose(file);
}


bool SemesterScheme::findSemesterNumbers(int semesterNumber) {
    cout << "In Check" << endl;
    if (isEmpty(head)) {
        cout << "Semester Scheme is Empty, no semester scheme Available.." << endl;
        return false;
    }
    SemesterScheme *pSemesterScheme = head;
    while (pSemesterScheme != nullptr) {
        if (semesterNumber == pSemesterScheme->semesterNumber) {
            cout << "Semester Scheme for Semester " << semesterNumber
                 << " already exists " << endl;
            return true;
        }
        pSemesterScheme = pSemesterScheme->next;
    }
    return false;
}


void SemesterScheme::setNext(SemesterScheme *next) {
    SemesterScheme::next = next;
}
int SemesterScheme::numberOfSubjects(){
    return Subject::getNumberOfSubjects(subjectListHead);
}
int SemesterScheme::getYear() const {
    return year;
}


