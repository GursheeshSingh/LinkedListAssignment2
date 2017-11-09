#ifndef STUDENTEXAMINATIONRECORDS_STUDENTMETHODS_H_H
#define STUDENTEXAMINATIONRECORDS_STUDENTMETHODS_H_H


#include "subject.h"

bool Subject::isEmpty(Subject *head) {
    return (head == nullptr);
}

bool Subject::hasNext(Subject *pSubject) {
    return (pSubject->next != nullptr);
}

int Subject::getNumberOfSubjects(Subject *head) {
    if (isEmpty(head)) {
        return 0;
    }
    Subject *temp = head;
    int count = 1;
    while (hasNext(temp)) {
        count++;
        temp = temp->next;
    }
    return count;
}

Subject *Subject::getSubject(Subject *head) {
    cin.ignore();
    char name[25], code[8];
    cout << "Enter Subject Name: ";
    cin.getline(name, sizeof(name));
    do {
        cout << "Enter Subject Code: ";
        cin.getline(code, sizeof(code));
    } while (findSubjectCode(code, head));
    Subject *pSubject = new Subject(name, code);
    return pSubject;
}

bool Subject::addASubject(Subject **head) {

    if (getNumberOfSubjects(*head) == MAX_SUBJECTS) {
        cout << "Maximum Number of Subjects already present" << endl;
        return false;
    }

    Subject *newSubject = getSubject(*head);

    if (isEmpty(*head)) {
        cout << "Subject List is Empty." << endl;
        *head = newSubject;
        cout << "First Subject added" << endl;
    } else {
        Subject *pSubject = *head;
        cout << "Subject List is Not Empty." << endl;
        while (hasNext(pSubject)) {
            pSubject = pSubject->next;
        }
//        pSubject->setNext(newSubject);
        pSubject->next = newSubject;
    }
    return true;

}


bool Subject::deleteASubject(Subject **head) {
    if (isEmpty(*head)) {
        cout << "Subjects List is Empty.." << endl;
        return false;
    }


    cout << "Enter Subject Code of Subject you want to delete: ";
    char code[8];
    cin >> code;

    Subject *pSubject = *head;

    while (pSubject != nullptr) {

        if (strcmp(code, pSubject->code) == 0) {
            Subject *tempNextSubject = pSubject->next;

            if (strcmp(code, (*head)->code) == 0) {
                *head = tempNextSubject;
                cout << "Was Head" << endl;
            } else {
                Subject *tempPtr = *head;
                while (strcmp((tempPtr->next)->code, code) != 0) {
                    tempPtr = tempPtr->next;
                }
                tempPtr->next = tempNextSubject;
            }

            return true;

        }

        pSubject = pSubject->next;

    }

        cout << "Subject with Subject Code: " << code << "does not exists" << endl;
        return false;
}


void Subject::printSubjects(Subject *head) {
    if (isEmpty(head)) {
        cout << "Subjects List is Empty" << endl;
    }
    int count = 1;
    Subject *pSubject = head;
    while (pSubject != nullptr) {
        cout << "Subject " << count << endl;
        cout << "Subject Name: " << pSubject->name << endl;
        cout << "Subject Code: " << pSubject->code << endl;
        pSubject = pSubject->next;
        count++;
    }
}

bool Subject::findSubjectCode(string subjectCode, Subject *head) {
    if (isEmpty(head)){
        cout << "Subject List is Empty Cannot Find Subject Code" << endl;
        return false;
    }
    Subject *pSubject = head;
    while (pSubject != nullptr) {
        if (strcmp(subjectCode.c_str(), pSubject->code) == 0) {
            cout << "Subject Code already exists" << endl;
            return true;
        }
        pSubject = pSubject->next;
    }
    return false;
}

//void Subject::setNext(Subject *next) {
//    Subject::next = next;
//}


#endif //STUDENTEXAMINATIONRECORDS_STUDENTMETHODS_H_H
