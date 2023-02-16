#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// Complete the struct type
struct student {
    int _number;
    char* _name;
};

static int studentCount;

Student newStudent()
{
    Student s = (Student) malloc(sizeof(struct student));
    if(s) {
        bzero(s, sizeof(struct student));
    }
    return s;
}

void setStudentNumber(Student s, int number)
{
    if(s) {
        s->_number = number;
    }
}

void setStudentName(Student s, char* name)
{
    if(s) {
        if(s->_name) {
            free(s->_name);
        }
        asprintf(&s->_name, "%s", name);
    }
}

int getStudentNumber(Student s)
{
    if(s) {
        return s->_number;
    } else {
        return -1;
    }
}

const char* getStudentName(Student s)
{
    if(s) {
        return s->_name;
    } else {
        return NULL;
    }
}

void deleteStudent(Student s)
{
    if(s) {
        free(s);
    }
}
