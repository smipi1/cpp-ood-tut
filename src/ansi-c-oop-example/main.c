#include <stdio.h>
#include "student.h"

int main(int argc, char const *argv[])
{
    Student s = newStudent();
    setStudentNumber(s, 12345);
    setStudentName(s, "Pietje Puk");

    printf("Our student is '%s' (%d)\n\n", getStudentName(s), getStudentNumber(s));

    return 0;
}
