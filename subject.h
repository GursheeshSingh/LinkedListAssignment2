#ifndef STUDENTEXAMINATIONRECORDS_SUBJECT_H
#define STUDENTEXAMINATIONRECORDS_SUBJECT_H

#include <cstring>
#include <iostream>

#define MAX_SUBJECTS 6

using namespace std;
struct Subject{
    char name[25] = {};
    char code[8] = {};
    Subject* next = nullptr;

public:
    Subject(){

    }
    Subject(char *name, char *code){
        strcpy(this->name,name);
        strcpy(this->code,code);
        this->next = nullptr;
    }


    static bool isEmpty(Subject* head);
    static bool hasNext(Subject* pSubject);

    static bool findSubjectCode(string subjectCode,Subject* head);
    static int getNumberOfSubjects(Subject* head);

    static bool addASubject(Subject** head);
    static bool deleteASubject(Subject** head);
    static void printSubjects(Subject* head);
    static Subject* getSubject(Subject* head);
};

#endif //STUDENTEXAMINATIONRECORDS_SUBJECT_H
