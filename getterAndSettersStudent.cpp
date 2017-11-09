#ifndef STUDENTEXAMINATIONRECORDS_GETTERANDSETTERSSTUDENT_H
#define STUDENTEXAMINATIONRECORDS_GETTERANDSETTERSSTUDENT_H

#include <cstring>
#include "student.h"

Student *Student::getNext() {
    return next;
}

void Student::setNext(Student *next) {
    this->next = next;
}
#endif //STUDENTEXAMINATIONRECORDS_GETTERANDSETTERSSTUDENT_H
