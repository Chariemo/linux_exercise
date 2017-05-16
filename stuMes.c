#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define MAX_STU 50

typedef struct student {
    char name[50];
    char no[16];
    double grade_Linux;
}Stu, * pStu;

int count = 0; //学生数量

void addStu() {
    Stu stu[MAX_STU];
    int numOfadd = 0;
    FILE * fp;
    if ((fp = fopen("liststu.txt", "r+")) == NULL) {
        perror("fopen");
        exit(1);
    }
    while (true) {
        char temp[50] = {' ', ' '};
        printf("student_name:(\"!\" to back) ");
        scanf("%s", temp);
        if (strcmp(temp, "!") == 0) {
            break;
        }
        strcpy(stu[numOfadd].name, temp);
        printf("student_no: ");
        scanf("%s", stu[numOfadd].no);
        printf("grade_Linux: ");
        scanf("%lf", &(stu[numOfadd].grade_Linux));
        getchar();
        numOfadd++;
    }
    fseek(fp, 0, SEEK_SET);
    fread(&count, sizeof(int), 1, fp);
    count += numOfadd;
    fseek(fp, 0, SEEK_SET);
    fwrite(&count, sizeof(int), 1, fp);
    fseek(fp, 0, SEEK_END);
    fwrite(stu, sizeof(Stu), numOfadd, fp);
    fclose(fp);
}

void printStu(pStu stu) {
    int i;
    printf("%-20s%-20s%-20s\n", "name", "no", "grade_Linux");
    for (i = 0; i < count; i++) {
        printf("%-20s%-20s%-20.02lf\n", stu[i].name, stu[i].no, stu[i].grade_Linux);
    }
}

void menu(int *select) {
    printf("1: addStudent\n2: delStudent\n3: queryStudent\n0: Quit!\nYour choice: ");
    scanf("%d", select);
}

void swap_stu(pStu stu, int x, int y) {
    Stu temp = stu[x];
    stu[x] = stu[y];
    stu[y] = temp;
}
int partition(pStu stu, int start, int end) {
    int key = stu[end].grade_Linux;
    int index_low = start - 1;
    int index;
    for (index = start; index < end; index++) {
        if (stu[index].grade_Linux < key) {
            index_low++;
            swap_stu(stu, index_low, index);
        }
    }
    swap_stu(stu, index_low + 1, end);
    return index_low + 1;
}

void sortbygrade(pStu stu, int start, int end) {
    if (start < end) {
        int index = partition(stu, start, end);
        sortbygrade(stu, start, index - 1);
        sortbygrade(stu, index + 1, end);
    }
}


void delStu() {
    char temp[50];
    FILE *fp;
    Stu stu[MAX_STU];
    int i;
    bool found = false;
    if ((fp = fopen("liststu.txt", "r")) == NULL) {
        perror("fopen");
        exit(1);
    }
    fseek(fp, 0, SEEK_SET);
    fread(&count, sizeof(int), 1, fp);
    fread(&stu, sizeof(Stu), count, fp);
    fclose(fp);
    printStu(stu);
    while (true) {
        printf("name of student you want to del:(\'!\' to back) ");
        scanf("%s", temp);
        if (strcmp(temp, "!") == 0) {
            break;
        }
        for (i = 0; i < count; i++) {
            if (strcmp(temp, stu[i].name) == 0) {
                printf("Found and Del!!!\n");
                for (; i < count - 1; i++) {
                    stu[i] = stu[i + 1];
                }
                found = true;
                count--;
                printStu(stu);
                break;
            }
        }
        if (!found) {
            printf("Not Found!\n");
        }
    }
    if ((fp = fopen("liststu.txt", "w+")) == NULL) {
        perror("fopen");
        exit(1);
    }
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(stu, sizeof(Stu), count, fp);
    fclose(fp);
}

void queryStu() {
    char temp[50];
    int i, select;
    FILE * fp;
    bool found = false;
    Stu stu[MAX_STU];
    Stu stuFound;
    if ((fp = fopen("liststu.txt", "r")) == NULL) {
        perror("fopen");
        exit(1);
    }

    fseek(fp, 0, SEEK_SET);
    fread(&count, sizeof(int), 1, fp);
    fread(&stu, sizeof(Stu), count, fp);
    fclose(fp);
    do{
        printf("1:check one student by name\n2:check all students by grade\n0:Back\nYour choice: ");
        scanf("%d", &select);
        switch(select) {
            case 1: printf("Enter the name you want to find: ");
                    scanf("%s", temp);
                    for (i = 0; i < count; i++) {
                        if (strcmp(temp, stu[i].name) == 0) {
                            found = true;
                            stuFound = stu[i];
                            printf("Found and Print!!\n");
                            printf("%-20s%-20s%-20lf\n", stuFound.name, stuFound.no, stuFound.grade_Linux);
                            break;
                        }
                    }
                    if (!found) {
                        printf("Not Found!\n");
                    }
                break;
            case 2: sortbygrade(stu, 0, count - 1);
                    printStu(stu);
                break;
            case 0: continue;
            default: printf("Wrong number, Input again!!!\n");
        }
        getchar();
    } while(select != 0);
}
int main(void) {
    pStu stu[MAX_STU];
    int select = 1;
    do {
        menu(&select);
        switch (select) {
            case 1: addStu();
                    break;
            case 2: delStu();
                    break;
            case 3: queryStu();
                    break;
            case 0: continue;
            default: printf("Wrong Number, Input again!!!!!\n");
        }
        getchar();
    } while(select != 0);
    return 0;
}
