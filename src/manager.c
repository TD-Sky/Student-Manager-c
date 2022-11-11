#include "manager.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "utils.h"
#include "vec.h"

Manager Manager_new(void) {
    Manager manager = {
        .students = Vec_new(),
    };

    return manager;
}

void Manager_admit(Manager *self) {
    Student st = {0};

    puts("请输入你要录入的学生信息");

    printf("学号：");
    scanf("%u", &st.id);

    printf("姓名：");
    scanf("%s", st.name);

    printf("性别：");
    scanf("%s", st.gender);

    printf("班级：");
    scanf("%hu", &st.m_class);

    printf("年龄：");
    scanf("%hhu", &st.age);

    printf("语数英成绩 (空格分割)：");
    scanf("%lf%lf%lf", &st.grade.chinese, &st.grade.math, &st.grade.english);

    clean_input();

    if (Vec_push(&self->students, st)) {
        puts("\n添加成功！");

    } else {
        puts("\n添加失败。");
    }

    getchar();
}

// 判断学号是否匹配
static bool id_eq(const Student *lhs, const void *rhs) {
    uint32_t *id = (uint32_t *)rhs;

    return lhs->id == *id;
}

void Manager_remove(Manager *self) {
    uint32_t id = 0;

    printf("\n请输入你要移除学生的学号: ");
    scanf("%u", &id);
    clean_input();

    size_t position = Vec_position(&self->students, &id, id_eq);

    if (position > 0) {
        puts("已找到该同学！你确定要删除吗?(y/n)");
        char opt = getchar();
        clean_input();

        switch (tolower(opt)) {
            case 'y':
                Vec_remove(&self->students, position - 1);
                puts("删除成功!");
                break;

            case 'n':
                puts("删除操作已取消!");
                break;

            default:
                puts("输入错误!请重新输入");
                break;
        }
    } else {
        puts("未找到该学生！");
    }

    getchar();
}

void Manager_search(const Manager *self) {
    uint32_t id = 0;

    printf("\n请输入你要查询学生的学号: ");
    scanf("%u", &id);
    clean_input();

    const Student *student = Vec_find(&self->students, &id, id_eq);

    if (student != NULL) {
        Student_display(student);
    } else {
        puts("没有找到该学生!");
    }

    getchar();
}

static bool is_loser(const Student *item) {
    return item->grade.chinese + item->grade.math + item->grade.english < 180;
}

void Manager_losers(const Manager *self) {
    VecFilter iter = Vec_filter(&self->students, is_loser);

    for (const Student *item = VecFilter_next(&iter); item != NULL;
         item = VecFilter_next(&iter)) {
        Student_display(item);
    }

    getchar();
}

void Manager_display(const Manager *self) {
    Vec_for_each(&self->students, Student_display);

    getchar();
}

void Manager_rank(const Manager *self) {
    size_t len = Vec_len(&self->students);
    Student **rank = calloc(len, sizeof(Student *));  // Student指针的数组

    puts("按哪科成绩排名？");

    // TODO
    // 语文，数学，英语
    // 赋值给指针

    getchar();
}

void Manager_quit(Manager *self) {
    char opt = 0;
    printf("您确定要退出吗?确认请按'y',取消请按'n'\n");

    for (;;) {
        opt = getchar();
        clean_input();

        switch (tolower(opt)) {
            case 'y':
                Manager_drop(self);
                puts("成功退出,感谢您的使用!");
                exit(0);

            case 'n':
                puts("退出已取消!");
                getchar();
                return;

            default:
                puts("输入错误!请重新输入");
                getchar();
                break;
        }
    }
}

void Manager_drop(Manager *self) { Vec_drop(&self->students); }
