#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h> 

struct student
{
    int marks;
    int sNo;
    char ch[30];
    struct student *next;
};
typedef struct student NODE;
typedef struct student *PNODE;
typedef struct student **PPNODE;

void InsertStudentData(PPNODE Head, char name[], int RollNo, int marks)
{
    PNODE newn = NULL;
    PNODE temp = *Head;
    newn = (PNODE)malloc(sizeof(NODE));

    strcpy(newn->ch, name);
    newn->sNo = RollNo;
    newn->marks = marks;
    newn->next = NULL;

    if (*Head == NULL)
    {
        *Head = newn;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newn;
    }
}

void Display(PNODE Head)
{
    int iCnt = 0;
    while (Head != NULL)
    {
        printf("\n---------------------------------------------------------------------------------------------------------------\n");
        iCnt++;
        printf("SRno:%d\t", iCnt);
        printf("student Name: %s\t", Head->ch);
        printf("Student Roll No.: %d\t", Head->sNo);
        printf("Student Marks:  %d\n", Head->marks);

        Head = Head->next;
    }
}
int Count(PNODE Head)
{
    int iCnt = 0;
    while (Head != NULL)
    {
        iCnt++;
        Head = Head->next;
    }
    return iCnt;
}
void DeleteFirst(PPNODE Head)
{
    PNODE temp = *Head;
    if (*Head == NULL)
    {
        return;
    }
    else if ((*Head)->next == NULL)
    {

        free(*Head);
        *Head = NULL;
    }
    else
    {
        *Head = (*Head)->next;
        free(temp);
    }
}
void DeleteLast(PPNODE Head)
{
    PNODE temp = *Head;
    if (*Head == NULL)
    {
        return;
    }
    else if ((*Head)->next == NULL)
    {
        free(*Head);
    }
    else
    {
        while (temp->next->next != NULL)
        {
            temp = temp->next;
        }
        free(temp->next);
        temp->next = NULL;
    }
}
void DeleteStudent(PPNODE Head, int iPos)
{
    if (iPos == 0)
    {
        return;
    }
    int iSize = 0, i = 0;
    PNODE temp = *Head;
    PNODE target = NULL;

    iSize = Count(*Head);

    if ((iPos < 1) || (iPos > iSize))
    {
        printf("please enter valid serial number number");
    }
    if (iPos == 1)
    {
        DeleteFirst(Head);
    }
    else if (iPos == iSize)
    {
        DeleteLast(Head);
    }
    else
    {
        for (i = 1; i < iPos - 1; i++)
        {
            temp = temp->next;
        }
        target = temp->next;

        temp->next = target->next;
        free(target);
    }
}
void SearchStudent(PNODE Head, int iNo)
{
    PNODE temp = Head;

    while (temp != NULL)
    {
        if (temp->sNo == iNo)
        {

            printf("student Name: %s\t", temp->ch);
            printf("Student Roll No.: %d\t", temp->sNo);
            printf("Student Marks:  %d\n", temp->marks);
        }
         temp = temp->next;
    }
}
void CreateFile(char name[])
{
    int fd = 0;
    fd = creat(name,0777);
    if(fd == -1)
    {
        printf("Unable to create file");
    }
    else{
        printf("File created sucessfully");
    }
}

void SaveData(PNODE Head,char Name[])
{
    int fd1 = 0;
    fd1 = open(Name,O_WRONLY|O_APPEND);
    if(fd1 == -1)
    {
        printf("!!ERROR!! Unable to write data..");
        exit(0);
    }
    else{
        printf("Data Write Sucessfully..");
    }
    while (Head != NULL)
    {
        write(fd1,Head->ch,50);
        Head = Head->next;
    }
}
void mainue()
{
    PNODE First = NULL;

    int iRet = 0, iChoice = 1, iMarks = 0, iRno = 0;
    char name[10];
    char str[30];

    while (iChoice != 0)
    {
        printf("\n________________________________________________\n");
        printf("Enter Your Choice\n");
        printf("1 :Enter New student information\n");
        printf("2 :Delet student information\n");
        printf("3 :Display All student information\n");
        printf("4 :Count total number of student\n");
        printf("5 :Enter Roll number to search student detail\n");
        printf("6 :Create File\n");
        printf("7 :Save Data At File\n");
        printf("0 :Exit Application\n");
        scanf("%d", &iChoice);
        printf("\n_________________________________________________\n");
        switch (iChoice)
        {
        case 1:
            printf("Enter student name:");
            scanf(" %[^'\n']s", name);
            printf("Enter student RollNo: ");
            scanf("%d", &iRno);
            printf("Enter student Marks: ");
            scanf("%d", &iMarks);
            InsertStudentData(&First, name, iRno, iMarks);
            break;

        case 2:
            printf("Enter SR No. of student to delete information\n");
            printf("Enter 0 to go menu\n");
            scanf("%d", &iRno);
            DeleteStudent(&First, iRno);

            break;

        case 3:
            printf("Student Information is:\n");
            Display(First);
            break;

        case 4:
            iRet = Count(First);
            printf("total Number of student is:%d\n", iRet);
            break;

        case 5:
            printf("Enter Roll Number:\n");
            scanf("%d", &iRno);
            SearchStudent(First, iRno);
            break;

        case 6:
            printf("Enter File Name to Creat that file\n");
            scanf(" %[^'\n']s", str);
            CreateFile(str);
            break;    

        case 7:
            printf("Enter file name to save the data in that file\n");
            scanf(" %[^'\n']s", str);
            SaveData(First,str);
            break;

        case 0:
            printf("Thank You For Using Our Application\n");
           // system("clear");
            break;

        }
    }
}

/*void UPDATE()
{
    int ID = 0
    char pass[] = "\0"
    printf("Enter new ID:%d",&ID);
    printf("Enter Password:%c",&pass[]);
    
}*/
bool LOGIN()
{

    
    int iNo = 0;
    char uName[] = "\0";


    printf("Enter UserID :\n");
    scanf("%d",&iNo);
    printf("Enter PASSWORD :\n");
    scanf("%[^'\n']s", &uName);

    if ((iNo == 11) || (uName == "aths"))
    {
        return true;
    }
    else 
    {
        return false;
    }
   
}

int main()
{
    printf("            ... STUDENT MANAGEMENT SYSTEM...\n");
        printf(" \n");
        printf(" \n");
        printf(" \n");


    bool bRet = 0;
    bRet = LOGIN();
    while (1)
    {
        if (bRet == true)
        {
            mainue();
            break;
        }
        else 
        {
            printf("ERROR:  incorrect Id / pass   \n");
            bRet = LOGIN();
           // system("clear");
        }
    }
    return 0;
}

