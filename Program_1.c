/*C Program to perform file operations */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
struct student
{
    char name[30],branch[5],sid[15],address[200];
    int semester;
};
typedef struct student student;
void file_check(FILE *fp)
{
    if(fp==NULL)
    {
        printf("\nError in opening file\n");
        exit(1);
    }
    else
        return;
}
void insert()
{
    	student stu;
        FILE *fp;
        char another_add='y';
        fp=fopen("record.txt","ab+");
        file_check(fp);
        fflush(stdin);
        while (another_add=='y')
        {
            printf("\n--Add new Record--\n");
            printf("\nEnter the SID or USN: \n");
            gets(stu.sid);
            fflush(stdin);
            printf("\nName: ");
            gets(stu.name);
            fflush(stdin);
            printf("\nEnter Branch: ");
            gets(stu.branch);
            fflush(stdin);
            printf("\nEnter Semester: ");
            scanf("%d",&stu.semester);
            fflush(stdin);
            printf("\nEnter address: ");
            gets(stu.address);
            fwrite(&stu,sizeof(stu),1,fp);
            printf("\nTo add another record press 'y', else press 'n': ");
            fflush(stdin);
            another_add=getch();
            fflush(stdin);
        }
        fclose(fp);
        printf("\nPress any key to continue: ");
        getch();
        menu();
}
void list()
{
    FILE *fp;
    student stu;
    printf("\n--RECORD LIST--");
    printf("\nSID\t\tNAme\t\tBranch\t\tSemester\t\tAddress\n");
    fp=fopen("record.txt","rb+");;
    file_check(fp);
    while(fread(&stu,sizeof(stu),1,fp)==1)
    {
        printf("%s\t%s\t%s\t%d\t\t%s\n",stu.sid,stu.name,stu.branch,stu.semester,stu.address);
    }
    fclose(fp);
    printf("\nPress any key to continue: \n");
    getch();
    menu();
}
void list_branch()
{
    char strbr[5];
    FILE *fp;
    student stu;
    int flag=0;
    printf("\n--LIST BRANCH--");
    printf("\nEnter the branch of the student to be found");
    fflush(stdin);
    gets(strbr);
    fp=fopen("record.txt","rb+");
    file_check(fp);
    fflush(stdin);
    printf("SID\tName\t\tBranch\t\tSemester\t\tAddress\n");
    while (fread(&stu,sizeof(stu),1,fp)==1)
    {
        if(strcmp(strbr,stu.branch)==0)
        {
            printf("%s\t%s\t%s\t%d\t\t%s\n",stu.sid,stu.name,stu.branch,stu.semester,stu.address);
        }
    }
    fclose(fp);
    menu();
}
void list_address_branch()
{
    char strbr[5],stAr[25];
    FILE *fp;
    student stu;
    printf("\n--List Branch and Address--\n");
    printf("\nEnter the branch of the student to be found: ");
    fflush(stdin);
    gets(strbr);
    printf("\nEnter the address substring of the student to be found: ");
    fflush(stdin);
    gets(stAr);
    fp=fopen("record.txt","rb+");
    file_check(fp);
    fflush(stdin);
    printf("SID\t\tName\t\tBranch\tSemester\t\tAddress\n");
    while (fread(&stu,sizeof(stu),1,fp)==1)
    {
        if(strcmp(strbr,stu.branch)==0&&strstr(stu.address,stAr)!=NULL)
        {
            printf("%s\t%s\t%s\t%d\t\t%s",stu.sid,stu.name,stu.branch,stu.semester,stu.address);
        }
    }
    fclose(fp);
    menu();
}
void modify()
{
    char stID[15];
    FILE *fp;
    student stu;
    int flag=0;
    printf("\n--MODIFY RECORD--");
    printf("\nEnter the SID of the student to be modified: \n");
    fflush(stdin);
    gets(stID);
    fp=fopen("record.txt","rb+");
    file_check(fp);
    fflush(stdin);
    while (fread(&stu,sizeof(stu),1,fp)==1)
    {
        if(strcmp(stID,stu.sid)==0)
        {
            flag=1;
            printf("\nEnter the address: ");
            gets(stu.address);
            fseek(fp,sizeof(stu),SEEK_CUR);
            fwrite(&stu,sizeof(stu),1,fp);
            break;
        }
    }
    if(flag==0)
    {
        printf("\nStudent not found, Enter a valid STP");
        modify();
    }
    fclose(fp);
    menu();
}
void delete()
{
    char STD[15];
    FILE *fp,*ft;
    student stu;
    printf("\n--DELETE RECORD--");
    printf("\nEnter the sid of the student to be deleted: ");
    fflush(stdin);
    fp=fopen("record.txt","rb+");
    file_check(fp);
    ft=fopen("temp.txt","wb+");
    file_check(ft);
    while(fread(&stu,sizeof(stu),1,fp)==1)
    {
        if(strcmp(STD,stu.sid)!=0)
        {
            fwrite(&stu,sizeof(stu),1,ft);
        }
    }
    fclose(fp);
    fclose(ft);
    remove("record.txt");
    rename("temp.txt","record.txt");
    menu();
}
void menu()
{
    int choice;
    printf("\n1. Add a new student record\n2. View all student record\n3. List students based on branch\n4. List students based on address and branch \n5. Modify a student record\n6. Delete a student record\n7. Exit\nEnter your choice: ");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1: insert();
                break;
        case 2: list();
                break;
        case 3:list_branch();
                break;
        case 4: list_address_branch();
                break;
        case 5: modify();
                break;
        case 6:delete();
                break;
        case 7:exit(0);
        default: printf("\nInvalid choice, Enter a New choice");
                menu();
    }
}
void main()
{
    menu();
}