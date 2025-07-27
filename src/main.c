#include <stdio.h>

#include "manager.h"
#include "utils.h"

int main() {
    Manager manager = Manager_new();

    for (;;) {
        printf("\033c");  // 清屏

        printf(
            "\n\n\n"
            "\t\t|*************************CONTACT***********************|\n"
            "\t\t|              1. 录入学生信息                          |\n"
            "\t\t|              2. 录入单科成绩                          |\n"
            "\t\t|              3. 删除学生                              |\n"
            "\t\t|              4. 修改学生信息                          |\n"
            "\t\t|              5. 查询学生信息                          |\n"
            "\t\t|              6. 打印不及格成绩超过两科的学生          |\n"
            "\t\t|              7. 打印所有学生信息                      |\n"
            "\t\t|              8. 单科成绩排名                          |\n"
            "\t\t|              9. 退出系统                              |\n"
            "\t\t|*******************************************************|\n"
            "\n"
            "\t\t请选择功能(1-9): ");

        int opt = 0;

        scanf("%d", &opt);
        clean_input();

        switch (opt) {
            case 1:
                Manager_admit(&manager);
                break;

            case 2:
                // 录入单科成绩
                // TODO
                break;

            case 3:
                Manager_remove(&manager);
                break;

            case 4:
                // 修改学生信息
                // TODO
                break;

            case 5:
                Manager_search(&manager);
                break;

            case 6:
                Manager_losers(&manager);
                break;

            case 7:
                Manager_display(&manager);
                break;

            case 8:
                Manager_rank(&manager);
                break;

            case 9:
                Manager_quit(&manager);
                break;

            default:
                printf("输入错误,请您重新输入!\n");
                break;
        }
    }
}
