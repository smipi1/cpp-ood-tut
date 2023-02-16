#ifndef __STUDENT_H_INCLUDED__
#define __STUDENT_H_INCLUDED__

// Incomplete pointer type to hide internal data
typedef struct student* Student;

// Methods
Student newStudent();
void setStudentNumber(Student s, int number);
void setStudentName(Student s, char* name);
int getStudentNumber(Student s);
const char* getStudentName(Student s);
void deleteStudent(Student s);

#endif
