#ifndef __STUDENT_H
#define __STUDENT_H

#include <stdint.h>

// 各科成绩
typedef struct Grade {
    double chinese;
    double math;
    double english;
} Grade;

// 学生
typedef struct Student {
    uint32_t id;       // 学号
    char name[45];     // 姓名
    char gender[4];    // 性别
    uint16_t m_class;  // 班级
    uint8_t age;       // 年龄
    Grade grade;       // 成绩
} Student;

// 打印学生信息
extern void Student_display(const Student* self);

#endif
