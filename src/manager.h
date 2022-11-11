#ifndef __MANAGER_H
#define __MANAGER_H

#include "student.h"
#include "vec.h"

typedef struct Manager {
    struct Vec students;
} Manager;

// 构造对象
extern Manager Manager_new(void);

// 录入学生信息
extern void Manager_admit(Manager *self);

// 移除学生
extern void Manager_remove(Manager *self);

// 查询学生信息
extern void Manager_search(const Manager *self);

// 打印不及格成绩超过两科的学生
extern void Manager_losers(const Manager *self);

// 打印所有学生信息
extern void Manager_display(const Manager *self);

// 单科成绩排名
extern void Manager_rank(const Manager *self);

// 退出程序
extern void Manager_quit(Manager *self);

// 销毁对象
extern void Manager_drop(Manager *self);

#endif
