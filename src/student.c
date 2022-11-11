#include "student.h"

#include <stdio.h>

/* Display */

void Student_display(const Student *self) {
    printf(
        "学号：%u\n"
        "姓名：%s\n"
        "班级：%u\n"
        "语文成绩: %.1lf\n"
        "数学成绩：%.1lf\n"
        "英语成绩：%.1lf\n\n",
        self->id, self->name, self->m_class, self->grade.chinese,
        self->grade.math, self->grade.english);
}
