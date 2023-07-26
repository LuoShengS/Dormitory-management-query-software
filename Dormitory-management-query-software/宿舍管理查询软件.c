#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 160         //����¼��
#define MAX_STUDENTID 10        //���ѧ�ų���
#define MAX_NAME_LENGTH 9      //������ֳ���
#define MAX_ROOM 600            //��������
#define MAX_ROOM_ROLE 6         //�����������
#define Data_file_path "C:\\Users\\������Ϣ.csv" //���������ļ���·��

typedef struct {
    char name[MAX_NAME_LENGTH];
    char studentId[MAX_STUDENTID];
    int roomNumber;
} Record;//Record�ṹ�����ڹ涨ѧ�������Ϣ 

Record records[MAX_RECORDS];
int numRecords = 0;
short room[MAX_ROOM] = { 0 };

//�����ȽϺ�����Ϊ������ҹ�����׼�� 
int compareNames(const void* a, const void* b) {
    return strcmp(((Record*)a)->name, ((Record*)b)->name);
}
int compareStudentIds(const void* a, const void* b) {
    return strcmp(((Record*)a)->studentId, ((Record*)b)->studentId);
}
int compareRoomNumbers(const void* a, const void* b) {
    return ((Record*)a)->roomNumber - ((Record*)b)->roomNumber;
}
//����������
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
    printf("��¼������\n");
}
//���뺯��
void inputRecords() {
    printf("�������¼��Ϣ��\n");
    for (; numRecords < MAX_RECORDS; ) {
        printf("��¼ %d��\n", numRecords + 1);
        printf("������");
        scanf("%s", records[numRecords].name);
        printf("ѧ�ţ�");
        scanf("%s", records[numRecords].studentId);
        printf("���ţ�");
        scanf("%d", &records[numRecords].roomNumber);
        room[records[numRecords].roomNumber] = room[records[numRecords].roomNumber] + 1;
        if (room[records[numRecords].roomNumber] > MAX_ROOM_ROLE) {
            printf("����������\n");
            room[records[numRecords].roomNumber] = room[records[numRecords].roomNumber] - 1;
        }
        else {
            numRecords++;
        }
        char ch;
        printf("�Ƿ���������¼��(y/n) ");
        scanf(" %c", &ch);
        if (ch == 'n' || ch == 'N') {
            insertRecords(compareStudentIds);//���ò��������������
            return;
        }
    }
}
//��ʾ����
void displayRecords() {
    if (numRecords == 0) {
        printf("û�м�¼����ʾ��\n");
        return;
    }
    printf("��¼��Ϣ���£�\n");
    printf("����    \tѧ��    \t����\n");
    int i;
    for (i = 0; i < numRecords; i++) {
        printf("%s  \t%s  \t%d\n", records[i].name, records[i].studentId, records[i].roomNumber);
    }
}

//ð��������
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
    printf("��¼������\n");
}

//���ֲ��� 
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
//���Һ���
void searchRecord() {
    if (numRecords == 0) {
        printf("û�м�¼�ɲ�ѯ��\n");
        return;
    }
    int choice;
    printf("��ѡ���ѯ��ʽ��\n");
    printf("1. ��������ѯ\n");
    printf("2. ��ѧ�Ų�ѯ\n");
    printf("3. �����Ų�ѯ\n");
    printf("������ѡ��");
    scanf("%d", &choice);
    Record key;
    switch (choice) {
    case 1:
        printf("������Ҫ��ѯ��������");
        scanf("%s", key.name);
        sortRecords(compareNames);
        Record* resultByName = binarySearch(&key, compareNames);
        if (resultByName != NULL) {
            printf("��ѯ�����\n");
            printf("����\tѧ��\t����\n");
            printf("%s\t%s\t%d\n", resultByName->name, resultByName->studentId, resultByName->roomNumber);
            // ��ǰ����
            int index = resultByName - records;
            int i = index - 1;
            while (i >= 0 && compareNames(&records[i], resultByName) == 0) {
                printf("%s\t%s\t%d\n", records[i].name, records[i].studentId, records[i].roomNumber);
                i--;
            }
            // ������
            i = index + 1;
            while (i < numRecords && compareNames(&records[i], resultByName) == 0) {
                printf("%s\t%s\t%d\n", records[i].name, records[i].studentId, records[i].roomNumber);
                i++;
            }
        }
        else {
            printf("δ�ҵ�ƥ��ļ�¼��\n");
        }
        break;
    case 2:
        printf("������Ҫ��ѯ��ѧ�ţ�");
        scanf("%s", &key.studentId);
        sortRecords(compareStudentIds);
        Record* resultByStudentId = binarySearch(&key, compareStudentIds);
        if (resultByStudentId != NULL) {
            printf("��ѯ�����\n");
            printf("����\tѧ��\t����\n");
            printf("%s\t%s\t%d\n", resultByStudentId->name, resultByStudentId->studentId, resultByStudentId->roomNumber);
        }
        else {
            printf("δ�ҵ�ƥ��ļ�¼��\n");
        }
        break;
    case 3:
        printf("������Ҫ��ѯ�ķ��ţ�");
        scanf("%d", &key.roomNumber);
        sortRecords(compareRoomNumbers);
        Record* resultByRoomNumber = binarySearch(&key, compareRoomNumbers);
        if (resultByRoomNumber != NULL) {
            printf("��ѯ�����\n");
            printf("����\tѧ��\t����\n");
            printf("%s\t%s\t%d\n", resultByRoomNumber->name, resultByRoomNumber->studentId, resultByRoomNumber->roomNumber);
            // ��ǰ����
            int index = resultByRoomNumber - records;
            int i = index - 1;
            while (i >= 0 && compareRoomNumbers(&records[i], resultByRoomNumber) == 0) {
                printf("%s\t%s\t%d\n", records[i].name, records[i].studentId, records[i].roomNumber);
                i--;
            }
            // ������
            i = index + 1;
            while (i < numRecords && compareRoomNumbers(&records[i], resultByRoomNumber) == 0) {
                printf("%s\t%s\t%d\n", records[i].name, records[i].studentId, records[i].roomNumber);
                i++;
            }
        }
        else {
            printf("δ�ҵ�ƥ��ļ�¼��\n");
        }
        break;
    default:
        printf("��Ч��ѡ��\n");
    }
}
//ɾ������
void deleteRecord() {
    if (numRecords == 0)
    {
        printf("û�м�¼��ɾ����\n");
        return;
    }
    Record key;
    printf("������Ҫɾ����ѧ�ţ�");
    scanf("%s", &key.studentId);
    sortRecords(compareStudentIds);
    Record* resultByStudentId = binarySearch(&key, compareStudentIds);
    if (resultByStudentId != NULL)
    {
        int index = resultByStudentId - records;
        memmove(resultByStudentId, resultByStudentId + 1, (numRecords - index - 1) * sizeof(Record));
        numRecords--;
        printf("��¼��ɾ����\n");
    }
    else
    {
        printf("δ�ҵ�ƥ��ļ�¼��\n");
    }
}
//���溯��
void writecsv()//���浽csv��
{
    FILE* fp = NULL;
    fp = fopen(Data_file_path, "w");
    fprintf(fp, "%s,%s,%s\n", "����", "ѧ��", "����");
    for (int i = 0; i < numRecords; i++)
        fprintf(fp, "%s,%s,%d\n", records[i].name, records[i].studentId, records[i].roomNumber);
    fclose(fp);
    printf("��¼�ѱ��浽CSV�ļ���\n");
}
//��ȡ����
void readcsv()//��csv���ȡ
{
    FILE* fp = NULL;
    fp = fopen(Data_file_path, "r");
    if (fp == NULL) {
        printf("�޷����ļ���\n");
        return;
    }
    char buffer[1024];//���ݻ�����
    int row = 0;//������
    int column = 0;//������
    while (fgets(buffer, 1024, fp)) {
        column = 0;
        row++;
        if (row == 1) {
            continue;
        }
        char* value = strtok(buffer, ",");
        while (value) {//0Ϊ������,1Ϊѧ����,2Ϊ������
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
    printf("��¼�Ѵ�CSV�ļ���ȡ��\n");
}
//ð������˵�
void menu()
{
    int choice;
    printf("\n��������ѯ���\n");
    printf("1. ����������\n");
    printf("2. ��ѧ������\n");
    printf("3. ����������\n");
    printf("0. �˳�\n");
    printf("������ѡ��");
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
        printf("��Ч��ѡ��\n");
    } while (choice != 0);
    return;
}
//���˵�
int main() {
    int choice;
    short flag = 0;//flag��Ϊ�ļ��Ƿ񱻶�ȡ�ı�־
    do {
        printf("\n��������ѯ���\n");
        printf("1. �����¼\n");//����֮����в�������
        printf("2. ��ʾ��¼\n");
        printf("3. ���Ҽ�¼\n");
        printf("4. ɾ����¼\n");
        printf("5. ��¼����\n");//ʹ��ð������
        printf("6. �����¼\n");
        printf("7. ��ȡ��¼\n");
        printf("0. �˳�\n");
        printf("������ѡ��");
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
                printf("�ļ��ѱ���ȡ��\n");
            }
            else
            {
                readcsv();
                flag = 1;
            }
            break;
        case 0:
            printf("��лʹ����������ѯ������ټ���\n");
            break;
        default:
            printf("��Ч��ѡ��\n");
            break;
        }
        system("pause");
        system("cls");
    } while (choice != 0);
    return 0;
}