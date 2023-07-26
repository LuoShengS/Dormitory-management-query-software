#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 160         //最大记录数
#define MAX_STUDENTID 10        //最大学号长度
#define MAX_NAME_LENGTH 9      //最大名字长度
#define MAX_ROOM 600            //宿舍总数
#define MAX_ROOM_ROLE 6         //宿舍最大人数
#define Data_file_path "C:\\Users\\宿舍信息.csv" //这是数据文件的路径

typedef struct {
    char name[MAX_NAME_LENGTH];
    char studentId[MAX_STUDENTID];
    int roomNumber;
} Record;//Record结构体用于规定学生相关信息 

Record records[MAX_RECORDS];
int numRecords = 0;
short room[MAX_ROOM] = { 0 };

//三个比较函数，为后面查找功能做准备 
int compareNames(const void* a, const void* b) {
    return strcmp(((Record*)a)->name, ((Record*)b)->name);
}
int compareStudentIds(const void* a, const void* b) {
    return strcmp(((Record*)a)->studentId, ((Record*)b)->studentId);
}
int compareRoomNumbers(const void* a, const void* b) {
    return ((Record*)a)->roomNumber - ((Record*)b)->roomNumber;
}
//插入排序函数
void insertRecords(int (*compare)(const void*, const void*)) {
    int i, j;
    for (i = 1; i < numRecords; i++) {
        Record temp = records[i];
        j = i - 1;
        while (j >= 0 && compare(&temp, &records[j]) < 0) {
            records[j + 1] = records[j];
            j--;
        }
        records[j + 1] = temp;
    }
    printf("记录已排序。\n");
}
//输入函数
void inputRecords() {
    printf("请输入记录信息：\n");
    for (; numRecords < MAX_RECORDS; ) {
        printf("记录 %d：\n", numRecords + 1);
        printf("姓名：");
        scanf("%s", records[numRecords].name);
        printf("学号：");
        scanf("%s", records[numRecords].studentId);
        printf("房号：");
        scanf("%d", &records[numRecords].roomNumber);
        room[records[numRecords].roomNumber] = room[records[numRecords].roomNumber] + 1;
        if (room[records[numRecords].roomNumber] > MAX_ROOM_ROLE) {
            printf("该宿舍已满\n");
            room[records[numRecords].roomNumber] = room[records[numRecords].roomNumber] - 1;
        }
        else {
            numRecords++;
        }
        char ch;
        printf("是否继续输入记录？(y/n) ");
        scanf(" %c", &ch);
        if (ch == 'n' || ch == 'N') {
            insertRecords(compareStudentIds);//调用插入排序进行排序
            return;
        }
    }
}
//显示函数
void displayRecords() {
    if (numRecords == 0) {
        printf("没有记录可显示。\n");
        return;
    }
    printf("记录信息如下：\n");
    printf("姓名    \t学号    \t房号\n");
    int i;
    for (i = 0; i < numRecords; i++) {
        printf("%s  \t%s  \t%d\n", records[i].name, records[i].studentId, records[i].roomNumber);
    }
}

//冒泡排序函数
void sortRecords(int (*compare)(const void*, const void*)) {
    int i, j;
    for (i = 0; i < numRecords - 1; i++) {
        for (j = 0; j < numRecords - 1 - i; j++) {
            if (compare(&records[j], &records[j + 1]) > 0) {
                Record temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
            }
        }
    }
    printf("记录已排序。\n");
}

//二分查找 
Record* binarySearch(const void* key, int (*compare)(const void*, const void*)) {
    int low = 0, high = numRecords - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (compare(key, &records[mid]) < 0) {
            high = mid - 1;
        }
        else if (compare(key, &records[mid]) > 0) {
            low = mid + 1;
        }
        else {
            return &records[mid];
        }
    }
    return NULL;
}
//查找函数
void searchRecord() {
    if (numRecords == 0) {
        printf("没有记录可查询。\n");
        return;
    }
    int choice;
    printf("请选择查询方式：\n");
    printf("1. 按姓名查询\n");
    printf("2. 按学号查询\n");
    printf("3. 按房号查询\n");
    printf("请输入选择：");
    scanf("%d", &choice);
    Record key;
    switch (choice) {
    case 1:
        printf("请输入要查询的姓名：");
        scanf("%s", key.name);
        sortRecords(compareNames);
        Record* resultByName = binarySearch(&key, compareNames);
        if (resultByName != NULL) {
            printf("查询结果：\n");
            printf("姓名\t学号\t房号\n");
            printf("%s\t%s\t%d\n", resultByName->name, resultByName->studentId, resultByName->roomNumber);
            // 向前查找
            int index = resultByName - records;
            int i = index - 1;
            while (i >= 0 && compareNames(&records[i], resultByName) == 0) {
                printf("%s\t%s\t%d\n", records[i].name, records[i].studentId, records[i].roomNumber);
                i--;
            }
            // 向后查找
            i = index + 1;
            while (i < numRecords && compareNames(&records[i], resultByName) == 0) {
                printf("%s\t%s\t%d\n", records[i].name, records[i].studentId, records[i].roomNumber);
                i++;
            }
        }
        else {
            printf("未找到匹配的记录。\n");
        }
        break;
    case 2:
        printf("请输入要查询的学号：");
        scanf("%s", &key.studentId);
        sortRecords(compareStudentIds);
        Record* resultByStudentId = binarySearch(&key, compareStudentIds);
        if (resultByStudentId != NULL) {
            printf("查询结果：\n");
            printf("姓名\t学号\t房号\n");
            printf("%s\t%s\t%d\n", resultByStudentId->name, resultByStudentId->studentId, resultByStudentId->roomNumber);
        }
        else {
            printf("未找到匹配的记录。\n");
        }
        break;
    case 3:
        printf("请输入要查询的房号：");
        scanf("%d", &key.roomNumber);
        sortRecords(compareRoomNumbers);
        Record* resultByRoomNumber = binarySearch(&key, compareRoomNumbers);
        if (resultByRoomNumber != NULL) {
            printf("查询结果：\n");
            printf("姓名\t学号\t房号\n");
            printf("%s\t%s\t%d\n", resultByRoomNumber->name, resultByRoomNumber->studentId, resultByRoomNumber->roomNumber);
            // 向前查找
            int index = resultByRoomNumber - records;
            int i = index - 1;
            while (i >= 0 && compareRoomNumbers(&records[i], resultByRoomNumber) == 0) {
                printf("%s\t%s\t%d\n", records[i].name, records[i].studentId, records[i].roomNumber);
                i--;
            }
            // 向后查找
            i = index + 1;
            while (i < numRecords && compareRoomNumbers(&records[i], resultByRoomNumber) == 0) {
                printf("%s\t%s\t%d\n", records[i].name, records[i].studentId, records[i].roomNumber);
                i++;
            }
        }
        else {
            printf("未找到匹配的记录。\n");
        }
        break;
    default:
        printf("无效的选择。\n");
    }
}
//删除函数
void deleteRecord() {
    if (numRecords == 0)
    {
        printf("没有记录可删除。\n");
        return;
    }
    Record key;
    printf("请输入要删除的学号：");
    scanf("%s", &key.studentId);
    sortRecords(compareStudentIds);
    Record* resultByStudentId = binarySearch(&key, compareStudentIds);
    if (resultByStudentId != NULL)
    {
        int index = resultByStudentId - records;
        memmove(resultByStudentId, resultByStudentId + 1, (numRecords - index - 1) * sizeof(Record));
        numRecords--;
        printf("记录已删除。\n");
    }
    else
    {
        printf("未找到匹配的记录。\n");
    }
}
//保存函数
void writecsv()//保存到csv里
{
    FILE* fp = NULL;
    fp = fopen(Data_file_path, "w");
    fprintf(fp, "%s,%s,%s\n", "姓名", "学号", "房号");
    for (int i = 0; i < numRecords; i++)
        fprintf(fp, "%s,%s,%d\n", records[i].name, records[i].studentId, records[i].roomNumber);
    fclose(fp);
    printf("记录已保存到CSV文件。\n");
}
//读取函数
void readcsv()//从csv里读取
{
    FILE* fp = NULL;
    fp = fopen(Data_file_path, "r");
    if (fp == NULL) {
        printf("无法打开文件。\n");
        return;
    }
    char buffer[1024];//数据缓冲区
    int row = 0;//行索引
    int column = 0;//列索引
    while (fgets(buffer, 1024, fp)) {
        column = 0;
        row++;
        if (row == 1) {
            continue;
        }
        char* value = strtok(buffer, ",");
        while (value) {//0为姓名列,1为学号列,2为房号列
            if (column == 0) {
                strcpy(records[numRecords].name, value);
            }
            else if (column == 1) {
                strcpy(records[numRecords].studentId, value);
            }
            else if (column == 2) {
                records[numRecords].roomNumber = atoi(value);
                room[atoi(value)] = room[atoi(value)] + 1;
            }
            value = strtok(NULL, ",");
            column++;
        }
        numRecords++;
    }
    fclose(fp);
    printf("记录已从CSV文件读取。\n");
}
//冒泡排序菜单
void menu()
{
    int choice;
    printf("\n宿舍管理查询软件\n");
    printf("1. 按名字排序\n");
    printf("2. 按学号排序\n");
    printf("3. 按房号排序\n");
    printf("0. 退出\n");
    printf("请输入选择：");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        sortRecords(compareNames);
        return;
    case 2:
        sortRecords(compareStudentIds);
        return;
    case 3:
        sortRecords(compareRoomNumbers);
        return;
    default:
        printf("无效的选择。\n");
    } while (choice != 0);
    return;
}
//主菜单
int main() {
    int choice;
    short flag = 0;//flag作为文件是否被读取的标志
    do {
        printf("\n宿舍管理查询软件\n");
        printf("1. 输入记录\n");//输入之后进行插入排序
        printf("2. 显示记录\n");
        printf("3. 查找记录\n");
        printf("4. 删除记录\n");
        printf("5. 记录排序\n");//使用冒泡排序
        printf("6. 保存记录\n");
        printf("7. 读取记录\n");
        printf("0. 退出\n");
        printf("请输入选择：");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            inputRecords();
            break;
        case 2:
            displayRecords();
            break;
        case 3:
            searchRecord();
            break;
        case 4:
            deleteRecord();
            break;
        case 5:
            menu();
            break;
        case 6:
            writecsv();
            break;
        case 7:
            if (flag == 1)
            {
                printf("文件已被读取过\n");
            }
            else
            {
                readcsv();
                flag = 1;
            }
            break;
        case 0:
            printf("感谢使用宿舍管理查询软件，再见！\n");
            break;
        default:
            printf("无效的选择。\n");
            break;
        }
        system("pause");
        system("cls");
    } while (choice != 0);
    return 0;
}